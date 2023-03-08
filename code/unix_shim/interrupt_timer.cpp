/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/support/interrupt_timer.hpp"

#include <mutex>
#include <thread>

extern "C" {
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
}

static std::thread timer_thread {};
static std::atomic<bool> paused = false;
static std::mutex main_pause;

static void cb_sig([[maybe_unused]] int signal) {
    std::unique_lock lck { main_pause };
}

namespace stm::support {
InterruptTimer::InterruptTimer(std::function<void()> on_timer, std::chrono::milliseconds period) {
    /**
     * Setup interrupt handlers for suspending the main thread while running the timer interrupt
     * This is to emulate MCU interrupt behaviour
     */
    struct sigaction act;

    pthread_detach(pthread_self());
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = cb_sig;

    if (sigaction(SIGUSR1, &act, NULL) == -1)
        printf("unable to handle siguser1\n");

    pthread_t main_thread_id = pthread_self();

    /* Run the actual thread */
    timer_thread = std::thread { [=] {
        sigset_t set;
        /* Block SIGUSR2 and SIGUSR1; Ensure that the main-thread has to handle them. */

        sigemptyset(&set);
        sigaddset(&set, SIGUSR1);
        int s = pthread_sigmask(SIG_BLOCK, &set, NULL);
        if (s != 0)
            printf("unable to mask siguser1 & siguser2\n");

        while (true) {
            {
                /* pause the main thread */
                std::unique_lock lck { main_pause };
                pthread_kill(main_thread_id, SIGUSR1);

                /* execute the timer callback */
                on_timer();
            }
            /* release the main thread */
            std::this_thread::sleep_for(period);
        }
    } };
}
} // namespace stm::support

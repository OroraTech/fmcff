/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/support/cycle_count.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <asm/unistd.h>
#include <inttypes.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
}

static int perf_event_open(struct perf_event_attr* hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    int ret;

    ret = int(syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags));
    return ret;
}

static int fd = 0;
static long long total_count = 0;

CycleCount::CycleCount() {
    struct perf_event_attr pe {};
    pe.type = PERF_TYPE_HARDWARE;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = PERF_COUNT_HW_CPU_CYCLES;
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    // Don't count hypervisor events.
    pe.exclude_hv = 1;

    fd = perf_event_open(&pe, 0, -1, -1, 0);
    if (fd == -1) {
        fprintf(stderr, "Error opening leader %llx\n", pe.config);
        exit(EXIT_FAILURE);
    }

    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
    index_ = 0;
}

void CycleCount::register_tick() {
    long long count = 0;
    // stop
    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);

    // read
    read(fd, &count, sizeof(long long));

    // restart
    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

    total_count += count;

    ticks_[index_] = uint32_t(total_count);
    printf("Registered tick\r\n");
    index_ += 1;
}

void CycleCount::print_ticks() {
    for (size_t i = 0; i < index_; i++) {
        printf("Tick #%d is %lu, %luus\r\n", (int)i, (unsigned long)ticks_[i], (unsigned long)ticks_[i] / 80'000);
    }
    printf("\r\n");
}

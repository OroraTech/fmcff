/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "health_monitor.hpp"
#include "stm/support/cycle_count.hpp"

#include <array>

constexpr size_t BENCHMARK_MAX = 2000;
constexpr size_t VALUES_CHECKED_PER_BENCHMARK = 10'000;
constexpr size_t ENTRIES_PER_CHUNK = fmcff::VALUE_RANGE_CHUNK_DEFAULT_SIZE_ENTRIES;

constexpr const char SCRIPT_TEMPLATE[] = "print('I: %d, failure detected')";
constexpr size_t TOTAL_CHUNKS_REQUIRED = (BENCHMARK_MAX / ENTRIES_PER_CHUNK) + 1;
constexpr size_t CHUNK_HEADER_SIZE = sizeof(fmcff::ChunkHeader<fmcff::ValueRange, ENTRIES_PER_CHUNK>);
constexpr size_t BYTES_PER_CHUNK = CHUNK_HEADER_SIZE + ENTRIES_PER_CHUNK * (sizeof(SCRIPT_TEMPLATE) + 2);
constexpr size_t BYTES_REQUIRED = BYTES_PER_CHUNK * TOTAL_CHUNKS_REQUIRED;

static_assert(BYTES_REQUIRED < 256'000, "Chunk Table will not fit in memory");

uint32_t run_benchmark(fmcff::HealthMonitor<BYTES_REQUIRED>& monitor, int i);

int main() {
    printf("Using %d B for ChunkTable\r\n", BYTES_REQUIRED);
    fmcff::ChunkTable<fmcff::ValueRange, BYTES_REQUIRED> table {};
    fmcff::HealthMonitor monitor { table, []([[maybe_unused]] int id, std::string_view script) {
                                      setup_micropython();
                                      execute_script(script.data());
                                  } };

    std::array<int, BENCHMARK_MAX> results {};
    printf("run,checks_per_sec,memory_used\r\n");
    for (size_t i = 0; i < BENCHMARK_MAX; i++) {
        fmcff::ValueRange int_range = { (int)i, (int32_t)i, (int32_t)i + 100 };
        char script[100] {};
        size_t c = (size_t)snprintf(script, 100, "print('I: %d, failure detected')", i);
        table.insert(int_range, { script, c });
        results[i] = run_benchmark(monitor, i + 1);

        double time_s = (double)results[i] / 80'000'000.0;
        double cycles_per_s = (double)VALUES_CHECKED_PER_BENCHMARK / time_s;
        size_t chunks_required = ((i + 1) / ENTRIES_PER_CHUNK) + 1;
        size_t memory_consumed = chunks_required * BYTES_PER_CHUNK;
        printf("%d,%f,%d\r\n", i + 1, cycles_per_s, memory_consumed);
    }

    return 0;
}

uint32_t run_benchmark(fmcff::HealthMonitor<BYTES_REQUIRED>& monitor, int i) {
    CycleCount cycles {};
    cycles.register_tick();
    for (size_t k = 0; k < VALUES_CHECKED_PER_BENCHMARK; k++) {
        monitor.check_value(k % i, (k % i) + 1); // Cycle trough all values in the table
    }
    cycles.register_tick();
    auto ticks = cycles.get_ticks();
    return ticks[1] - ticks[0];
}

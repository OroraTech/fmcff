/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "health_monitor.hpp"

int main() {
    fmcff::ChunkTable<fmcff::ValueRange> table {};
    fmcff::HealthMonitor monitor { table, [] ([[maybe_unused]] int id, std::string_view script) {
        setup_micropython();
        execute_script(script.data());
    } };
    constexpr int int_type_id = 4;
    constexpr int float_type_id = 123;

    fmcff::ValueRange int_range = { int_type_id, int32_t(3), int32_t(5) };
    table.insert(int_range, { "print('Int Failure detected!')" });

    fmcff::ValueRange float_range = { float_type_id, 3.0F, 5.0F };
    table.insert(float_range, { "print('Float Failure detected!')" });

    monitor.check_value(int_type_id, 4);
    monitor.check_value(int_type_id, 6);

    monitor.check_value(float_type_id, 4.F);
    monitor.check_value(float_type_id, 60.F);

    return 0;
}

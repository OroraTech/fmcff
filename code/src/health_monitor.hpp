/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "chunk_table.hpp"
#include "mpy_helpers.hpp"
#include "value_range.hpp"

namespace fmcff {
template <size_t SIZE_BYTES>
class HealthMonitor {
public:
    HealthMonitor(fmcff::ChunkTable<fmcff::ValueRange, SIZE_BYTES>& table, std::function<void(int, std::string_view)> fault_handler) :
        table_ { table }, fault_handler_ { fault_handler } {}

    template <typename T>
    void check_value(int id, const T& value) {
        auto maybe_entry = table_.template find<std::equal_to>(fmcff::ValueRange { id });

        if (maybe_entry) {
            auto& entry = maybe_entry->get();
            //            printf("Found entry: '%s'\r\n", entry.payload.data());

            bool is_in_range = entry.header.is_in_range((const void*)&value, sizeof(value), VALUE_TYPE<T>);

            if (!is_in_range) {
                /**
                 * Now we can handle a failure
                 */
                if (fault_handler_) {
                    fault_handler_(id, { entry.payload.data(), entry.payload.size() });
                }
            }
        } else {
            printf("Could not find entry %d\r\n", id);
        }
    }

private:
    fmcff::ChunkTable<fmcff::ValueRange, SIZE_BYTES>& table_;
    std::function<void(int, std::string_view)> fault_handler_;
};
} // namespace fmcff

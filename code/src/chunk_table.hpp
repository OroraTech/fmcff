/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <limits>
#include <optional>
#include <span>

namespace fmcff {
constexpr size_t VALUE_RANGE_CHUNK_DEFAULT_SIZE_ENTRIES = 20;
constexpr size_t VALUE_RANGE_TABLE_DEFAULT_SIZE_BYTES = 32000;

template <typename EntryHeader>
struct TableEntry {
    EntryHeader header;
    std::span<const char> payload;
};

template <typename EntryHeader, size_t CHUNK_SIZE = VALUE_RANGE_CHUNK_DEFAULT_SIZE_ENTRIES>
class ChunkHeader {
public:
    static constexpr uint64_t EXPECTED_CHUNK_MARKER = 0xC5C5C5C5C5C5C5C5;
    using Entry = TableEntry<EntryHeader>;
    using MaybeEntry = std::optional<std::reference_wrapper<const Entry>>;

    void insert(const EntryHeader& header, std::span<const char> payload);
    ptrdiff_t get_offset_to_next() const;
    void set_offset_to_next(ptrdiff_t offset);
    size_t get_used_entries() const;
    size_t free_payload_space() const;
    size_t sum_payload_sizes() const;
    uint64_t get_chunk_marker() const;

    template <template <typename> typename ComparisonOp, typename T>
    MaybeEntry find(T id) const;

private:
    const uint64_t chunk_marker_ { EXPECTED_CHUNK_MARKER };
    std::atomic<size_t> used_entries_ {};
    std::atomic<ptrdiff_t> offset_to_next_ {};
    std::array<Entry, CHUNK_SIZE> entries_ {};
};

template <typename EntryHeader, size_t SIZE_BYTES = VALUE_RANGE_TABLE_DEFAULT_SIZE_BYTES, size_t CHUNK_SIZE = VALUE_RANGE_CHUNK_DEFAULT_SIZE_ENTRIES>
class ChunkTable {
public:
    using Chunk = ChunkHeader<EntryHeader, CHUNK_SIZE>;
    using MaybeChunk = std::optional<std::reference_wrapper<Chunk>>;
    using MaybeConstChunk = std::optional<std::reference_wrapper<const Chunk>>;

    using Entry = typename Chunk::Entry;
    using MaybeEntry = std::optional<std::reference_wrapper<const Entry>>;

    ChunkTable();

    void insert(const EntryHeader& header, std::span<const char> payload);

    template <template <typename T> typename ComparisonOp, typename T>
    MaybeEntry find(T id) const;

private: /* functions */
    MaybeChunk find_or_create_chunk_with_free_size(size_t min_free_size);

    MaybeChunk get_or_create_next_chunk(Chunk& chunk);

    Chunk& get_first_chunk();
    const Chunk& get_first_chunk() const;

    char* get_free_payload_ptr(Chunk& chunk);

    MaybeChunk get_next_chunk(Chunk& chunk);
    MaybeConstChunk get_next_chunk(const Chunk& chunk) const;

    void chunk_sanity_check(const Chunk& chunk) const;

    void restore_sanity([[maybe_unused]] const Chunk& faulty_chunk) const;

private: /* members */
    char workspace_ alignas(8)[SIZE_BYTES] {};
};
} // namespace fmcff

#include "chunk_table.tpp"

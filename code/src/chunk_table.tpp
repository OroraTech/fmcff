/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "chunk_table.hpp"

namespace fmcff {
template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::ChunkTable() {
    new (workspace_) Chunk {};
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
void ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::insert(const EntryHeader& header, std::span<const char> payload) {
    MaybeChunk maybe_chunk = find_or_create_chunk_with_free_size(payload.size());
    if (maybe_chunk) {
        Chunk& chunk = maybe_chunk->get();

        char* payload_space = get_free_payload_ptr(chunk);
        std::copy(payload.begin(), payload.end(), payload_space);

        chunk.insert(header, { (const char*)payload_space, payload.size() });
    }
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
template <template <typename> typename ComparisonOp, typename T>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::find(T id) const -> MaybeEntry {
    MaybeEntry entry {};
    MaybeConstChunk chunk { std::ref(get_first_chunk()) };
    while (chunk) {
        entry = chunk->get().template find<ComparisonOp, T>(id);
        if (entry) {
            break;
        }
        chunk = get_next_chunk(chunk->get());
    }
    return entry;
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::find_or_create_chunk_with_free_size(size_t min_free_size) -> MaybeChunk {
    MaybeChunk chunk { std::ref(get_first_chunk()) };
    while (chunk && (chunk->get().get_used_entries() == CHUNK_SIZE || chunk->get().free_payload_space() < min_free_size)) {
        chunk = get_or_create_next_chunk(chunk->get());
    }
    return chunk;
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::get_first_chunk() -> Chunk& {
    return reinterpret_cast<Chunk&>(workspace_);
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::get_first_chunk() const -> const Chunk& {
    return reinterpret_cast<const Chunk&>(workspace_);
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::get_next_chunk(Chunk& chunk) -> MaybeChunk {
    intptr_t chunk_position = reinterpret_cast<intptr_t>(&chunk);

    if (chunk.get_offset_to_next() != 0) {
        intptr_t next_chunk_position = chunk_position + chunk.get_offset_to_next();
        Chunk& next_chunk = *reinterpret_cast<Chunk*>(next_chunk_position);
        chunk_sanity_check(next_chunk);
        return next_chunk;
    }

    return {};
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::get_next_chunk(const Chunk& chunk) const -> MaybeConstChunk {
    intptr_t chunk_position = reinterpret_cast<intptr_t>(&chunk);

    if (chunk.get_offset_to_next() != 0) {
        intptr_t next_chunk_position = chunk_position + chunk.get_offset_to_next();
        const Chunk& next_chunk = *reinterpret_cast<const Chunk*>(next_chunk_position);
        chunk_sanity_check(next_chunk);
        return next_chunk;
    }

    return {};
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
auto ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::get_or_create_next_chunk(Chunk& chunk) -> MaybeChunk {
    MaybeChunk next_chunk = get_next_chunk(chunk);

    if (!next_chunk) {
        /* There is no next chunk yet, create one */
        intptr_t chunk_position = reinterpret_cast<intptr_t>(&chunk);
        intptr_t next_chunk_position = chunk_position + (ptrdiff_t)sizeof(Chunk) + (ptrdiff_t)chunk.sum_payload_sizes();
        if (next_chunk_position % 8 != 0) {
            /* Ensure 8-byte alignment of struct */
            next_chunk_position -= (next_chunk_position % 8);
            next_chunk_position += 8;
        }
        if (next_chunk_position + (ptrdiff_t)sizeof(Chunk) > (intptr_t)workspace_ + (ptrdiff_t)SIZE_BYTES) {
            printf("ValueRangeTable out of memory\r\n");
            return {};
        }
        next_chunk = *reinterpret_cast<Chunk*>(next_chunk_position);
        new ((void*)next_chunk_position) Chunk {};

        /* next_chunk is already valid here, so no corruption possible */
        chunk.set_offset_to_next((intptr_t)&next_chunk->get() - (intptr_t)&chunk);

        chunk_sanity_check(chunk);
    }

    chunk_sanity_check(*next_chunk);
    return std::ref(*next_chunk);
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
void ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::chunk_sanity_check(const Chunk& chunk) const {
    bool sane = true;
    intptr_t chunk_position = reinterpret_cast<intptr_t>(&chunk);

    if (chunk.get_chunk_marker() != Chunk::EXPECTED_CHUNK_MARKER) {
        printf("Incorrect Chunk marker: %llx\r\n", (long long unsigned)chunk.get_chunk_marker());
        sane = false;
    }
    if (chunk.get_used_entries() > CHUNK_SIZE) {
        printf("More used entries than capacity: %lld vs %lld\r\n", (long long)chunk.get_used_entries(), (long long)CHUNK_SIZE);
        sane = false;
    }
    if (chunk_position + chunk.get_offset_to_next() > (intptr_t)workspace_ + (ptrdiff_t)SIZE_BYTES) {
        printf("Next Chunk overflow by %lld bytes\r\n", (long long)((chunk_position + chunk.get_offset_to_next()) - ((intptr_t)workspace_ + (ptrdiff_t)SIZE_BYTES)));
        sane = false;
    }
    if (chunk.get_offset_to_next() != 0 && sizeof(Chunk) + chunk.sum_payload_sizes() > (size_t)chunk.get_offset_to_next()) {
        printf("Chunk overflowing into next. Total Chunk size: %lld, Chunk offset to next: %lld\r\n", (long long)(sizeof(Chunk) + chunk.sum_payload_sizes()), (long long)chunk.get_offset_to_next());
        sane = false;
    }
    if (!sane) {
        printf("Fault Chunk at position %llx\r\n", (long long)(chunk_position - (intptr_t)workspace_));
        restore_sanity(chunk);
    }
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
void ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::restore_sanity([[maybe_unused]] const Chunk& faulty_chunk) const {
    /**
     * Here I would propose reloading from FRAM or even resetting the whole MCU.
     * For now just log the error and exit.
     */

    __builtin_trap();
}

template<typename EntryHeader, size_t SIZE_BYTES, size_t CHUNK_SIZE>
char* ChunkTable<EntryHeader, SIZE_BYTES, CHUNK_SIZE>::get_free_payload_ptr(Chunk& chunk) {
    intptr_t chunk_position = reinterpret_cast<intptr_t>(&chunk);
    intptr_t payload_position = chunk_position + (ptrdiff_t)sizeof(Chunk);
    intptr_t free_payload_position = payload_position + (ptrdiff_t)chunk.sum_payload_sizes();
    if (free_payload_position > (intptr_t)workspace_ + (ptrdiff_t)SIZE_BYTES) {
        printf("Workspace overflow\r\n");
        restore_sanity(chunk);
    }
    return reinterpret_cast<char*>(free_payload_position);
}

template <typename EntryHeader, size_t CHUNK_SIZE>
size_t ChunkHeader<EntryHeader, CHUNK_SIZE>::free_payload_space() const {
    if (get_offset_to_next() == 0) {
        return std::numeric_limits<size_t>::max();
    }
    if (get_offset_to_next() <= (ptrdiff_t)sum_payload_sizes()) {
        return 0;
    }
    return (size_t)get_offset_to_next() - sum_payload_sizes();
}

template <typename EntryHeader, size_t CHUNK_SIZE>
size_t ChunkHeader<EntryHeader, CHUNK_SIZE>::sum_payload_sizes() const {
    size_t sum {};
    for (size_t i = 0; i < get_used_entries(); i++) {
        sum += entries_[i].payload.size();
    }
    return sum;
}

template <typename EntryHeader, size_t CHUNK_SIZE>
ptrdiff_t ChunkHeader<EntryHeader, CHUNK_SIZE>::get_offset_to_next() const {
    return offset_to_next_;
}

template <typename EntryHeader, size_t CHUNK_SIZE>
void ChunkHeader<EntryHeader, CHUNK_SIZE>::set_offset_to_next(ptrdiff_t offset) {
    offset_to_next_ = offset;
}

template <typename EntryHeader, size_t CHUNK_SIZE>
size_t ChunkHeader<EntryHeader, CHUNK_SIZE>::get_used_entries() const {
    return used_entries_;
}

template <typename EntryHeader, size_t CHUNK_SIZE>
uint64_t ChunkHeader<EntryHeader, CHUNK_SIZE>::get_chunk_marker() const {
    return chunk_marker_;
}

template <typename EntryHeader, size_t CHUNK_SIZE>
template <template <typename> typename ComparisonOp, typename T>
auto ChunkHeader<EntryHeader, CHUNK_SIZE>::find(T id) const -> MaybeEntry {
    for (size_t i = 0; i < get_used_entries(); i++) {
        if (ComparisonOp()(entries_[i].header, id)) {
            return entries_[i];
        }
    }
    return {};
}

template <typename EntryHeader, size_t CHUNK_SIZE>
void ChunkHeader<EntryHeader, CHUNK_SIZE>::insert(const EntryHeader& header, std::span<const char> payload) {
        entries_[used_entries_] = { header, payload };

        /* Only after setting the get_used_entries() are incremented the new entry is "visible". Half-copied / interrupted values are OK */
        used_entries_ += 1;
}

} // namespace fmcff

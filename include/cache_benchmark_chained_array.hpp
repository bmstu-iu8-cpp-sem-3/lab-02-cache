// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_CACHE_BENCHMARK_CHAINED_ARRAY_HPP_
#define INCLUDE_CACHE_BENCHMARK_CHAINED_ARRAY_HPP_

#include <cstddef>
#include <random>
#include <unordered_set>

// include target-specific intrinsics required for good random seeding
#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

namespace cache_benchmark {
    /**
     * @brief Fills the passed array with its own addresses forming a direct chain.
     * @tparam Length positive length of the given array
     * @param array_start address of the first element of the array
     */
    template <size_t const Length>
    static void fill_direct_order_(void const** array_start);

    /**
     * @brief Fills the passed array with its own addresses forming a reverse chain.
     * @tparam Length positive length of the given array
     * @param array_start address of the first element of the array
     */
    template <size_t const Length>
    static void fill_reverse_order_(void const** array_start);

    /**
     * @brief Fills the passed array with its own addresses forming a random chain.
     * @tparam Length positive length of the given array
     * @param array_start address of the first element of the array
     */
    template <size_t const Length>
    static void fill_random_order_(void const** array_start);

    template <const size_t Length>
    void fill_direct_order_(const void** array_start) {
        static_assert(Length > 0);

        for (size_t i = 0; i < Length - 1; ++i) array_start[i] = array_start + i + 1;
        array_start[Length - 1] = nullptr;
    }

    template <const size_t Length>
    void fill_reverse_order_(const void** array_start) {
        static_assert(Length > 0);

        for (size_t i = 0; i < Length - 1; ++i) array_start[i] = array_start + i + 1;
        array_start[Length - 1] = nullptr;
    }

    /**
     * @brief Produces a pseudo-save random seed;
     * @return pseudo-safe random seed
     */
    inline uintmax_t random_seed_() { return __rdtsc(); }

    template <const size_t Length>
    void fill_random_order_(const void** const array_start) {
        static_assert(Length > 0);

        std::default_random_engine random_engine(random_seed_());
        std::uniform_int_distribution<ptrdiff_t> randomizer;
        std::fill(array_start, array_start + Length, nullptr);

        std::unordered_set<ptrdiff_t> used_offsets{0u};
        void const** current = array_start;
        // one should contain nullptr to be the last one in the chain so starting from 1
        for (size_t i = 1; i < Length; ++i) {
            ptrdiff_t offset = randomizer(random_engine) % Length;
            {
                auto const end = used_offsets.end();
                while (used_offsets.find(offset) != end) offset = (offset + 1) % Length;
            }
            used_offsets.insert(offset);
            *current = array_start + offset;
            current = array_start + offset;
        }
    }
} // namespace cache_benchmark

#endif // INCLUDE_CACHE_BENCHMARK_CHAINED_ARRAY_HPP_

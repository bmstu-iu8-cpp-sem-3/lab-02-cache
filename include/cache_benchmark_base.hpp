// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_CACHE_BENCHMARK_BASE_HPP_
#define INCLUDE_CACHE_BENCHMARK_BASE_HPP_

#include <algorithm>
#include <cache_benchmark_alloc.hpp>
#include <cache_benchmark_chained_array.hpp>
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <random>
#include <unordered_set>

#include <cassert>

namespace cache_benchmark {

    struct Results {
        using Duration = std::chrono::duration<std::intmax_t, std::nano>;

        Duration direct_order_duration, reverse_order_duration, random_order_duration;
    };

    template <size_t const LENGTH, size_t const WARMUP_COUNT, size_t const ITERATIONS_COUNT>
    Results run_benchmark();

    namespace {

#ifdef __always_inline
        __always_inline
#else
        inline
#endif
        void iterate_chained_array_(void const* const* array_start) {
            // up to nullptr
            while ((array_start = static_cast<void const* const*>(*array_start)));
        }

        template <const size_t WARMUP_COUNT, const size_t ITERATIONS_COUNT>
        Results::Duration benchmarked_iterate_chained_array_(const void* const* const chained_array) {
            typedef std::chrono::steady_clock Clock;

            // Warmup
            for (size_t i = 0; i < WARMUP_COUNT; ++i) iterate_chained_array_(chained_array);

            // Benchmark
            auto const start = Clock::now(); // instantly start measuring
            for (size_t i = 0; i < ITERATIONS_COUNT; ++i) iterate_chained_array_(chained_array);
            auto const end = Clock::now(); // instantly stop measuring

            return std::chrono::duration_cast<Results::Duration>(end - start);
        }
    }

    template <const size_t LENGTH, const size_t WARMUP_COUNT, const size_t ITERATIONS_COUNT>
    Results run_benchmark() {
        static_assert(LENGTH > 0, "LENGTH should be positive");
        static_assert(LENGTH % sizeof(void const*) == 0, "LENGTH should be divisible by `sizeof(void const*)`");

        constexpr auto elements_count = LENGTH / sizeof(void const*);

        // pre-allocate space for durations so that the data is better aligned
        Results::Duration direct_order_duration, reverse_order_direction, random_order_direction;
        {
            auto chained_array = page_aligned_alloc_<elements_count>();
            fill_direct_order_<elements_count>(chained_array);
            direct_order_duration = benchmarked_iterate_chained_array_<WARMUP_COUNT, ITERATIONS_COUNT>(chained_array);
            page_aligned_free_(chained_array);
        }
        {
            auto chained_array = page_aligned_alloc_<elements_count>();
            fill_reverse_order_<elements_count>(chained_array);
            reverse_order_direction = benchmarked_iterate_chained_array_<WARMUP_COUNT, ITERATIONS_COUNT>(chained_array);
            page_aligned_free_(chained_array);
        }
        {
            auto chained_array = page_aligned_alloc_<elements_count>();
            fill_random_order_<elements_count>(chained_array);
            random_order_direction = benchmarked_iterate_chained_array_<WARMUP_COUNT, ITERATIONS_COUNT>(chained_array);
            page_aligned_free_(chained_array);
        }

        return {direct_order_duration, reverse_order_direction, random_order_direction};
    }
} // namespace cache_benchmark

#endif // INCLUDE_CACHE_BENCHMARK_BASE_HPP_

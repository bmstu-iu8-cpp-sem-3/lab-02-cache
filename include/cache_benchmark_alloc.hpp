// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_CACHE_BENCHMARK_ALLOC_HPP_
#define INCLUDE_CACHE_BENCHMARK_ALLOC_HPP_

#include <unistd.h>

#include <cstddef>
#include <cstdlib>

namespace cache_benchmark {

    /**
     * @brief Allocates an array of {@code void const*} fitting the given length.
     * @tparam LENGTH minimal required length of the created array
     * @return created array
     */
    template <size_t const LENGTH>
    [[nodiscard]] inline void const** page_aligned_alloc_();

    /**
     * @brief Frees the array of {@code void const*}.
     * @param array array to be freed
     */
    inline void page_aligned_free_(void const** array);

    template <const size_t LENGTH>
    void const** page_aligned_alloc_() {
        constexpr auto size_bytes = LENGTH * sizeof(void const*);

        auto const page_size = sysconf(_SC_PAGESIZE);
        return static_cast<void const**>(std::aligned_alloc(
            page_size, size_bytes % page_size == 0 ? size_bytes : ((size_bytes / page_size) + 1) * size_bytes));
    }

    void page_aligned_free_(const void** const array) { std::free(array); }
} // namespace cache_benchmark

#endif // INCLUDE_CACHE_BENCHMARK_ALLOC_HPP_

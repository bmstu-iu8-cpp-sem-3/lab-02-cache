// Copyright 2018 Petr Portnov <gh@progrm-jarvis.ru>

#include <gtest/gtest.h>

#include <cache_benchmark_base.hpp>
#include <unordered_set>

namespace cache_benchmark {

    template <size_t const Length>
    static void assert_array_is_chained_(void const* const* chained_array) {
        static_assert(Length > 0);

        auto const upper_bound = chained_array + Length;

        std::unordered_set<void const*> unique_values;
        {
            auto current = chained_array;
            size_t attempts = 0u;
            while (true) {
                if (attempts++ == Length) {
                    ASSERT_EQ(current, (nullptr)) << "End of expectedly chained array was not reached";
                    break;
                } else {
                    ASSERT_NE(current, nullptr) << "End of expectedly chained array was reached too early";
                    ASSERT_GE(current, chained_array) << "Expectedly chained array references outer address";
                    ASSERT_LT(current, upper_bound) << "Expectedly chained array references outer address";
                }

                // jump to next
                unique_values.insert(*current);
                current = static_cast<void const* const*>(*current);
            }
        }

        ASSERT_EQ(unique_values.size(), Length) << "Expectedly chained is not of unique elements";
    }

    TEST(RandomBanchmarkBase, DirectOrder) {
        constexpr size_t size = 10;
        void const** chained_array = new void const*[size];
        fill_direct_order_<size>(chained_array);

        assert_array_is_chained_<size>(chained_array);

        delete[] chained_array;
    }

    TEST(RandomBanchmarkBase, ReverseOrder) {
        constexpr size_t size = 10;
        void const** chained_array = new void const*[size];
        fill_reverse_order_<size>(chained_array);

        assert_array_is_chained_<size>(chained_array);

        delete[] chained_array;
    }

    TEST(RandomBanchmarkBase, RandomOrder) {
        constexpr size_t size = 10;
        void const** chained_array = new void const*[size];
        fill_random_order_<size>(chained_array);

        assert_array_is_chained_<size>(chained_array);

        delete[] chained_array;
    }
} // namespace cache_benchmark

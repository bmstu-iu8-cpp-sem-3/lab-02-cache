// Copyright [2020] <Alyona Dorodnyaya>

#include <vector>

#include "direction.hpp"

// Cache:
// - L1 = 128 Kb
// - L2 = 512 Kb
// - L3 = 3 Mb

// Experiments: 1/2 * 2^6 < ... < 3/2 * (3*2^10) Kb
// ~ 2^6 < ... < 2^13 Kb
// ~ 2^6, 2^7, 2^8, 2^9, 2^10, 2^11, 2^12, 2^13 Kb

int main() {
  std::vector<size_t> c{64u, 128u, 256u, 512u, 1024u, 2048u, 4096u, 8192u};
  std::cout << "2^6 < 2^7 < 2^8 < 2^9 < 2^10 < 2^11 < 2^12 < 2^13 Kb"
            << std::endl;
  for (unsigned long i : c) {
    // создаём массивы для прямого, обратного и рандомного обхода
    auto const tested_direct = direct((i << 10u) / sizeof(void*));
    auto const tested_reverse = reverse((i << 10u) / sizeof(void*));
    auto const tested_random = random((i << 10u) / sizeof(void*));

    void const* const* current_direct;
    void const* const* current_reverse;
    void const* const* current_random;

    // direct
    // прогрев
    for (size_t j = 0u; j < 100u; ++j) {
      current_direct = tested_direct;
      while (current_direct)
        current_direct = static_cast<void const* const*>(*current_direct);
    }

    // start
    auto const start_time = std::chrono::steady_clock::now();
    for (size_t j = 0u; j < 1000u; ++j) {
      current_direct = tested_direct;
      while (current_direct)
        current_direct = static_cast<void const* const*>(*current_direct);
    }
    // finish
    auto const end_time = std::chrono::steady_clock::now();
    auto const duration_direct =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            (end_time - start_time) / 1000u)
            .count();

    // reverse
    // прогрев
    for (size_t j = 0u; j < 100u; ++j) {
      current_reverse = tested_reverse;
      while (current_reverse)
        current_reverse = static_cast<void const* const*>(*current_reverse);
    }

    // start
    auto const start_time_1 = std::chrono::steady_clock::now();
    for (size_t j = 0u; j < 1000u; ++j) {
      current_reverse = tested_reverse;
      while (current_reverse)
        current_reverse = static_cast<void const* const*>(*current_reverse);
    }
    // finish
    auto const end_time_1 = std::chrono::steady_clock::now();
    auto const duration_reverse =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            (end_time_1 - start_time_1) / 1000u)
            .count();

    // random
    // прогрев
    for (size_t j = 0u; j < 100u; ++j) {
      current_random = tested_random;
      while (current_random)
        current_random = static_cast<void const* const*>(*current_random);
    }

    // start
    auto const start_time_2 = std::chrono::steady_clock::now();
    for (size_t j = 0u; j < 1000u; ++j) {
      current_random = tested_random;
      while (current_random)
        current_random = static_cast<void const* const*>(*current_random);
    }
    // finish
    auto const end_time_2 = std::chrono::steady_clock::now();
    auto const duration_random =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            (end_time_2 - start_time_2) / 1000u)
            .count();

    std::cout << "For " << i << "Kb size duration is:" << std::endl;
    std::cout << "Direct  array = " << duration_direct << std::endl;
    std::cout << "Reverse  array = " << duration_reverse << std::endl;
    std::cout << "Random   array = " << duration_random << std::endl;
    std::cout << std::endl;
  }

  return 0;
}

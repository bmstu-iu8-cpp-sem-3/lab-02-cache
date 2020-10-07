#include <cache_benchmark_base.hpp>
#include <iostream>
#include <map>

void append_investigation_header(std::ostream& output, std::string const& travel_variant);

void append_investigation_experiment(std::ostream& output, size_t buffer_size,
                                     cache_benchmark::Results::Duration const& duration, size_t number);

constexpr unsigned long long operator"" _m(unsigned long const long value) { return value << 20u; }

int main() {
    constexpr size_t WARMUP_COUNT = 100u, ITERATIONS_COUNT = 1000u;

    std::map<size_t, cache_benchmark::Results> results{
        std::make_pair(1, cache_benchmark::run_benchmark<1_m, WARMUP_COUNT, ITERATIONS_COUNT>()),
        std::make_pair(2, cache_benchmark::run_benchmark<2_m, WARMUP_COUNT, ITERATIONS_COUNT>()),
        std::make_pair(4, cache_benchmark::run_benchmark<4_m, WARMUP_COUNT, ITERATIONS_COUNT>()),
        std::make_pair(8, cache_benchmark::run_benchmark<8_m, WARMUP_COUNT, ITERATIONS_COUNT>()),
        std::make_pair(12, cache_benchmark::run_benchmark<12_m, WARMUP_COUNT, ITERATIONS_COUNT>()),
    };

    //@formatter:off
    append_investigation_header(std::cout, "direct");
    {
        size_t i = 0;
        for (auto const& result_pair : results) append_investigation_experiment(
                std::cout, result_pair.first, result_pair.second.direct_order_duration, ++i);
    }
    std::cout << std::endl;

    append_investigation_header(std::cout, "reverse");
    {
        size_t i = 0;
        for (auto const& result_pair : results) append_investigation_experiment(
                std::cout, result_pair.first, result_pair.second.reverse_order_duration, ++i);
    }
    std::cout << std::endl;

    append_investigation_header(std::cout, "random");
    {
        size_t i = 0;
        for (auto const& result_pair : results) append_investigation_experiment(
                std::cout, result_pair.first, result_pair.second.random_order_duration, ++i);
    }
    std::cout << std::endl;
    //@formatter:on
}

void append_investigation_header(std::ostream& output, std::string const& travel_variant) {
    output << "investigation:\n"
              "  travel_variant: \""
           << travel_variant
           << "\"\n"
              "  experiments:\n";
}

void append_investigation_experiment(std::ostream& output, size_t const buffer_size,
                                     cache_benchmark::Results::Duration const& duration, size_t const number) {
    output << "  - experiment:\n"
              "      number: "
           << number
           << "\n"
              "      input_data:"
              "        buffer_size: \"\n"
           << buffer_size
           << "mb\"\n"
              "      results: \n"
              "        duration: \""
           << std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()) << "ns\"\n";
}

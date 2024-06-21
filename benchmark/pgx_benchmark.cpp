#include <benchmark/benchmark.h>
#include <regex>
#include "lib/cregex.h"
#include <string>

static void BM_std_regex(benchmark::State& state) {
    std::string pattern = state.range(0) == 0 ? "(a|b)*" : "a|(bc)*";
    std::string text = state.range(1) == 0 ? "ab" : "bcbc";
    for (auto _ : state) {
        bool result = std::regex_match(text, std::regex(pattern));
        benchmark::DoNotOptimize(result);
    }
}

static void BM_CRegex(benchmark::State& state) {
    std::string pattern = state.range(0) == 0 ? "(a|b)*" : "a|(bc)*";
    std::string text = state.range(1) == 0 ? "ab" : "bcbc";
    for (auto _ : state) {
        bool result = pgx::RegexMatch(pgx::CRegex(pattern), text);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_std_regex)->Args({0, 0})->Args({0, 1})->Args({1, 0})->Args({1, 1});
BENCHMARK(BM_CRegex)->Args({0, 0})->Args({0, 1})->Args({1, 0})->Args({1, 1});

BENCHMARK_MAIN();

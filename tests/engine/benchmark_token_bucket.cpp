/*
Copyright (C) 2020 The Falco Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <memory>

#include "token_bucket.h"
#include "utils.h"
#include <catch.hpp>

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)

// See: https://github.com/catchorg/Catch2/blob/v2.12.1/docs/test-cases-and-sections.md#special-tags
TEST_CASE("tocken bucket benchmarks", "[!benchmark][tocken_bucket]")
{
	auto tb_chrono_steady_clock = std::make_shared<token_bucket>();
	auto tb_gettimeofday = std::make_shared<token_bucket>(sinsp_utils::get_current_time_ns);

    BENCHMARK("Using C++ chrono") {
        return tb_chrono_steady_clock->claim();
    };

    BENCHMARK("Using C library function gettimeofday") {
        return tb_gettimeofday->claim();
    };
}

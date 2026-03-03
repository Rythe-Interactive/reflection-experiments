#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "impl/reflection_parsers/ast_source_parser.h"
#include "impl/reflection_context/reflection_context.h"
#include "impl/reflection_context/reflection_registration_registry.h"

TEST_CASE("Measure going over all reflected objects")
{
    reflection_registration_registry::instance().run_all();

    BENCHMARK("Generate single reflection files")
    {
        reflection_context::instance().
            simulate_printing_classes();
    };
}

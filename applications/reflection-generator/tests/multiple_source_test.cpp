#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "impl/reflection_parsers/ast_source_parser.h"
#include "rsl/impl/util/primitives.hpp"
TEST_CASE("Measure generation time")
{
    std::unordered_set<std::string> folders;
    folders.insert(
        "D:/MyProjects/reflection-experiments/applications/reflection-generator/tests/source_folders/multiple_source_files");
    std::string generate_folder =
        "D:/MyProjects/reflection-experiments/applications/reflection-experiments/tests/generated_folders/multiple_generated_files";


    BENCHMARK("Generate multiple reflection files")
    {
        auto parser = reflection_parsers::ast_source_parser();
        parser.generate_reflection_files(folders, generate_folder);
    };
}

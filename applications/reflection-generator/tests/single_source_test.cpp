#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "impl/reflection_parsers/ast_source_parser.h"
#include "rsl/impl/util/primitives.hpp"
TEST_CASE("Measure single generation time")
{
    std::unordered_set<std::string> folders;
    folders.insert(
        "D:/MyProjects/reflection-experiments/applications/reflection-generator/tests/source_folders/single_source_file");
    std::string generate_folder =
        "D:/MyProjects/reflection-experiments/applications/reflection-experiments/tests/generated_folders/single_generated_file";


    BENCHMARK("Generate single reflection files")
    {
        auto parser = reflection_parsers::ast_source_parser();
        parser.generate_reflection_files(folders, generate_folder);
    };
}

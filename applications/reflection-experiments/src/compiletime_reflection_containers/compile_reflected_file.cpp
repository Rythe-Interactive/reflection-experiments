#include "compile_reflected_file.h"

compile_reflected_file::compile_reflected_file(const rsl::dynamic_string source_location)
    : source_location(source_location) {}

compile_reflected_file::compile_reflected_file(const compile_reflected_file& other) {}

compile_reflected_file::compile_reflected_file(compile_reflected_file&& other) noexcept {}

compile_reflected_file::~compile_reflected_file() {}

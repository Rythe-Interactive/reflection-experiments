#pragma once
#include <rsl/containers>

#include "clang-c/Index.h"

struct compile_reflected_variable
{
public:
    rsl::dynamic_string name;
    rsl::dynamic_string type;

    compile_reflected_variable(CXCursor cursor);
    ~compile_reflected_variable();
    compile_reflected_variable(const compile_reflected_variable& other) = default;
    compile_reflected_variable(compile_reflected_variable&& other) noexcept = default;
};

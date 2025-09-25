#pragma once
#include "clang-c/Index.h"

#include <rsl/string>

class compile_reflection_function
{
public:
    rsl::dynamic_string name;
    rsl::dynamic_string type;

    compile_reflection_function(CXCursor cursor);
    compile_reflection_function(const compile_reflection_function& other) = default;
    compile_reflection_function(compile_reflection_function&& other) noexcept = default;
    ~compile_reflection_function();
};

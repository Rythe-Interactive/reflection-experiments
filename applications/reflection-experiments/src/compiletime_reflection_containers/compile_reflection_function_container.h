#pragma once
#include <deque>

#include "compile_reflection_function.h"
#include "clang-c/Index.h"

class compile_reflected_function_container
{
public:
    compile_reflection_function& add_function_from_cursor(CXCursor cursor);

    compile_reflected_function_container();
    ~compile_reflected_function_container();
    compile_reflected_function_container(const compile_reflected_function_container& other) = default;
    compile_reflected_function_container(compile_reflected_function_container&& other) noexcept = default;
protected:
    std::deque<compile_reflection_function> functions;
};

#pragma once
#include <deque>

#include "../compiletime_reflection_containers/compile_reflected_variable.h"

class compile_reflected_variable_container
{
public:
    compile_reflected_variable_container();
    ~compile_reflected_variable_container();
    compile_reflected_variable_container(const compile_reflected_variable_container& other) = default;
    compile_reflected_variable_container(compile_reflected_variable_container&& other) noexcept = default;

    compile_reflected_variable& add_variable_from_cursor(CXCursor cursor);
protected:
    std::deque<compile_reflected_variable> variables;
};

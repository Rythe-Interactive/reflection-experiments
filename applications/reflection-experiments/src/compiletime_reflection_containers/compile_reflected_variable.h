#pragma once
#include <rsl/containers>
#include <iostream>
#include "compile_reflected_element.h"
#include "clang-c/Index.h"

struct compile_reflected_variable : public compile_reflected_element
{
public:
    rsl::dynamic_string type;

    compile_reflected_variable(CXCursor cursor);
    compile_reflected_variable(rsl::dynamic_string name, rsl::dynamic_string type);
    ~compile_reflected_variable();
    compile_reflected_variable(const compile_reflected_variable& other) = default;
    compile_reflected_variable(compile_reflected_variable&& other) noexcept = default;

    std::string_view get_string_constructor() const;
    
    void print(int indent) const override;
};

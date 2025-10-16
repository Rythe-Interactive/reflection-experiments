#pragma once
#include <rsl/containers>
#include <iostream>
#include "compile_reflected_element.h"
#include "../reflection_id/reflection_id.h"
#include "clang-c/Index.h"

struct compile_reflected_variable : public compile_reflected_element
{
public:
    rsl::dynamic_string type;

    compile_reflected_variable(CXCursor cursor);
    compile_reflected_variable(rsl::dynamic_string name, reflection_id type);
    ~compile_reflected_variable();
    compile_reflected_variable(const compile_reflected_variable& other) = default;
    compile_reflected_variable(compile_reflected_variable&& other) noexcept = default;

    std::string_view get_string_constructor() const;


    rsl::dynamic_string get_string_for_structure_hash() const override;
    void print(int indent) const override;
};

#pragma once
#include "clang-c/Index.h"
#include <iostream>
#include <rsl/string>

#include "compile_reflected_element.h"

struct compile_reflected_function : public compile_reflected_element
{
public:
    rsl::dynamic_string type;

    compile_reflected_function(const CXCursor& cursor, const CXCursor& parent);
    compile_reflected_function(const compile_reflected_function& other) = default;
    compile_reflected_function(compile_reflected_function&& other) noexcept = default;
    ~compile_reflected_function();

    void print(int indent) const override;
};

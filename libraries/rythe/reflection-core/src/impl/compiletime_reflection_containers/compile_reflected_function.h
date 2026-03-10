#pragma once
#include "clang-c/Index.h"
#include <iostream>
#include <rsl/string>

#include "compile_reflected_element.h"

struct compile_reflected_function : public compile_reflected_element
{
public:
    rsl::dynamic_string                     return_type_spelling;
    rsl::dynamic_array<reflection_id>       parameter_types;
    rsl::dynamic_array<rsl::dynamic_string> parameter_type_spellings;
    rsl::dynamic_array<rsl::dynamic_string> parameter_names;
    bool                                    is_const = false;
    bool                                    is_static = false;

    compile_reflected_function(const CXCursor& cursor, const CXCursor& parent);
    compile_reflected_function(const compile_reflected_function& other) = default;
    compile_reflected_function(compile_reflected_function&& other) noexcept = default;
    ~compile_reflected_function();

    void print(int indent) const override;
private:
    rsl::id_type compute_own_structure_hash() noexcept override;
};

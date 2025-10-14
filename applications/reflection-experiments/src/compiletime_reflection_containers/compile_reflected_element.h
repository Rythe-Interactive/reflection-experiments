#pragma once
#include "clang-c/Index.h"
#include "rsl/containers"

struct compile_reflected_element
{
public:
    rsl::dynamic_string name;

    compile_reflected_element(rsl::dynamic_string name);
    compile_reflected_element(const compile_reflected_element& other) = default;
    compile_reflected_element(compile_reflected_element&& other) noexcept = default;
    virtual ~compile_reflected_element();

    virtual void print(int indent) const;

    virtual rsl::dynamic_string get_string_for_structure_hash() const;
private:
protected:
    static rsl::dynamic_string get_name_from_cursor(CXCursor& cursor);
};

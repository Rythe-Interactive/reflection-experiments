#pragma once
#include "../reflection_id/reflection_id.h"
#include "clang-c/Index.h"
#include "rsl/containers"

struct compile_reflected_element
{
public:
    rsl::dynamic_string name;
    reflection_id       id;

    compile_reflected_element(rsl::dynamic_string name);
    compile_reflected_element(rsl::dynamic_string name, reflection_id id);
    compile_reflected_element(const compile_reflected_element& other) = default;
    compile_reflected_element(compile_reflected_element&& other) noexcept = default;
    virtual ~compile_reflected_element() = default;

    virtual void print(int indent) const;

    virtual void finalize_creating_id() noexcept;
private:
protected:
    rsl::id_type compute_structure_hash();
    rsl::id_type compute_name_hash();

    
    static rsl::dynamic_string get_name_from_cursor(CXCursor& cursor);
};

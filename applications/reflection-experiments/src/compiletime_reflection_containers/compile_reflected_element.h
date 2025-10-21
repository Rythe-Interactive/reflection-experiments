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

    void set_full_hash() noexcept;
private:
protected:
    rsl::id_type compute_structure_hash() noexcept;
    rsl::id_type compute_name_hash() const noexcept;

    virtual rsl::id_type compute_own_structure_hash() noexcept;
    virtual rsl::id_type compute_container_structure_hash() noexcept;

    static rsl::dynamic_string get_name_from_cursor(CXCursor& cursor);
};

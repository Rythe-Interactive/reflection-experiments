#include "compile_reflected_element.h"

#include <iostream>
#include <ostream>

compile_reflected_element::compile_reflected_element(rsl::dynamic_string name)
    : name(std::move(name))
  , id(reflection_id::null()) {}

compile_reflected_element::compile_reflected_element(rsl::dynamic_string name, reflection_id id)
    : name(std::move(name))
  , id(id) {}

void compile_reflected_element::print(int indent) const
{
    for(auto i = 0; i < indent; i++) { std::cout << ' '; }
    std::cout << "Name: " << this->name.data() << '\n';

    for(auto i = 0; i < indent; i++) { std::cout << ' '; }
    std::cout << "Reflection hash: " << this->id.get_full_hash() << '\n';
}
void compile_reflected_element::set_full_hash() noexcept
{
    rsl::id_type name_hash = compute_name_hash();
    rsl::id_type structure_hash = compute_structure_hash();

    id.set_name_hash(name_hash);
    id.set_structure_hash(structure_hash);
    id.set_full_hash(rsl::combine_hash(rsl::internal::hash::default_seed, name_hash, structure_hash));
}

rsl::id_type compile_reflected_element::compute_name_hash() const noexcept { return rsl::hash_string(name); }

rsl::id_type compile_reflected_element::compute_structure_hash() noexcept
{
    rsl::id_type hash = rsl::internal::hash::default_seed;

    rsl::id_type own_hash = compute_own_structure_hash();
    if(own_hash != 0) { hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, own_hash); }

    rsl::id_type container_hash = compute_container_structure_hash();
    if(container_hash != 0) { hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, container_hash); }

    return hash;
}

rsl::id_type compile_reflected_element::compute_own_structure_hash() noexcept { return 0; }

rsl::id_type compile_reflected_element::compute_container_structure_hash() noexcept { return 0; }

rsl::dynamic_string compile_reflected_element::get_name_from_cursor(const CXCursor& cursor)
{
    CXString    field_name = clang_getCursorSpelling(cursor);
    const char* field_spelling = clang_getCString(field_name);
    auto result = rsl::dynamic_string::from_string_length(field_spelling);
    clang_disposeString(field_name);
    return result;
}

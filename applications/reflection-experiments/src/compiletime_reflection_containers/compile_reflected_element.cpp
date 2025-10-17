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
void compile_reflected_element::finalize_creating_id() noexcept {}

rsl::dynamic_string compile_reflected_element::get_name_from_cursor(CXCursor& cursor)
{
    CXString    field_name = clang_getCursorSpelling(cursor);
    const char* field_spelling = clang_getCString(field_name);
    auto result = rsl::dynamic_string::from_string_length(field_spelling);
    clang_disposeString(field_name);
    return result;
}

#include "compile_reflected_element.h"

#include <iostream>
#include <ostream>

compile_reflected_element::compile_reflected_element(rsl::dynamic_string&& name) : name(std::move(name)) {}

compile_reflected_element::~compile_reflected_element() {}

void compile_reflected_element::print(int indent) const
{
    for(auto i = 0; i < indent; i++) { std::cout << ' '; }
    std::cout << this->name.data() << '\n';
}

rsl::dynamic_string compile_reflected_element::get_name_from_cursor(CXCursor& cursor)
{
    CXString    field_name = clang_getCursorSpelling(cursor);
    const char* field_spelling = clang_getCString(field_name);
    clang_disposeString(field_name);
    auto result = rsl::dynamic_string::from_string_length(field_spelling);
    return result;
}

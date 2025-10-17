#include "compile_reflected_variable.h"

compile_reflected_variable::compile_reflected_variable(CXCursor cursor)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    CXType      cursorType = clang_getCursorType(cursor);
    CXString    typeSpelling = clang_getTypeSpelling(cursorType);
    const char* type_spelling = clang_getCString(typeSpelling);

    this->type_spelling = rsl::dynamic_string::from_string_length(type_spelling);

    clang_disposeString(typeSpelling);
}

compile_reflected_variable::compile_reflected_variable(rsl::dynamic_string name, reflection_id type)
    : compile_reflected_element(name) { if(type.get_name_hash()) {} }

compile_reflected_variable::~compile_reflected_variable() {}

void compile_reflected_variable::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Type: " << this->type_spelling.data() << '\n';
}


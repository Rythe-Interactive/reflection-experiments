#include "compile_reflected_variable.h"

compile_reflected_variable::compile_reflected_variable(CXCursor cursor)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    CXType      cursorType = clang_getCursorType(cursor);
    CXString    typeSpelling = clang_getTypeSpelling(cursorType);
    const char* type_spelling = clang_getCString(typeSpelling);
    
    this->type = rsl::dynamic_string::from_string_length(type_spelling);

    clang_disposeString(typeSpelling);
}

compile_reflected_variable::~compile_reflected_variable() {}

void compile_reflected_variable::print(int indent) const
{
    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Field name: ";
    compile_reflected_element::print(0);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Type: " << this->type.data() << '\n';
}

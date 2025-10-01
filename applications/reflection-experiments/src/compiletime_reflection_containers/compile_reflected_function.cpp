#include "compile_reflected_function.h"


compile_reflected_function::compile_reflected_function(CXCursor cursor)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    CXType      cursorType = clang_getCursorType(cursor);
    CXString    typeSpelling = clang_getTypeSpelling(cursorType);
    const char* type_spelling = clang_getCString(typeSpelling);
    
    this->type = rsl::dynamic_string::from_string_length(type_spelling);
    
    clang_disposeString(typeSpelling);
}

compile_reflected_function::~compile_reflected_function() {}

void compile_reflected_function::print(int indent) const
{
    compile_reflected_element::print(indent);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << this->type.data() << '\n';
}

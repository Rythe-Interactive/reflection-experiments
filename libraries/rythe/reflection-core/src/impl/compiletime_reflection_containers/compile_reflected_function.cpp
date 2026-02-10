#include "compile_reflected_function.h"


compile_reflected_function::compile_reflected_function(const CXCursor& cursor, const CXCursor& parent)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    CXType      cursorType = clang_getCursorType(cursor);
    CXString    typeSpelling = clang_getTypeSpelling(cursorType);
    const char* type_spelling_cstring = clang_getCString(typeSpelling);

    this->type_spelling = rsl::dynamic_string::from_string_length(type_spelling_cstring);
    
    clang_disposeString(typeSpelling);

    if(parent.kind) {}
}

compile_reflected_function::~compile_reflected_function() {}

void compile_reflected_function::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Type: " << this->type_spelling.data() << '\n';
}

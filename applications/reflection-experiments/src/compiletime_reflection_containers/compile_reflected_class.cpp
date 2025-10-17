#include "compile_reflected_class.h"

compile_reflected_class::compile_reflected_class(CXCursor cursor)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    this->compile_reflection_container<compile_reflected_class>::verify_typename();
    this->compile_reflection_container<compile_reflected_variable>::verify_typename();
    this->compile_reflection_container<compile_reflected_function>::verify_typename();
    
    CXType      cursorType = clang_getCursorType(cursor);
    CXString    typeSpelling = clang_getTypeSpelling(cursorType);
    const char* type_spelling = clang_getCString(typeSpelling);

    this->type_spelling = rsl::dynamic_string::from_string_length(type_spelling);
    
    clang_disposeString(typeSpelling);
}

compile_reflected_class::~compile_reflected_class() {}

void compile_reflected_class::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Type: " << this->name.data() << '\n';
    
    compile_reflection_container<compile_reflected_class>::print_container(indent + 1);
    compile_reflection_container<compile_reflected_function>::print_container(indent + 1);
    compile_reflection_container<compile_reflected_variable>::print_container(indent + 1);
}

#include "compile_reflected_variable.h"

compile_reflected_variable::compile_reflected_variable(CXCursor cursor)
{
    CXString    field_name = clang_getCursorSpelling(cursor);
    const char* field_spelling = clang_getCString(field_name);

    CXType      cursorType = clang_getCursorType(cursor);
    CXString    typeSpelling = clang_getTypeSpelling(cursorType);
    const char* type_spelling = clang_getCString(typeSpelling);

    this->name = rsl::dynamic_string::from_string_length(field_spelling);
    this->type = rsl::dynamic_string::from_string_length(type_spelling);

    clang_disposeString(field_name);
    clang_disposeString(typeSpelling);
}

compile_reflected_variable::~compile_reflected_variable() {}

compile_reflected_variable::compile_reflected_variable(compile_reflected_variable&& other) {}

compile_reflected_variable::compile_reflected_variable(const compile_reflected_variable& other) {}
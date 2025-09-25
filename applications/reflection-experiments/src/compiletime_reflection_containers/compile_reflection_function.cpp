#include "compile_reflection_function.h"

compile_reflection_function::compile_reflection_function(CXCursor cursor)
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

compile_reflection_function::compile_reflection_function(const compile_reflection_function& other) {}

compile_reflection_function::compile_reflection_function(compile_reflection_function&& other) {}

compile_reflection_function::~compile_reflection_function() {}

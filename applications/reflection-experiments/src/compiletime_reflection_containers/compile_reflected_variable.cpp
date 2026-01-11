#include "compile_reflected_variable.h"

compile_reflected_variable::compile_reflected_variable(const CXCursor& cursor, const CXCursor& parent)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    CXType parent_type = clang_getCursorType(parent);

    CXType      cursor_type = clang_getCursorType(cursor);
    CXString    type_spelling_string = clang_getTypeSpelling(cursor_type);
    const char* type_spelling_var = clang_getCString(type_spelling_string);

    this->type_spelling = rsl::dynamic_string::from_string_length(type_spelling_var);

    long long offset_bits = clang_Type_getOffsetOf(parent_type, name.data());
    if(offset_bits < 0) { std::cout << "Offset bits are less than 0: " << offset_bits << '\n'; }
    this->offset = static_cast<rsl::size_type>(offset_bits) / 8;
    
    clang_disposeString(type_spelling_string);
}

compile_reflected_variable::compile_reflected_variable(
    rsl::dynamic_string name,
    reflection_id       type,
    rsl::size_type      offset)
    : compile_reflected_element(name)
  , offset(offset) { if(type.get_name_hash()) {} }

compile_reflected_variable::~compile_reflected_variable() {}

void compile_reflected_variable::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Type: " << this->type_spelling.data() << '\n';

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Offset in bytes: " << this->offset << '\n';
}

rsl::id_type compile_reflected_variable::compute_own_structure_hash() noexcept
{
    return rsl::combine_hash(
        rsl::internal::hash::default_seed,
        rsl::internal::hash::default_seed,
        rsl::hash_string(type_spelling));
}

#include "compile_reflected_class.h"

compile_reflected_class::compile_reflected_class(const CXCursor& cursor, const CXCursor& parent)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    this->compile_reflection_container<compile_reflected_class>::verify_typename();
    this->compile_reflection_container<compile_reflected_variable>::verify_typename();
    this->compile_reflection_container<compile_reflected_function>::verify_typename();

    CXType parent_type = clang_getCursorType(parent);

    CXType      cursor_type = clang_getCursorType(cursor);
    CXString    type_spelling_string = clang_getTypeSpelling(cursor_type);
    const char* type_spelling = clang_getCString(type_spelling_string);

    this->type_spelling = rsl::dynamic_string::from_string_length(type_spelling);

    long long offset_bits = clang_Type_getOffsetOf(parent_type, type_spelling);
    this->offset = static_cast<rsl::size_type>(offset_bits);
    clang_disposeString(type_spelling_string);
}

compile_reflected_class::~compile_reflected_class() {}

compile_reflected_class& compile_reflected_class::add_class(const CXCursor& cursor, const CXCursor& parent)
{
    return this->compile_reflection_container<compile_reflected_class>::add_element(cursor, parent);
}

compile_reflected_variable& compile_reflected_class::add_variable(const CXCursor& cursor, const CXCursor& parent)
{
    return this->compile_reflection_container<compile_reflected_variable>::add_element(cursor, parent);
}

compile_reflected_function& compile_reflected_class::add_function(const CXCursor& cursor, const CXCursor& parent)
{
    return this->compile_reflection_container<compile_reflected_function>::add_element(cursor, parent);
}

void compile_reflected_class::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Type: " << this->name.data() << '\n';
    
    compile_reflection_container<compile_reflected_class>::print_container(indent + 1);
    compile_reflection_container<compile_reflected_function>::print_container(indent + 1);
    compile_reflection_container<compile_reflected_variable>::print_container(indent + 1);
}

rsl::id_type compile_reflected_class::compute_own_structure_hash() noexcept
{
    return rsl::combine_hash(
        rsl::internal::hash::default_seed,
        rsl::internal::hash::default_seed,
        rsl::hash_string(type_spelling));
}

rsl::id_type compile_reflected_class::compute_container_structure_hash() noexcept
{
    rsl::id_type hash = rsl::internal::hash::default_seed;

    this->compile_reflection_container<compile_reflected_class>::sort_container(sort_by_offset_comparator);
    rsl::id_type class_container_hash = this->compile_reflection_container<
        compile_reflected_class>::get_container_hash();
    if(hash != 0) { hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, class_container_hash); }

    rsl::id_type variable_container_hash = this->compile_reflection_container<
        compile_reflected_variable>::get_container_hash();
    if(hash != 0) { hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, variable_container_hash); }

    rsl::id_type function_container_hash = this->compile_reflection_container<
        compile_reflected_function>::get_container_hash();
    if(hash != 0) { hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, function_container_hash); }

    return hash;
}

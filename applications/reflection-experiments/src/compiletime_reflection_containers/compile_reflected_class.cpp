#include "compile_reflected_class.h"

compile_reflected_class::compile_reflected_class(const CXCursor& cursor, const CXCursor& parent)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    this->compile_reflection_container<compile_reflected_class>::verify_typename();
    this->compile_reflection_container<compile_reflected_variable>::verify_typename();
    this->compile_reflection_container<compile_reflected_function>::verify_typename();

    CXType parent_type = clang_getCursorType(parent);

    long long offset_bits = clang_Type_getOffsetOf(parent_type, name.data());
    if(offset_bits < 0) { std::cout << "Offset bits are less than 0: " << offset_bits << '\n'; }
    this->offset = static_cast<rsl::size_type>(offset_bits);
}

compile_reflected_class::~compile_reflected_class() {}

compile_reflected_class& compile_reflected_class::add_class(CXCursor& cursor, CXCursor& parent)
{
    return this->compile_reflection_container<compile_reflected_class>::add_element(cursor, parent);
}

compile_reflected_variable& compile_reflected_class::add_variable(CXCursor& cursor, CXCursor& parent)
{
    return this->compile_reflection_container<compile_reflected_variable>::add_element(cursor, parent);
}

compile_reflected_function& compile_reflected_class::add_function(CXCursor& cursor, CXCursor& parent)
{
    return this->compile_reflection_container<compile_reflected_function>::add_element(cursor, parent);
}

void compile_reflected_class::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Offset in bytes: " << this->offset << '\n';
    
    compile_reflection_container<compile_reflected_class>::print_container(indent + 1);
    compile_reflection_container<compile_reflected_function>::print_container(indent + 1);
    compile_reflection_container<compile_reflected_variable>::print_container(indent + 1);
}

rsl::id_type compile_reflected_class::compute_own_structure_hash() noexcept
{
    return SIZE_MAX;
}

// This order should be always deterministic.
// Embedded classes -> functions -> variables.
// Important because same input should produce same hash.
rsl::id_type compile_reflected_class::compute_container_structure_hash() noexcept
{
    rsl::id_type hash = rsl::internal::hash::default_seed;

    this->compile_reflection_container<compile_reflected_class>::sort_container(
        &compile_reflection_container<compile_reflected_class>::sort_by_offset_comparator);
    rsl::id_type class_container_hash = this->compile_reflection_container<
        compile_reflected_class>::get_container_hash();

    if(class_container_hash != SIZE_MAX)
    {
        hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, class_container_hash);
    }

    this->compile_reflection_container<compile_reflected_variable>::sort_container(
        &compile_reflection_container<compile_reflected_variable>::sort_by_offset_comparator);
    rsl::id_type variable_container_hash = this->compile_reflection_container<
        compile_reflected_variable>::get_container_hash();

    if(variable_container_hash != SIZE_MAX)
    {
        hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, variable_container_hash);
    }

    this->compile_reflection_container<compile_reflected_function>::sort_container(
        &compile_reflection_container<compile_reflected_function>::sort_by_name_comparator);
    rsl::id_type function_container_hash = this->compile_reflection_container<
        compile_reflected_function>::get_container_hash();

    if(function_container_hash != SIZE_MAX)
    {
        hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, function_container_hash);
    }

    return hash;
}

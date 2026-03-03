#include "compile_reflected_function.h"

compile_reflected_function::compile_reflected_function(const CXCursor& cursor, const CXCursor& parent)
    : compile_reflected_element(get_name_from_cursor(cursor))
{
    (void)parent;

    CXType func_type = clang_getCursorType(cursor);

    CXType return_type = clang_getResultType(func_type);

    CXString    return_type_spelling_string = clang_getTypeSpelling(return_type);
    const char* return_type_spelling_cstr = clang_getCString(return_type_spelling_string);

    this->return_type_spelling = rsl::dynamic_string::from_string_length(return_type_spelling_cstr);

    clang_disposeString(return_type_spelling_string);

    int num_args = clang_Cursor_getNumArguments(cursor);

    for(auto i = 0; i < num_args; ++i)
    {
        CXCursor arg_cursor = clang_Cursor_getArgument(cursor, i);
        CXType   arg_type = clang_getCursorType(arg_cursor);

        CXString    arg_type_spelling_string = clang_getTypeSpelling(arg_type);
        const char* arg_type_spelling_cstr = clang_getCString(arg_type_spelling_string);

        rsl::dynamic_string spelling = rsl::dynamic_string::from_string_length(
            arg_type_spelling_cstr);

        parameter_type_spellings.push_back(spelling);

        clang_disposeString(arg_type_spelling_string);

        CXString    arg_name_string = clang_getCursorSpelling(arg_cursor);
        const char* arg_name_cstr = clang_getCString(arg_name_string);

        rsl::dynamic_string param_name = rsl::dynamic_string::from_string_length(arg_name_cstr);

        parameter_names.push_back(param_name);

        clang_disposeString(arg_name_string);
    }

    is_const = clang_CXXMethod_isConst(cursor);
    is_static = clang_CXXMethod_isStatic(cursor);
}

compile_reflected_function::~compile_reflected_function() {}

void compile_reflected_function::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Return type: " << this->return_type_spelling.data() << '\n';

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Const: " << (this->is_const ? "true" : "false") << '\n';

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Static: " << (this->is_static ? "true" : "false") << '\n';

    for(rsl::size_type i = 0; i < parameter_type_spellings.size(); ++i)
    {
        for(auto j = 0; j < indent + 2; j++) { std::cout << ' '; }
        std::cout << "Param[" << i << "]: " << parameter_type_spellings[i].data() << '\n';
    }
}

rsl::id_type compile_reflected_function::compute_own_structure_hash() noexcept
{
    rsl::id_type hash = rsl::combine_hash(
        rsl::internal::hash::default_seed,
        rsl::internal::hash::default_seed,
        rsl::hash_string(return_type_spelling));

    for(const auto& param : parameter_type_spellings)
    {
        hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, rsl::hash_string(param));
    }

    hash = rsl::combine_hash(
        rsl::internal::hash::default_seed,
        hash,
        static_cast<rsl::id_type>(is_const));

    hash = rsl::combine_hash(
        rsl::internal::hash::default_seed,
        hash,
        static_cast<rsl::id_type>(is_static));

    return hash;
}

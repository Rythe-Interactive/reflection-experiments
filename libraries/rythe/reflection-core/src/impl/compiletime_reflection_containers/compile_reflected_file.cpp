#include "compile_reflected_file.h"

#include <iostream>

compile_reflected_file::compile_reflected_file(rsl::dynamic_string&& name, rsl::dynamic_string&& source_location)
    : compile_reflected_element(std::move(name))
  , source_location(std::move(source_location))
{
    this->compile_reflection_container<compile_reflected_class>::verify_typename();
    this->compile_reflection_container<compile_reflected_variable>::verify_typename();
    this->compile_reflection_container<compile_reflected_function>::verify_typename();
}

compile_reflected_file::~compile_reflected_file() {}

rsl::string_view compile_reflected_file::get_source_location() const { return source_location; }

const std::vector<std::unique_ptr<compile_reflected_class>>&
compile_reflected_file::get_class_container() const
{
    return this->compile_reflection_container<compile_reflected_class>::get_container();
}

const std::vector<std::unique_ptr<compile_reflected_function>>&
compile_reflected_file::get_function_container() const
{
    return this->compile_reflection_container<compile_reflected_function>::get_container();
}

const std::vector<std::unique_ptr<compile_reflected_variable>>&
compile_reflected_file::get_variable_container() const
{
    return this->compile_reflection_container<compile_reflected_variable>::get_container();
}


void compile_reflected_file::print(int indent) const
{
    compile_reflected_element::print(indent + 1);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Source location: " << this->source_location.data() << '\n';

    this->compile_reflection_container<compile_reflected_class>::print_container(indent + 1);
    this->compile_reflection_container<compile_reflected_function>::print_container(indent + 1);
    this->compile_reflection_container<compile_reflected_variable>::print_container(indent + 1);
}


#include "compile_reflected_file.h"

#include <iostream>

compile_reflected_file::compile_reflected_file(rsl::dynamic_string&& name, rsl::dynamic_string&& source_location)
    : compile_reflected_element(std::move(name))
  , source_location(std::move(source_location)) {}

compile_reflected_file::~compile_reflected_file() {}

void compile_reflected_file::print(int indent) const
{
    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "File name: ";
    compile_reflected_element::print(0);

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Source location: " << this->source_location.data() << '\n';

    this->compile_reflection_container<compile_reflected_class>::print_container(indent + 1);
    this->compile_reflection_container<compile_reflected_function>::print_container(indent + 1);
    this->compile_reflection_container<compile_reflected_variable>::print_container(indent + 1);
}


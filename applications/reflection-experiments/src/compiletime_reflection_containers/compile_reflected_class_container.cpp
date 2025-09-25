#include "compile_reflected_class_container.h"
#include "compile_reflected_class.h"

compile_reflected_class& compile_reflected_class_container::add_class_from_cursor(CXCursor cursor)
{
    classes.emplace_back(std::make_unique<compile_reflected_class>(cursor));
    return *classes.back();
}

compile_reflected_class_container::compile_reflected_class_container() {}

compile_reflected_class_container::~compile_reflected_class_container() {}

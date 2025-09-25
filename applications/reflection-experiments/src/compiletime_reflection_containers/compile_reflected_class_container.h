#pragma once
#include <deque>
#include <memory>

#include "clang-c/Index.h"

struct compile_reflected_class; 

class compile_reflected_class_container
{
public:
    compile_reflected_class& add_class_from_cursor(CXCursor cursor);

    compile_reflected_class_container();
    ~compile_reflected_class_container();
protected:
    std::deque<std::unique_ptr<compile_reflected_class>> classes;
};

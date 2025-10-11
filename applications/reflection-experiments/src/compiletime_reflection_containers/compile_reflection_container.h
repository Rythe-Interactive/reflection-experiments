#pragma once
#include <memory>
#include <vector>
#include "clang-c/Index.h"
#include "compile_reflected_element.h"
#include <iostream>

template<typename T>
class compile_reflection_container
{
public:
    T& add_element(const CXCursor& cursor);

    void print_container(int indent) const;
    
protected:
    std::vector<std::unique_ptr<T>> container;
};

#include "compile_reflection_container.inl"

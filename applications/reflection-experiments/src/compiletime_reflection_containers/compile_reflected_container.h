#pragma once
#include <vector>

#include <memory>
#include "clang-c/Index.h"
template<typename T>
class compile_reflected_container
{
public:
    T& add_element(const CXCursor& cursor);
protected:
    std::vector<std::unique_ptr<T>> container;
};

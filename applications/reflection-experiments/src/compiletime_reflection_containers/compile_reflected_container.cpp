#include "compile_reflected_container.h"

class compile_reflected_class;

template<typename T>
T& compile_reflected_container<T>::add_element(const CXCursor& cursor)
{
    container.emplace_back(std::make_unique<T>(cursor));
    return *container.back();
}

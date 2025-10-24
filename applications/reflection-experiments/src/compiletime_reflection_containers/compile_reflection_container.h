#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "clang-c/Index.h"
#include "compile_reflected_element.h"
#include <iostream>

template<typename T>
class compile_reflection_container
{
public:
    T& add_element(const CXCursor& cursor, const CXCursor& parent);
    
    void print_container(int indent) const;

    // Need to me manually called in the owner class.
    // Done so because using CRTP and class can have compile_reflection_container<class>
    void verify_typename() const;

    rsl::id_type get_container_hash() const noexcept;
    
protected:
    std::vector<std::unique_ptr<T>> container;

    template<typename Comparator>
    void sort_container(Comparator&& comparator);

    static bool sort_by_name_comparator(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b);
    static bool sort_by_offset_comparator(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b);
};

#include "compile_reflection_container.inl"

#pragma once
template<typename T>
T& compile_reflection_container<T>::add_element(const CXCursor& cursor, const CXCursor& parent)
{
    container.emplace_back(std::make_unique<T>(cursor, parent));
    return *container.back();
}

template<typename T>
void compile_reflection_container<T>::print_container(int indent) const
{
    for(const auto& element : container)
    {
        auto element_object = static_cast<compile_reflected_element*>(element.get());
        if(!element_object) { std::cout << "Reflected container does not store reflected elements." << '\n'; }
        element_object->print(indent);
    }
}

template<typename T>
void compile_reflection_container<T>::verify_typename() const
{
    static_assert(std::is_base_of_v<compile_reflected_element, T>, "T must inherit from compile_reflected_element");
}

template<typename T>
rsl::id_type compile_reflection_container<T>::get_container_hash() const noexcept
{
    if(container.size() == 0) { return SIZE_MAX; }

    rsl::id_type hash = rsl::internal::hash::default_seed;
    for(const auto& element : container)
    {
        auto element_object = static_cast<compile_reflected_element*>(element.get());
        hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, element_object->id.get_structure_hash());
    }
    
    return hash;
}

template<typename T>
template<typename Comparator>
void compile_reflection_container<T>::sort_container(Comparator&& comparator)
{
    std::ranges::sort(container, std::forward<Comparator>(comparator));
}

template<typename T>
bool compile_reflection_container<T>::sort_by_name_comparator(const std::unique_ptr<T>& a, const std::unique_ptr<T>& b)
{
    rsl::dynamic_string a_string = a->name;
    rsl::dynamic_string b_string = b->name;
    const std::size_t   min_length = a_string.size() < b_string.size() ? a_string.size() : b_string.size();

    for(std::size_t i = 0; i < min_length; ++i)
    {
        if(a_string[i] < b_string[i]) { return true; }
        if(a_string[i] > b_string[i]) { return false; }
    }
    return a_string.size() < b_string.size();
}

template<typename T>
bool compile_reflection_container<T>::sort_by_offset_comparator(
    const std::unique_ptr<T>& a,
    const std::unique_ptr<T>& b)
{
    return a->offset < b->offset;
}

#pragma once
// TODO: Make it so that you do not need to call specific base class to add_element();  
template<typename T>
T& compile_reflection_container<T>::add_element(const CXCursor& cursor)
{
    container.emplace_back(std::make_unique<T>(cursor));
    return *container.back();
}

template<typename T>
void compile_reflection_container<T>::print_container(int indent) const
{
    for(const auto& element : container)
    {
        auto element_object = dynamic_cast<compile_reflected_element*>(element.get());
        if(!element_object) { std::cout << "Reflected container does not store reflected elements." << '\n'; }
        element_object->print(indent);
    }
}

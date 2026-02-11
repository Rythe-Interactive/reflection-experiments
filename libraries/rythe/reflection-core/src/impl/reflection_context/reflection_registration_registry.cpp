#include "reflection_registration_registry.h"

#include <iostream>

reflection_registration_registry& reflection_registration_registry::instance()
{
    static reflection_registration_registry registry;
    return registry;
}

void reflection_registration_registry::add(void (*func)()) { functions.push_back(func); }

void reflection_registration_registry::run_all() const
{
    std::cout << functions.size() << std::endl;
    for(auto function : functions)
    {
        if(function)
        {
            std::cout << "lala";
            function();
        }
    }
}

void reflection_registration_registry::clear() { functions.clear(); }

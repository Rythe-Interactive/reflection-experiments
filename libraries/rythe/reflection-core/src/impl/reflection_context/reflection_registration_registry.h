#pragma once
#include <vector>
#include <functional>

class reflection_registration_registry
{
public:
    static reflection_registration_registry& instance();

    void add(void (*func)());

    void run_all() const;

    void clear();
private:
    reflection_registration_registry() = default;
    ~reflection_registration_registry() = default;

    reflection_registration_registry(const reflection_registration_registry&) = delete;
    reflection_registration_registry& operator=(const reflection_registration_registry&) = delete;

    std::vector<void(*)()> functions;
};

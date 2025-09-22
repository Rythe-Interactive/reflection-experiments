#pragma once
#include "rsl/impl/containers/string.hpp"

class comp_reflected_element {
public:
    comp_reflected_element(const rsl::dynamic_string &usr_id);
    ~comp_reflected_element();

    rsl::dynamic_string get_usr_id() const;
protected:
    const rsl::dynamic_string usr_id;
};

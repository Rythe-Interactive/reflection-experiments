#include "comp_reflected_element.h"

comp_reflected_element::comp_reflected_element(const rsl::dynamic_string usr_id) : usr_id(usr_id) {
    
}

comp_reflected_element::~comp_reflected_element() {
    
}

rsl::dynamic_string comp_reflected_element::get_usr_id() const {
    return usr_id;
}


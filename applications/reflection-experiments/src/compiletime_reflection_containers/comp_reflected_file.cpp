#include "comp_reflected_file.h"

comp_reflected_file::comp_reflected_file(const rsl::dynamic_string &usr_id) : comp_reflected_element(usr_id) {
    
}

comp_reflected_file::~comp_reflected_file() {
    
}

void comp_reflected_file::addVariableToFile(const rsl::dynamic_string &parent_usr_id, comp_reflected_variable variable) {
    auto it = all_elements.find(parent_usr_id);
    if (it != all_elements.end()) {
        //it->second->addVariable(std::move(variable));
    } else {
        this->addVariable(std::move(variable));
    }
    
}


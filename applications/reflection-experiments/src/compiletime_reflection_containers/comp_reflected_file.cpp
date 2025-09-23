#include "comp_reflected_file.h"

#include "rsl/impl/util/source_location.hpp"

// Having source_location as USR does work, as there are no source files in AST.
comp_reflected_file::comp_reflected_file(const rsl::dynamic_string source_location)
: comp_reflected_element(source_location), source_location(source_location) {
    all_elements[usr_id] = std::make_unique<comp_reflected_element>(usr_id);    
}

comp_reflected_file::~comp_reflected_file() {
    
}

void comp_reflected_file::addVariableToFile(const rsl::dynamic_string &parent_usr_id, comp_reflected_variable variable) {
    auto it = all_elements.find(parent_usr_id);
    if (it != all_elements.end()) {
        comp_reflected_variable_container variable_container = it->second->asVariableContainer();
        if (variable_container == nullptr) {
            std::cout << "There is no variable container in " << parent_usr_id.data() << '\n';
            return;
        }
        
        all_elements[usr_id] = std::move(variable_container);
        variable_container->addVariable(variable);
        
    } else {
        std::cout << "There is no usr like" << parent_usr_id.data() << '\n';
    }
    
}


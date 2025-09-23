#pragma once
#include <map>

#include "comp_reflected_variable_container.h"
#include "clang-c/Index.h"

class comp_reflected_file : public comp_reflected_variable_container,
                            public comp_reflected_element {
public:
    rsl::dynamic_string name;
    comp_reflected_file(const rsl::dynamic_string source_location);
    ~comp_reflected_file() override;

    void addVariableToFile(const rsl::dynamic_string &parent_usr_id, comp_reflected_variable variable);

    comp_reflected_variable_container* asVariableContainer() override {return this;}
    
private:
    std::map<rsl::dynamic_string, std::unique_ptr<comp_reflected_element>> all_elements;

    rsl::dynamic_string source_location;
};

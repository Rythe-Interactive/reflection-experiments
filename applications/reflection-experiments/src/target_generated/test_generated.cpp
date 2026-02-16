#include "runtime_reflection_containers.h"
#include "impl/reflection_id/reflection_id.h"
#include "impl/reflection_context/reflection_registration_registry.h"
#include "impl/reflection_context/reflection_context.h"
void register_reflection_file_test()
{
    runtime_reflected_class class_14985410343605238495;
    class_14985410343605238495.id = reflection_id(1644627251862529318ULL, 13483286640053009272ULL, 14985410343605238495ULL);
    class_14985410343605238495.type_spelling = rsl::dynamic_string::from_string_length("very_cool_target_class");

    runtime_reflected_variable variable_6501503083828029313;
    variable_6501503083828029313.id = reflection_id(10933754376540684078ULL, 16350452351519940193ULL, 6501503083828029313ULL);
    variable_6501503083828029313.offset = 0;
    variable_6501503083828029313.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_14985410343605238495.add_variable(std::move(variable_6501503083828029313));

    runtime_reflected_variable variable_126163732700301715;
    variable_126163732700301715.id = reflection_id(5770744143431503129ULL, 12913254394975708779ULL, 126163732700301715ULL);
    variable_126163732700301715.offset = 4;
    variable_126163732700301715.type_spelling = rsl::dynamic_string::from_string_length("float");
    class_14985410343605238495.add_variable(std::move(variable_126163732700301715));

    runtime_reflected_variable variable_17337086075296791468;
    variable_17337086075296791468.id = reflection_id(15779825311949492597ULL, 9221959329564397894ULL, 17337086075296791468ULL);
    variable_17337086075296791468.offset = 8;
    variable_17337086075296791468.type_spelling = rsl::dynamic_string::from_string_length("char");
    class_14985410343605238495.add_variable(std::move(variable_17337086075296791468));

    runtime_reflected_class class_3168970719907517523;
    class_3168970719907517523.id = reflection_id(8627741348740311923ULL, 10691473971882747459ULL, 3168970719907517523ULL);
    class_3168970719907517523.type_spelling = rsl::dynamic_string::from_string_length("nested_class");

    runtime_reflected_variable variable_9809713342160364025;
    variable_9809713342160364025.id = reflection_id(785375445157317512ULL, 16350452351519940193ULL, 9809713342160364025ULL);
    variable_9809713342160364025.offset = 0;
    variable_9809713342160364025.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_3168970719907517523.add_variable(std::move(variable_9809713342160364025));

    class_14985410343605238495.add_class(std::move(class_3168970719907517523));

    reflection_context::instance().add_class(std::move(class_14985410343605238495));

    runtime_reflected_class class_862151746601595251;
    class_862151746601595251.id = reflection_id(14404923345981690111ULL, 31932944099034707ULL, 862151746601595251ULL);
    class_862151746601595251.type_spelling = rsl::dynamic_string::from_string_length("target_class2");

    runtime_reflected_variable variable_13153249853553726320;
    variable_13153249853553726320.id = reflection_id(4281340778281841492ULL, 16350452351519940193ULL, 13153249853553726320ULL);
    variable_13153249853553726320.offset = 0;
    variable_13153249853553726320.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_862151746601595251.add_variable(std::move(variable_13153249853553726320));

    runtime_reflected_variable variable_6526241590453974317;
    variable_6526241590453974317.id = reflection_id(10234543199726084352ULL, 9221959329564397894ULL, 6526241590453974317ULL);
    variable_6526241590453974317.offset = 4;
    variable_6526241590453974317.type_spelling = rsl::dynamic_string::from_string_length("char");
    class_862151746601595251.add_variable(std::move(variable_6526241590453974317));

    reflection_context::instance().add_class(std::move(class_862151746601595251));

};

struct reflection_file_registration_helper
{
    reflection_file_registration_helper()
    {
        reflection_registration_registry::instance().add(&register_reflection_file_test);
    }
};
static reflection_file_registration_helper registration_instance;
#include "runtime_reflection_containers.h"
#include "impl/reflection_id/reflection_id.h"
#include "impl/reflection_context/reflection_registration_registry.h"
#include "impl/reflection_context/reflection_context.h"
void register_reflection_file_test3()
{
    runtime_reflected_class class_5872925259695595721;
    class_5872925259695595721.name = rsl::dynamic_string::from_string_length("very_cool_target_class3");
    class_5872925259695595721.id = reflection_id(4079449365956602113ULL, 3676408051602900246ULL, 5872925259695595721ULL);
    class_5872925259695595721.type_spelling = rsl::dynamic_string::from_string_length("very_cool_target_class3");

    runtime_reflected_variable variable_6501503083828029313;
    variable_6501503083828029313.name = rsl::dynamic_string::from_string_length("int_variable");
    variable_6501503083828029313.id = reflection_id(10933754376540684078ULL, 16350452351519940193ULL, 6501503083828029313ULL);
    variable_6501503083828029313.offset = 0;
    variable_6501503083828029313.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_5872925259695595721.add_variable(std::move(variable_6501503083828029313));

    runtime_reflected_variable variable_126163732700301715;
    variable_126163732700301715.name = rsl::dynamic_string::from_string_length("variable");
    variable_126163732700301715.id = reflection_id(5770744143431503129ULL, 12913254394975708779ULL, 126163732700301715ULL);
    variable_126163732700301715.offset = 4;
    variable_126163732700301715.type_spelling = rsl::dynamic_string::from_string_length("float");
    class_5872925259695595721.add_variable(std::move(variable_126163732700301715));

    runtime_reflected_variable variable_17337086075296791468;
    variable_17337086075296791468.name = rsl::dynamic_string::from_string_length("char_variable");
    variable_17337086075296791468.id = reflection_id(15779825311949492597ULL, 9221959329564397894ULL, 17337086075296791468ULL);
    variable_17337086075296791468.offset = 8;
    variable_17337086075296791468.type_spelling = rsl::dynamic_string::from_string_length("char");
    class_5872925259695595721.add_variable(std::move(variable_17337086075296791468));

    runtime_reflected_function function_11759744666720004420;
    function_11759744666720004420.name = rsl::dynamic_string::from_string_length("void_function");
    function_11759744666720004420.id = reflection_id(5474487154151368338ULL, 18229931349466367843ULL, 11759744666720004420ULL);
    function_11759744666720004420.return_type_spelling = rsl::dynamic_string::from_string_length("void");
    function_11759744666720004420.parameter_types_spelling.push_back(rsl::dynamic_string::from_string_length("int"));
    function_11759744666720004420.parameter_names.push_back(rsl::dynamic_string::from_string_length("int_parameter"));
    function_11759744666720004420.is_const = false;
    function_11759744666720004420.is_static = false;
    class_5872925259695595721.add_function(std::move(function_11759744666720004420));

    runtime_reflected_class class_18055574374418813810;
    class_18055574374418813810.name = rsl::dynamic_string::from_string_length("nested_class3");
    class_18055574374418813810.id = reflection_id(2369122574965995126ULL, 7743830921338232219ULL, 18055574374418813810ULL);
    class_18055574374418813810.type_spelling = rsl::dynamic_string::from_string_length("nested_class3");

    runtime_reflected_variable variable_9809713342160364025;
    variable_9809713342160364025.name = rsl::dynamic_string::from_string_length("value");
    variable_9809713342160364025.id = reflection_id(785375445157317512ULL, 16350452351519940193ULL, 9809713342160364025ULL);
    variable_9809713342160364025.offset = 0;
    variable_9809713342160364025.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_18055574374418813810.add_variable(std::move(variable_9809713342160364025));

    runtime_reflected_function function_8326206098713976876;
    function_8326206098713976876.name = rsl::dynamic_string::from_string_length("get_value");
    function_8326206098713976876.id = reflection_id(4568201618035357963ULL, 3401684896289255038ULL, 8326206098713976876ULL);
    function_8326206098713976876.return_type_spelling = rsl::dynamic_string::from_string_length("int");
    function_8326206098713976876.is_const = true;
    function_8326206098713976876.is_static = false;
    class_18055574374418813810.add_function(std::move(function_8326206098713976876));

    runtime_reflected_function function_3472948984907647894;
    function_3472948984907647894.name = rsl::dynamic_string::from_string_length("nested_class");
    function_3472948984907647894.id = reflection_id(8627741348740311923ULL, 1911340477269032797ULL, 3472948984907647894ULL);
    function_3472948984907647894.return_type_spelling = rsl::dynamic_string::from_string_length("int");
    function_3472948984907647894.is_const = false;
    function_3472948984907647894.is_static = false;
    class_18055574374418813810.add_function(std::move(function_3472948984907647894));

    runtime_reflected_function function_15519012992129584017;
    function_15519012992129584017.name = rsl::dynamic_string::from_string_length("set_value");
    function_15519012992129584017.id = reflection_id(4624142122059757516ULL, 18229931349466367843ULL, 15519012992129584017ULL);
    function_15519012992129584017.return_type_spelling = rsl::dynamic_string::from_string_length("void");
    function_15519012992129584017.parameter_types_spelling.push_back(rsl::dynamic_string::from_string_length("int"));
    function_15519012992129584017.parameter_names.push_back(rsl::dynamic_string::from_string_length("v"));
    function_15519012992129584017.is_const = false;
    function_15519012992129584017.is_static = false;
    class_18055574374418813810.add_function(std::move(function_15519012992129584017));

    class_5872925259695595721.add_class(std::move(class_18055574374418813810));

    reflection_context::instance().add_class(std::move(class_5872925259695595721));

    runtime_reflected_class class_3640212928964342919;
    class_3640212928964342919.name = rsl::dynamic_string::from_string_length("target_class3");
    class_3640212928964342919.id = reflection_id(4085243785640479523ULL, 529573297870223312ULL, 3640212928964342919ULL);
    class_3640212928964342919.type_spelling = rsl::dynamic_string::from_string_length("target_class3");

    runtime_reflected_variable variable_13153249853553726320;
    variable_13153249853553726320.name = rsl::dynamic_string::from_string_length("int_variable2");
    variable_13153249853553726320.id = reflection_id(4281340778281841492ULL, 16350452351519940193ULL, 13153249853553726320ULL);
    variable_13153249853553726320.offset = 0;
    variable_13153249853553726320.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_3640212928964342919.add_variable(std::move(variable_13153249853553726320));

    runtime_reflected_variable variable_6526241590453974317;
    variable_6526241590453974317.name = rsl::dynamic_string::from_string_length("char_variable2");
    variable_6526241590453974317.id = reflection_id(10234543199726084352ULL, 9221959329564397894ULL, 6526241590453974317ULL);
    variable_6526241590453974317.offset = 4;
    variable_6526241590453974317.type_spelling = rsl::dynamic_string::from_string_length("char");
    class_3640212928964342919.add_variable(std::move(variable_6526241590453974317));

    runtime_reflected_function function_14922869285292655127;
    function_14922869285292655127.name = rsl::dynamic_string::from_string_length("void_function2");
    function_14922869285292655127.id = reflection_id(15516586722032245315ULL, 7342613789149850713ULL, 14922869285292655127ULL);
    function_14922869285292655127.return_type_spelling = rsl::dynamic_string::from_string_length("void");
    function_14922869285292655127.parameter_types_spelling.push_back(rsl::dynamic_string::from_string_length("int"));
    function_14922869285292655127.parameter_names.push_back(rsl::dynamic_string::from_string_length("int_parameter"));
    function_14922869285292655127.is_const = false;
    function_14922869285292655127.is_static = true;
    class_3640212928964342919.add_function(std::move(function_14922869285292655127));

    reflection_context::instance().add_class(std::move(class_3640212928964342919));

};

struct reflection_file_registration_helper
{
    reflection_file_registration_helper()
    {
        reflection_registration_registry::instance().add(&register_reflection_file_test3);
    }
};
static reflection_file_registration_helper registration_instance;
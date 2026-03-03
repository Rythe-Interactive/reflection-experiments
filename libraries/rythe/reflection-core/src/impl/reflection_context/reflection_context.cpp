#include "reflection_context.h"
reflection_context& reflection_context::instance()
{
    static reflection_context ctx;
    return ctx;
}

runtime_reflected_class* reflection_context::find_class(reflection_id id)
{
    auto it = classes.find(id);
    if(it != classes.end()) { return &it->second; }
    return nullptr;
}

void reflection_context::add_class(runtime_reflected_class&& cls)
{
    classes.emplace(cls.id, std::move(cls));
}

void reflection_context::clear() { classes.clear(); }

void reflection_context::print_classes() const
{
    std::cout << "Registered reflection classes:\n";

    for(const auto& [id, cls] : classes)
    {
        std::cout << "- name: " << cls.name.data() << ", reflection id: " << cls.id.get_full_hash()
            << ", type spelling: " << cls.type_spelling.data()
            << "\n";

        if(!cls.variables.empty())
        {
            std::cout << "  Variables:\n";
            for(const auto& var : cls.variables)
            {
                std::cout << "    - " << var.type_spelling.data() << " " << var.name.data() <<
                    " (offset " << var.offset <<
                    ", id: " << var.id.get_full_hash() << ")\n";
            }
        }

        if(!cls.classes.empty())
        {
            std::cout << "  Nested Classes:\n";
            for(const auto& nested : cls.classes)
            {
                std::cout << "    - name: " << nested.name.data() << ", id: " << nested.id.
                                                                                        get_full_hash()
                    <<
                    ", type spelling: " << nested.type_spelling.data() << "\n";
            }
        }

        if(!cls.functions.empty())
        {
            std::cout << "  Functions:\n";
            for(const auto& func : cls.functions)
            {
                std::cout << "    - name: " << func.name.data() << ", id: " << id.
                    get_full_hash() << ", return type: " << func.return_type_spelling.data() <<
                    ", const: " << (func.is_const ? "true" : "false") << ", static: " << (
                        func.is_static ? "true" : "false") << "\n";

                if(!func.parameter_names.empty())
                {
                    std::cout << "    parameters:\n";

                    for(rsl::size_type i = 0; i < func.parameter_names.size(); ++i)
                    {
                        std::cout << "      - " << func.parameter_types_spelling[i].data() << " " <<
                            func.parameter_names[i].data() << "\n";
                    }
                }
            }
        }
    }
}

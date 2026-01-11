class target_class
{
public:
    int int_variable;

    float very_cool_variable;
    
    void void_function(int int_parameter);

    class even_cooler_nested_class
    {
    public:
        even_cooler_nested_class() : value(0) {}

        void set_value(int v) { value = v; }

        int get_value() const { return value; }
    private:
        int value;
    };
    
private:
    char char_variable;
};

class target_class2
{
public:
    int int_variable2;

    void void_function2(int int_parameter);
private:
    char char_variable2;
};
#pragma once

class very_cool_target_class5
{
public:
    int int_variable;

    float variable;

    void void_function(int int_parameter);

    class nested_class5
    {
    public:
        nested_class() : value(0) {}

        void set_value(int v) { value = v; }

        int get_value() const { return value; }
    private:
        int value;
    };
private:
    char char_variable;
};

class target_class25
{
public:
    int int_variable2;

    static void void_function2(int int_parameter);
private:
    char char_variable2;
};

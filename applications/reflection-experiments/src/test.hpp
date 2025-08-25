#define RYTHE_STRINGIFY(x) #x

namespace rsl
{
    struct custom_attribute{};
}

#define RYTHE_DEFINE_ATTRIBUTE_WITH_PARAMS(Attrib, ...) clang::annotate(RYTHE_STRINGIFY(attributes::Attrib(__VA_ARGS__)))
#define RYTHE_DEFINE_ATTRIBUTE(Attrib) clang::annotate(RYTHE_STRINGIFY(attributes::Attrib()))


namespace attributes
{
    struct my_attrib : public rsl::custom_attribute
    {
        float f;
        int i;
        my_attrib(float flt, int integ) : f(flt), i(integ) {}
    };
}

#define my_attrib(...) RYTHE_DEFINE_ATTRIBUTE_WITH_PARAMS(my_attrib, __VA_ARGS__)
#define my_other_attrib RYTHE_DEFINE_ATTRIBUTE(my_other_attrib)

namespace rsl
{
    struct [[my_attrib(0.5f, 2)]] MyStruct
    {
        int value;
        [[my_other_attrib]] bool b;

        float my_func([[maybe_unused]] float f) { return 0.4f; }
        void my_other_func() {}
    };

    struct OtherStruct
    {
        struct ChildStruct{};
        float f;
    };
}

struct GlobalNamespaceStruct
{
    bool bb;
    unsigned uInt;
};
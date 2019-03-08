#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/msg/str/IsDefault.h"

BASIC_TEST_CONSTRUCT;

const char * BoolToString(bool && b)
{
    return (b ? "true" : "false");
}

const char * StorageToString(char ** && s)
{
    if (*s == nullptr) return "null";
    return *s;
}

template<typename TStorge>
const char * StorageToString(TStorge * && s)
{
    return *s;
}

struct TestValueIsDefault {};

template<typename TStorage>
using VariableTestStringIsDefault = basic::test::Variable<
    TStorage,
    basic::test::Value<TStorage *>,
    basic::test::Value<bool>,
    basic::test::type::Function<const char *(bool &&), &BoolToString>,
    basic::test::type::Function<const char *(TStorage *&&),
        &StorageToString>>;

typedef basic::test::msg::Argument<TestValueIsDefault,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::type::Function<4,
        basic::test::msg::arg::Value<1>>,
    basic::test::msg::arg::type::Function<3,
        basic::test::msg::arg::Value<2>>> ArgTestValueIsDefault;

typedef basic::test::msg::Base<TestValueIsDefault, char, 
    ArgTestValueIsDefault, ArgTestValueIsDefault, 
    ArgTestValueIsDefault> MessageBaseTestValueIsDefault;

template<typename... TVariables>
struct TestStringIsDefault :
    public basic::test::Message<BASIC_TEST, 
        TestStringIsDefault<TVariables...>>,
    public basic::test::Case<TestStringIsDefault<TVariables...>,
        TestValueIsDefault>,
    public basic::test::Base<TestStringIsDefault<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueIsDefault
{
public:
    using MessageBaseTestValueIsDefault::Format;
    using MessageBaseTestValueIsDefault::SetFormat;
    using MessageBaseTestValueIsDefault::Argument;
    using basic::test::Case<TestStringIsDefault<TVariables...>,
        TestValueIsDefault>::Run;
    using basic::test::Base<TestStringIsDefault<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringIsDefault(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringIsDefault< 
            TVariables...>>(*this),
        basic::test::Case<TestStringIsDefault<TVariables...>,
            TestValueIsDefault>(*this),
        basic::test::Base<TestStringIsDefault<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;
        
        TestValueIsDefault testValueIsDefault;
        SetFormat(info, testValueIsDefault, "test %s {%s} is_default "
            "is same with %s\n");
        SetFormat(debug, testValueIsDefault, "test %s {%s} is_default "
            "is same with %s\n");
        SetFormat(err, testValueIsDefault, "Error check %s {%s} is_default "
            "is not same with %s\n");
    }
    template<typename TStorage>
    bool Result(const TestValueIsDefault &, VariableTestStringIsDefault<
        TStorage> & var)
    {
        auto & storage = *basic::test::var::At<1>(var).Get().Get();
        auto test = basic::test::var::At<2>(var).Get().Get();
        bool get = basic::err::msg::str::IsDefault(storage);
        return get == test;
    }
};

char tmp[] = "test";

char * obj1_1 = nullptr;
char * obj1_2 = tmp;
char obj1_3[] = {'\0'};
char obj1_4[] = "test";

BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("char [1]", char [1]);
BASIC_TEST_TYPE_NAME("char [5]", char [5]);

typedef VariableTestStringIsDefault<char *> T1Var1;
typedef VariableTestStringIsDefault<char[1]> T1Var2;
typedef VariableTestStringIsDefault<char[5]> T1Var3;

T1Var1 t1_var1{&obj1_1, true};
T1Var1 t1_var2{&obj1_2, false};
T1Var2 t1_var3{&obj1_3, true};
T1Var3 t1_var4{&obj1_4, false};

REGISTER_TEST(t1, new TestStringIsDefault<T1Var1, T1Var1, T1Var2, 
    T1Var3>(t1_var1, t1_var2, t1_var3, t1_var4));

int main()
{
    return RUN_TEST();
}

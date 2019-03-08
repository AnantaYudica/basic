#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/defn/type/Char.h"
#include "err/msg/str/Value.h"

#include <cstring>

BASIC_TEST_CONSTRUCT;

struct TestValueValue {};

template<typename TStorage>
const char * StorgeToString(TStorage * && storage)
{
    return (*storage == nullptr ? "null" : *storage);
}

template<typename TStorage>
using VariableTestStringValue = basic::test::Variable<
    TStorage,
    basic::test::Value<TStorage *>,
    basic::test::Value<const basic::err::defn::type::Char *>,
    basic::test::type::Function<const char * (TStorage * &&),
        &StorgeToString>>;

typedef basic::test::msg::Argument<TestValueValue,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::type::Function<3,
        basic::test::msg::arg::Value<1>>,
    basic::test::msg::arg::Value<2>> ArgTestValueValue;

typedef basic::test::msg::Base<TestValueValue, char, 
    ArgTestValueValue, ArgTestValueValue, ArgTestValueValue> 
        MessageBaseTestValueValue;

template<typename... TVariables>
struct TestStringValue :
    public basic::test::Message<BASIC_TEST, 
        TestStringValue<TVariables...>>,
    public basic::test::Case<TestStringValue<TVariables...>,
        TestValueValue>,
    public basic::test::Base<TestStringValue<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueValue
{
public:
    using MessageBaseTestValueValue::Format;
    using MessageBaseTestValueValue::SetFormat;
    using MessageBaseTestValueValue::Argument;
    using basic::test::Case<TestStringValue<TVariables...>,
        TestValueValue>::Run;
    using basic::test::Base<TestStringValue<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringValue(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringValue< 
            TVariables...>>(*this),
        basic::test::Case<TestStringValue<TVariables...>,
            TestValueValue>(*this),
        basic::test::Base<TestStringValue<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "test value "
            "%s {\"%s\"} is same with \"%s\"\n");
        SetFormat(debug, testValueValue, "test value "
            "%s {\"%s\"} is same with \"%s\"\n");
        SetFormat(err, testValueValue, "Error value "
            "%s {\"%s\"} is not same with \"%s\"\n");
    }
    template<typename TStorage>
    bool Result(const TestValueValue &, 
        VariableTestStringValue<TStorage> & var)
    {
        TStorage & storage = *basic::test::var::At<1>(var).Get().Get();
        const basic::err::defn::type::Char * value = 
            basic::test::var::At<2>(var).Get().Get();
        auto get = basic::err::msg::str::Value(storage);
        return strcmp(get, value) == 0;
    }
};

BASIC_TEST_TYPE_NAME("const char *", const char *);
BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("char [11]", char [11]);
BASIC_TEST_TYPE_NAME("char [4]", char [4]);

char * obj1_1 = new char[5];
char * obj1_2 = new char[5];
char * obj1_3 = nullptr;
char obj1_4[11];
char obj1_5[4];

typedef VariableTestStringValue<char *> T1Var1;
typedef VariableTestStringValue<char [11]> T1Var2;
typedef VariableTestStringValue<char [4]> T1Var3;

T1Var1 t1_var1{&obj1_1, "test"};
T1Var1 t1_var2{&obj1_2, "12"};
T1Var1 t1_var3{&obj1_3, ""};
T1Var2 t1_var4{&obj1_4, ""};
T1Var3 t1_var5{&obj1_5, "123"};

REGISTER_TEST(t1, new TestStringValue<T1Var1, T1Var1, T1Var1, 
    T1Var2, T1Var3>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

int main()
{
    std::memcpy(obj1_1, "test", 5);
    std::memcpy(obj1_2, "12", 3);
    std::memcpy(obj1_4, "", 1);
    std::memcpy(obj1_5, "123", 4);
    auto ret = RUN_TEST();
    if (obj1_1 != nullptr)delete[] obj1_1;
    if (obj1_2 != nullptr)delete[] obj1_2;
    return ret;
}


#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/msg/str/Copy.h"

#include <cstring>
#include <string>
#include <utility>

BASIC_TEST_CONSTRUCT;

const char * CopyVariableToString(const char * && cstr)
{
    return cstr;
}

const char * CopyVariableToString(const std::string && str)
{
    return str.c_str();
}


struct TestValueCopy {};

template<typename TStorage, typename TCopyVar>
using VariableTestStringCopy = basic::test::Variable<
    TStorage,
    TCopyVar,
    basic::test::Value<TStorage *>,
    basic::test::Value<std::size_t>,
    basic::test::Value<TCopyVar>,
    basic::test::type::Function<const char *(TCopyVar &&), 
        &CopyVariableToString>>;

typedef basic::test::msg::Argument<TestValueCopy,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::type::Name<1>,
    basic::test::msg::arg::type::Function<5,
    basic::test::msg::arg::Value<4>>> ArgTestValueCopy;

typedef basic::test::msg::Base<TestValueCopy, char, 
    ArgTestValueCopy, ArgTestValueCopy, ArgTestValueCopy> 
        MessageBaseTestValueCopy;

template<typename... TVariables>
struct TestStringCopy :
    public basic::test::Message<BASIC_TEST, 
        TestStringCopy<TVariables...>>,
    public basic::test::Case<TestStringCopy<TVariables...>,
        TestValueCopy>,
    public basic::test::Base<TestStringCopy<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueCopy
{
public:
    using MessageBaseTestValueCopy::Format;
    using MessageBaseTestValueCopy::SetFormat;
    using MessageBaseTestValueCopy::Argument;
    using basic::test::Case<TestStringCopy<TVariables...>,
        TestValueCopy>::Run;
    using basic::test::Base<TestStringCopy<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringCopy(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringCopy< 
            TVariables...>>(*this),
        basic::test::Case<TestStringCopy<TVariables...>,
            TestValueCopy>(*this),
        basic::test::Base<TestStringCopy<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestValueCopy testValueCopy;
        SetFormat(info, testValueCopy, "test copy "
            "%s with %s {\"%s\"} pass\n");
        SetFormat(debug, testValueCopy, "test copy "
            "%s with %s {\"%s\"} pass\n");
        SetFormat(error, testValueCopy, "Error copy "
            "%s with %s {\"%s\"}\n");
    }
    template<typename TStorage, typename TCopyVar>
    bool Result(const TestValueCopy &, VariableTestStringCopy<TStorage, 
        TCopyVar> & var)
    {
        auto & storage = *basic::test::var::At<2>(var).Get().Get();
        auto & size = basic::test::var::At<3>(var).Get().Get();
        auto & copy_var = basic::test::var::At<4>(var).Get().Get();
        basic::error::msg::str::Copy(storage, size, copy_var);
        return std::strcmp(storage, CopyVariableToString(std::move(copy_var))) == 0;
    }
};

BASIC_TEST_TYPE_NAME("const char *", const char *);
BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("const std::string", const std::string);
BASIC_TEST_TYPE_NAME("char [11]", char [11]);
BASIC_TEST_TYPE_NAME("char [6]", char [6]);

char * obj1_1 = new char[5];
char * obj1_2 = new char[5];
char obj1_3[11];
char obj1_4[6];

typedef VariableTestStringCopy<char *, const char *> T1Var1;
typedef VariableTestStringCopy<char *, const std::string> T1Var2;
typedef VariableTestStringCopy<char [11], const char *> T1Var3;
typedef VariableTestStringCopy<char [6], const std::string> T1Var4;

T1Var1 t1_var1{&obj1_1, 5, "1234"};
T1Var2 t1_var2{&obj1_2, 3, "41"};
T1Var3 t1_var3{&obj1_3, 11, "aabbccddee"};
T1Var4 t1_var4{&obj1_4, 4, "248"};

REGISTER_TEST(t1, new TestStringCopy<T1Var1, T1Var2, T1Var3, T1Var4>(t1_var1, 
    t1_var2, t1_var3, t1_var4));

int main()
{
    auto ret = RUN_TEST();
    if (obj1_1 != nullptr)delete[] obj1_1;
    if (obj1_2 != nullptr)delete[] obj1_2;
    return ret;
}


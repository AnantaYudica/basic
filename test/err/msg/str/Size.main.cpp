#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/msg/str/Size.h"

#include <string>

BASIC_TEST_CONSTRUCT;

struct TestValueSize {};

template<typename TStorage>
const char * StorgeToString(TStorage * && storage)
{
    return (*storage == nullptr ? "null" : *storage);
}

const char * StorgeToString(std::string * && storage)
{
    return storage->c_str();
}

template<typename TStorage>
using VariableTestStringSize = basic::test::Variable<
    TStorage,
    basic::test::Value<TStorage *>,
    basic::test::Value<std::size_t>,
    basic::test::type::Function<const char * (TStorage * &&),
        &StorgeToString>>;

typedef basic::test::msg::Argument<TestValueSize,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::type::Function<3,
        basic::test::msg::arg::Value<1>>,
    basic::test::msg::arg::Value<2>> ArgTestValueSize;

typedef basic::test::msg::Base<TestValueSize, char, 
    ArgTestValueSize, ArgTestValueSize, ArgTestValueSize> 
        MessageBaseTestValueSize;

template<typename... TVariables>
struct TestStringSize :
    public basic::test::Message<BASIC_TEST, 
        TestStringSize<TVariables...>>,
    public basic::test::Case<TestStringSize<TVariables...>,
        TestValueSize>,
    public basic::test::Base<TestStringSize<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueSize
{
public:
    using MessageBaseTestValueSize::Format;
    using MessageBaseTestValueSize::SetFormat;
    using MessageBaseTestValueSize::Argument;
    using basic::test::Case<TestStringSize<TVariables...>,
        TestValueSize>::Run;
    using basic::test::Base<TestStringSize<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringSize(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringSize< 
            TVariables...>>(*this),
        basic::test::Case<TestStringSize<TVariables...>,
            TestValueSize>(*this),
        basic::test::Base<TestStringSize<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueSize testValueSize;
        SetFormat(info, testValueSize, "test size "
            "%s {\"%s\"} is equal with %d\n");
        SetFormat(debug, testValueSize, "test size "
            "%s {\"%s\"} is equal with %d\n");
        SetFormat(err, testValueSize, "Error size "
            "%s {\"%s\"} is not equal with %d\n");
    }
    template<typename TStorage>
    bool Result(const TestValueSize &, VariableTestStringSize<TStorage> & var)
    {
        TStorage & storage = *basic::test::var::At<1>(var).Get().Get();
        std::size_t & size = basic::test::var::At<2>(var).Get().Get();
        auto get = basic::err::msg::str::Size(storage);
        return get == size;
    }
};

BASIC_TEST_TYPE_NAME("const char *", const char *);
BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("const std::string", const std::string);
BASIC_TEST_TYPE_NAME("std::string", std::string);
BASIC_TEST_TYPE_NAME("char [11]", char [11]);
BASIC_TEST_TYPE_NAME("char [4]", char [4]);

char * obj1_1 = new char[5];
char * obj1_2 = new char[5];
char * obj1_3 = nullptr;
char obj1_4[11];
char obj1_5[4];
std::string obj1_6{"test"};

typedef VariableTestStringSize<char *> T1Var1;
typedef VariableTestStringSize<char [11]> T1Var2;
typedef VariableTestStringSize<char [4]> T1Var3;
typedef VariableTestStringSize<std::string> T1Var4;

T1Var1 t1_var1{&obj1_1, 4};
T1Var1 t1_var2{&obj1_2, 2};
T1Var1 t1_var3{&obj1_3, 0};
T1Var2 t1_var4{&obj1_4, 0};
T1Var3 t1_var5{&obj1_5, 3};
T1Var4 t1_var6{&obj1_6, 4};

REGISTER_TEST(t1, new TestStringSize<T1Var1, T1Var1, T1Var1, 
    T1Var2, T1Var3, T1Var4>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5, 
    t1_var6));

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


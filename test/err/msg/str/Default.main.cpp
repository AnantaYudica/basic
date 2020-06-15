#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/msg/str/Default.h"

#include <cstring>

BASIC_TEST_CONSTRUCT;

struct TestValueDefault {};

template<typename TStorage, typename TDefault, typename TChar = char>
using VariableTestStringDefault = basic::test::Variable<
    TStorage,
    basic::test::Value<TDefault *>>;

typedef basic::test::msg::Argument<TestValueDefault,
    basic::test::msg::arg::type::Name<0>> ArgTestValueDefault;

typedef basic::test::msg::Base<TestValueDefault, char, 
    ArgTestValueDefault, ArgTestValueDefault, 
    ArgTestValueDefault> MessageBaseTestValueDefault;

template<typename... TVariables>
struct TestStringDefault :
    public basic::test::Message<BASIC_TEST, 
        TestStringDefault<TVariables...>>,
    public basic::test::Case<TestStringDefault<TVariables...>,
        TestValueDefault>,
    public basic::test::Base<TestStringDefault<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDefault
{
public:
    using MessageBaseTestValueDefault::Format;
    using MessageBaseTestValueDefault::SetFormat;
    using MessageBaseTestValueDefault::Argument;
    using basic::test::Case<TestStringDefault<TVariables...>,
        TestValueDefault>::Run;
    using basic::test::Base<TestStringDefault<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringDefault(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringDefault< 
            TVariables...>>(*this),
        basic::test::Case<TestStringDefault<TVariables...>,
            TestValueDefault>(*this),
        basic::test::Base<TestStringDefault<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;
        
        TestValueDefault testValueDefault;
        SetFormat(info, testValueDefault, "test default "
            "%s pass\n");
        SetFormat(debug, testValueDefault, "test default "
            "%s pass\n");
        SetFormat(err, testValueDefault, "Error default "
            "%s \n");
    }
    template<typename TDefault>
    bool Result(const TestValueDefault &, VariableTestStringDefault<
        char *, TDefault> & var)
    {
        auto storage_default = basic::test::var::At<1>(var).Get().Get();
        char * storage;
        basic::err::msg::str::Default(storage);
        return storage == *storage_default;
    }
    template<typename TDefault, std::size_t Size>
    bool Result(const TestValueDefault &, VariableTestStringDefault<
        char[Size], TDefault> & var)
    {
        auto storage_default = basic::test::var::At<1>(var).Get().Get();
        char storage[Size];
        basic::err::msg::str::Default(storage);
        return std::strcmp(storage, *storage_default) == 0;
    }
};

BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("char [5]", char [5]);

const char * pointer_default = nullptr;
char array_default[] = {'\0'};

typedef VariableTestStringDefault<char *, const char *> T1Var1;
typedef VariableTestStringDefault<char[5], char[1]> T1Var2;

T1Var1 t1_var1{&pointer_default};
T1Var2 t1_var2{&array_default};

REGISTER_TEST(t1, new TestStringDefault<T1Var1, T1Var2>(t1_var1, t1_var2));

int main()
{
    return RUN_TEST();
}

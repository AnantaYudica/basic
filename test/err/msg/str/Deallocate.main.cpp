#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/msg/str/Deallocate.h"

#include <cstring>

BASIC_TEST_CONSTRUCT;

struct TestValueDeallocate {};

template<typename TStorage, typename TDefault, typename TChar = char>
using VariableTestStringDeallocate = basic::test::Variable<
    TStorage,
    basic::test::Value<TStorage *>,
    basic::test::Value<TDefault *>>;

typedef basic::test::msg::Argument<TestValueDeallocate,
    basic::test::msg::arg::type::Name<0>> ArgTestValueDeallocate;

typedef basic::test::msg::Base<TestValueDeallocate, char, 
    ArgTestValueDeallocate, ArgTestValueDeallocate, 
    ArgTestValueDeallocate> MessageBaseTestValueDeallocate;

template<typename... TVariables>
struct TestStringDeallocate :
    public basic::test::Message<BASIC_TEST, 
        TestStringDeallocate<TVariables...>>,
    public basic::test::Case<TestStringDeallocate<TVariables...>,
        TestValueDeallocate>,
    public basic::test::Base<TestStringDeallocate<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDeallocate
{
public:
    using MessageBaseTestValueDeallocate::Format;
    using MessageBaseTestValueDeallocate::SetFormat;
    using MessageBaseTestValueDeallocate::Argument;
    using basic::test::Case<TestStringDeallocate<TVariables...>,
        TestValueDeallocate>::Run;
    using basic::test::Base<TestStringDeallocate<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringDeallocate(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringDeallocate< 
            TVariables...>>(*this),
        basic::test::Case<TestStringDeallocate<TVariables...>,
            TestValueDeallocate>(*this),
        basic::test::Base<TestStringDeallocate<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;
        
        TestValueDeallocate testValueDeallocate;
        SetFormat(info, testValueDeallocate, "test deallocate "
            "%s pass\n");
        SetFormat(debug, testValueDeallocate, "test deallocate "
            "%s pass\n");
        SetFormat(err, testValueDeallocate, "Error deallocate "
            "%s \n");
    }
    template<typename TDefault>
    bool Result(const TestValueDeallocate &, VariableTestStringDeallocate<
        char *, TDefault> & var)
    {
        auto & storage = *basic::test::var::At<1>(var).Get().Get();
        auto storage_default = basic::test::var::At<2>(var).Get().Get();
        basic::err::msg::str::Deallocate(storage);
        return storage == *storage_default;
    }
    template<typename TDefault, std::size_t Size>
    bool Result(const TestValueDeallocate &, VariableTestStringDeallocate<
        char[Size], TDefault> & var)
    {
        auto & storage = *basic::test::var::At<1>(var).Get().Get();
        auto storage_default = basic::test::var::At<2>(var).Get().Get();
        basic::err::msg::str::Deallocate(storage);
        return std::strcmp(storage, *storage_default) == 0;
    }
};

BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("char [5]", char [5]);

const char * pointer_default = nullptr;
char array_default[] = {'\0'};

char * obj1_1 = new char[5];
char obj1_2[] = "tset";

typedef VariableTestStringDeallocate<char *, const char *> T1Var1;
typedef VariableTestStringDeallocate<char[5], char[1]> T1Var2;

T1Var1 t1_var1{&obj1_1, &pointer_default};
T1Var2 t1_var2{&obj1_2, &array_default};

REGISTER_TEST(t1, new TestStringDeallocate<T1Var1, T1Var2>(t1_var1, t1_var2));

int main()
{
    std::memcpy(obj1_1, "test", 5);
    auto ret = RUN_TEST();
    if (obj1_1 != nullptr)delete[] obj1_1;
    return ret;
}

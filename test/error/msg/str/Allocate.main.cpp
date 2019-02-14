#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/msg/str/Allocate.h"

BASIC_TEST_CONSTRUCT;

struct TestValueAllocate {};

template<typename TStorage>
using VariableTestStringAllocate = basic::test::Variable<
    TStorage,
    basic::test::Value<TStorage *>,
    basic::test::Value<std::size_t>>;

typedef basic::test::msg::Argument<TestValueAllocate,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::Value<2>> ArgTestValueAllocate;

typedef basic::test::msg::Base<TestValueAllocate, char, 
    ArgTestValueAllocate, ArgTestValueAllocate, 
    ArgTestValueAllocate> MessageBaseTestValueAllocate;

template<typename... TVariables>
struct TestStringAllocate :
    public basic::test::Message<BASIC_TEST, 
        TestStringAllocate<TVariables...>>,
    public basic::test::Case<TestStringAllocate<TVariables...>,
        TestValueAllocate>,
    public basic::test::Base<TestStringAllocate<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueAllocate
{
public:
    using MessageBaseTestValueAllocate::Format;
    using MessageBaseTestValueAllocate::SetFormat;
    using MessageBaseTestValueAllocate::Argument;
    using basic::test::Case<TestStringAllocate<TVariables...>,
        TestValueAllocate>::Run;
    using basic::test::Base<TestStringAllocate<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringAllocate(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringAllocate< 
            TVariables...>>(*this),
        basic::test::Case<TestStringAllocate<TVariables...>,
            TestValueAllocate>(*this),
        basic::test::Base<TestStringAllocate<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        TestValueAllocate testValueAllocate;
        SetFormat(info, testValueAllocate, "test allocation "
            "%s with size %d pass\n");
        SetFormat(debug, testValueAllocate, "test allocation "
            "%s with size %d pass\n");
        SetFormat(error, testValueAllocate, "Error allocation "
            "%s with size %d\n");
    }
    template<typename TStorage>
    bool Result(const TestValueAllocate &, VariableTestStringAllocate<
        TStorage> & var)
    {
        auto * obj_ptr = basic::test::var::At<1>(var).Get().Get();
        auto size = basic::test::var::At<2>(var).Get().Get();
        if (obj_ptr == nullptr)return false;
        basic::error::msg::str::Allocate(*obj_ptr, size);
        if (obj_ptr == nullptr)return false;
        return *obj_ptr[0] == '\0';
    }
};

BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("char [100]", char [100]);
BASIC_TEST_TYPE_NAME("char [100]", char [50]);

char * obj1_1 = nullptr;
char obj1_2[100];
char obj1_3[50];

typedef VariableTestStringAllocate<char *> T1Var1;
typedef VariableTestStringAllocate<char[100]> T1Var2;
typedef VariableTestStringAllocate<char[50]> T1Var3;

T1Var1 t1_var1{&obj1_1, 100};
T1Var2 t1_var2{&obj1_2, 100};
T1Var3 t1_var3{&obj1_3, 100};

REGISTER_TEST(t1, new TestStringAllocate<T1Var1, T1Var2, T1Var3>(t1_var1, 
    t1_var2, t1_var3));

int main()
{
    auto ret = RUN_TEST();
    if (obj1_1 != nullptr)delete obj1_1;
    return ret;
}

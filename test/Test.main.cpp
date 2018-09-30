#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include <typeinfo>

struct TestA1 {};
struct TestA2 {};
struct TestA3 {};

typedef basic::test::msg::Argument<TestA1, 
    basic::test::msg::arg::type::Name<0>> InfoArgTestA1;
typedef basic::test::msg::Argument<TestA2, 
    basic::test::msg::arg::type::Name<0>> InfoArgTestA2;
typedef basic::test::msg::Argument<TestA3, 
    basic::test::msg::arg::type::Name<0>> InfoArgTestA3;

typedef basic::test::msg::Argument<TestA1, 
    basic::test::msg::arg::type::Value<1>> DebugArgTestA1;
typedef basic::test::msg::Argument<TestA2, 
    basic::test::msg::arg::type::Value<1>> DebugArgTestA2;
typedef basic::test::msg::Argument<TestA3, 
    basic::test::msg::arg::type::Value<1>> DebugArgTestA3;
    
typedef basic::test::msg::Argument<TestA1, 
    basic::test::msg::arg::Value<2>> ErrorArgTestA1;
typedef basic::test::msg::Argument<TestA2, 
    basic::test::msg::arg::Value<2>> ErrorArgTestA2;
typedef basic::test::msg::Argument<TestA3, 
    basic::test::msg::arg::Value<2>> ErrorArgTestA3;

typedef basic::test::msg::Base<TestA1, char, InfoArgTestA1,
    DebugArgTestA1, ErrorArgTestA1> MessageBaseTestA1;
typedef basic::test::msg::Base<TestA2, char, InfoArgTestA2,
    DebugArgTestA2, ErrorArgTestA2> MessageBaseTestA2;
typedef basic::test::msg::Base<TestA3, char, InfoArgTestA3,
    DebugArgTestA3, ErrorArgTestA3> MessageBaseTestA3;

template<typename... TVariables>
class TestA :
    public MessageBaseTestA1,
    public MessageBaseTestA2,
    public MessageBaseTestA3,
    public basic::test::Message<BASIC_TEST, TestA<TVariables...>>,
    public basic::test::Case<TestA<TVariables...>,
        basic::test::type::Parameter<TestA1, TestA2, TestA3>>,
    public basic::test::Base<TestA<TVariables...>, TVariables...>
{
public:
    using MessageBaseTestA1::Format;
    using MessageBaseTestA2::Format;
    using MessageBaseTestA3::Format;
    using MessageBaseTestA1::SetFormat;
    using MessageBaseTestA2::SetFormat;
    using MessageBaseTestA3::SetFormat;
    using MessageBaseTestA1::Argument;
    using MessageBaseTestA2::Argument;
    using MessageBaseTestA3::Argument;
    using basic::test::Case<TestA<TVariables...>,
        basic::test::type::Parameter<TestA1, TestA2, TestA3>>::Run;
    using basic::test::Base<TestA<TVariables...>, TVariables...>::Run;
public:
    TestA(TVariables&... var) :
        basic::test::Message<BASIC_TEST, TestA<TVariables...>>(*this),
        basic::test::Case<TestA<TVariables...>,
            basic::test::type::Parameter<TestA1, TestA2, TestA3>>(*this),
        basic::test::Base<TestA<TVariables...>, TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        TestA1 testa1;
        TestA2 testa2;
        TestA3 testa3;

        basic::test::msg::Format<char> formatTestA1("Test TestA1 : %s\n");
        SetFormat(debug, testa1, {formatTestA1, 
            formatTestA1.Size() + 10, "type %d"});
        SetFormat(info, testa1, std::move(formatTestA1));
        SetFormat(error, testa1, "Error TestA1 msg %d\n");

        basic::test::msg::Format<char> formatTestA2("Test TestA2 : %s\n");
        SetFormat(debug, testa2, {formatTestA2, 
            formatTestA2.Size() + 10, "type %d"});
        SetFormat(info, testa2, std::move(formatTestA2));
        SetFormat(error, testa2, "Error TestA2 msg %d\n");

        basic::test::msg::Format<char> formatTestA3("Test TestA3 : %s\n");
        SetFormat(debug, testa3, {formatTestA3, 
            formatTestA3.Size() + 10, "type %d"});
        SetFormat(info, testa3, std::move(formatTestA3));
        SetFormat(error, testa3, "Error TestA3 msg %d\n");
    }
public:
    template<typename T1, typename T2, T2 T2Value, typename T3>
    bool Result(const TestA1&, basic::test::Variable<T1, 
        basic::test::type::Value<T2, T2Value>,
        basic::test::Value<T3>>& var)
    {
        return typeid(T1).hash_code() == typeid(int).hash_code();
    }
    template<typename T1, typename T2, T2 T2Value, typename T3>
    bool Result(const TestA2&, basic::test::Variable<T1, 
        basic::test::type::Value<T2, T2Value>,
        basic::test::Value<T3>>& var)
    {
        return T2Value == 4;
    }
    template<typename T1, typename T2, T2 T2Value, typename T3>
    bool Result(const TestA3&, basic::test::Variable<T1, 
        basic::test::type::Value<T2, T2Value>,
        basic::test::Value<T3>>& var)
    {
        return basic::test::var::At<2>(var).Get().Get() == 14;
    }
};

template<typename T1, typename T2, T2 T2Value, typename T3>
using VariableTestA = basic::test::Variable<T1, 
    basic::test::type::Value<T2, T2Value>,
    basic::test::Value<T3>>;

VariableTestA<int, int, 4, int> var1(14);
VariableTestA<char, int, 4, int> var2(14);
VariableTestA<int, int, 14, int> var3(14);
VariableTestA<int, int, 4, int> var4(4);

REGISTER_TEST(t1, new TestA<VariableTestA<int, int, 4, int>,
    VariableTestA<char, int, 4, int>,
    VariableTestA<int, int, 14, int>,
    VariableTestA<int, int, 4, int>>(var1, var2, var3, var4));


int main()
{
    RUN_TEST();
}
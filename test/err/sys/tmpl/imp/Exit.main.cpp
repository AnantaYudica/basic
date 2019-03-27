#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/intf/Exit.h"
#include "err/sys/tmpl/imp/Exit.h"
#include "err/sys/tmpl/imp/exit/HasCleanup.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

struct CategoryTrait1 :
    basic::err::intf::Exit
{
    static int m_sig;
    void Cleanup(int sig) noexcept
    {
        m_sig = sig;
    }
};

int CategoryTrait1::m_sig = 0; 

struct CategoryTrait2
{
    static int m_sig;
};

int CategoryTrait2::m_sig = 0;

struct TestValueSignal {};

template<typename TCategoryTrait>
using VariableTestExit = basic::test::Variable<
    TCategoryTrait,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    int,
    basic::test::Value<int>,
    basic::test::Value<int>>;

constexpr std::size_t ICategoryTraitType = 0;
constexpr std::size_t ITmplCategoryType = 1;
constexpr std::size_t ISignalType = 2;
constexpr std::size_t ISignalValue = 3;
constexpr std::size_t ISignalCheckValue = 4;

typedef basic::test::msg::Argument<TestValueSignal,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ISignalType>,
    basic::test::msg::arg::Value<ISignalValue>,
    basic::test::msg::arg::Value<ISignalCheckValue>> 
        ArgTestValueSignal;

typedef basic::test::msg::Base<TestValueSignal, char,
    ArgTestValueSignal, ArgTestValueSignal, ArgTestValueSignal> 
        MessageBaseTestValueSignal;

template<typename TCases, typename... TVariables>
struct TestImpExit :
    public basic::test::Message<BASIC_TEST, TestImpExit<TCases, 
        TVariables...>>,
    public basic::test::Case<TestImpExit<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestImpExit<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueSignal
{
public:
    using basic::test::Case<TestImpExit<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestImpExit<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestValueSignal::Argument;
    using MessageBaseTestValueSignal::Format;
    using MessageBaseTestValueSignal::SetFormat;
public:
    TestImpExit(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestImpExit<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestImpExit<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestImpExit<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueSignal testValueSignal;
        SetFormat(info, testValueSignal, "Test call %s::"
            "Cleanup(%s{%d}) and value signal is %d\n");
        SetFormat(debug, testValueSignal, "Test call %s::"
            "Cleanup(%s{%d}) and value signal is %d\n");
        SetFormat(err, testValueSignal, "Error call %s::"
            "Cleanup(%s{%d}) and value signal is not %d\n");
    }
    template<typename TCategoryTrait>
    bool Result(const TestValueSignal &, 
        VariableTestExit<TCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ISignalType,
            VariableTestExit<TCategoryTrait>>::Type SignalType;
        auto & signal_check_value = basic::test::var::
            At<ISignalCheckValue>(var).Get().Get();
        auto & signal_value = basic::test::var::
            At<ISignalValue>(var).Get().Get();
        auto & exit_intf = static_cast<basic::err::intf::Exit &>(
            const_cast<basic::err::sys::tmpl::Category<TCategoryTrait> &>(
            basic::err::sys::tmpl::Category<TCategoryTrait>::GetInstance()));
        exit_intf.Cleanup(signal_value);
        auto & result = TCategoryTrait::m_sig;
        return signal_check_value == result;
    }
};

typedef basic::test::type::Parameter<
    TestValueSignal> Case1;

typedef VariableTestExit<CategoryTrait1> T1Var1;
typedef VariableTestExit<CategoryTrait2> T1Var2;

int sig1 = 4;
int sig2 = 0;

T1Var1 t1_var1{sig1, sig1};
T1Var2 t1_var2{sig1, sig2};

REGISTER_TEST(t1, new TestImpExit<Case1, T1Var1, T1Var2>(t1_var1, t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);

BASIC_TEST_TYPE_NAME("signed char", signed char);
BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("unsigned char", unsigned char);
BASIC_TEST_TYPE_NAME("short", short);
BASIC_TEST_TYPE_NAME("unsigned short", unsigned short);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("unsigned int", unsigned int);
BASIC_TEST_TYPE_NAME("long", long);
BASIC_TEST_TYPE_NAME("unsigned long", unsigned long);
BASIC_TEST_TYPE_NAME("long long", long long);
BASIC_TEST_TYPE_NAME("unsigned long long", unsigned long long);

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::Category<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::Category<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};



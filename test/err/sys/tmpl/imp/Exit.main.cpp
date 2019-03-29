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

struct TestBaseOfCategoryBase {};
struct TestBaseOfInterfaceExit {};
struct TestValueSignal {};

template<typename TCategoryTrait>
using VariableTestExit = basic::test::Variable<
    TCategoryTrait,
    basic::err::sys::tmpl::categ::Base<TCategoryTrait>,
    basic::err::intf::Exit,
    basic::err::sys::tmpl::imp::Exit<TCategoryTrait>,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    int,
    basic::test::Value<int>,
    basic::test::Value<int>>;

constexpr std::size_t ICategoryTraitType = 0;
constexpr std::size_t ITmplCategoryBaseType = 1;
constexpr std::size_t IInterfaceExitType = 2;
constexpr std::size_t ITmplImpExitType = 3;
constexpr std::size_t ITmplCategoryType = 4;
constexpr std::size_t ISignalType = 5;
constexpr std::size_t ISignalValue = 6;
constexpr std::size_t ISignalCheckValue = 7;

typedef basic::test::msg::Argument<TestBaseOfCategoryBase,
    basic::test::msg::arg::type::Name<ITmplImpExitType>,
    basic::test::msg::arg::type::Name<ITmplCategoryBaseType>>
        ArgTestBaseOfCategoryBase;

typedef basic::test::msg::Base<TestBaseOfCategoryBase, char, 
    ArgTestBaseOfCategoryBase, ArgTestBaseOfCategoryBase, 
    ArgTestBaseOfCategoryBase> MessageBaseTestBaseOfCategoryBase;

typedef basic::test::msg::Argument<TestBaseOfInterfaceExit,
    basic::test::msg::arg::type::Name<ITmplImpExitType>,
    basic::test::msg::arg::type::Name<IInterfaceExitType>>
        ArgTestBaseOfInterfaceExit;

typedef basic::test::msg::Base<TestBaseOfInterfaceExit, char, 
    ArgTestBaseOfInterfaceExit, ArgTestBaseOfInterfaceExit, 
    ArgTestBaseOfInterfaceExit> MessageBaseTestBaseOfInterfaceExit;

typedef basic::test::msg::Argument<TestValueSignal,
    basic::test::msg::arg::type::Name<ITmplImpExitType>,
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
    public MessageBaseTestBaseOfCategoryBase,
    public MessageBaseTestBaseOfInterfaceExit,
    public MessageBaseTestValueSignal
{
public:
    using basic::test::Case<TestImpExit<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestImpExit<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfCategoryBase::Argument;
    using MessageBaseTestBaseOfCategoryBase::Format;
    using MessageBaseTestBaseOfCategoryBase::SetFormat;
    using MessageBaseTestBaseOfInterfaceExit::Argument;
    using MessageBaseTestBaseOfInterfaceExit::Format;
    using MessageBaseTestBaseOfInterfaceExit::SetFormat;
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

        TestBaseOfCategoryBase testBaseOfCategoryBase;
        SetFormat(info, testBaseOfCategoryBase, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfCategoryBase, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfCategoryBase, 
            "Error Test %s is not base of %s\n");

        TestBaseOfInterfaceExit testBaseOfInterfaceExit;
        SetFormat(info, testBaseOfInterfaceExit, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfInterfaceExit, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfInterfaceExit, 
            "Error Test %s is not base of %s\n");

        TestValueSignal testValueSignal;
        SetFormat(info, testValueSignal, "Test call %s::"
            "Cleanup(%s{%d}) and value signal is %d\n");
        SetFormat(debug, testValueSignal, "Test call %s::"
            "Cleanup(%s{%d}) and value signal is %d\n");
        SetFormat(err, testValueSignal, "Error call %s::"
            "Cleanup(%s{%d}) and value signal is not %d\n");
    }
    template<typename TCategoryTrait>
    bool Result(const TestBaseOfCategoryBase &, 
        VariableTestExit<TCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ITmplCategoryBaseType,
            VariableTestExit<TCategoryTrait>>::Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::imp::
            Exit<TCategoryTrait>>::value;
    }
    template<typename TCategoryTrait>
    bool Result(const TestBaseOfInterfaceExit &, 
        VariableTestExit<TCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IInterfaceExitType,
            VariableTestExit<TCategoryTrait>>::Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::imp::
            Exit<TCategoryTrait>>::value;
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
    TestBaseOfCategoryBase,
    TestBaseOfInterfaceExit,
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

BASIC_TEST_TYPE_NAME("basic::err::intf::Exit", basic::err::intf::Exit);

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

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::categ::Base<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::Base<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg, bool B>
struct basic::test::type::Name<basic::err::sys::tmpl::imp::Exit<TArg, B>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::imp::Exit<%s, %s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + 
            tArgCStr.Size() + 5, _format, *tArgCStr, (B?"true":"false"));
    }
};


#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/Instance.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include <type_traits>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;
typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;

struct CategoryTrait1
{
    int m_value;
    CategoryTrait1(int val) : m_value(val){};
    CategoryTrait1() : m_value(44){};
    CategoryTrait1(const CategoryTrait1 & cpy) : m_value(cpy.m_value) {};
    CategoryTrait1(CategoryTrait1 && mov) : m_value(mov.m_value) {}
    static CategoryTrait1 Instance()
    {
        return {4};
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    int m_value;
    CategoryTrait2() : m_value(44) {};
    CategoryTrait2(const CategoryTrait2 & cpy) : m_value(cpy.m_value) {};
    CategoryTrait2(CategoryTrait2 && mov) : m_value(mov.m_value) {}
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct TestValueInstance {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait>
using VariableTestInstance = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    basic::test::Value<TCategoryTrait *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICategoryTraitValue = 2;

typedef basic::test::msg::Argument<TestValueInstance,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::Value<ICategoryTraitValue>> 
        ArgTestValueInstance;

typedef basic::test::msg::Base<TestValueInstance, char, 
    ArgTestValueInstance, ArgTestValueInstance, 
    ArgTestValueInstance> MessageBaseTestValueInstance;

template<typename TCases, typename... TVariables>
struct TestInstance :
    public basic::test::Message<BASIC_TEST, TestInstance<TCases, 
        TVariables...>>,
    public basic::test::Case<TestInstance<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestInstance<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueInstance
{
public:
    using MessageBaseTestValueInstance::Format;
    using MessageBaseTestValueInstance::SetFormat;
    using MessageBaseTestValueInstance::Argument;
public:
    using basic::test::Case<TestInstance<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestInstance<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestInstance(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestInstance<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestInstance<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestInstance<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueInstance testValueInstance;
        SetFormat(info, testValueInstance, "Test value "
            "%s::Instance<%s>() is same with %s {%s}\n");
        SetFormat(debug, testValueInstance, "Test value "
            "%s::Instance<%s>() is same with %s {%s}\n");
        SetFormat(err, testValueInstance, "Error value "
            "%s::Instance<%s>() is not same with %s {%s}\n");

    }
    template<typename TCategoryTrait>
    bool Result(const TestValueInstance &, 
        VariableTestInstance<TCategoryTrait> & var)
    {
        auto * instance = basic::test::var::At<ICategoryTraitValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Instance<TCategoryTrait>();
        return res.m_value == instance->m_value;
    }

};

typedef basic::test::type::Parameter<TestValueInstance> Case1;

typedef VariableTestInstance<CategoryTrait1> T1Var1;
typedef VariableTestInstance<CategoryTrait2> T1Var2;

CategoryTrait1 categoryTrait1{4};
CategoryTrait2 categoryTrait2{};

T1Var1 t1_var1{&categoryTrait1};
T1Var2 t1_var2{&categoryTrait2};

REGISTER_TEST(t1, new TestInstance<Case1, T1Var1, T1Var2>(t1_var1, 
    t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);

BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);

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

template<typename TCategoryTrait>
struct basic::test::out::Argument<const basic::err::sys::tmpl::
    Category<TCategoryTrait> *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(const basic::err::sys::tmpl::
        Category<TCategoryTrait> * & categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", categ->Value()));
        return *ms_cstr;
    }
    static const char * Value(const basic::err::sys::tmpl::
        Category<TCategoryTrait> * && categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", categ->Value()));
        return *ms_cstr;
    }
};

template<typename TCategoryTrait>
basic::test::CString<char> basic::test::out::Argument<const basic::err::
    sys::tmpl::Category<TCategoryTrait> *>::ms_cstr;

template<>
struct basic::test::out::Argument<CategoryTrait1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CategoryTrait1 * & categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", categ->m_value));
        return *ms_cstr;
    }
    static const char * Value(CategoryTrait1 * && categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", categ->m_value));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CategoryTrait1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CategoryTrait2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CategoryTrait2 * & categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", categ->m_value));
        return *ms_cstr;
    }
    static const char * Value(CategoryTrait2 * && categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", categ->m_value));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CategoryTrait2 *>::ms_cstr;



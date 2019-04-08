#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/DefaultCondition.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;

enum class CodeEnum1
{
    value1 = 4
};

struct CategoryTrait1
{
    typedef CodeEnum1 CodeEnumType;
    CategoryTrait1() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const basic::err::sys::Code & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code.Value() + 10), categ};
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

enum class CodeEnum2
{
    value1 = 14
};

struct CategoryTrait2
{
    typedef CodeEnum2 CodeEnumType;
    CategoryTrait2() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeValueType & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code - 4), categ};
    }
    CategoryValueType Value() const
    {
        return 11;
    }
};

enum class CodeEnum3
{
    value1 = 4
};

struct CategoryTrait3
{
    typedef CodeEnum3 CodeEnumType;
    CategoryTrait3() = default;
    CategoryValueType Value() const
    {
        return 111;
    }
};

enum class CodeEnum4
{
    value1 = 4
};

struct CategoryTrait4
{
    typedef CodeEnum4 CodeEnumType;
    CategoryTrait4() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const basic::err::sys::Code & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code.Value() + 10), categ};
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeValueType & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code - 4), categ};
    }
    CategoryValueType Value() const
    {
        return 14;
    }
};

enum class CodeEnum5
{
    value1 = 1
};

struct CategoryTrait5
{
    typedef CodeEnum5 CodeEnumType;
    CategoryTrait5() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeEnumType & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>((CodeValueType)code + 6), 
            categ};
    }
    CategoryValueType Value() const
    {
        return 15;
    }
};

enum class CodeEnum6
{
    value1 = 1
};

struct CategoryTrait6
{
    typedef CodeEnum6 CodeEnumType;
    CategoryTrait6() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const basic::err::sys::Code & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code.Value() + 11), categ};
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeValueType & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code - 4), categ};
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeEnumType & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>((CodeValueType)code + 7), 
            categ};
    }
    CategoryValueType Value() const
    {
        return 16;
    }
};

struct TestValueDefaultCondition {};

char namespaceFuncName[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TCode>
using VariableTestDefaultCondition = basic::test::Variable<
    basic::test::type::Value<const char *, namespaceFuncName>,
    TCategoryTrait,
    TCode,
    basic::err::sys::Condition,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    basic::test::Value<const basic::err::sys::tmpl::
        Category<TCategoryTrait> *>,
    basic::test::Value<TCode *>,
    basic::test::Value<basic::err::sys::Condition *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICodeType = 2;
constexpr std::size_t IConditionType = 3;
constexpr std::size_t ITmplCategoryType = 4;
constexpr std::size_t ITmplCategoryValue = 5;
constexpr std::size_t ICodeValue = 6;
constexpr std::size_t IConditionValue = 7;

typedef basic::test::msg::Argument<TestValueDefaultCondition,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::Value<IConditionValue>> 
        ArgTestValueDefaultCondition;

typedef basic::test::msg::Base<TestValueDefaultCondition, char, 
    ArgTestValueDefaultCondition, ArgTestValueDefaultCondition, 
    ArgTestValueDefaultCondition> MessageBaseTestValueDefaultCondition;

template<typename TCases, typename... TVariables>
struct TestDefaultCondition :
    public basic::test::Message<BASIC_TEST, TestDefaultCondition<TCases, 
        TVariables...>>,
    public basic::test::Case<TestDefaultCondition<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestDefaultCondition<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDefaultCondition
{
public:
    using MessageBaseTestValueDefaultCondition::Format;
    using MessageBaseTestValueDefaultCondition::SetFormat;
    using MessageBaseTestValueDefaultCondition::Argument;
public:
    using basic::test::Case<TestDefaultCondition<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestDefaultCondition<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestDefaultCondition(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefaultCondition<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestDefaultCondition<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestDefaultCondition<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueDefaultCondition testValueDefaultCondition;
        SetFormat(info, testValueDefaultCondition, "Test value of "
            "%s::DefaultCondition<%s>(%s(), %s {%s}, %s {%s}) "
            "is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCondition, "Test value of "
            "%s::DefaultCondition<%s>(%s(), %s {%s}, %s {%s}) "
            "is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCondition, "Error value of "
            "%s::DefaultCondition<%s>(%s(), %s {%s}, %s {%s}) "
            "is not same with %s {%s}\n");

    }
    template<typename TCategoryTrait, typename TCode>
    bool Result(const TestValueDefaultCondition &, 
        VariableTestDefaultCondition<TCategoryTrait, TCode> & var)
    {
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto * cond = basic::test::var::At<IConditionValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            DefaultCondition(TCategoryTrait {}, *code, *categ);
        return res == *cond;
    }
};

typedef basic::test::type::Parameter<TestValueDefaultCondition> Case1;

typedef VariableTestDefaultCondition<CategoryTrait1, 
    basic::err::sys::Code> T1Var1_1;
typedef VariableTestDefaultCondition<CategoryTrait1, 
    CodeValueType> T1Var1_2;
typedef VariableTestDefaultCondition<CategoryTrait1, 
    CodeEnum1> T1Var1_3;
typedef VariableTestDefaultCondition<CategoryTrait2, 
    CodeValueType> T1Var2_1;
typedef VariableTestDefaultCondition<CategoryTrait2, 
    basic::err::sys::Code> T1Var2_2;
typedef VariableTestDefaultCondition<CategoryTrait2, 
    CodeEnum2> T1Var2_3;
typedef VariableTestDefaultCondition<CategoryTrait3,
    basic::err::sys::Code> T1Var3_1;
typedef VariableTestDefaultCondition<CategoryTrait3,
    CodeValueType> T1Var3_2;
typedef VariableTestDefaultCondition<CategoryTrait3,
    CodeEnum3> T1Var3_3;
typedef VariableTestDefaultCondition<CategoryTrait4,
    basic::err::sys::Code> T1Var4_1;
typedef VariableTestDefaultCondition<CategoryTrait4,
    CodeValueType> T1Var4_2;
typedef VariableTestDefaultCondition<CategoryTrait4,
    CodeEnum4> T1Var4_3;
typedef VariableTestDefaultCondition<CategoryTrait5,
    basic::err::sys::Code> T1Var5_1;
typedef VariableTestDefaultCondition<CategoryTrait5,
    CodeValueType> T1Var5_2;
typedef VariableTestDefaultCondition<CategoryTrait5,
    CodeEnum5> T1Var5_3;
typedef VariableTestDefaultCondition<CategoryTrait6,
    basic::err::sys::Code> T1Var6_1;
typedef VariableTestDefaultCondition<CategoryTrait6,
    CodeValueType> T1Var6_2;
typedef VariableTestDefaultCondition<CategoryTrait6,
    CodeEnum6> T1Var6_3;

auto & tmplCategory1 = basic::err::sys::tmpl::
    Category<CategoryTrait1>::GetInstance();
auto & tmplCategory2 = basic::err::sys::tmpl::
    Category<CategoryTrait2>::GetInstance();
auto & tmplCategory3 = basic::err::sys::tmpl::
    Category<CategoryTrait3>::GetInstance();
auto & tmplCategory4 = basic::err::sys::tmpl::
    Category<CategoryTrait4>::GetInstance();
auto & tmplCategory5 = basic::err::sys::tmpl::
    Category<CategoryTrait5>::GetInstance();
auto & tmplCategory6 = basic::err::sys::tmpl::
    Category<CategoryTrait6>::GetInstance();

basic::err::sys::Code code1_1{4, tmplCategory1};
CodeValueType code1_2{4};
CodeEnum1 code1_3 = CodeEnum1::value1;
basic::err::sys::Condition cond1_1{14, tmplCategory1};
CodeValueType code2_1{14};
basic::err::sys::Code code2_2{14, tmplCategory2};
CodeEnum2 code2_3 = CodeEnum2::value1;
basic::err::sys::Condition cond2_1{10, tmplCategory2};
basic::err::sys::Code code3_1{11, tmplCategory3};
basic::err::sys::Condition cond3_1{11, tmplCategory3};
CodeValueType code3_2{44};
basic::err::sys::Condition cond3_2{44, tmplCategory3};
CodeEnum3 code3_3 = CodeEnum3::value1;
basic::err::sys::Condition cond3_3{4, tmplCategory3};
basic::err::sys::Code code4_1{4, tmplCategory4};
basic::err::sys::Condition cond4_1{14, tmplCategory4};
CodeValueType code4_2{14};
basic::err::sys::Condition cond4_2{10, tmplCategory4};
CodeEnum4 code4_3 = CodeEnum4::value1;
basic::err::sys::Condition cond4_3{0, tmplCategory4};
basic::err::sys::Code code5_1{4, tmplCategory5};
basic::err::sys::Condition cond5_1{4, tmplCategory5};
CodeValueType code5_2{14};
basic::err::sys::Condition cond5_2{14, tmplCategory5};
CodeEnum5 code5_3 = CodeEnum5::value1;
basic::err::sys::Condition cond5_3{7, tmplCategory5};
basic::err::sys::Code code6_1{5, tmplCategory6};
basic::err::sys::Condition cond6_1{16, tmplCategory6};
CodeValueType code6_2{10};
basic::err::sys::Condition cond6_2{6, tmplCategory6};
CodeEnum6 code6_3 = CodeEnum6::value1;
basic::err::sys::Condition cond6_3{8, tmplCategory6};

T1Var1_1 t1_var1_1{&tmplCategory1, &code1_1, &cond1_1};
T1Var1_2 t1_var1_2{&tmplCategory1, &code1_2, &cond1_1};
T1Var1_3 t1_var1_3{&tmplCategory1, &code1_3, &cond1_1};
T1Var2_1 t1_var2_1{&tmplCategory2, &code2_1, &cond2_1};
T1Var2_2 t1_var2_2{&tmplCategory2, &code2_2, &cond2_1};
T1Var2_3 t1_var2_3{&tmplCategory2, &code2_3, &cond2_1};
T1Var3_1 t1_var3_1{&tmplCategory3, &code3_1, &cond3_1};
T1Var3_2 t1_var3_2{&tmplCategory3, &code3_2, &cond3_2};
T1Var3_3 t1_var3_3{&tmplCategory3, &code3_3, &cond3_3};
T1Var4_1 t1_var4_1{&tmplCategory4, &code4_1, &cond4_1};
T1Var4_2 t1_var4_2{&tmplCategory4, &code4_2, &cond4_2};
T1Var4_3 t1_var4_3{&tmplCategory4, &code4_3, &cond4_3};
T1Var5_1 t1_var5_1{&tmplCategory5, &code5_1, &cond5_1};
T1Var5_2 t1_var5_2{&tmplCategory5, &code5_2, &cond5_2};
T1Var5_3 t1_var5_3{&tmplCategory5, &code5_3, &cond5_3};
T1Var6_1 t1_var6_1{&tmplCategory6, &code6_1, &cond6_1};
T1Var6_2 t1_var6_2{&tmplCategory6, &code6_2, &cond6_2};
T1Var6_3 t1_var6_3{&tmplCategory6, &code6_3, &cond6_3};

REGISTER_TEST(t1, new TestDefaultCondition<Case1, T1Var1_1, T1Var1_2,
    T1Var1_3, T1Var2_1, T1Var2_2, T1Var2_3, T1Var3_1, T1Var3_2, T1Var3_3,
    T1Var4_1, T1Var4_2, T1Var4_3, T1Var5_1, T1Var5_2, T1Var5_3, T1Var6_1,
    T1Var6_2, T1Var6_3>(t1_var1_1, t1_var1_2, t1_var1_3, t1_var2_1, t1_var2_2, 
        t1_var2_3, t1_var3_1, t1_var3_2, t1_var3_3, t1_var4_1, t1_var4_2, 
        t1_var4_3, t1_var5_1, t1_var5_2, t1_var5_3, t1_var6_1, t1_var6_2,
        t1_var6_3));

int main()
{
    return RUN_TEST();
}

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

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);
BASIC_TEST_TYPE_NAME("CategoryTrait3", CategoryTrait3);
BASIC_TEST_TYPE_NAME("CategoryTrait4", CategoryTrait4);
BASIC_TEST_TYPE_NAME("CategoryTrait5", CategoryTrait5);
BASIC_TEST_TYPE_NAME("CategoryTrait6", CategoryTrait6);
BASIC_TEST_TYPE_NAME("basic::err::sys::Code", 
    basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);

BASIC_TEST_TYPE_NAME("CodeEnum1", CodeEnum1);
BASIC_TEST_TYPE_NAME("CodeEnum2", CodeEnum2);
BASIC_TEST_TYPE_NAME("CodeEnum3", CodeEnum3);
BASIC_TEST_TYPE_NAME("CodeEnum4", CodeEnum4);
BASIC_TEST_TYPE_NAME("CodeEnum5", CodeEnum5);
BASIC_TEST_TYPE_NAME("CodeEnum6", CodeEnum6);

template<>
struct basic::err::sys::make::Category<CodeEnum1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum5>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait5>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum6>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6>::
            GetInstance();
    }
};

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
struct basic::test::out::Argument<basic::err::sys::Condition *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Condition * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Condition * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Condition *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::err::sys::Code *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Code * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Code * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Code *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::err::defn::type::sys::code::Value *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::defn::type::sys::code::
        Value * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
    static const char * Value(basic::err::defn::type::sys::code::
        Value * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::err::defn::type::sys::code::Value *>::ms_cstr;
    
template<>
struct basic::test::out::Argument<CodeEnum1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum4 *>::ms_cstr;
    
template<>
struct basic::test::out::Argument<CodeEnum5 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum5 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum5 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum5 *>::ms_cstr;
    
template<>
struct basic::test::out::Argument<CodeEnum6 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum6 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum6 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum6 *>::ms_cstr;

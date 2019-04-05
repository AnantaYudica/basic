#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/DefaultCode.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;
typedef basic::err::sys::Category CategoryType;

typedef basic::err::msg::String MessageStringType;

struct CategoryTrait1
{
    CategoryTrait1() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const TCategory & categ) const
    {
        return {4, categ};
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    CategoryTrait2() = default;
    CategoryValueType Value() const
    {
        return 2;
    }
};

enum class CodeEnum1
{
    value1 = 4
};

struct CategoryTrait3
{
    typedef CodeEnum1 CodeEnumType;
    CategoryTrait3() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeValueType & code, 
        const TCategory & categ) const
    {
        return TRet(code + 2, categ);
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeEnumType & code, 
        const TCategory & categ) const
    {
        return TRet((CodeValueType)code + 4, categ);
    }
    CategoryValueType Value() const
    {
        return 3;
    }
};

enum class CodeEnum2
{
    value1 = 4
};

struct CategoryTrait4
{
    typedef CodeEnum2 CodeEnumType;
    CategoryTrait4() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeValueType & code, 
        const TCategory & categ) const
    {
        return TRet(code + 2, categ);
    }
    CategoryValueType Value() const
    {
        return 4;
    }
};

struct CategoryTrait5
{
    CategoryTrait5() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeValueType & code, 
        const TCategory & categ) const
    {
        return TRet(code + 2, categ);
    }
    CategoryValueType Value() const
    {
        return 5;
    }
};

enum class CodeEnum3
{
    value1 = 4
};

struct CategoryTrait6
{
    typedef CodeEnum3 CodeEnumType;
    CategoryTrait6() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeEnumType & code, 
        const TCategory & categ) const
    {
        return TRet((CodeValueType)code + 4, categ);
    }
    CategoryValueType Value() const
    {
        return 6;
    }
};

struct CategoryTrait7
{
    CategoryTrait7() = default;
    CategoryValueType Value() const
    {
        return 7;
    }
};

enum class CodeEnum4
{
    value1 = 4
};

struct CategoryTrait8
{
    typedef CodeEnum4 CodeEnumType;
    CategoryTrait8() = default;
    CategoryValueType Value() const
    {
        return 8;
    }
};


struct TestValueDefaultCode {};
struct TestValueDefaultCodeValue {};

char namespaceFuncName[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TValue = char>
using VariableTestDefaultCode = basic::test::Variable<
    basic::test::type::Value<const char *, namespaceFuncName>,
    TCategoryTrait,
    basic::err::sys::Code,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    TValue,
    basic::test::Value<const basic::err::sys::tmpl::
        Category<TCategoryTrait> *>,
    basic::test::Value<basic::err::sys::Code *>,
    basic::test::Value<TValue *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICodeType = 2;
constexpr std::size_t ITmplCategoryType = 3;
constexpr std::size_t IValueType = 4;
constexpr std::size_t ITmplCategoryValue = 5;
constexpr std::size_t ICodeValue = 6;
constexpr std::size_t IValueValue = 7;

typedef basic::test::msg::Argument<TestValueDefaultCode,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>> 
        ArgTestValueDefaultCode;

typedef basic::test::msg::Base<TestValueDefaultCode, char, 
    ArgTestValueDefaultCode, ArgTestValueDefaultCode, 
    ArgTestValueDefaultCode> MessageBaseTestValueDefaultCode;

typedef basic::test::msg::Argument<TestValueDefaultCodeValue,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<IValueType>,
    basic::test::msg::arg::Value<IValueValue>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>> 
        ArgTestValueDefaultCodeValue;

typedef basic::test::msg::Base<TestValueDefaultCodeValue, char, 
    ArgTestValueDefaultCodeValue, ArgTestValueDefaultCodeValue, 
    ArgTestValueDefaultCodeValue> MessageBaseTestValueDefaultCodeValue;

template<typename TCases, typename... TVariables>
struct TestDefaultCode :
    public basic::test::Message<BASIC_TEST, TestDefaultCode<TCases, 
        TVariables...>>,
    public basic::test::Case<TestDefaultCode<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestDefaultCode<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDefaultCode,
    public MessageBaseTestValueDefaultCodeValue
{
public:
    using MessageBaseTestValueDefaultCode::Format;
    using MessageBaseTestValueDefaultCode::SetFormat;
    using MessageBaseTestValueDefaultCode::Argument;
    using MessageBaseTestValueDefaultCodeValue::Format;
    using MessageBaseTestValueDefaultCodeValue::SetFormat;
    using MessageBaseTestValueDefaultCodeValue::Argument;
public:
    using basic::test::Case<TestDefaultCode<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestDefaultCode<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestDefaultCode(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefaultCode<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestDefaultCode<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestDefaultCode<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueDefaultCode testValueDefaultCode;
        SetFormat(info, testValueDefaultCode, "Test value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}) is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCode, "Test value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}) is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCode, "Error value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}) is not same with %s {%s}\n");
        
        TestValueDefaultCodeValue testValueDefaultCodeValue;
        SetFormat(info, testValueDefaultCodeValue, "Test value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}, %s {%s}) "
            "is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCodeValue, "Test value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}, %s {%s}) "
            "is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCodeValue, "Error value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}, %s {%s}) "
            "is not same with %s {%s}\n");

    }
    template<typename TCategoryTrait, typename TValue>
    bool Result(const TestValueDefaultCode &, 
        VariableTestDefaultCode<TCategoryTrait, TValue> & var)
    {
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            DefaultCode(TCategoryTrait {}, *categ);
        return res == *code;
    }
    template<typename TCategoryTrait, typename TValue>
    bool Result(const TestValueDefaultCodeValue &, 
        VariableTestDefaultCode<TCategoryTrait, TValue> & var)
    {
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto * value = basic::test::var::At<IValueValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            DefaultCode(TCategoryTrait {}, *value, *categ);
        return res == *code;
    }

};

typedef basic::test::type::Parameter<TestValueDefaultCode> Case1;
typedef basic::test::type::Parameter<TestValueDefaultCodeValue> Case2;

typedef VariableTestDefaultCode<CategoryTrait1> T1Var1;
typedef VariableTestDefaultCode<CategoryTrait2> T1Var2;

auto & tmplCategory1 = basic::err::sys::tmpl::
    Category<CategoryTrait1>::GetInstance();
auto & tmplCategory2 = basic::err::sys::tmpl::
    Category<CategoryTrait2>::GetInstance();

basic::err::sys::Code code1_1{4, tmplCategory1};
basic::err::sys::Code code1_2{0, tmplCategory2};

T1Var1 t1_var1{&tmplCategory1, &code1_1, nullptr};
T1Var2 t1_var2{&tmplCategory2, &code1_2, nullptr};

REGISTER_TEST(t1, new TestDefaultCode<Case1, T1Var1, T1Var2>(t1_var1,
    t1_var2));

typedef VariableTestDefaultCode<CategoryTrait3, CodeValueType> T2Var1_1;
typedef VariableTestDefaultCode<CategoryTrait3, CodeEnum1> T2Var1_2;
typedef VariableTestDefaultCode<CategoryTrait4, CodeValueType> T2Var2_1;
typedef VariableTestDefaultCode<CategoryTrait4, CodeEnum2> T2Var2_2;
typedef VariableTestDefaultCode<CategoryTrait5, CodeValueType> T2Var3;
typedef VariableTestDefaultCode<CategoryTrait6, CodeValueType> T2Var4_1;
typedef VariableTestDefaultCode<CategoryTrait6, CodeEnum3> T2Var4_2;
typedef VariableTestDefaultCode<CategoryTrait7, CodeValueType> T2Var5;
typedef VariableTestDefaultCode<CategoryTrait8, CodeValueType> T2Var6_1;
typedef VariableTestDefaultCode<CategoryTrait8, CodeEnum4> T2Var6_2;

auto & tmplCategory3 = basic::err::sys::tmpl::
    Category<CategoryTrait3>::GetInstance();
auto & tmplCategory4 = basic::err::sys::tmpl::
    Category<CategoryTrait4>::GetInstance();
auto & tmplCategory5 = basic::err::sys::tmpl::
    Category<CategoryTrait5>::GetInstance();
auto & tmplCategory6 = basic::err::sys::tmpl::
    Category<CategoryTrait6>::GetInstance();
auto & tmplCategory7 = basic::err::sys::tmpl::
    Category<CategoryTrait7>::GetInstance();
auto & tmplCategory8 = basic::err::sys::tmpl::
    Category<CategoryTrait8>::GetInstance();

basic::err::sys::Code code2_1_1{4, tmplCategory3};
basic::err::sys::Code code2_1_2{8, tmplCategory3};

CodeValueType code_val2_1 = 2;
CodeEnum1 code_enum2_1 = CodeEnum1::value1;

T2Var1_1 t2_var1_1{&tmplCategory3, &code2_1_1, &code_val2_1};
T2Var1_2 t2_var1_2{&tmplCategory3, &code2_1_2, &code_enum2_1};

basic::err::sys::Code code2_2_1{4, tmplCategory4};
basic::err::sys::Code code2_2_2{6, tmplCategory4};

CodeValueType code_val2_2 = 2;
CodeEnum2 code_enum2_2 = CodeEnum2::value1;

T2Var2_1 t2_var2_1{&tmplCategory4, &code2_2_1, &code_val2_2};
T2Var2_2 t2_var2_2{&tmplCategory4, &code2_2_2, &code_enum2_2};

basic::err::sys::Code code2_3{4, tmplCategory5};

CodeValueType code_val3 = 2;

T2Var3 t2_var3{&tmplCategory5, &code2_3, &code_val3};

basic::err::sys::Code code2_4_1{2, tmplCategory6};
basic::err::sys::Code code2_4_2{8, tmplCategory6};

CodeValueType code_val4_2 = 2;
CodeEnum3 code_enum4_2 = CodeEnum3::value1;

T2Var4_1 t2_var4_1{&tmplCategory6, &code2_4_1, &code_val4_2};
T2Var4_2 t2_var4_2{&tmplCategory6, &code2_4_2, &code_enum4_2};

basic::err::sys::Code code2_5{2, tmplCategory7};

CodeValueType code_val5 = 2;

T2Var5 t2_var5{&tmplCategory7, &code2_5, &code_val5};

basic::err::sys::Code code2_6_1{2, tmplCategory8};
basic::err::sys::Code code2_6_2{4, tmplCategory8};

CodeValueType code_val6_2 = 2;
CodeEnum4 code_enum6_2 = CodeEnum4::value1;

T2Var6_1 t2_var6_1{&tmplCategory8, &code2_6_1, &code_val6_2};
T2Var6_2 t2_var6_2{&tmplCategory8, &code2_6_2, &code_enum6_2};
 
REGISTER_TEST(t2, new TestDefaultCode<Case2, T2Var1_1, T2Var1_2,
    T2Var2_1, T2Var2_2, T2Var3, T2Var4_1, T2Var4_2, T2Var5, T2Var6_1,
    T2Var6_2>(t2_var1_1, t2_var1_2, t2_var2_1, t2_var2_2, t2_var3, 
        t2_var4_1, t2_var4_2, t2_var5, t2_var6_1, t2_var6_2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);
BASIC_TEST_TYPE_NAME("CategoryTrait3", CategoryTrait3);
BASIC_TEST_TYPE_NAME("CategoryTrait4", CategoryTrait4);
BASIC_TEST_TYPE_NAME("CategoryTrait5", CategoryTrait5);
BASIC_TEST_TYPE_NAME("CategoryTrait6", CategoryTrait6);
BASIC_TEST_TYPE_NAME("CategoryTrait7", CategoryTrait7);
BASIC_TEST_TYPE_NAME("CategoryTrait8", CategoryTrait8);
BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("CodeEnum1", CodeEnum1);
BASIC_TEST_TYPE_NAME("CodeEnum2", CodeEnum2);
BASIC_TEST_TYPE_NAME("CodeEnum3", CodeEnum3);
BASIC_TEST_TYPE_NAME("CodeEnum4", CodeEnum4);

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

template<>
struct basic::err::sys::make::Category<CodeEnum1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait8>::
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
struct basic::test::out::Argument<CodeValueType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeValueType * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
    static const char * Value(CodeValueType * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeValueType *>::ms_cstr;

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

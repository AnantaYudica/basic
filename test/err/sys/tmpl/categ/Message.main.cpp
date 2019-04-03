#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/Message.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include <type_traits>
#include <cstring>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;
typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;
typedef basic::err::msg::String StringType;

typedef basic::err::sys::tmpl::categ::msg::tag::Code CodeTagType;
typedef basic::err::sys::tmpl::categ::msg::tag::Condition
    ConditionTagType;

StringType codeMsg{"code msg"};
StringType condMsg{"condition msg"};
StringType codeMsgTag{"code msg tag"};
StringType condMsgTag{"condition msg tag"};
StringType emptyMsg{""};

struct CategoryTrait1
{
    int m_value;
    CategoryTrait1() = default;
    StringType Message(const CodeType & code) const
    {
        return codeMsg;
    }
    StringType Message(const ConditionType & cond) const
    {
        return condMsg;
    }
    StringType Message(const CodeTagType &, const CodeValueType & val) const
    {
        return codeMsgTag;
    }
    StringType Message(const ConditionTagType &, 
        const ConditionValueType & val) const
    {
        return condMsgTag;
    }
    
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    int m_value;
    CategoryTrait2() = default;
    CategoryValueType Value() const
    {
        return 2;
    }
};

struct CategoryTrait3
{
    int m_value;
    CategoryTrait3() = default;
    StringType Message(const CodeValueType & value) const
    {
        return codeMsg;
    }
    template<typename TCondValue = ConditionValueType>
    typename std::enable_if<!std::is_same<CodeValueType, 
        TCondValue>::value, StringType>::type
            Message(const TCondValue & value) const
    {
        return codeMsg;
    }
    CategoryValueType Value() const
    {
        return 3;
    }
};

struct CategoryTrait4
{
    int m_value;
    CategoryTrait4() = default;
    StringType Message(const ConditionValueType & value) const
    {
        return condMsg;
    }
    template<typename TCodeValue = CodeValueType>
    typename std::enable_if<!std::is_same<ConditionValueType, 
        TCodeValue>::value, StringType>::type
            Message(const TCodeValue & value) const
    {
        return condMsg;
    }
    CategoryValueType Value() const
    {
        return 4;
    }
};

struct CategoryTrait5
{
    int m_value;
    CategoryTrait5() = default;
    StringType Message(const CodeType & value) const
    {
        return codeMsg;
    }
    StringType Message(const ConditionType & value) const
    {
        return condMsg;
    }
    CategoryValueType Value() const
    {
        return 5;
    }
};

struct CategoryTrait6
{
    int m_value;
    CategoryTrait6() = default;
    StringType Message(const CodeTagType &, const CodeValueType & val) const
    {
        return codeMsgTag;
    }
    StringType Message(const ConditionTagType &, 
        const ConditionValueType & val) const
    {
        return condMsgTag;
    }
    CategoryValueType Value() const
    {
        return 6;
    }
};

struct TestValueMessage {};
struct TestValueMessageTag {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TMessageTag, typename TValue, 
        typename TTagValue>
using VariableTestMessage = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    TValue,
    TMessageTag,
    TTagValue,
    TCategoryTrait,
    basic::test::Value<
        const basic::err::sys::tmpl::Category<TCategoryTrait> *>,
    basic::test::Value<TValue *>,
    basic::test::Value<TTagValue *>,
    basic::test::Value<const char *>,
    basic::test::Value<const char *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ITmplCategoryType = 1;
constexpr std::size_t IValueType = 2;
constexpr std::size_t IMessageTagType = 3;
constexpr std::size_t ITagValueType = 4;
constexpr std::size_t ICategoryTraitType = 5;
constexpr std::size_t ITmplCategoryValue = 6;
constexpr std::size_t IValueValue = 7;
constexpr std::size_t ITagValueValue = 8;
constexpr std::size_t IMessageValue = 9;
constexpr std::size_t IMessageTagValue = 10;

typedef basic::test::msg::Argument<TestValueMessage,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<IMessageTagType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<IValueType>,
    basic::test::msg::arg::Value<IValueValue>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::Value<IMessageValue>> 
        ArgTestValueMessage;

typedef basic::test::msg::Base<TestValueMessage, char, 
    ArgTestValueMessage, ArgTestValueMessage, 
    ArgTestValueMessage> MessageBaseTestValueMessage;

typedef basic::test::msg::Argument<TestValueMessageTag,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<IMessageTagType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ITagValueType>,
    basic::test::msg::arg::Value<ITagValueValue>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::Value<IMessageTagValue>> 
        ArgTestValueMessageTag;

typedef basic::test::msg::Base<TestValueMessageTag, char, 
    ArgTestValueMessageTag, ArgTestValueMessageTag, 
    ArgTestValueMessageTag> MessageBaseTestValueMessageTag;

template<typename TCases, typename... TVariables>
struct TestMessage :
    public basic::test::Message<BASIC_TEST, TestMessage<TCases, 
        TVariables...>>,
    public basic::test::Case<TestMessage<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestMessage<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueMessage,
    public MessageBaseTestValueMessageTag
{
public:
    using MessageBaseTestValueMessage::Format;
    using MessageBaseTestValueMessage::SetFormat;
    using MessageBaseTestValueMessage::Argument;
    using MessageBaseTestValueMessageTag::Format;
    using MessageBaseTestValueMessageTag::SetFormat;
    using MessageBaseTestValueMessageTag::Argument;
public:
    using basic::test::Case<TestMessage<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestMessage<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestMessage(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestMessage<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestMessage<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestMessage<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueMessage testValueMessage;
        SetFormat(info, testValueMessage, "Test value "
            "%s::Message<%s>(%s(), %s {%s}, %s{%s}) is same with \"%s\"\n");
        SetFormat(debug, testValueMessage, "Test value "
            "%s::Message<%s>(%s(), %s {%s}, %s{%s}) is same with \"%s\"\n");
        SetFormat(err, testValueMessage, "Error value "
            "%s::Message<%s>(%s(), %s {%s}, %s{%s}) "
            "is not same with \"%s\"\n");
        
        TestValueMessageTag testValueMessageTag;
        SetFormat(info, testValueMessageTag, "Test value "
            "%s::Message<%s>(%s(), %s {%s}, %s{%s}) is same with \"%s\"\n");
        SetFormat(debug, testValueMessageTag, "Test value "
            "%s::Message<%s>(%s(), %s {%s}, %s{%s}) is same with \"%s\"\n");
        SetFormat(err, testValueMessageTag, "Error value "
            "%s::Message<%s>(%s(), %s {%s}, %s{%s}) "
            "is not same with \"%s\"\n");

    }
    template<typename TCategoryTrait, typename TMessageTag, typename TValue, 
        typename TTagValue>
    bool Result(const TestValueMessage &, VariableTestMessage<TCategoryTrait, 
        TMessageTag, TValue, TTagValue> & var)
    {
        auto * value = basic::test::var::At<IValueValue>(var).
            Get().Get();
        auto * msg = basic::test::var::At<IMessageValue>(var).
            Get().Get();
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Message<TMessageTag>(TCategoryTrait{}, *value, *categ);
        return strcmp(res.Value(), msg) == 0;
    }
    template<typename TCategoryTrait, typename TMessageTag, typename TValue, 
        typename TTagValue>
    bool Result(const TestValueMessageTag &, VariableTestMessage<TCategoryTrait, 
        TMessageTag, TValue, TTagValue> & var)
    {
        auto * value = basic::test::var::At<ITagValueValue>(var).
            Get().Get();
        auto * msg = basic::test::var::At<IMessageTagValue>(var).
            Get().Get();
        
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Message<TMessageTag>(TCategoryTrait{}, *value, *categ);
        return strcmp(res.Value(), msg) == 0;
    }

};

typedef basic::test::type::Parameter<TestValueMessage,
    TestValueMessageTag> Case1;

typedef VariableTestMessage<CategoryTrait1,
    CodeTagType, CodeType, CodeValueType> T1Var1;
typedef VariableTestMessage<CategoryTrait1,
    ConditionTagType, ConditionType, ConditionValueType> T1Var2;
typedef VariableTestMessage<CategoryTrait2,
    CodeTagType, CodeType, CodeValueType> T1Var3;
typedef VariableTestMessage<CategoryTrait2,
    ConditionTagType, ConditionType, ConditionValueType> T1Var4;
typedef VariableTestMessage<CategoryTrait3,
    CodeTagType, CodeType, CodeValueType> T1Var5;
typedef VariableTestMessage<CategoryTrait3,
    ConditionTagType, ConditionType, ConditionValueType> T1Var6;
typedef VariableTestMessage<CategoryTrait4,
    CodeTagType, CodeType, CodeValueType> T1Var7;
typedef VariableTestMessage<CategoryTrait4,
    ConditionTagType, ConditionType, ConditionValueType> T1Var8;
typedef VariableTestMessage<CategoryTrait5,
    CodeTagType, CodeType, CodeValueType> T1Var9;
typedef VariableTestMessage<CategoryTrait5,
    ConditionTagType, ConditionType, ConditionValueType> T1Var10;
typedef VariableTestMessage<CategoryTrait6,
    CodeTagType, CodeType, CodeValueType> T1Var11;
typedef VariableTestMessage<CategoryTrait6,
    ConditionTagType, ConditionType, ConditionValueType> T1Var12;

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

CodeType code1{1, tmplCategory1};
CodeValueType code_val1{1};
ConditionType cond1{1, tmplCategory1};
ConditionValueType cond_val1{1};

CodeType code2{1, tmplCategory2};
CodeValueType code_val2{1};
ConditionType cond2{1, tmplCategory2};
ConditionValueType cond_val2{1};

CodeType code3{1, tmplCategory3};
CodeValueType code_val3{1};
ConditionType cond3{1, tmplCategory3};
ConditionValueType cond_val3{1};

CodeType code4{1, tmplCategory4};
CodeValueType code_val4{1};
ConditionType cond4{1, tmplCategory4};
ConditionValueType cond_val4{1};

CodeType code5{1, tmplCategory5};
CodeValueType code_val5{1};
ConditionType cond5{1, tmplCategory5};
ConditionValueType cond_val5{1};

CodeType code6{1, tmplCategory6};
CodeValueType code_val6{1};
ConditionType cond6{1, tmplCategory6};
ConditionValueType cond_val6{1};

T1Var1 t1_var1{&tmplCategory1, &code1, &code_val1, 
    codeMsg.Value(), codeMsgTag.Value()};
T1Var2 t1_var2{&tmplCategory1, &cond1, &cond_val1, 
    condMsg.Value(), condMsgTag.Value()};
T1Var3 t1_var3{&tmplCategory2, &code2, &code_val2, 
    emptyMsg.Value(), emptyMsg.Value()};
T1Var4 t1_var4{&tmplCategory2, &cond2, &cond_val2, 
    emptyMsg.Value(), emptyMsg.Value()};
T1Var5 t1_var5{&tmplCategory3, &code3, &code_val3, 
    codeMsg.Value(), codeMsg.Value()};
T1Var6 t1_var6{&tmplCategory3, &cond3, &cond_val3, 
    codeMsg.Value(), codeMsg.Value()};
T1Var7 t1_var7{&tmplCategory4, &code4, &code_val4, 
    condMsg.Value(), condMsg.Value()};
T1Var8 t1_var8{&tmplCategory4, &cond4, &cond_val4, 
    condMsg.Value(), condMsg.Value()};
T1Var9 t1_var9{&tmplCategory5, &code5, &code_val5, 
    codeMsg.Value(), codeMsg.Value()};
T1Var10 t1_var10{&tmplCategory5, &cond5, &cond_val5, 
    condMsg.Value(), condMsg.Value()};
T1Var11 t1_var11{&tmplCategory6, &code6, &code_val6, 
    codeMsgTag.Value(), codeMsgTag.Value()};
T1Var12 t1_var12{&tmplCategory6, &cond6, &cond_val6, 
    condMsgTag.Value(), condMsgTag.Value()};

REGISTER_TEST(t1, new TestMessage<Case1, T1Var1, T1Var2, T1Var3,
    T1Var4, T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, 
    T1Var12>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5, t1_var6, t1_var7, 
        t1_var8, t1_var9, t1_var10, t1_var11, t1_var12));

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

BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);
    
BASIC_TEST_TYPE_NAME("basic::err::sys::tmpl::categ::msg::tag::Code",
    basic::err::sys::tmpl::categ::msg::tag::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::tmpl::categ::msg::tag::Condition",
    basic::err::sys::tmpl::categ::msg::tag::Condition);

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
struct basic::test::out::Argument<CodeType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeType * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(CodeType * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeType *>::ms_cstr;

struct Void1 {};

template<>
struct basic::test::out::Argument<typename std::conditional<std::is_same<
    ConditionValueType, CodeValueType>::value, Void1, 
    ConditionValueType>::type *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionValueType * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
    static const char * Value(ConditionValueType * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<typename std::conditional<std::is_same<ConditionValueType, 
    CodeValueType>::value, Void1, ConditionValueType>::type *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionType * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", cond->Value()));
        return *ms_cstr;
    }
    static const char * Value(ConditionType * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", cond->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionType *>::ms_cstr;



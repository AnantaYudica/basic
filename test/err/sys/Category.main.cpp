#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/Code.h"
#include "err/sys/Condition.h"
#include "err/sys/Category.h"

BASIC_TEST_CONSTRUCT;

const char * ToString0(bool && b)
{
    static char true_cstr[] = "true";
    static char false_cstr[] = "false";
    return b ? true_cstr : false_cstr;
};

struct TestBaseOfIntfOutput {};
struct TestAliasCharType {};
struct TestAliasOutputType {};
struct TestAliasValueType {};
struct TestAliasCodeValueType {};
struct TestAliasConditionValueType {};
struct TestAliasStringType {};
struct TestAliasCodeType {};
struct TestAliasConditionType {};
struct TestComparisonNotEqual {};
struct TestComparisonMore {};

struct CategoryTrait1
{
    CategoryTrait1() = default;
    basic::err::defn::type::sys::categ::Value Value() const
    {
        return 14;
    }
};

struct CategoryTrait2
{
    CategoryTrait2() = default;
    basic::err::defn::type::sys::categ::Value Value() const
    {
        return 4;
    }
};

template<
    typename TComparisonArgs0Type,
    typename TComparisonArgs1Type,
    typename TComparisonArgs0Value, 
    typename TComparisonArgs1Value,
    std::size_t NComparison>
using VariableTestCategory_ = basic::test::Variable<
    basic::err::sys::Category,
    basic::err::intf::Output,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::defn::type::sys::categ::Value,
    basic::err::defn::type::sys::code::Value,
    basic::err::defn::type::sys::cond::Value,
    basic::err::msg::String,
    basic::err::sys::Code,
    basic::err::sys::Condition,
    basic::test::Value<
        const basic::err::sys::Category *>,
    TComparisonArgs0Type,
    TComparisonArgs1Type,
    TComparisonArgs0Value,
    TComparisonArgs1Value,
    basic::test::val::Sequence<bool, NComparison>,
    basic::test::type::Function<const char *(bool &&), &ToString0>>;

template<typename TComparison0Args, typename TComparison1Args>
struct VariableTestCategory {};

template<typename... TComparison0Args, typename... TComparison1Args>
struct VariableTestCategory<
    basic::test::type::Parameter<TComparison0Args...>,
    basic::test::type::Parameter<TComparison1Args...>> : 
        VariableTestCategory_< 
            basic::test::type::Parameter<TComparison0Args...>,
            basic::test::type::Parameter<TComparison1Args...>,
            basic::test::val::Parameter<TComparison0Args *...>,
            basic::test::val::Parameter<TComparison1Args *...>,
            sizeof...(TComparison0Args)>
{
    typedef VariableTestCategory_< 
        basic::test::type::Parameter<TComparison0Args...>,
        basic::test::type::Parameter<TComparison1Args...>,
        basic::test::val::Parameter<TComparison0Args *...>,
        basic::test::val::Parameter<TComparison1Args *...>,
        sizeof...(TComparison0Args)> BaseType;

    template<typename... TValArgs>
    VariableTestCategory(TValArgs&&... val_args) :
        BaseType(std::forward<TValArgs>(val_args)...)
    {}
};

enum : std::size_t
{
    ICategoryType,
    IIntfOutputType,
    ICharType,
    IOutputType,
    IValueType,
    ICodeValueType,
    IConditionValueType,
    IStringType,
    ICodeType,
    IConditionType,
    ICategoryValue,
    IComparisonArgs0ParamType,
    IComparisonArgs1ParamType,
    IComparisonArgs0ParamValue,
    IComparisonArgs1ParamValue,
    IComparisonResultSeqValue,
    IBoolToString0TypeFunc
}; 

typedef basic::test::msg::Argument<TestBaseOfIntfOutput,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IIntfOutputType>>
        ArgTestBaseOfIntfOutput;

typedef basic::test::msg::Base<TestBaseOfIntfOutput, char, 
    ArgTestBaseOfIntfOutput, ArgTestBaseOfIntfOutput, 
    ArgTestBaseOfIntfOutput> MessageBaseTestBaseOfIntfOutput;
    
typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICharType>>
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IOutputType>>
        ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestAliasValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IValueType>>
        ArgTestAliasValueType;

typedef basic::test::msg::Base<TestAliasValueType, char, 
    ArgTestAliasValueType, ArgTestAliasValueType, 
    ArgTestAliasValueType> MessageBaseTestAliasValueType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasConditionValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionValueType>>
        ArgTestAliasConditionValueType;

typedef basic::test::msg::Base<TestAliasConditionValueType, char, 
    ArgTestAliasConditionValueType, ArgTestAliasConditionValueType, 
    ArgTestAliasConditionValueType> MessageBaseTestAliasConditionValueType;

typedef basic::test::msg::Argument<TestAliasStringType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IStringType>>
        ArgTestAliasStringType;

typedef basic::test::msg::Base<TestAliasStringType, char, 
    ArgTestAliasStringType, ArgTestAliasStringType, 
    ArgTestAliasStringType> MessageBaseTestAliasStringType;

typedef basic::test::msg::Argument<TestAliasCodeType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeType>>
        ArgTestAliasCodeType;

typedef basic::test::msg::Base<TestAliasCodeType, char, 
    ArgTestAliasCodeType, ArgTestAliasCodeType, 
    ArgTestAliasCodeType> MessageBaseTestAliasCodeType;

typedef basic::test::msg::Argument<TestAliasConditionType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionType>>
        ArgTestAliasConditionType;

typedef basic::test::msg::Base<TestAliasConditionType, char, 
    ArgTestAliasConditionType, ArgTestAliasConditionType, 
    ArgTestAliasConditionType> MessageBaseTestAliasConditionType;

typedef basic::test::msg::Argument<TestComparisonNotEqual,
    basic::test::msg::arg::type::Index<IComparisonArgs0ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Index<IComparisonArgs1ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Function<IBoolToString0TypeFunc,
        basic::test::msg::arg::type::Index<IComparisonResultSeqValue,
            basic::test::msg::arg::val::seq::At>>>
                ArgTestComparisonNotEqual;

typedef basic::test::msg::Base<TestComparisonNotEqual, char, 
    ArgTestComparisonNotEqual, ArgTestComparisonNotEqual, 
    ArgTestComparisonNotEqual> MessageBaseTestComparisonNotEqual;

typedef basic::test::msg::Argument<TestComparisonMore,
    basic::test::msg::arg::type::Index<IComparisonArgs0ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Index<IComparisonArgs1ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Function<IBoolToString0TypeFunc,
        basic::test::msg::arg::type::Index<IComparisonResultSeqValue,
            basic::test::msg::arg::val::seq::At>>>
                ArgTestComparisonMore;

typedef basic::test::msg::Base<TestComparisonMore, char, 
    ArgTestComparisonMore, ArgTestComparisonMore, 
    ArgTestComparisonMore> MessageBaseTestComparisonMore;

template<typename TCases, typename... TVariables>
struct TestCategory :
    public basic::test::Message<BASIC_TEST, TestCategory<TCases, 
        TVariables...>>,
    public basic::test::Case<TestCategory<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestCategory<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfIntfOutput,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestAliasValueType,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasConditionValueType,
    public MessageBaseTestAliasStringType,
    public MessageBaseTestAliasCodeType,
    public MessageBaseTestAliasConditionType,
    public MessageBaseTestComparisonNotEqual,
    public MessageBaseTestComparisonMore
{
public:
    using basic::test::Case<TestCategory<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestCategory<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfIntfOutput::Format;
    using MessageBaseTestBaseOfIntfOutput::SetFormat;
    using MessageBaseTestBaseOfIntfOutput::Argument;
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasOutputType::Format;
    using MessageBaseTestAliasOutputType::SetFormat;
    using MessageBaseTestAliasOutputType::Argument;
    using MessageBaseTestAliasValueType::Format;
    using MessageBaseTestAliasValueType::SetFormat;
    using MessageBaseTestAliasValueType::Argument;
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestAliasConditionValueType::Format;
    using MessageBaseTestAliasConditionValueType::SetFormat;
    using MessageBaseTestAliasConditionValueType::Argument;
    using MessageBaseTestAliasStringType::Format;
    using MessageBaseTestAliasStringType::SetFormat;
    using MessageBaseTestAliasStringType::Argument;
    using MessageBaseTestAliasCodeType::Format;
    using MessageBaseTestAliasCodeType::SetFormat;
    using MessageBaseTestAliasCodeType::Argument;
    using MessageBaseTestAliasConditionType::Format;
    using MessageBaseTestAliasConditionType::SetFormat;
    using MessageBaseTestAliasConditionType::Argument;
    using MessageBaseTestComparisonNotEqual::Format;
    using MessageBaseTestComparisonNotEqual::SetFormat;
    using MessageBaseTestComparisonNotEqual::Argument;
    using MessageBaseTestComparisonMore::Format;
    using MessageBaseTestComparisonMore::SetFormat;
    using MessageBaseTestComparisonMore::Argument;
public:
    TestCategory(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestCategory<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestCategory<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestCategory<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestBaseOfIntfOutput testBaseOfIntfOutput;
        SetFormat(info, testBaseOfIntfOutput, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfIntfOutput, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfIntfOutput, 
            "Error Test %s is not base of %s\n");

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(err, testAliasCharType, "Error alias type "
            "%s::CharType is not same with %s\n");

        TestAliasOutputType testAliasOutputType;
        SetFormat(info, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(debug, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(err, testAliasOutputType, "Error alias type "
            "%s::OutputType is not same with %s\n");

        TestAliasValueType testAliasValueType;
        SetFormat(info, testAliasValueType, "Test alias type "
            "%s::ValueType is same with %s\n");
        SetFormat(debug, testAliasValueType, "Test alias type "
            "%s::ValueType is same with %s\n");
        SetFormat(err, testAliasValueType, "Error alias type "
            "%s::ValueType is not same with %s\n");

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(err, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType is not same with %s\n");

        TestAliasConditionValueType testAliasConditionValueType;
        SetFormat(info, testAliasConditionValueType, "Test alias type "
            "%s::ConditionValueType is same with %s\n");
        SetFormat(debug, testAliasConditionValueType, "Test alias type "
            "%s::ConditionValueType is same with %s\n");
        SetFormat(err, testAliasConditionValueType, "Error alias type "
            "%s::ConditionValueType is not same with %s\n");

        TestAliasStringType testAliasStringType;
        SetFormat(info, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(debug, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(err, testAliasStringType, "Error alias type "
            "%s::StringType is not same with %s\n");

        TestAliasCodeType testAliasCodeType;
        SetFormat(info, testAliasCodeType, "Test alias type "
            "%s::CodeType is same with %s\n");
        SetFormat(debug, testAliasCodeType, "Test alias type "
            "%s::CodeType is same with %s\n");
        SetFormat(err, testAliasCodeType, "Error alias type "
            "%s::CodeType is not same with %s\n");

        TestAliasConditionType testAliasConditionType;
        SetFormat(info, testAliasConditionType, "Test alias type "
            "%s::ConditionType is same with %s\n");
        SetFormat(debug, testAliasConditionType, "Test alias type "
            "%s::ConditionType is same with %s\n");
        SetFormat(err, testAliasConditionType, "Error alias type "
            "%s::ConditionType is not same with %s\n");

        TestComparisonNotEqual testComparisonNotEqual;
        SetFormat(info, testComparisonNotEqual, "Test comparison equal "
            "between %s and %s is %s\n");
        SetFormat(debug, testComparisonNotEqual, "Test comparison equal "
            "between %s and %s is %s\n");
        SetFormat(err, testComparisonNotEqual, "Error comparison equal "
            "between %s and %s is not %s\n");

        TestComparisonMore testComparisonMore;
        SetFormat(info, testComparisonMore, "Test comparison more than "
            "between %s and %s is %s\n");
        SetFormat(debug, testComparisonMore, "Test comparison more than "
            "between %s and %s is %s\n");
        SetFormat(err, testComparisonMore, "Error comparison more than "
            "between %s and %s is not %s\n");
    }
    template<typename... TArgs>
    bool Result(const TestBaseOfIntfOutput &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IIntfOutputType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return std::is_base_of<BaseType, CategoryType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasCharType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ICharType,
            basic::test::Variable<TArgs...>>::Type CharType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::CharType).hash_code() == 
            typeid(CharType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasOutputType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IOutputType,
            basic::test::Variable<TArgs...>>::Type OutputType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::OutputType).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IValueType,
            basic::test::Variable<TArgs...>>::Type ValueType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::ValueType).hash_code() == 
            typeid(ValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasCodeValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ICodeValueType,
            basic::test::Variable<TArgs...>>::Type CodeValueType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::CodeValueType).hash_code() == 
            typeid(CodeValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasConditionValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IConditionValueType,
            basic::test::Variable<TArgs...>>::Type ConditionValueType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::ConditionValueType).hash_code() ==
            typeid(ConditionValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasStringType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IStringType,
            basic::test::Variable<TArgs...>>::Type StringType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::StringType).hash_code() ==
            typeid(StringType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasCodeType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::CodeType).hash_code() ==
            typeid(CodeType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasConditionType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IConditionType,
            basic::test::Variable<TArgs...>>::Type ConditionType;
        typedef typename basic::test::var::Element<ICategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return typeid(typename CategoryType::ConditionType).hash_code() ==
            typeid(ConditionType).hash_code();
    }
    template<std::size_t ICaseId, typename... TArgs>
    bool Result(const basic::test::type::Index<TestComparisonNotEqual, 
        ICaseId> &, basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<
            IComparisonArgs0ParamValue>(var).Get().template At<ICaseId>();
        auto * other_ptr = basic::test::var::At<
            IComparisonArgs1ParamValue>(var).Get().template At<ICaseId>();
        auto & res = basic::test::var::At<IComparisonResultSeqValue>(var).
            Get().template At<ICaseId>();
        if (!obj_ptr || !other_ptr) return false;
        return (*obj_ptr != *other_ptr) == res;
    }
    template<std::size_t ICaseId, typename... TArgs>
    bool Result(const basic::test::type::Index<TestComparisonMore, 
        ICaseId> &, basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<
            IComparisonArgs0ParamValue>(var).Get().template At<ICaseId>();
        auto * other_ptr = basic::test::var::At<
            IComparisonArgs1ParamValue>(var).Get().template At<ICaseId>();
        auto & res = basic::test::var::At<IComparisonResultSeqValue>(var).
            Get().template At<ICaseId>();
        if (!obj_ptr || !other_ptr) return false;
        return (*obj_ptr > *other_ptr) == res;
    }
};

typedef basic::test::type::Parameter<
    TestBaseOfIntfOutput,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasValueType,
    TestAliasCodeValueType,
    TestAliasConditionValueType,
    TestAliasStringType,
    TestAliasCodeType,
    TestAliasConditionType> Case1;

typedef basic::test::type::Parameter<
    basic::test::type::Index<TestComparisonNotEqual, 0>> Case2;

typedef basic::test::type::Parameter<
    basic::test::type::Index<TestComparisonMore, 0>> Case3;

typedef VariableTestCategory<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T1Var1;
typedef VariableTestCategory<
    basic::test::type::Parameter<
        const basic::err::sys::Category>,
    basic::test::type::Parameter<
        const basic::err::sys::Category>> T2Var1;
typedef VariableTestCategory<
    basic::test::type::Parameter<
        const basic::err::sys::Category>,
    basic::test::type::Parameter<
        const basic::err::sys::Category>> T3Var1;

#define BASE_TYPE(T) typename T::BaseType

auto & categ1 = basic::err::sys::tmpl::Category<CategoryTrait1>::GetInstance();
auto & categ2 = basic::err::sys::tmpl::Category<CategoryTrait2>::GetInstance();

T1Var1 t1_var1{&categ1};

REGISTER_TEST(t1, new TestCategory<Case1, BASE_TYPE(T1Var1)>(t1_var1));

T2Var1 t2_var1{nullptr, &categ1, &categ1, false};

REGISTER_TEST(t2, new TestCategory<Case2, BASE_TYPE(T2Var1)>(t2_var1));

T3Var1 t3_var1{nullptr, &categ2, &categ1, false};

REGISTER_TEST(t3, new TestCategory<Case3, BASE_TYPE(T3Var1)>(t3_var1));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);

BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", basic::err::sys::Condition);
BASIC_TEST_TYPE_NAME("basic::err::intf::Output", basic::err::intf::Output);
BASIC_TEST_TYPE_NAME("basic::err::intf::Exit", basic::err::intf::Exit);
BASIC_TEST_TYPE_NAME("basic::err::sys::intf::Category", 
    basic::err::sys::intf::Category);

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

BASIC_TEST_TYPE_NAME("basic::err::msg::String", 
    basic::err::msg::String);

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<std::basic_ostream<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::basic_ostream<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, *tArg1CStr,
            *tArg2CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<std::char_traits<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::char_traits<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<const TArg>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "const %s";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

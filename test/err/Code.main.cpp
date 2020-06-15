#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/Code.h"

#include <cstdio>
#include <cstring>
#include <utility>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

const char * ToString0(bool && b)
{
    static char true_cstr[] = "true";
    static char false_cstr[] = "false";
    return b ? true_cstr : false_cstr;
};

const char * ToString0(basic::err::defn::type::code::Value * && val)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "%d", *val);
    return tmp;
};

struct TestAliasCodeValueType {};
struct TestValueValue {};
struct TestCallCopyAssignment {};
struct TestCallMoveAssignment {};
struct TestCallValueAssignment {};
struct TestComparisonNotEqual {};

template<
    typename TAssignmentParamType,
    typename TComparisonArgs0ParamType,
    typename TComparisonArgs1ParamType,
    typename TAssignmentParamValue,
    typename TComparisonArgs0ParamValue, 
    typename TComparisonArgs1ParamValue,
    std::size_t NComparison>
using VariableTestCode_ = basic::test::Variable<
    basic::err::Code,
    basic::err::defn::type::code::Value,
    TAssignmentParamType,
    TComparisonArgs0ParamType,
    TComparisonArgs1ParamType,
    basic::test::Value<basic::err::Code *>,
    basic::test::Value<basic::err::defn::type::code::Value *>,
    TAssignmentParamValue,
    TComparisonArgs0ParamValue,
    TComparisonArgs1ParamValue,
    basic::test::val::Sequence<bool, NComparison>,
    basic::test::type::Function<
        const char *(basic::err::defn::type::code::Value * &&), ToString0>,
    basic::test::type::Function<const char *(bool &&), &ToString0>>;

template<typename TAssignmentArgs, typename TComparison0Args, 
    typename TComparison1Args>
struct VariableTestCode {};

template<typename... TAssignmentArgs, typename... TComparison0Args, 
    typename... TComparison1Args>
struct VariableTestCode<
    basic::test::type::Parameter<TAssignmentArgs...>,
    basic::test::type::Parameter<TComparison0Args...>,
    basic::test::type::Parameter<TComparison1Args...>> : 
        VariableTestCode_< 
            basic::test::type::Parameter<TAssignmentArgs...>,
            basic::test::type::Parameter<TComparison0Args...>,
            basic::test::type::Parameter<TComparison1Args...>,
            basic::test::val::Parameter<TAssignmentArgs *...>,
            basic::test::val::Parameter<TComparison0Args *...>,
            basic::test::val::Parameter<TComparison1Args *...>,
            sizeof...(TComparison0Args)>
{
    typedef VariableTestCode_< 
        basic::test::type::Parameter<TAssignmentArgs...>,
        basic::test::type::Parameter<TComparison0Args...>,
        basic::test::type::Parameter<TComparison1Args...>,
        basic::test::val::Parameter<TAssignmentArgs *...>,
        basic::test::val::Parameter<TComparison0Args *...>,
        basic::test::val::Parameter<TComparison1Args *...>,
        sizeof...(TComparison0Args)> BaseType;

    template<typename... TValArgs>
    VariableTestCode(TValArgs&&... val_args) :
        BaseType(std::forward<TValArgs>(val_args)...)
    {}
};

enum : std::size_t
{
    ICodeType,
    ICodeValueType,
    IAssignmentParamType,
    IComparisonArg0ParamType,
    IComparisonArg1ParamType,
    ICodeValue,
    ICodeValueValue,
    IAssignmentParamValue,
    IComparisonArg0ParamValue,
    IComparisonArg1ParamValue,
    IComparisonResultSeqValue,
    IValueToStringTypeFunc,
    IBoolToStringTypeFunc
};

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestValueValue,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Function<IValueToStringTypeFunc,
        basic::test::msg::arg::Value<ICodeValueValue>>, 
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestValueValue;

typedef basic::test::msg::Base<TestValueValue, char, 
    ArgTestValueValue, ArgTestValueValue, 
    ArgTestValueValue> MessageBaseTestValueValue;

typedef basic::test::msg::Argument<TestCallCopyAssignment,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IAssignmentParamType>>
        ArgTestCallCopyAssignment;

typedef basic::test::msg::Base<TestCallCopyAssignment, char, 
    ArgTestCallCopyAssignment, ArgTestCallCopyAssignment, 
    ArgTestCallCopyAssignment> MessageBaseTestCallCopyAssignment;

typedef basic::test::msg::Argument<TestCallMoveAssignment,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IAssignmentParamType>>
        ArgTestCallMoveAssignment;

typedef basic::test::msg::Base<TestCallMoveAssignment, char, 
    ArgTestCallMoveAssignment, ArgTestCallMoveAssignment, 
    ArgTestCallMoveAssignment> MessageBaseTestCallMoveAssignment;

typedef basic::test::msg::Argument<TestCallValueAssignment,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IAssignmentParamType>>
        ArgTestCallValueAssignment;

typedef basic::test::msg::Base<TestCallValueAssignment, char, 
    ArgTestCallValueAssignment, ArgTestCallValueAssignment, 
    ArgTestCallValueAssignment> MessageBaseTestCallValueAssignment;

typedef basic::test::msg::Argument<TestComparisonNotEqual,
    basic::test::msg::arg::type::Index<IComparisonArg0ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Index<IComparisonArg1ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Function<IBoolToStringTypeFunc,
        basic::test::msg::arg::type::Index<IComparisonResultSeqValue,
            basic::test::msg::arg::val::seq::At>>>
                ArgTestComparisonNotEqual;

typedef basic::test::msg::Base<TestComparisonNotEqual, char, 
    ArgTestComparisonNotEqual, ArgTestComparisonNotEqual, 
    ArgTestComparisonNotEqual> MessageBaseTestComparisonNotEqual;

template<typename TCases, typename... TVariables>
struct TestCode :
    public basic::test::Message<BASIC_TEST, TestCode<TCases, 
        TVariables...>>,
    public basic::test::Case<TestCode<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestCode<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestValueValue,
    public MessageBaseTestCallCopyAssignment,
    public MessageBaseTestCallMoveAssignment,
    public MessageBaseTestCallValueAssignment,
    public MessageBaseTestComparisonNotEqual
{
public:
    using basic::test::Case<TestCode<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestCode<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestValueValue::Format;
    using MessageBaseTestValueValue::SetFormat;
    using MessageBaseTestValueValue::Argument;
    using MessageBaseTestCallCopyAssignment::Format;
    using MessageBaseTestCallCopyAssignment::SetFormat;
    using MessageBaseTestCallCopyAssignment::Argument;
    using MessageBaseTestCallMoveAssignment::Format;
    using MessageBaseTestCallMoveAssignment::SetFormat;
    using MessageBaseTestCallMoveAssignment::Argument;
    using MessageBaseTestCallValueAssignment::Format;
    using MessageBaseTestCallValueAssignment::SetFormat;
    using MessageBaseTestCallValueAssignment::Argument;
    using MessageBaseTestComparisonNotEqual::Format;
    using MessageBaseTestComparisonNotEqual::SetFormat;
    using MessageBaseTestComparisonNotEqual::Argument;
public:
    TestCode(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestCode<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestCode<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestCode<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(err, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType is not same with %s\n");

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test Value %s::"
            "Value() is same with %s {%s}\n");
        SetFormat(debug, testValueValue, "Test Value %s::"
            "Value() is same with %s {%s}\n");
        SetFormat(err, testValueValue, "Error Value %s::"
            "Value() is not same with %s {%s}\n");

        TestCallCopyAssignment testCallCopyAssignment;
        SetFormat(info, testCallCopyAssignment, "Test Call %s "
            "Copy Assignment with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallCopyAssignment, "Test Call %s "
            "Copy Assignment with {%s} as parameter(s) type\n");
        SetFormat(err, testCallCopyAssignment, "Error Call %s "
            "Copy Assignment with {%s} as parameter(s) type\n");

        TestCallMoveAssignment testCallMoveAssignment;
        SetFormat(info, testCallMoveAssignment, "Test Call %s "
            "Move Assignment with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallMoveAssignment, "Test Call %s "
            "Move Assignment with {%s} as parameter(s) type\n");
        SetFormat(err, testCallMoveAssignment, "Error Call %s "
            "Move Assignment with {%s} as parameter(s) type\n");

        TestCallValueAssignment testCallValueAssignment;
        SetFormat(info, testCallValueAssignment, "Test Call %s "
            "Value Assignment with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallValueAssignment, "Test Call %s "
            "Value Assignment with {%s} as parameter(s) type\n");
        SetFormat(err, testCallValueAssignment, "Error Call %s "
            "Value Assignment with {%s} as parameter(s) type\n");

        TestComparisonNotEqual testComparisonNotEqual;
        SetFormat(info, testComparisonNotEqual, "Test comparison equal "
            "between %s and %s is %s\n");
        SetFormat(debug, testComparisonNotEqual, "Test comparison equal "
            "between %s and %s is %s\n");
        SetFormat(err, testComparisonNotEqual, "Error comparison equal "
            "between %s and %s is not %s\n");
    }
    template<typename... TArgs>
    bool Result(const TestAliasCodeValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        typedef typename basic::test::var::Element<ICodeValueType,
            basic::test::Variable<TArgs...>>::Type CodeValueType;
        return typeid(typename CodeType::CodeValueType).hash_code() == 
            typeid(CodeValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestValueValue &, basic::test::Variable<TArgs...> & var)
    {
        auto * code = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * code_val = basic::test::var::At<ICodeValueValue>(var).Get().
            Get();
        if (!code || !code_val) return false;
        return code->Value() == *code_val;
    }
    template<typename... TArgs>
    bool Result(const TestCallCopyAssignment &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IAssignmentParamValue>(var).
            Get().template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        *obj_ptr = *arg0_ptr;
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallMoveAssignment &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IAssignmentParamValue>(var).
            Get().template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        *obj_ptr = std::move(*arg0_ptr);
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallValueAssignment &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IAssignmentParamValue>(var).
            Get().template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        *obj_ptr = *arg0_ptr;
        return true;
    }
    template<std::size_t ICaseId, typename... TArgs>
    bool Result(const basic::test::type::Index<TestComparisonNotEqual, 
        ICaseId> &, basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<
            IComparisonArg0ParamValue>(var).Get().template At<ICaseId>();
        auto * other_ptr = basic::test::var::At<
            IComparisonArg1ParamValue>(var).Get().template At<ICaseId>();
        auto & res = basic::test::var::At<IComparisonResultSeqValue>(var).
            Get().template At<ICaseId>();
        if (!obj_ptr || !other_ptr) return false;
        return (*obj_ptr != *other_ptr) == res;
    }
};

typedef basic::test::type::Parameter<
    TestAliasCodeValueType> Case1;
typedef basic::test::type::Parameter<
    TestValueValue> Case2;
typedef basic::test::type::Parameter<
    TestCallCopyAssignment,
    TestValueValue> Case3;
typedef basic::test::type::Parameter<
    TestCallMoveAssignment,
    TestValueValue> Case4;
typedef basic::test::type::Parameter<
    TestCallValueAssignment,
    TestValueValue> Case5;
typedef basic::test::type::Parameter<
    basic::test::type::Index<TestComparisonNotEqual, 0>,
    basic::test::type::Index<TestComparisonNotEqual, 1>,
    basic::test::type::Index<TestComparisonNotEqual, 2>> Case6;

typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T1Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T2Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        basic::err::Code>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T3Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        basic::err::Code>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T4Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T5Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        basic::err::defn::type::code::Value>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T6Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<
        basic::err::Code,
        basic::err::Code,
        basic::err::defn::type::code::Value>,
    basic::test::type::Parameter<
        basic::err::Code,
        basic::err::defn::type::code::Value,
        basic::err::Code>> T7Var1;

#define BASE_TYPE(T) typename T::BaseType

T1Var1 t1_var1{nullptr, nullptr};

REGISTER_TEST(t1, new TestCode<Case1, BASE_TYPE(T1Var1)>(t1_var1));

basic::err::Code code2_1{};
basic::err::Code code2_2{4};
basic::err::Code code2_3{code2_2};
basic::err::Code code2_4{code2_2};
basic::err::Code code2_5{std::move(code2_4)};
basic::err::defn::type::code::Value code_val2_1 = 0;
basic::err::defn::type::code::Value code_val2_2 = 4;

T2Var1 t2_var1{&code2_1, &code_val2_1};
T2Var1 t2_var2{&code2_2, &code_val2_2};
T2Var1 t2_var3{&code2_3, &code_val2_2};
T2Var1 t2_var4{&code2_5, &code_val2_2};
T2Var1 t2_var5{&code2_4, &code_val2_1};

REGISTER_TEST(t2, new TestCode<Case2, BASE_TYPE(T2Var1), BASE_TYPE(T2Var1),
    BASE_TYPE(T2Var1), BASE_TYPE(T2Var1), BASE_TYPE(T2Var1)>(t2_var1, t2_var2,
    t2_var3, t2_var4, t2_var5));

basic::err::Code code3_1{};
basic::err::Code code3_2{4};
basic::err::defn::type::code::Value code_val3_1 = 0;
basic::err::defn::type::code::Value code_val3_2 = 4;

T3Var1 t3_var1{&code3_1, &code_val3_2, &code3_2};

REGISTER_TEST(t3, new TestCode<Case3, BASE_TYPE(T3Var1)>(t3_var1));

basic::err::Code code4_1{};
basic::err::Code code5_1{4};
basic::err::defn::type::code::Value code_val4_1 = 4;
basic::err::defn::type::code::Value code_val5_1 = 0;

T4Var1 t4_var1{&code4_1, &code_val4_1, &code5_1};
T5Var1 t5_var1{&code5_1, &code_val5_1};

REGISTER_TEST(t4, new TestCode<Case4, BASE_TYPE(T4Var1)>(t4_var1));
REGISTER_TEST(t5, new TestCode<Case2, BASE_TYPE(T5Var1)>(t5_var1));

basic::err::Code code6_1{};
basic::err::defn::type::code::Value code_val6_1 = 4;

T6Var1 t6_var1{&code6_1, &code_val6_1, &code_val6_1};

REGISTER_TEST(t6, new TestCode<Case5, BASE_TYPE(T6Var1)>(t6_var1));

basic::err::Code code7_1{};
basic::err::Code code7_2{4};
basic::err::defn::type::code::Value code_val7_1 = 0;
basic::err::defn::type::code::Value code_val7_2 = 4;

T7Var1 t7_var1{nullptr, nullptr, 
    &code7_1, &code7_1, &code_val7_1, 
    &code7_2, &code_val7_2, &code7_2,
    true, true, true};

REGISTER_TEST(t7, new TestCode<Case6, BASE_TYPE(T7Var1)>(t7_var1));

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
BASIC_TEST_TYPE_NAME("basic::err::Code", basic::err::Code);


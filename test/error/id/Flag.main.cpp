#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/CString.h"
#include "test/cstr/out/Argument.h"

#include "error/id/Flag.h"

BASIC_TEST_CONSTRUCT;

const char * BoolToCstr(bool && b)
{
    return b ? "true" : "false";
}

basic::test::CString<char> ToCString(basic::error::id::Flag * && f)
{
    return basic::test::cstr::Format(4 + sizeof(*f), "0x%x",
        reinterpret_cast<const unsigned char&>(*f));
}

bool CompareFlag(basic::error::id::Flag * && a,
    basic::error::id::Flag * && b)
{
    return reinterpret_cast<const unsigned char&>(*a) ==
        reinterpret_cast<const unsigned char&>(*b);
}

typedef std::uint8_t FlagValueType;

struct TestIsSameValue {};
struct TestDefaultAValue {};
struct TestBadAValue {};
struct TestStandardAValue {};
struct TestCatchAValue {};
struct TestSystemAValue {};
struct TestAAssignFlagCatch {};
struct TestAliasValueType {};

using VariableTestIdFlag = basic::test::Variable<
    basic::error::id::Flag,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::id::Flag *>,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::id::Flag *>,
    basic::test::type::Function<bool(basic::error::id::Flag * &&,
        basic::error::id::Flag * &&), &CompareFlag>,
    basic::test::type::Function<basic::test::
        CString<char>(basic::error::id::Flag * &&), &ToCString>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::type::Function<const char *(bool &&), &BoolToCstr>,
    FlagValueType>;

constexpr std::size_t IFlagValueType = 0;
constexpr std::size_t IAName = 1;
constexpr std::size_t IAValue = 2;
constexpr std::size_t IBName = 3;
constexpr std::size_t IBValue = 4;
constexpr std::size_t ICompareFlagFunc = 5;
constexpr std::size_t IFlagToCstrFunc = 6;
constexpr std::size_t IDefaultValue = 7;
constexpr std::size_t IBadValue = 8;
constexpr std::size_t IStandardValue = 9;
constexpr std::size_t ICatchValue = 10;
constexpr std::size_t ISystemValue = 11;
constexpr std::size_t IBoolToCstrFunc = 12;
constexpr std::size_t IAliasValueType = 13;

typedef basic::test::msg::Argument<TestIsSameValue,
    basic::test::msg::arg::Value<IAName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IAValue>>,
    basic::test::msg::arg::Value<IBName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IBValue>>> ArgTestIsSameValue;

typedef basic::test::msg::Base<TestIsSameValue, char, 
    ArgTestIsSameValue, ArgTestIsSameValue, 
    ArgTestIsSameValue> MessageBaseTestIsSameValue;

typedef basic::test::msg::Argument<TestDefaultAValue,
    basic::test::msg::arg::Value<IAName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IAValue>>,
    basic::test::msg::arg::type::Function<IBoolToCstrFunc,
        basic::test::msg::arg::Value<IDefaultValue>>> ArgTestDefaultAValue;

typedef basic::test::msg::Base<TestDefaultAValue, char, 
    ArgTestDefaultAValue, ArgTestDefaultAValue, 
    ArgTestDefaultAValue> MessageBaseTestDefaultAValue;

typedef basic::test::msg::Argument<TestBadAValue,
    basic::test::msg::arg::Value<IAName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IAValue>>,
    basic::test::msg::arg::type::Function<IBoolToCstrFunc,
        basic::test::msg::arg::Value<IBadValue>>> ArgTestBadAValue;

typedef basic::test::msg::Base<TestBadAValue, char, 
    ArgTestBadAValue, ArgTestBadAValue, 
    ArgTestBadAValue> MessageBaseTestBadAValue;

typedef basic::test::msg::Argument<TestStandardAValue,
    basic::test::msg::arg::Value<IAName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IAValue>>,
    basic::test::msg::arg::type::Function<IBoolToCstrFunc,
        basic::test::msg::arg::Value<IStandardValue>>> ArgTestStandardAValue;

typedef basic::test::msg::Base<TestStandardAValue, char, 
    ArgTestStandardAValue, ArgTestStandardAValue, 
    ArgTestStandardAValue> MessageBaseTestStandardAValue;

typedef basic::test::msg::Argument<TestCatchAValue,
    basic::test::msg::arg::Value<IAName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IAValue>>,
    basic::test::msg::arg::type::Function<IBoolToCstrFunc,
        basic::test::msg::arg::Value<ICatchValue>>> ArgTestCatchAValue;

typedef basic::test::msg::Base<TestCatchAValue, char, 
    ArgTestCatchAValue, ArgTestStandardAValue, 
    ArgTestCatchAValue> MessageBaseTestCatchAValue;

typedef basic::test::msg::Argument<TestSystemAValue,
    basic::test::msg::arg::Value<IAName>,
    basic::test::msg::arg::type::Function<IFlagToCstrFunc, 
        basic::test::msg::arg::Value<IAValue>>,
    basic::test::msg::arg::type::Function<IBoolToCstrFunc,
        basic::test::msg::arg::Value<ISystemValue>>> ArgTestSystemAValue;

typedef basic::test::msg::Base<TestSystemAValue, char, 
    ArgTestSystemAValue, ArgTestSystemAValue, 
    ArgTestSystemAValue> MessageBaseTestSystemAValue;

typedef basic::test::msg::Argument<TestAAssignFlagCatch,
    basic::test::msg::arg::Value<IAName>> ArgTestAAssignFlagCatch;

typedef basic::test::msg::Base<TestAAssignFlagCatch, char, 
    ArgTestAAssignFlagCatch, ArgTestAAssignFlagCatch, 
    ArgTestAAssignFlagCatch> MessageBaseTestAAssignFlagCatch;

typedef basic::test::msg::Argument<TestAliasValueType,
    basic::test::msg::arg::type::Name<IFlagValueType>,
    basic::test::msg::arg::type::Name<IAliasValueType>> 
        ArgTestAliasValueType;

typedef basic::test::msg::Base<TestAliasValueType, char, 
    ArgTestAliasValueType, ArgTestAliasValueType, 
    ArgTestAliasValueType> MessageBaseTestAliasValueType;

template<typename TCases, typename... TVariables>
class TestIdFlagType :
    public MessageBaseTestIsSameValue,
    public MessageBaseTestDefaultAValue,
    public MessageBaseTestBadAValue,
    public MessageBaseTestStandardAValue,
    public MessageBaseTestCatchAValue,
    public MessageBaseTestSystemAValue,
    public MessageBaseTestAAssignFlagCatch,
    public MessageBaseTestAliasValueType,
    public basic::test::Message<BASIC_TEST, TestIdFlagType<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdFlagType<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdFlagType<TCases, TVariables...>, 
        TVariables...>
{
public:
    using MessageBaseTestIsSameValue::Format;
    using MessageBaseTestIsSameValue::SetFormat;
    using MessageBaseTestIsSameValue::Argument;
    using MessageBaseTestDefaultAValue::Format;
    using MessageBaseTestDefaultAValue::SetFormat;
    using MessageBaseTestDefaultAValue::Argument;
    using MessageBaseTestBadAValue::Format;
    using MessageBaseTestBadAValue::SetFormat;
    using MessageBaseTestBadAValue::Argument;
    using MessageBaseTestStandardAValue::Format;
    using MessageBaseTestStandardAValue::SetFormat;
    using MessageBaseTestStandardAValue::Argument;
    using MessageBaseTestCatchAValue::Format;
    using MessageBaseTestCatchAValue::SetFormat;
    using MessageBaseTestCatchAValue::Argument;
    using MessageBaseTestSystemAValue::Format;
    using MessageBaseTestSystemAValue::SetFormat;
    using MessageBaseTestSystemAValue::Argument;
    using MessageBaseTestAAssignFlagCatch::Format;
    using MessageBaseTestAAssignFlagCatch::SetFormat;
    using MessageBaseTestAAssignFlagCatch::Argument;
    using MessageBaseTestAliasValueType::Format;
    using MessageBaseTestAliasValueType::SetFormat;
    using MessageBaseTestAliasValueType::Argument;
    using basic::test::Case<TestIdFlagType<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdFlagType<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdFlagType(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdFlagType<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdFlagType<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdFlagType<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestIsSameValue testIsSameValue;
        basic::test::msg::Format<char> formatIsSameValue("Test %s{value %s} "
            "and %s{value %s} is same\n");
        SetFormat(debug, testIsSameValue, formatIsSameValue);
        SetFormat(info, testIsSameValue, std::move(formatIsSameValue));
        SetFormat(error, testIsSameValue, "Error %s{value %s} and "
            "%s{value %s} is not same\n");
        
        TestDefaultAValue testDefaultAValue;
        basic::test::msg::Format<char> formatDefaultAValue("Test Default flag "
            "of %s{value %s} is %s\n");
        SetFormat(debug, testDefaultAValue, formatDefaultAValue);
        SetFormat(info, testDefaultAValue, std::move(formatDefaultAValue));
        SetFormat(error, testDefaultAValue, "Error Default flag "
            "of %s{value %s} is not same with %s\n");

        TestBadAValue testBadAValue;
        basic::test::msg::Format<char> formatBadAValue("Test Bad flag of "
            "%s{value %s} is %s\n");
        SetFormat(debug, testBadAValue, formatBadAValue);
        SetFormat(info, testBadAValue, std::move(formatBadAValue));
        SetFormat(error, testBadAValue, "Error Bad flag of %s{value %s} "
            "is not same with %s\n");

        TestStandardAValue testStandardAValue;
        basic::test::msg::Format<char> formatStandardAValue("Test "
            "Standard flag of %s{value %s} is %s\n");
        SetFormat(debug, testStandardAValue, formatStandardAValue);
        SetFormat(info, testStandardAValue, std::move(formatStandardAValue));
        SetFormat(error, testStandardAValue, "Error Standard flag of "
            "%s{value %s} is not same with %s\n");

        TestCatchAValue testCatchAValue;
        basic::test::msg::Format<char> formatCatchAValue("Test "
            "Catch flag of %s{value %s} is %s\n");
        SetFormat(debug, testCatchAValue, formatCatchAValue);
        SetFormat(info, testCatchAValue, std::move(formatCatchAValue));
        SetFormat(error, testCatchAValue, "Error Catch flag of "
            "%s{value %s} is not same with %s\n");

        TestSystemAValue testSystemAValue;
        basic::test::msg::Format<char> formatSystemAValue("Test "
            "System flag of %s{value %s} is %s\n");
        SetFormat(debug, testSystemAValue, formatSystemAValue);
        SetFormat(info, testSystemAValue, std::move(formatSystemAValue));
        SetFormat(error, testSystemAValue, "Error System flag of "
            "%s{value %s} is not same with %s\n");

        TestAAssignFlagCatch testAAssignFlagCatch;
        SetFormat(debug, testAAssignFlagCatch, "Assign %s with "
            "basic::error::id::flag::Catch{}\n");
        SetFormat(info, testAAssignFlagCatch, "Assign %s with "
            "basic::error::id::flag::Catch{}\n");
        SetFormat(error, testAAssignFlagCatch, "Error value of "
            "%s is nullptr\n");
        
        TestAliasValueType testAliasValueType;
        basic::test::msg::Format<char> formatAliasTypeCodeValue("Test "
            "alias type %s::ValueType is same type with %s\n");
        SetFormat(debug, testAliasValueType, formatAliasTypeCodeValue);
        SetFormat(info, testAliasValueType, 
            std::move(formatAliasTypeCodeValue));
        SetFormat(error, testAliasValueType, "Error alias type "
            "%s::ValueType is not same type with %s\n");
    }
public:
    bool Result(const TestIsSameValue &, VariableTestIdFlag & var)
    {
        return basic::test::var::At<ICompareFlagFunc>(var).Get().Call(
            std::move(basic::test::var::At<IAValue>(var).Get().Get()),
            std::move(basic::test::var::At<IBValue>(var).Get().Get()));
    }
    bool Result(const TestDefaultAValue &, VariableTestIdFlag & var)
    {
        return basic::test::var::At<IAValue>(var).Get().Get()->IsDefault() ==
            basic::test::var::At<IDefaultValue>(var).Get().Get();
    }
    bool Result(const TestBadAValue &, VariableTestIdFlag & var)
    {
        return basic::test::var::At<IAValue>(var).Get().Get()->IsBad() ==
            basic::test::var::At<IBadValue>(var).Get().Get();
    }
    bool Result(const TestStandardAValue &, VariableTestIdFlag & var)
    {
        return basic::test::var::At<IAValue>(var).Get().Get()->IsStandard() ==
            basic::test::var::At<IStandardValue>(var).Get().Get();
    }
    bool Result(const TestCatchAValue &, VariableTestIdFlag & var)
    {
        return basic::test::var::At<IAValue>(var).Get().Get()->IsCatch() ==
            basic::test::var::At<ICatchValue>(var).Get().Get();
    }
    bool Result(const TestSystemAValue &, VariableTestIdFlag & var)
    {
        return basic::test::var::At<IAValue>(var).Get().Get()->IsSystem() ==
            basic::test::var::At<ISystemValue>(var).Get().Get();
    }
    bool Result(const TestAAssignFlagCatch &, VariableTestIdFlag & var)
    {
        auto a_value = basic::test::var::At<IAValue>(var).Get().Get();
        if (a_value == nullptr)
            return false;
        *a_value = basic::error::id::flag::Catch{};
        return true;
    }
    bool Result(const TestAliasValueType &, VariableTestIdFlag & var)
    {
        return typeid(typename basic::error::id::Flag::ValueType).
            hash_code() == typeid(FlagValueType).hash_code();
    }
};

using Case1 = basic::test::type::Parameter<TestDefaultAValue, TestBadAValue,
    TestStandardAValue, TestCatchAValue, TestSystemAValue, TestAliasValueType>;
using Case2 = basic::test::type::Parameter<TestIsSameValue, TestDefaultAValue, 
    TestBadAValue, TestStandardAValue, TestCatchAValue, TestSystemAValue,
    TestAliasValueType>;
using Case3 = basic::test::type::Parameter<TestAAssignFlagCatch, 
    TestIsSameValue, TestDefaultAValue, TestBadAValue, TestStandardAValue, 
    TestCatchAValue, TestSystemAValue, TestAliasValueType>;

BASIC_TEST_TYPE_NAME("unsigned char", unsigned char);

basic::error::id::Flag obj_undefined;

basic::error::id::Flag obj1_1;

VariableTestIdFlag t1_var1{"obj1_1", &obj1_1, "undefined", &obj_undefined,
    true, false, false, false, false};

REGISTER_TEST(t1, new TestIdFlagType<Case1, VariableTestIdFlag>(t1_var1));

basic::error::id::Flag obj2_1{basic::error::id::flag::Error{}};
basic::error::id::Flag obj2_2{obj2_1};
basic::error::id::Flag obj2_3{basic::error::id::flag::Error{}};
basic::error::id::Flag obj2_4{std::move(obj2_3)};

VariableTestIdFlag t2_var1{"obj2_1", &obj2_1, "obj2_2", &obj2_2,
    false, false, false, false, false};
VariableTestIdFlag t2_var2{"obj2_3", &obj2_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t2_var3{"obj2_4", &obj2_4, "obj2_2", &obj2_2,
    false, false, false, false, false};

REGISTER_TEST(t2, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t2_var1, t2_var2, t2_var3));

basic::error::id::Flag obj3_1{basic::error::id::flag::Error{},
    basic::error::id::flag::Standard{}};
basic::error::id::Flag obj3_2{obj3_1};
basic::error::id::Flag obj3_3{basic::error::id::flag::Error{},
    basic::error::id::flag::Standard{}};
basic::error::id::Flag obj3_4{std::move(obj3_3)};

VariableTestIdFlag t3_var1{"obj3_1", &obj3_1, "obj3_2", &obj3_2,
    false, false, true, false, false};
VariableTestIdFlag t3_var2{"obj3_3", &obj3_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t3_var3{"obj3_4", &obj3_4, "obj3_2", &obj3_2,
    false, false, true, false, false};

REGISTER_TEST(t3, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t3_var1, t3_var2, t3_var3));

basic::error::id::Flag obj4_1{basic::error::id::flag::System{}};
basic::error::id::Flag obj4_2{obj4_1};
basic::error::id::Flag obj4_3{basic::error::id::flag::System{}};
basic::error::id::Flag obj4_4{std::move(obj4_3)};

VariableTestIdFlag t4_var1{"obj4_1", &obj4_1, "obj4_2", &obj4_2,
    false, false, false, false, true};
VariableTestIdFlag t4_var2{"obj4_3", &obj4_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t4_var3{"obj4_4", &obj4_4, "obj4_2", &obj4_2,
    false, false, false, false, true};

REGISTER_TEST(t4, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t4_var1, t4_var2, t4_var3));

basic::error::id::Flag obj5_1{basic::error::id::flag::System{},
    basic::error::id::flag::Standard{}};
basic::error::id::Flag obj5_2{obj5_1};
basic::error::id::Flag obj5_3{basic::error::id::flag::System{},
    basic::error::id::flag::Standard{}};
basic::error::id::Flag obj5_4{std::move(obj5_3)};

VariableTestIdFlag t5_var1{"obj5_1", &obj5_1, "obj5_2", &obj5_2,
    false, false, true, false, true};
VariableTestIdFlag t5_var2{"obj5_3", &obj5_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t5_var3{"obj5_4", &obj5_4, "obj5_2", &obj5_2,
    false, false, true, false, true};

REGISTER_TEST(t5, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t5_var1, t5_var2, t5_var3));

basic::error::id::Flag obj6_1{basic::error::id::flag::Catch{}};
basic::error::id::Flag obj6_2{obj6_1};
basic::error::id::Flag obj6_3{basic::error::id::flag::Catch{}};
basic::error::id::Flag obj6_4{std::move(obj6_3)};

VariableTestIdFlag t6_var1{"obj6_1", &obj6_1, "obj6_2", &obj6_2,
    false, false, false, true, false};
VariableTestIdFlag t6_var2{"obj6_3", &obj6_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t6_var3{"obj6_4", &obj6_4, "obj6_2", &obj6_2,
    false, false, false, true, false};

REGISTER_TEST(t6, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t6_var1, t6_var2, t6_var3));

basic::error::id::Flag obj7_1{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}};
basic::error::id::Flag obj7_2{obj7_1};
basic::error::id::Flag obj7_3{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}};
basic::error::id::Flag obj7_4{std::move(obj7_3)};

VariableTestIdFlag t7_var1{"obj7_1", &obj7_1, "obj7_2", &obj7_2,
    false, false, true, true, false};
VariableTestIdFlag t7_var2{"obj7_3", &obj7_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t7_var3{"obj7_4", &obj7_4, "obj7_2", &obj7_2,
    false, false, true, true, false};

REGISTER_TEST(t7, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t7_var1, t7_var2, t7_var3));

basic::error::id::Flag obj8_1{basic::error::id::flag::Catch{},
    basic::error::id::flag::System{}};
basic::error::id::Flag obj8_2{obj8_1};
basic::error::id::Flag obj8_3{basic::error::id::flag::Catch{},
    basic::error::id::flag::System{}};
basic::error::id::Flag obj8_4{std::move(obj8_3)};

VariableTestIdFlag t8_var1{"obj8_1", &obj8_1, "obj8_2", &obj8_2,
    false, false, false, true, true};
VariableTestIdFlag t8_var2{"obj8_3", &obj8_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t8_var3{"obj8_4", &obj8_4, "obj8_2", &obj8_2,
    false, false, false, true, true};

REGISTER_TEST(t8, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t8_var1, t8_var2, t8_var3));

basic::error::id::Flag obj9_1{basic::error::id::flag::Catch{},
    basic::error::id::flag::System{}, basic::error::id::flag::Standard{}};
basic::error::id::Flag obj9_2{obj9_1};
basic::error::id::Flag obj9_3{basic::error::id::flag::Catch{},
    basic::error::id::flag::System{}, basic::error::id::flag::Standard{}};
basic::error::id::Flag obj9_4{std::move(obj9_3)};

VariableTestIdFlag t9_var1{"obj9_1", &obj9_1, "obj9_2", &obj9_2,
    false, false, true, true, true};
VariableTestIdFlag t9_var2{"obj9_3", &obj9_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t9_var3{"obj9_4", &obj9_4, "obj9_2", &obj9_2,
    false, false, true, true, true};

REGISTER_TEST(t9, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t9_var1, t9_var2, t9_var3));

basic::error::id::Flag obj10_1{basic::error::id::flag::Catch{}, obj1_1};
basic::error::id::Flag obj10_2{obj10_1};
basic::error::id::Flag obj10_3{basic::error::id::flag::Catch{}, obj1_1};
basic::error::id::Flag obj10_4{std::move(obj10_3)};

basic::error::id::Flag obj10_5{basic::error::id::flag::Catch{}, obj2_1};
basic::error::id::Flag obj10_6{obj10_5};
basic::error::id::Flag obj10_7{basic::error::id::flag::Catch{}, obj2_1};
basic::error::id::Flag obj10_8{std::move(obj10_7)};

basic::error::id::Flag obj10_9{basic::error::id::flag::Catch{}, obj3_1};
basic::error::id::Flag obj10_10{obj10_9};
basic::error::id::Flag obj10_11{basic::error::id::flag::Catch{}, obj3_1};
basic::error::id::Flag obj10_12{std::move(obj10_11)};

basic::error::id::Flag obj10_13{basic::error::id::flag::Catch{}, obj4_1};
basic::error::id::Flag obj10_14{obj10_13};
basic::error::id::Flag obj10_15{basic::error::id::flag::Catch{}, obj4_1};
basic::error::id::Flag obj10_16{std::move(obj10_15)};

basic::error::id::Flag obj10_17{basic::error::id::flag::Catch{}, obj5_1};
basic::error::id::Flag obj10_18{obj10_17};
basic::error::id::Flag obj10_19{basic::error::id::flag::Catch{}, obj5_1};
basic::error::id::Flag obj10_20{std::move(obj10_19)};

basic::error::id::Flag obj10_21{basic::error::id::flag::Catch{}, obj6_1};
basic::error::id::Flag obj10_22{obj10_21};
basic::error::id::Flag obj10_23{basic::error::id::flag::Catch{}, obj6_1};
basic::error::id::Flag obj10_24{std::move(obj10_23)};

basic::error::id::Flag obj10_25{basic::error::id::flag::Catch{}, obj7_1};
basic::error::id::Flag obj10_26{obj10_25};
basic::error::id::Flag obj10_27{basic::error::id::flag::Catch{}, obj7_1};
basic::error::id::Flag obj10_28{std::move(obj10_27)};

basic::error::id::Flag obj10_29{basic::error::id::flag::Catch{}, obj8_1};
basic::error::id::Flag obj10_30{obj10_29};
basic::error::id::Flag obj10_31{basic::error::id::flag::Catch{}, obj8_1};
basic::error::id::Flag obj10_32{std::move(obj10_31)};

basic::error::id::Flag obj10_33{basic::error::id::flag::Catch{}, obj9_1};
basic::error::id::Flag obj10_34{obj10_33};
basic::error::id::Flag obj10_35{basic::error::id::flag::Catch{}, obj9_1};
basic::error::id::Flag obj10_36{std::move(obj10_35)};

VariableTestIdFlag t10_var1{"obj10_1", &obj10_1, "obj10_2", &obj10_2,
    true, true, false, true, false};
VariableTestIdFlag t10_var2{"obj10_3", &obj10_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var3{"obj10_4", &obj10_4, "obj10_2", &obj10_2,
    true, true, false, true, false};
    
VariableTestIdFlag t10_var4{"obj10_5", &obj10_5, "obj10_6", &obj10_6,
    false, false, false, true, false};
VariableTestIdFlag t10_var5{"obj10_7", &obj10_7, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var6{"obj10_8", &obj10_8, "obj10_6", &obj10_6,
    false, false, false, true, false};

VariableTestIdFlag t10_var7{"obj10_9", &obj10_9, "obj10_10", &obj10_10,
    false, false, true, true, false};
VariableTestIdFlag t10_var8{"obj10_11", &obj10_11, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var9{"obj10_12", &obj10_12, "obj10_10", &obj10_10,
    false, false, true, true, false};

VariableTestIdFlag t10_var10{"obj10_13", &obj10_13, "obj10_14", &obj10_14,
    false, false, false, true, true};
VariableTestIdFlag t10_var11{"obj10_15", &obj10_15, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var12{"obj10_16", &obj10_16, "obj10_14", &obj10_14,
    false, false, false, true, true};

VariableTestIdFlag t10_var13{"obj10_17", &obj10_17, "obj10_18", &obj10_18,
    false, false, true, true, true};
VariableTestIdFlag t10_var14{"obj10_19", &obj10_19, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var15{"obj10_20", &obj10_20, "obj10_18", &obj10_18,
    false, false, true, true, true};

VariableTestIdFlag t10_var16{"obj10_21", &obj10_21, "obj10_22", &obj10_22,
    false, false, false, true, false};
VariableTestIdFlag t10_var17{"obj10_23", &obj10_23, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var18{"obj10_24", &obj10_24, "obj10_22", &obj10_22,
    false, false, false, true, false};

VariableTestIdFlag t10_var19{"obj10_25", &obj10_25, "obj10_26", &obj10_26,
    false, false, true, true, false};
VariableTestIdFlag t10_var20{"obj10_27", &obj10_27, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var21{"obj10_28", &obj10_28, "obj10_26", &obj10_26,
    false, false, true, true, false};

VariableTestIdFlag t10_var22{"obj10_29", &obj10_29, "obj10_30", &obj10_30,
    false, false, false, true, true};
VariableTestIdFlag t10_var23{"obj10_31", &obj10_31, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var26{"obj10_32", &obj10_32, "obj10_30", &obj10_30,
    false, false, false, true, true};

VariableTestIdFlag t10_var27{"obj10_33", &obj10_33, "obj10_34", &obj10_34,
    false, false, true, true, true};
VariableTestIdFlag t10_var28{"obj10_35", &obj10_35, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t10_var29{"obj10_36", &obj10_36, "obj10_34", &obj10_34,
    false, false, true, true, true};

REGISTER_TEST(t10, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t10_var1, t10_var2, t10_var3,
        t10_var4, t10_var5, t10_var6, t10_var7, t10_var8, t10_var9, t10_var10,
        t10_var11, t10_var12, t10_var13, t10_var14, t10_var15, t10_var16,
        t10_var17, t10_var18, t10_var19, t10_var20, t10_var21, t10_var22,
        t10_var23, t10_var26, t10_var27, t10_var28, t10_var29));

basic::error::id::Flag obj11_1{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj1_1};
basic::error::id::Flag obj11_2{obj11_1};
basic::error::id::Flag obj11_3{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj1_1};
basic::error::id::Flag obj11_4{std::move(obj11_3)};

basic::error::id::Flag obj11_5{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj2_1};
basic::error::id::Flag obj11_6{obj11_5};
basic::error::id::Flag obj11_7{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj2_1};
basic::error::id::Flag obj11_8{std::move(obj11_7)};

basic::error::id::Flag obj11_9{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj3_1};
basic::error::id::Flag obj11_10{obj11_9};
basic::error::id::Flag obj11_11{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj3_1};
basic::error::id::Flag obj11_12{std::move(obj11_11)};

basic::error::id::Flag obj11_13{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj4_1};
basic::error::id::Flag obj11_14{obj11_13};
basic::error::id::Flag obj11_15{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj4_1};
basic::error::id::Flag obj11_16{std::move(obj11_15)};

basic::error::id::Flag obj11_17{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj5_1};
basic::error::id::Flag obj11_18{obj11_17};
basic::error::id::Flag obj11_19{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj5_1};
basic::error::id::Flag obj11_20{std::move(obj11_19)};

basic::error::id::Flag obj11_21{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj6_1};
basic::error::id::Flag obj11_22{obj11_21};
basic::error::id::Flag obj11_23{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj6_1};
basic::error::id::Flag obj11_24{std::move(obj11_23)};

basic::error::id::Flag obj11_25{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj7_1};
basic::error::id::Flag obj11_26{obj11_25};
basic::error::id::Flag obj11_27{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj7_1};
basic::error::id::Flag obj11_28{std::move(obj11_27)};

basic::error::id::Flag obj11_29{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj8_1};
basic::error::id::Flag obj11_30{obj11_29};
basic::error::id::Flag obj11_31{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj8_1};
basic::error::id::Flag obj11_32{std::move(obj11_31)};

basic::error::id::Flag obj11_33{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj9_1};
basic::error::id::Flag obj11_34{obj11_33};
basic::error::id::Flag obj11_35{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, obj9_1};
basic::error::id::Flag obj11_36{std::move(obj11_35)};

VariableTestIdFlag t11_var1{"obj11_1", &obj11_1, "obj11_2", &obj11_2,
    true, true, true, true, false};
VariableTestIdFlag t11_var2{"obj11_3", &obj11_3, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var3{"obj11_4", &obj11_4, "obj11_2", &obj11_2,
    true, true, true, true, false};
    
VariableTestIdFlag t11_var4{"obj11_5", &obj11_5, "obj11_6", &obj11_6,
    false, false, true, true, false};
VariableTestIdFlag t11_var5{"obj11_7", &obj11_7, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var6{"obj11_8", &obj11_8, "obj11_6", &obj11_6,
    false, false, true, true, false};

VariableTestIdFlag t11_var7{"obj11_9", &obj11_9, "obj11_10", &obj11_10,
    false, false, true, true, false};
VariableTestIdFlag t11_var8{"obj11_11", &obj11_11, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var9{"obj11_12", &obj11_12, "obj11_10", &obj11_10,
    false, false, true, true, false};

VariableTestIdFlag t11_var10{"obj11_13", &obj11_13, "obj11_14", &obj11_14,
    false, false, true, true, true};
VariableTestIdFlag t11_var11{"obj11_15", &obj11_15, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var12{"obj11_16", &obj11_16, "obj11_14", &obj11_14,
    false, false, true, true, true};

VariableTestIdFlag t11_var13{"obj11_17", &obj11_17, "obj11_18", &obj11_18,
    false, false, true, true, true};
VariableTestIdFlag t11_var14{"obj11_19", &obj11_19, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var15{"obj11_20", &obj11_20, "obj11_18", &obj11_18,
    false, false, true, true, true};

VariableTestIdFlag t11_var16{"obj11_21", &obj11_21, "obj11_22", &obj11_22,
    false, false, true, true, false};
VariableTestIdFlag t11_var17{"obj11_23", &obj11_23, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var18{"obj11_24", &obj11_24, "obj11_22", &obj11_22,
    false, false, true, true, false};

VariableTestIdFlag t11_var19{"obj11_25", &obj11_25, "obj11_26", &obj11_26,
    false, false, true, true, false};
VariableTestIdFlag t11_var20{"obj11_27", &obj11_27, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var21{"obj11_28", &obj11_28, "obj11_26", &obj11_26,
    false, false, true, true, false};

VariableTestIdFlag t11_var22{"obj11_29", &obj11_29, "obj11_30", &obj11_30,
    false, false, true, true, true};
VariableTestIdFlag t11_var23{"obj11_31", &obj11_31, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var26{"obj11_32", &obj11_32, "obj11_30", &obj11_30,
    false, false, true, true, true};

VariableTestIdFlag t11_var27{"obj11_33", &obj11_33, "obj11_34", &obj11_34,
    false, false, true, true, true};
VariableTestIdFlag t11_var28{"obj11_35", &obj11_35, "obj1_1", &obj1_1,
    true, false, false, false, false};
VariableTestIdFlag t11_var29{"obj11_36", &obj11_36, "obj11_34", &obj11_34,
    false, false, true, true, true};

REGISTER_TEST(t11, new TestIdFlagType<Case2, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t11_var1, t11_var2, t11_var3,
        t11_var4, t11_var5, t11_var6, t11_var7, t11_var8, t11_var9, t11_var10,
        t11_var11, t11_var12, t11_var13, t11_var14, t11_var15, t11_var16,
        t11_var17, t11_var18, t11_var19, t11_var20, t11_var21, t11_var22,
        t11_var23, t11_var26, t11_var27, t11_var28, t11_var29));

VariableTestIdFlag t12_var1{"obj1_1", &obj1_1, "obj10_1", &obj10_1,
    true, true, false, true, false};
VariableTestIdFlag t12_var2{"obj2_1", &obj2_1, "obj10_5", &obj10_5,
    false, false, false, true, false};
VariableTestIdFlag t12_var3{"obj3_1", &obj3_1, "obj10_9", &obj10_9,
    false, false, true, true, false};
VariableTestIdFlag t12_var4{"obj4_1", &obj4_1, "obj10_13", &obj10_13,
    false, false, false, true, true};
VariableTestIdFlag t12_var5{"obj5_1", &obj5_1, "obj10_17", &obj10_17,
    false, false, true, true, true};
VariableTestIdFlag t12_var6{"obj6_1", &obj6_1, "obj10_21", &obj10_21,
    false, false, false, true, false};
VariableTestIdFlag t12_var7{"obj7_1", &obj7_1, "obj10_25", &obj10_25,
    false, false, true, true, false};
VariableTestIdFlag t12_var8{"obj8_1", &obj8_1, "obj10_29", &obj10_29,
    false, false, false, true, true};
VariableTestIdFlag t12_var9{"obj9_1", &obj9_1, "obj10_33", &obj10_33,
    false, false, true, true, true};

REGISTER_TEST(t12, new TestIdFlagType<Case3, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag, VariableTestIdFlag,
    VariableTestIdFlag, VariableTestIdFlag>(t12_var1, t12_var2, t12_var3,
        t12_var4, t12_var5, t12_var6, t12_var7, t12_var8, t12_var9));

int main()
{
    return RUN_TEST();
}
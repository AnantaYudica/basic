#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/CString.h"
#include "test/cstr/out/Argument.h"

#include "error/id/rec/Error.h"

#include <typeinfo>
#include <cstdint>
#include <utility>

struct TestCodeValue {};
struct TestValueAssignment {};
struct TestCopyAssignment {};
struct TestMoveAssignment {};
struct TestAliasTypeCodeValue {};

template<typename TCodeValue, typename TAssignValue = int>
using VariableTestIdRecError = basic::test::Variable<
    TCodeValue,
    TAssignValue,
    basic::error::id::rec::Error<TCodeValue>,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::id::rec::Error<TCodeValue> *>,
    basic::test::Value<TAssignValue>,
    basic::test::Value<TCodeValue>>;

constexpr std::size_t ICodeValueType = 0;
constexpr std::size_t IAssignValueType = 1;
constexpr std::size_t IIdRecErrorType = 2;
constexpr std::size_t IObjName = 3;
constexpr std::size_t IObjValue = 4;
constexpr std::size_t IAssignValue = 5;
constexpr std::size_t ICodeValue = 6;

typedef basic::test::msg::Argument<TestCodeValue,
    basic::test::msg::arg::type::Name<IIdRecErrorType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::Value<ICodeValue>> ArgTestCodeValue;

typedef basic::test::msg::Base<TestCodeValue, char, 
    ArgTestCodeValue, ArgTestCodeValue, 
    ArgTestCodeValue> MessageBaseTestCodeValue;

typedef basic::test::msg::Argument<TestValueAssignment,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IAssignValueType>,
    basic::test::msg::arg::Value<IAssignValue>> 
        ArgTestValueAssignment;

typedef basic::test::msg::Argument<TestValueAssignment,
    basic::test::msg::arg::Value<IObjName>> 
        ArgErrorTestValueAssignment;

typedef basic::test::msg::Base<TestValueAssignment, char, 
    ArgTestValueAssignment, ArgTestValueAssignment, 
    ArgErrorTestValueAssignment> MessageBaseTestValueAssignment;

typedef basic::test::msg::Argument<TestCopyAssignment,
    basic::test::msg::arg::Value<IObjName>> ArgTestCopyAssignment;

typedef basic::test::msg::Base<TestCopyAssignment, char, 
    ArgTestCopyAssignment, ArgTestCopyAssignment, 
    ArgTestCopyAssignment> MessageBaseTestCopyAssignment;

typedef basic::test::msg::Argument<TestMoveAssignment,
    basic::test::msg::arg::Value<IObjName>> ArgTestMoveAssignment;

typedef basic::test::msg::Base<TestMoveAssignment, char, 
    ArgTestMoveAssignment, ArgTestMoveAssignment, 
    ArgTestMoveAssignment> MessageBaseTestMoveAssignment;

typedef basic::test::msg::Argument<TestAliasTypeCodeValue,
    basic::test::msg::arg::type::Name<IIdRecErrorType>,
    basic::test::msg::arg::type::Name<ICodeValueType>> 
        ArgTestAliasTypeCodeValue;

typedef basic::test::msg::Base<TestAliasTypeCodeValue, char, 
    ArgTestAliasTypeCodeValue, ArgTestAliasTypeCodeValue, 
    ArgTestAliasTypeCodeValue> MessageBaseTestAliasTypeCodeValue;

template<typename TCases, typename... TVariables>
class TestIdRecError :
    public MessageBaseTestCodeValue,
    public MessageBaseTestValueAssignment,
    public MessageBaseTestCopyAssignment,
    public MessageBaseTestMoveAssignment,
    public MessageBaseTestAliasTypeCodeValue,
    public basic::test::Message<BASIC_TEST, TestIdRecError<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdRecError<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdRecError<TCases, TVariables...>, 
        TVariables...>
{
public:
    using MessageBaseTestCodeValue::Format;
    using MessageBaseTestCodeValue::SetFormat;
    using MessageBaseTestCodeValue::Argument;
    using MessageBaseTestValueAssignment::Format;
    using MessageBaseTestValueAssignment::SetFormat;
    using MessageBaseTestValueAssignment::Argument;
    using MessageBaseTestCopyAssignment::Format;
    using MessageBaseTestCopyAssignment::SetFormat;
    using MessageBaseTestCopyAssignment::Argument;
    using MessageBaseTestMoveAssignment::Format;
    using MessageBaseTestMoveAssignment::SetFormat;
    using MessageBaseTestMoveAssignment::Argument;
    using MessageBaseTestAliasTypeCodeValue::Format;
    using MessageBaseTestAliasTypeCodeValue::SetFormat;
    using MessageBaseTestAliasTypeCodeValue::Argument;
    using basic::test::Case<TestIdRecError<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdRecError<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdRecError(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdRecError<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdRecError<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdRecError<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestCodeValue testCodeValue;
        basic::test::msg::Format<char> formatCodeValue("Test return value "
            "%s::Code() {%s} is equal with %s {%d}\n");
        SetFormat(debug, testCodeValue, formatCodeValue);
        SetFormat(info, testCodeValue, std::move(formatCodeValue));
        SetFormat(error, testCodeValue, "Error return value %s::Code() {%s} "
            "is not equal with %s {%d}\n");

        TestValueAssignment testValueAssignment;
        basic::test::msg::Format<char> formatValueAssignment("Assign %s with "
            "%s {%d}\n");
        SetFormat(debug, testValueAssignment, formatValueAssignment);
        SetFormat(info, testValueAssignment, std::move(formatValueAssignment));
        SetFormat(error, testValueAssignment, "Error %s is nullptr\n");
        
        TestCopyAssignment testCopyAssignment;
        basic::test::msg::Format<char> formatCopyAssignment("Copy "
            "assign of %s\n");
        SetFormat(debug, testCopyAssignment, formatCopyAssignment);
        SetFormat(info, testCopyAssignment, std::move(formatCopyAssignment));
        SetFormat(error, testCopyAssignment, "Error %s is nullptr\n");
        
        TestMoveAssignment testMoveAssignment;
        basic::test::msg::Format<char> formatMoveAssignment("Move "
            "assign of %s\n");
        SetFormat(debug, testMoveAssignment, formatMoveAssignment);
        SetFormat(info, testMoveAssignment, std::move(formatMoveAssignment));
        SetFormat(error, testMoveAssignment, "Error %s is nullptr\n");

        TestAliasTypeCodeValue testAliasTypeCodeValue;
        basic::test::msg::Format<char> formatAliasTypeCodeValue("Test "
            "alias type %s::CodeValueType is same type with %s\n");
        SetFormat(debug, testAliasTypeCodeValue, formatAliasTypeCodeValue);
        SetFormat(info, testAliasTypeCodeValue, 
            std::move(formatAliasTypeCodeValue));
        SetFormat(error, testAliasTypeCodeValue, "Error alias type "
            "%s::CodeValueType is not same type with %s\n");
    }
public:
    template<typename TCodeValue, typename TAssignValue>
    bool Result(const TestCodeValue &, VariableTestIdRecError<TCodeValue,
        TAssignValue> & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->Code() ==
            basic::test::var::At<ICodeValue>(var).Get().Get();
    }
    template<typename TCodeValue, typename TAssignValue>
    bool Result(const TestValueAssignment &, VariableTestIdRecError<TCodeValue,
        TAssignValue> & var)
    {
        auto obj = basic::test::var::At<IObjValue>(var).Get().Get();
        if (obj != nullptr)
        {
            *obj = basic::test::var::At<IAssignValue>(var).Get().Get();
            return true;
        }
        return false;
    }
    template<typename TCodeValue, typename TAssignValue>
    bool Result(const TestCopyAssignment &, VariableTestIdRecError<TCodeValue,
        TAssignValue> & var)
    {
        auto obj = basic::test::var::At<IObjValue>(var).Get().Get();
        if (obj != nullptr)
        {
            *obj = *basic::test::var::At<IAssignValue>(var).Get().Get();
            return true;
        }
        return false;
    }
    template<typename TCodeValue, typename TAssignValue>
    bool Result(const TestMoveAssignment &, VariableTestIdRecError<TCodeValue,
        TAssignValue> & var)
    {
        auto obj = basic::test::var::At<IObjValue>(var).Get().Get();
        if (obj != nullptr)
        {
            *obj = std::move(*basic::test::var::At<IAssignValue>(var).
                Get().Get());
            return true;
        }
        return false;
    }
    template<typename TCodeValue, typename TAssignValue>
    bool Result(const TestAliasTypeCodeValue &, 
        VariableTestIdRecError<TCodeValue, TAssignValue> & var)
    {
        return typeid(typename basic::error::id::rec::Error<TCodeValue>::
            CodeValueType).hash_code() == typeid(TCodeValue).hash_code();
    }
};

using Case1 = basic::test::type::Parameter<TestAliasTypeCodeValue, 
    TestCodeValue>;
using Case2 = basic::test::type::Parameter<TestAliasTypeCodeValue, 
    TestValueAssignment, TestCodeValue>;
using Case3 = basic::test::type::Parameter<TestAliasTypeCodeValue, 
    TestCopyAssignment, TestCodeValue>;
using Case4 = basic::test::type::Parameter<TestAliasTypeCodeValue,
    TestMoveAssignment, TestCodeValue>;

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

template<typename TArg1>
struct basic::test::type::Name<basic::error::id::rec::Error<TArg1>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::rec::Code<%s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + 
            tArg1CStr.Size(), _format, *tArg1CStr);
    }
};

basic::error::id::rec::Error<std::int8_t> obj1_1;
basic::error::id::rec::Error<std::uint8_t> obj1_2;
basic::error::id::rec::Error<std::int16_t> obj1_3;
basic::error::id::rec::Error<std::uint16_t> obj1_4;
basic::error::id::rec::Error<std::int32_t> obj1_5;
basic::error::id::rec::Error<std::uint32_t> obj1_6;
basic::error::id::rec::Error<std::int64_t> obj1_7;
basic::error::id::rec::Error<std::uint64_t> obj1_8;

typedef VariableTestIdRecError<std::int8_t> T1Var1;
typedef VariableTestIdRecError<std::uint8_t> T1Var2;
typedef VariableTestIdRecError<std::int16_t> T1Var3;
typedef VariableTestIdRecError<std::uint16_t> T1Var4;
typedef VariableTestIdRecError<std::int32_t> T1Var5;
typedef VariableTestIdRecError<std::uint32_t> T1Var6;
typedef VariableTestIdRecError<std::int64_t> T1Var7;
typedef VariableTestIdRecError<std::uint64_t> T1Var8;

T1Var1 t1_var1{"obj1_1", &obj1_1, 0, 0};
T1Var2 t1_var2{"obj1_2", &obj1_2, 0, 0};
T1Var3 t1_var3{"obj1_3", &obj1_3, 0, 0};
T1Var4 t1_var4{"obj1_4", &obj1_4, 0, 0};
T1Var5 t1_var5{"obj1_5", &obj1_5, 0, 0};
T1Var6 t1_var6{"obj1_6", &obj1_6, 0, 0};
T1Var7 t1_var7{"obj1_7", &obj1_7, 0, 0};
T1Var8 t1_var8{"obj1_8", &obj1_8, 0, 0};

REGISTER_TEST(t1, new TestIdRecError<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8>(t1_var1, t1_var2, t1_var3,
        t1_var4, t1_var5, t1_var6, t1_var7, t1_var8));
        
std::int8_t error1_int8 = -127;
std::uint8_t error1_uint8 = 255;
std::int16_t error1_int16 = -32767;
std::uint16_t error1_uint16 = 65535;
std::int32_t error1_int32 = -2147483641l;
std::uint32_t error1_uint32 = 4294967295ul;
std::int64_t error1_int64 = -9223372036854775807ll;
std::uint64_t error1_uint64 = 18446744073709551615ull;

basic::error::id::rec::Error<std::int8_t> obj2_1{error1_int8};
basic::error::id::rec::Error<std::uint8_t> obj2_2{error1_uint8};
basic::error::id::rec::Error<std::int16_t> obj2_3{error1_int16};
basic::error::id::rec::Error<std::uint16_t> obj2_4{error1_uint16};
basic::error::id::rec::Error<std::int32_t> obj2_5{error1_int32};
basic::error::id::rec::Error<std::uint32_t> obj2_6{error1_uint32};
basic::error::id::rec::Error<std::int64_t> obj2_7{error1_int64};
basic::error::id::rec::Error<std::uint64_t> obj2_8{error1_uint64};

T1Var1 t2_var1{"obj2_1", &obj2_1, 0, error1_int8};
T1Var2 t2_var2{"obj2_2", &obj2_2, 0, error1_uint8};
T1Var3 t2_var3{"obj2_3", &obj2_3, 0, error1_int16};
T1Var4 t2_var4{"obj2_4", &obj2_4, 0, error1_uint16};
T1Var5 t2_var5{"obj2_5", &obj2_5, 0, error1_int32};
T1Var6 t2_var6{"obj2_6", &obj2_6, 0, error1_uint32};
T1Var7 t2_var7{"obj2_7", &obj2_7, 0, error1_int64};
T1Var8 t2_var8{"obj2_8", &obj2_8, 0, error1_uint64};

REGISTER_TEST(t2, new TestIdRecError<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8>(t2_var1, t2_var2, t2_var3,
        t2_var4, t2_var5, t2_var6, t2_var7, t2_var8));

basic::error::id::rec::Error<std::int8_t> obj3_1{obj2_1};
basic::error::id::rec::Error<std::uint8_t> obj3_2{obj2_2};
basic::error::id::rec::Error<std::int16_t> obj3_3{obj2_3};
basic::error::id::rec::Error<std::uint16_t> obj3_4{obj2_4};
basic::error::id::rec::Error<std::int32_t> obj3_5{obj2_5};
basic::error::id::rec::Error<std::uint32_t> obj3_6{obj2_6};
basic::error::id::rec::Error<std::int64_t> obj3_7{obj2_7};
basic::error::id::rec::Error<std::uint64_t> obj3_8{obj2_8};

T1Var1 t3_var1{"obj3_1", &obj3_1, 0, error1_int8};
T1Var2 t3_var2{"obj3_2", &obj3_2, 0, error1_uint8};
T1Var3 t3_var3{"obj3_3", &obj3_3, 0, error1_int16};
T1Var4 t3_var4{"obj3_4", &obj3_4, 0, error1_uint16};
T1Var5 t3_var5{"obj3_5", &obj3_5, 0, error1_int32};
T1Var6 t3_var6{"obj3_6", &obj3_6, 0, error1_uint32};
T1Var7 t3_var7{"obj3_7", &obj3_7, 0, error1_int64};
T1Var8 t3_var8{"obj3_8", &obj3_8, 0, error1_uint64};

REGISTER_TEST(t3, new TestIdRecError<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8>(t3_var1, t3_var2, t3_var3,
        t3_var4, t3_var5, t3_var6, t3_var7, t3_var8));

basic::error::id::rec::Error<std::int8_t> obj3_1_c{obj3_1};
basic::error::id::rec::Error<std::uint8_t> obj3_2_c{obj3_2};
basic::error::id::rec::Error<std::int16_t> obj3_3_c{obj3_3};
basic::error::id::rec::Error<std::uint16_t> obj3_4_c{obj3_4};
basic::error::id::rec::Error<std::int32_t> obj3_5_c{obj3_5};
basic::error::id::rec::Error<std::uint32_t> obj3_6_c{obj3_6};
basic::error::id::rec::Error<std::int64_t> obj3_7_c{obj3_7};
basic::error::id::rec::Error<std::uint64_t> obj3_8_c{obj3_8};

basic::error::id::rec::Error<std::int8_t> obj4_1{std::move(obj3_1_c)};
basic::error::id::rec::Error<std::uint8_t> obj4_2{std::move(obj3_2_c)};
basic::error::id::rec::Error<std::int16_t> obj4_3{std::move(obj3_3_c)};
basic::error::id::rec::Error<std::uint16_t> obj4_4{std::move(obj3_4_c)};
basic::error::id::rec::Error<std::int32_t> obj4_5{std::move(obj3_5_c)};
basic::error::id::rec::Error<std::uint32_t> obj4_6{std::move(obj3_6_c)};
basic::error::id::rec::Error<std::int64_t> obj4_7{std::move(obj3_7_c)};
basic::error::id::rec::Error<std::uint64_t> obj4_8{std::move(obj3_8_c)};

T1Var1 t4_var1{"obj4_1", &obj4_1, 0, error1_int8};
T1Var2 t4_var2{"obj4_2", &obj4_2, 0, error1_uint8};
T1Var3 t4_var3{"obj4_3", &obj4_3, 0, error1_int16};
T1Var4 t4_var4{"obj4_4", &obj4_4, 0, error1_uint16};
T1Var5 t4_var5{"obj4_5", &obj4_5, 0, error1_int32};
T1Var6 t4_var6{"obj4_6", &obj4_6, 0, error1_uint32};
T1Var7 t4_var7{"obj4_7", &obj4_7, 0, error1_int64};
T1Var8 t4_var8{"obj4_8", &obj4_8, 0, error1_uint64};

T1Var1 t4_var9{"obj3_1", &obj3_1_c, 0, 0};
T1Var2 t4_var10{"obj3_2", &obj3_2_c, 0, 0};
T1Var3 t4_var11{"obj3_3", &obj3_3_c, 0, 0};
T1Var4 t4_var12{"obj3_4", &obj3_4_c, 0, 0};
T1Var5 t4_var13{"obj3_5", &obj3_5_c, 0, 0};
T1Var6 t4_var14{"obj3_6", &obj3_6_c, 0, 0};
T1Var7 t4_var15{"obj3_7", &obj3_7_c, 0, 0};
T1Var8 t4_var16{"obj3_8", &obj3_8_c, 0, 0};

REGISTER_TEST(t4, new TestIdRecError<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8>(t4_var1, t4_var2, t4_var3,
        t4_var4, t4_var5, t4_var6, t4_var7, t4_var8, t4_var9, 
        t4_var10, t4_var11, t4_var12, t4_var13, t4_var14, 
        t4_var15, t4_var16));

typedef VariableTestIdRecError<std::int8_t, std::int8_t> T5Var1;
typedef VariableTestIdRecError<std::uint8_t, std::uint8_t> T5Var2;
typedef VariableTestIdRecError<std::int16_t, std::int16_t> T5Var3;
typedef VariableTestIdRecError<std::uint16_t, std::uint16_t> T5Var4;
typedef VariableTestIdRecError<std::int32_t, std::int32_t> T5Var5;
typedef VariableTestIdRecError<std::uint32_t, std::uint32_t> T5Var6;
typedef VariableTestIdRecError<std::int64_t, std::int64_t> T5Var7;
typedef VariableTestIdRecError<std::uint64_t, std::uint64_t> T5Var8;

basic::error::id::rec::Error<std::int8_t> obj5_1;
basic::error::id::rec::Error<std::uint8_t> obj5_2;
basic::error::id::rec::Error<std::int16_t> obj5_3;
basic::error::id::rec::Error<std::uint16_t> obj5_4;
basic::error::id::rec::Error<std::int32_t> obj5_5;
basic::error::id::rec::Error<std::uint32_t> obj5_6;
basic::error::id::rec::Error<std::int64_t> obj5_7;
basic::error::id::rec::Error<std::uint64_t> obj5_8;

T5Var1 t5_var1{"obj5_1", &obj5_1, error1_int8, error1_int8};
T5Var2 t5_var2{"obj5_2", &obj5_2, error1_uint8, error1_uint8};
T5Var3 t5_var3{"obj5_3", &obj5_3, error1_int16, error1_int16};
T5Var4 t5_var4{"obj5_4", &obj5_4, error1_uint16, error1_uint16};
T5Var5 t5_var5{"obj5_5", &obj5_5, error1_int32, error1_int32};
T5Var6 t5_var6{"obj5_6", &obj5_6, error1_uint32, error1_uint32};
T5Var7 t5_var7{"obj5_7", &obj5_7, error1_int64, error1_int64};
T5Var8 t5_var8{"obj5_8", &obj5_8, error1_uint64, error1_uint64};

REGISTER_TEST(t5, new TestIdRecError<Case2, T5Var1, T5Var2, T5Var3, T5Var4, 
    T5Var5, T5Var6, T5Var7, T5Var8>(t5_var1, t5_var2, t5_var3,
        t5_var4, t5_var5, t5_var6, t5_var7, t5_var8));

typedef VariableTestIdRecError<std::int8_t, 
    basic::error::id::rec::Error<std::int8_t> *> T6Var1;
typedef VariableTestIdRecError<std::uint8_t, 
    basic::error::id::rec::Error<std::uint8_t> *> T6Var2;
typedef VariableTestIdRecError<std::int16_t, 
    basic::error::id::rec::Error<std::int16_t> *> T6Var3;
typedef VariableTestIdRecError<std::uint16_t, 
    basic::error::id::rec::Error<std::uint16_t> *> T6Var4;
typedef VariableTestIdRecError<std::int32_t, 
    basic::error::id::rec::Error<std::int32_t> *> T6Var5;
typedef VariableTestIdRecError<std::uint32_t, 
    basic::error::id::rec::Error<std::uint32_t> *> T6Var6;
typedef VariableTestIdRecError<std::int64_t, 
    basic::error::id::rec::Error<std::int64_t> *> T6Var7;
typedef VariableTestIdRecError<std::uint64_t, 
    basic::error::id::rec::Error<std::uint64_t> *> T6Var8;
    
basic::error::id::rec::Error<std::int8_t> obj6_1;
basic::error::id::rec::Error<std::uint8_t> obj6_2;
basic::error::id::rec::Error<std::int16_t> obj6_3;
basic::error::id::rec::Error<std::uint16_t> obj6_4;
basic::error::id::rec::Error<std::int32_t> obj6_5;
basic::error::id::rec::Error<std::uint32_t> obj6_6;
basic::error::id::rec::Error<std::int64_t> obj6_7;
basic::error::id::rec::Error<std::uint64_t> obj6_8;

T6Var1 t6_var1{"obj6_1", &obj6_1, &obj5_1, error1_int8};
T6Var2 t6_var2{"obj6_2", &obj6_2, &obj5_2, error1_uint8};
T6Var3 t6_var3{"obj6_3", &obj6_3, &obj5_3, error1_int16};
T6Var4 t6_var4{"obj6_4", &obj6_4, &obj5_4, error1_uint16};
T6Var5 t6_var5{"obj6_5", &obj6_5, &obj5_5, error1_int32};
T6Var6 t6_var6{"obj6_6", &obj6_6, &obj5_6, error1_uint32};
T6Var7 t6_var7{"obj6_7", &obj6_7, &obj5_7, error1_int64};
T6Var8 t6_var8{"obj6_8", &obj6_8, &obj5_8, error1_uint64};

REGISTER_TEST(t6, new TestIdRecError<Case3, T6Var1, T6Var2, T6Var3, T6Var4, 
    T6Var5, T6Var6, T6Var7, T6Var8>(t6_var1, t6_var2, t6_var3,
        t6_var4, t6_var5, t6_var6, t6_var7, t6_var8));

basic::error::id::rec::Error<std::int8_t> obj7_1;
basic::error::id::rec::Error<std::uint8_t> obj7_2;
basic::error::id::rec::Error<std::int16_t> obj7_3;
basic::error::id::rec::Error<std::uint16_t> obj7_4;
basic::error::id::rec::Error<std::int32_t> obj7_5;
basic::error::id::rec::Error<std::uint32_t> obj7_6;
basic::error::id::rec::Error<std::int64_t> obj7_7;
basic::error::id::rec::Error<std::uint64_t> obj7_8;

T6Var1 t7_var1{"obj7_1", &obj7_1, &obj6_1, error1_int8};
T6Var2 t7_var2{"obj7_2", &obj7_2, &obj6_2, error1_uint8};
T6Var3 t7_var3{"obj7_3", &obj7_3, &obj6_3, error1_int16};
T6Var4 t7_var4{"obj7_4", &obj7_4, &obj6_4, error1_uint16};
T6Var5 t7_var5{"obj7_5", &obj7_5, &obj6_5, error1_int32};
T6Var6 t7_var6{"obj7_6", &obj7_6, &obj6_6, error1_uint32};
T6Var7 t7_var7{"obj7_7", &obj7_7, &obj6_7, error1_int64};
T6Var8 t7_var8{"obj7_8", &obj7_8, &obj6_8, error1_uint64};

REGISTER_TEST(t7, new TestIdRecError<Case4, T6Var1, T6Var2, T6Var3, T6Var4, 
    T6Var5, T6Var6, T6Var7, T6Var8>(t7_var1, t7_var2, t7_var3,
        t7_var4, t7_var5, t7_var6, t7_var7, t7_var8));

T1Var1 t8_var1{"obj6_1", &obj6_1, 0, 0};
T1Var2 t8_var2{"obj6_2", &obj6_2, 0, 0};
T1Var3 t8_var3{"obj6_3", &obj6_3, 0, 0};
T1Var4 t8_var4{"obj6_4", &obj6_4, 0, 0};
T1Var5 t8_var5{"obj6_5", &obj6_5, 0, 0};
T1Var6 t8_var6{"obj6_6", &obj6_6, 0, 0};
T1Var7 t8_var7{"obj6_7", &obj6_7, 0, 0};
T1Var8 t8_var8{"obj6_8", &obj6_8, 0, 0};

REGISTER_TEST(t8, new TestIdRecError<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8>(t8_var1, t8_var2, t8_var3,
        t8_var4, t8_var5, t8_var6, t8_var7, t8_var8));

int main()
{
    return RUN_TEST();
}

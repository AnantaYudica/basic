#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/CString.h"
#include "test/cstr/out/Argument.h"

#include "error/id/rec/Code.h"

#include <cstdint>
#include <utility>

BASIC_TEST_CONSTRUCT;

struct TestErrorValue {};
struct TestErrorSystemValue {};
struct TestAssignValue {};
struct TestCopyAssignValue {};
struct TestMoveAssignValue {};

template<typename TErrorCodeValue, typename TErrorSystemCodeValue,
    typename TAssignValue = int>
using VariableTestIdRecCode = basic::test::Variable<
    TErrorCodeValue,
    TErrorSystemCodeValue,
    TAssignValue,
    basic::error::id::rec::Code<TErrorCodeValue,
        TErrorSystemCodeValue>,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::id::rec::Code<TErrorCodeValue,
        TErrorSystemCodeValue> *>,
    basic::test::Value<TAssignValue>,
    basic::test::Value<TErrorCodeValue>,
    basic::test::Value<TErrorSystemCodeValue>>;

constexpr std::size_t IErrorCodeValueType = 0;
constexpr std::size_t IErrorSystemCodeValueType = 1;
constexpr std::size_t IAssignValueType = 2;
constexpr std::size_t IErrorIdRecCodeType = 3;
constexpr std::size_t IObjName = 4;
constexpr std::size_t IObjValue = 5;
constexpr std::size_t IAssignValue = 6;
constexpr std::size_t IErrorCodeValue = 7;
constexpr std::size_t IErrorSystemCodeValue = 8;

typedef basic::test::msg::Argument<TestErrorValue,
    basic::test::msg::arg::type::Name<IErrorIdRecCodeType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorCodeValueType>,
    basic::test::msg::arg::Value<IErrorCodeValue>> ArgTestErrorValue;

typedef basic::test::msg::Base<TestErrorValue, char, 
    ArgTestErrorValue, ArgTestErrorValue, 
    ArgTestErrorValue> MessageBaseTestErrorValue;

typedef basic::test::msg::Argument<TestErrorSystemValue,
    basic::test::msg::arg::type::Name<IErrorIdRecCodeType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorSystemCodeValueType>,
    basic::test::msg::arg::Value<IErrorSystemCodeValue>> 
        ArgTestErrorSystemValue;

typedef basic::test::msg::Base<TestErrorSystemValue, char, 
    ArgTestErrorSystemValue, ArgTestErrorSystemValue, 
    ArgTestErrorSystemValue> MessageBaseTestErrorSystemValue;

typedef basic::test::msg::Argument<TestAssignValue,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IAssignValueType>,
    basic::test::msg::arg::Value<IAssignValue>> 
        ArgTestAssignValue;

typedef basic::test::msg::Argument<TestAssignValue,
    basic::test::msg::arg::Value<IObjName>> 
        ArgErrorTestAssignValue;

typedef basic::test::msg::Base<TestAssignValue, char, 
    ArgTestAssignValue, ArgTestAssignValue, 
    ArgErrorTestAssignValue> MessageBaseTestAssignValue;

typedef basic::test::msg::Argument<TestCopyAssignValue,
    basic::test::msg::arg::Value<IObjName>> ArgTestCopyAssignValue;

typedef basic::test::msg::Base<TestCopyAssignValue, char, 
    ArgTestCopyAssignValue, ArgTestCopyAssignValue, 
    ArgTestCopyAssignValue> MessageBaseTestCopyAssignValue;

typedef basic::test::msg::Argument<TestMoveAssignValue,
    basic::test::msg::arg::Value<IObjName>> ArgTestMoveAssignValue;

typedef basic::test::msg::Base<TestMoveAssignValue, char, 
    ArgTestMoveAssignValue, ArgTestMoveAssignValue, 
    ArgTestMoveAssignValue> MessageBaseTestMoveAssignValue;

template<typename TCases, typename... TVariables>
class TestIdRecCode :
    public MessageBaseTestErrorValue,
    public MessageBaseTestErrorSystemValue,
    public MessageBaseTestAssignValue,
    public MessageBaseTestCopyAssignValue,
    public MessageBaseTestMoveAssignValue,
    public basic::test::Message<BASIC_TEST, TestIdRecCode<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdRecCode<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdRecCode<TCases, TVariables...>, 
        TVariables...>
{
public:
    using MessageBaseTestErrorValue::Format;
    using MessageBaseTestErrorValue::SetFormat;
    using MessageBaseTestErrorValue::Argument;
    using MessageBaseTestErrorSystemValue::Format;
    using MessageBaseTestErrorSystemValue::SetFormat;
    using MessageBaseTestErrorSystemValue::Argument;
    using MessageBaseTestAssignValue::Format;
    using MessageBaseTestAssignValue::SetFormat;
    using MessageBaseTestAssignValue::Argument;
    using MessageBaseTestCopyAssignValue::Format;
    using MessageBaseTestCopyAssignValue::SetFormat;
    using MessageBaseTestCopyAssignValue::Argument;
    using MessageBaseTestMoveAssignValue::Format;
    using MessageBaseTestMoveAssignValue::SetFormat;
    using MessageBaseTestMoveAssignValue::Argument;
    using basic::test::Case<TestIdRecCode<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdRecCode<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdRecCode(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdRecCode<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdRecCode<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdRecCode<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        TestErrorValue testErrorValue;
        basic::test::msg::Format<char> formatErrorValue("Test value "
            "%s::Error {%s} is equal with %s {%d}\n");
        SetFormat(debug, testErrorValue, formatErrorValue);
        SetFormat(info, testErrorValue, std::move(formatErrorValue));
        SetFormat(error, testErrorValue, "Error value %s::Error {%s}"
            "is not equal with %s {%d}\n");

        TestErrorSystemValue testErrorSystemValue;
        basic::test::msg::Format<char> formatErrorSystemValue("Test value "
            "%s::ErrorSystem {%s} is equal with %s {%d}\n");
        SetFormat(debug, testErrorSystemValue, formatErrorSystemValue);
        SetFormat(info, testErrorSystemValue, 
            std::move(formatErrorSystemValue));
        SetFormat(error, testErrorSystemValue, "Error value %s::ErrorSystem "
            "{%s} is not equal with %s {%d}\n");

        TestAssignValue testAssignValue;
        basic::test::msg::Format<char> formatAssignValue("Assign %s with "
            "%s {%d}\n");
        SetFormat(debug, testAssignValue, formatAssignValue);
        SetFormat(info, testAssignValue, std::move(formatAssignValue));
        SetFormat(error, testAssignValue, "Error %s is nullptr\n");
        
        TestCopyAssignValue testCopyAssignValue;
        basic::test::msg::Format<char> formatCopyAssignValue("Copy "
            "assign of %s\n");
        SetFormat(debug, testCopyAssignValue, formatCopyAssignValue);
        SetFormat(info, testCopyAssignValue, std::move(formatCopyAssignValue));
        SetFormat(error, testCopyAssignValue, "Error %s is nullptr\n");

        TestMoveAssignValue testMoveAssignValue;
        basic::test::msg::Format<char> formatMoveAssignValue("Move "
            "assign of %s\n");
        SetFormat(debug, testMoveAssignValue, formatMoveAssignValue);
        SetFormat(info, testMoveAssignValue, std::move(formatMoveAssignValue));
        SetFormat(error, testMoveAssignValue, "Error %s is nullptr\n");
    }
    template<typename TErrorCodeValue, typename TErrorSystemCodeValue,
        typename TAssignValue>
    bool Result(const TestErrorValue &, VariableTestIdRecCode<TErrorCodeValue,
        TErrorSystemCodeValue, TAssignValue> & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->Error ==
            basic::test::var::At<IErrorCodeValue>(var).Get().Get();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCodeValue,
        typename TAssignValue>
    bool Result(const TestErrorSystemValue &, VariableTestIdRecCode<
        TErrorCodeValue, TErrorSystemCodeValue, TAssignValue> & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->Error ==
            basic::test::var::At<IErrorSystemCodeValue>(var).Get().Get();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCodeValue,
        typename TAssignValue>
    bool Result(const TestAssignValue &, VariableTestIdRecCode<
        TErrorCodeValue, TErrorSystemCodeValue, TAssignValue> & var)
    {
        auto obj = basic::test::var::At<IObjValue>(var).Get().Get();
        if (obj != nullptr)
        {
            *obj = basic::test::var::At<IAssignValue>(var).Get().Get();
            return true;
        }
        return false;
    }
    template<typename TErrorCodeValue, typename TErrorSystemCodeValue,
        typename TAssignValue>
    bool Result(const TestCopyAssignValue &, VariableTestIdRecCode<
        TErrorCodeValue, TErrorSystemCodeValue, TAssignValue> & var)
    {
        auto obj = basic::test::var::At<IObjValue>(var).Get().Get();
        if (obj != nullptr)
        {
            *obj = *basic::test::var::At<IAssignValue>(var).Get().Get();
            return true;
        }
        return false;
    }
    template<typename TErrorCodeValue, typename TErrorSystemCodeValue,
        typename TAssignValue>
    bool Result(const TestMoveAssignValue &, VariableTestIdRecCode<
        TErrorCodeValue, TErrorSystemCodeValue, TAssignValue> & var)
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
};

using Case1 = basic::test::type::Parameter<TestErrorValue, 
    TestErrorSystemValue>;
using Case2 = basic::test::type::Parameter<TestErrorValue>;
using Case3 = basic::test::type::Parameter<TestErrorSystemValue>;
using Case4 = basic::test::type::Parameter<TestAssignValue, TestErrorValue>;
using Case5 = basic::test::type::Parameter<TestAssignValue, 
    TestErrorSystemValue>;
using Case6 = basic::test::type::Parameter<TestCopyAssignValue, 
    TestErrorValue>;
using Case7 = basic::test::type::Parameter<TestCopyAssignValue, 
    TestErrorSystemValue>;
using Case8 = basic::test::type::Parameter<TestMoveAssignValue, 
    TestErrorValue>;
using Case9 = basic::test::type::Parameter<TestMoveAssignValue, 
    TestErrorSystemValue>;

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

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::error::id::rec::Code<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::rec::Code<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};


basic::error::id::rec::Code<std::int8_t, std::int8_t> obj1_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj1_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj1_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj1_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj1_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj1_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj1_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj1_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj1_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj1_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj1_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj1_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj1_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj1_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj1_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj1_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj1_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj1_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj1_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj1_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj1_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj1_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj1_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj1_24;

typedef VariableTestIdRecCode<std::int8_t, std::int8_t> T1Var1;
typedef VariableTestIdRecCode<std::uint8_t, std::uint8_t> T1Var2;
typedef VariableTestIdRecCode<std::int16_t, std::int16_t> T1Var3;
typedef VariableTestIdRecCode<std::uint16_t, std::uint16_t> T1Var4;
typedef VariableTestIdRecCode<std::int32_t, std::int32_t> T1Var5;
typedef VariableTestIdRecCode<std::uint32_t, std::uint32_t> T1Var6;
typedef VariableTestIdRecCode<std::int64_t, std::int64_t> T1Var7;
typedef VariableTestIdRecCode<std::uint64_t, std::uint64_t> T1Var8;

typedef VariableTestIdRecCode<std::int8_t, std::int64_t> T1Var9;
typedef VariableTestIdRecCode<std::uint8_t, std::uint64_t> T1Var10;
typedef VariableTestIdRecCode<std::int16_t, std::int32_t> T1Var11;
typedef VariableTestIdRecCode<std::uint16_t, std::uint32_t> T1Var12;
typedef VariableTestIdRecCode<std::int32_t, std::int16_t> T1Var13;
typedef VariableTestIdRecCode<std::uint32_t, std::uint16_t> T1Var14;
typedef VariableTestIdRecCode<std::int64_t, std::int8_t> T1Var15;
typedef VariableTestIdRecCode<std::uint64_t, std::uint8_t> T1Var16;

typedef VariableTestIdRecCode<std::int8_t, std::uint64_t> T1Var17;
typedef VariableTestIdRecCode<std::uint8_t, std::int64_t> T1Var18;
typedef VariableTestIdRecCode<std::int16_t, std::uint32_t> T1Var19;
typedef VariableTestIdRecCode<std::uint16_t, std::int32_t> T1Var20;
typedef VariableTestIdRecCode<std::int32_t, std::uint16_t> T1Var21;
typedef VariableTestIdRecCode<std::uint32_t, std::int16_t> T1Var22;
typedef VariableTestIdRecCode<std::int64_t, std::uint8_t> T1Var23;
typedef VariableTestIdRecCode<std::uint64_t, std::int8_t> T1Var24;

T1Var1 t1_var1{"obj1_1", &obj1_1, 0, 0, 0};
T1Var2 t1_var2{"obj1_2", &obj1_2, 0, 0, 0};
T1Var3 t1_var3{"obj1_3", &obj1_3, 0, 0, 0};
T1Var4 t1_var4{"obj1_4", &obj1_4, 0, 0, 0};
T1Var5 t1_var5{"obj1_5", &obj1_5, 0, 0, 0};
T1Var6 t1_var6{"obj1_6", &obj1_6, 0, 0, 0};
T1Var7 t1_var7{"obj1_7", &obj1_7, 0, 0, 0};
T1Var8 t1_var8{"obj1_8", &obj1_8, 0, 0, 0};

T1Var9 t1_var9{"obj1_9", &obj1_9, 0, 0, 0};
T1Var10 t1_var10{"obj1_10", &obj1_10, 0, 0, 0};
T1Var11 t1_var11{"obj1_11", &obj1_11, 0, 0, 0};
T1Var12 t1_var12{"obj1_12", &obj1_12, 0, 0, 0};
T1Var13 t1_var13{"obj1_13", &obj1_13, 0, 0, 0};
T1Var14 t1_var14{"obj1_14", &obj1_14, 0, 0, 0};
T1Var15 t1_var15{"obj1_15", &obj1_15, 0, 0, 0};
T1Var16 t1_var16{"obj1_16", &obj1_16, 0, 0, 0};

T1Var17 t1_var17{"obj1_17", &obj1_17, 0, 0, 0};
T1Var18 t1_var18{"obj1_18", &obj1_18, 0, 0, 0};
T1Var19 t1_var19{"obj1_19", &obj1_19, 0, 0, 0};
T1Var20 t1_var20{"obj1_20", &obj1_20, 0, 0, 0};
T1Var21 t1_var21{"obj1_21", &obj1_21, 0, 0, 0};
T1Var22 t1_var22{"obj1_22", &obj1_22, 0, 0, 0};
T1Var23 t1_var23{"obj1_23", &obj1_23, 0, 0, 0};
T1Var24 t1_var24{"obj1_24", &obj1_24, 0, 0, 0};

REGISTER_TEST(t1, new TestIdRecCode<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t1_var1, t1_var2, t1_var3,
        t1_var4, t1_var5, t1_var6, t1_var7, t1_var8, t1_var9, t1_var10,
        t1_var11, t1_var12, t1_var13, t1_var14, t1_var15, t1_var16, t1_var17,
        t1_var18, t1_var19, t1_var20, t1_var21, t1_var22, t1_var23, t1_var24));

std::int8_t code1_int8 = 1;
std::uint8_t code1_uint8 = 14;
std::int16_t code1_int16 = 4;
std::uint16_t code1_uint16 = 11;
std::int32_t code1_int32 = 6;
std::uint32_t code1_uint32 = 9;
std::int64_t code1_int64 = 8;
std::uint64_t code1_uint64 = 7;

basic::error::id::rec::Code<std::int8_t, 
    std::int8_t> obj2_1{code1_int8};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint8_t> obj2_2{code1_uint8};
basic::error::id::rec::Code<std::int16_t, 
    std::int16_t> obj2_3{code1_int16};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint16_t> obj2_4{code1_uint16};
basic::error::id::rec::Code<std::int32_t, 
    std::int32_t> obj2_5{code1_int32};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint32_t> obj2_6{code1_uint32};
basic::error::id::rec::Code<std::int64_t, 
    std::int64_t> obj2_7{code1_int64};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint64_t> obj2_8{code1_uint64};

basic::error::id::rec::Code<std::int8_t, 
    std::int64_t> obj2_9{code1_int8};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint64_t> obj2_10{code1_uint8};
basic::error::id::rec::Code<std::int16_t, 
    std::int32_t> obj2_11{code1_int16};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint32_t> obj2_12{code1_uint16};
basic::error::id::rec::Code<std::int32_t, 
    std::int16_t> obj2_13{code1_int32};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint16_t> obj2_14{code1_uint32};
basic::error::id::rec::Code<std::int64_t, 
    std::int8_t> obj2_15{code1_int64};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint8_t> obj2_16{code1_uint64};

basic::error::id::rec::Code<std::int8_t, 
    std::uint64_t> obj2_17{code1_int8};
basic::error::id::rec::Code<std::uint8_t, 
    std::int64_t> obj2_18{code1_uint8};
basic::error::id::rec::Code<std::int16_t, 
    std::uint32_t> obj2_19{code1_int16};
basic::error::id::rec::Code<std::uint16_t, 
    std::int32_t> obj2_20{code1_uint16};
basic::error::id::rec::Code<std::int32_t, 
    std::uint16_t> obj2_21{code1_int32};
basic::error::id::rec::Code<std::uint32_t, 
    std::int16_t> obj2_22{code1_uint32};
basic::error::id::rec::Code<std::int64_t, 
    std::uint8_t> obj2_23{code1_int64};
basic::error::id::rec::Code<std::uint64_t, 
    std::int8_t> obj2_24{code1_uint64};

T1Var1 t2_var1{"obj2_1", &obj2_1, 0, code1_int8, 0};
T1Var2 t2_var2{"obj2_2", &obj2_2, 0, code1_uint8, 0};
T1Var3 t2_var3{"obj2_3", &obj2_3, 0, code1_int16, 0};
T1Var4 t2_var4{"obj2_4", &obj2_4, 0, code1_uint16, 0};
T1Var5 t2_var5{"obj2_5", &obj2_5, 0, code1_int32, 0};
T1Var6 t2_var6{"obj2_6", &obj2_6, 0, code1_uint32, 0};
T1Var7 t2_var7{"obj2_7", &obj2_7, 0, code1_int64, 0};
T1Var8 t2_var8{"obj2_8", &obj2_8, 0, code1_uint64, 0};

T1Var9 t2_var9{"obj2_9", &obj2_9, 0, code1_int8, 0};
T1Var10 t2_var10{"obj2_10", &obj2_10, 0, code1_uint8, 0};
T1Var11 t2_var11{"obj2_11", &obj2_11, 0, code1_int16, 0};
T1Var12 t2_var12{"obj2_12", &obj2_12, 0, code1_uint16, 0};
T1Var13 t2_var13{"obj2_13", &obj2_13, 0, code1_int32, 0};
T1Var14 t2_var14{"obj2_14", &obj2_14, 0, code1_uint32, 0};
T1Var15 t2_var15{"obj2_15", &obj2_15, 0, code1_int64, 0};
T1Var16 t2_var16{"obj2_16", &obj2_16, 0, code1_uint64, 0};

T1Var17 t2_var17{"obj2_17", &obj2_17, 0, code1_int8, 0};
T1Var18 t2_var18{"obj2_18", &obj2_18, 0, code1_uint8, 0};
T1Var19 t2_var19{"obj2_19", &obj2_19, 0, code1_int16, 0};
T1Var20 t2_var20{"obj2_20", &obj2_20, 0, code1_uint16, 0};
T1Var21 t2_var21{"obj2_21", &obj2_21, 0, code1_int32, 0};
T1Var22 t2_var22{"obj2_22", &obj2_22, 0, code1_uint32, 0};
T1Var23 t2_var23{"obj2_23", &obj2_23, 0, code1_int64, 0};
T1Var24 t2_var24{"obj2_24", &obj2_24, 0, code1_uint64, 0};

REGISTER_TEST(t2, new TestIdRecCode<Case2, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t2_var1, t2_var2, t2_var3,
        t2_var4, t2_var5, t2_var6, t2_var7, t2_var8, t2_var9, t2_var10,
        t2_var11, t2_var12, t2_var13, t2_var14, t2_var15, t2_var16, t2_var17,
        t2_var18, t2_var19, t2_var20, t2_var21, t2_var22, t2_var23, t2_var24));

basic::error::id::rec::Code<std::int8_t, 
    std::int8_t> obj3_1{code1_int8};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint8_t> obj3_2{code1_uint8};
basic::error::id::rec::Code<std::int16_t, 
    std::int16_t> obj3_3{code1_int16};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint16_t> obj3_4{code1_uint16};
basic::error::id::rec::Code<std::int32_t, 
    std::int32_t> obj3_5{code1_int32};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint32_t> obj3_6{code1_uint32};
basic::error::id::rec::Code<std::int64_t, 
    std::int64_t> obj3_7{code1_int64};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint64_t> obj3_8{code1_uint64};

basic::error::id::rec::Code<std::int8_t, 
    std::int64_t> obj3_9{code1_int64};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint64_t> obj3_10{code1_uint64};
basic::error::id::rec::Code<std::int16_t, 
    std::int32_t> obj3_11{code1_int32};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint32_t> obj3_12{code1_uint32};
basic::error::id::rec::Code<std::int32_t, 
    std::int16_t> obj3_13{code1_int16};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint16_t> obj3_14{code1_uint16};
basic::error::id::rec::Code<std::int64_t, 
    std::int8_t> obj3_15{code1_int8};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint8_t> obj3_16{code1_uint8};

basic::error::id::rec::Code<std::int8_t, 
    std::uint64_t> obj3_17{code1_uint64};
basic::error::id::rec::Code<std::uint8_t, 
    std::int64_t> obj3_18{code1_int64};
basic::error::id::rec::Code<std::int16_t, 
    std::uint32_t> obj3_19{code1_uint32};
basic::error::id::rec::Code<std::uint16_t, 
    std::int32_t> obj3_20{code1_int32};
basic::error::id::rec::Code<std::int32_t, 
    std::uint16_t> obj3_21{code1_uint16};
basic::error::id::rec::Code<std::uint32_t, 
    std::int16_t> obj3_22{code1_int16};
basic::error::id::rec::Code<std::int64_t, 
    std::uint8_t> obj3_23{code1_uint8};
basic::error::id::rec::Code<std::uint64_t, 
    std::int8_t> obj3_24{code1_int8};

T1Var1 t3_var1{"obj3_1", &obj3_1, 0, 0, code1_int8};
T1Var2 t3_var2{"obj3_2", &obj3_2, 0, 0, code1_uint8};
T1Var3 t3_var3{"obj3_3", &obj3_3, 0, 0, code1_int16};
T1Var4 t3_var4{"obj3_4", &obj3_4, 0, 0, code1_uint16};
T1Var5 t3_var5{"obj3_5", &obj3_5, 0, 0, code1_int32};
T1Var6 t3_var6{"obj3_6", &obj3_6, 0, 0, code1_uint32};
T1Var7 t3_var7{"obj3_7", &obj3_7, 0, 0, code1_int64};
T1Var8 t3_var8{"obj3_8", &obj3_8, 0, 0, code1_uint64};

T1Var9 t3_var9{"obj3_9", &obj3_9, 0, 0, code1_int64};
T1Var10 t3_var10{"obj3_10", &obj3_10, 0, 0, code1_uint64};
T1Var11 t3_var11{"obj3_11", &obj3_11, 0, 0, code1_int32};
T1Var12 t3_var12{"obj3_12", &obj3_12, 0, 0, code1_uint32};
T1Var13 t3_var13{"obj3_13", &obj3_13, 0, 0, code1_int16};
T1Var14 t3_var14{"obj3_14", &obj3_14, 0, 0, code1_uint16};
T1Var15 t3_var15{"obj3_15", &obj3_15, 0, 0, code1_int8};
T1Var16 t3_var16{"obj3_16", &obj3_16, 0, 0, code1_uint8};

T1Var17 t3_var17{"obj3_17", &obj3_17, 0, 0, code1_uint64};
T1Var18 t3_var18{"obj3_18", &obj3_18, 0, 0, code1_int64};
T1Var19 t3_var19{"obj3_19", &obj3_19, 0, 0, code1_uint32};
T1Var20 t3_var20{"obj3_20", &obj3_20, 0, 0, code1_int32};
T1Var21 t3_var21{"obj3_21", &obj3_21, 0, 0, code1_uint16};
T1Var22 t3_var22{"obj3_22", &obj3_22, 0, 0, code1_int16};
T1Var23 t3_var23{"obj3_23", &obj3_23, 0, 0, code1_uint8};
T1Var24 t3_var24{"obj3_24", &obj3_24, 0, 0, code1_int8};

REGISTER_TEST(t3, new TestIdRecCode<Case3, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t3_var1, t3_var2, t3_var3,
        t3_var4, t3_var5, t3_var6, t3_var7, t3_var8, t3_var9, t3_var10,
        t3_var11, t3_var12, t3_var13, t3_var14, t3_var15, t3_var16, t3_var17,
        t3_var18, t3_var19, t3_var20, t3_var21, t3_var22, t3_var23, t3_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj4_1{obj2_1};
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj4_2{obj2_2};
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj4_3{obj2_3};
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj4_4{obj2_4};
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj4_5{obj2_5};
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj4_6{obj2_6};
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj4_7{obj2_7};
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj4_8{obj2_8};

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj4_9{obj2_9};
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj4_10{obj2_10};
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj4_11{obj2_11};
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj4_12{obj2_12};
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj4_13{obj2_13};
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj4_14{obj2_14};
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj4_15{obj2_15};
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj4_16{obj2_16};

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj4_17{obj2_17};
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj4_18{obj2_18};
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj4_19{obj2_19};
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj4_20{obj2_20};
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj4_21{obj2_21};
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj4_22{obj2_22};
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj4_23{obj2_23};
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj4_24{obj2_24};

T1Var1 t4_var1{"obj4_1", &obj4_1, 0, obj2_1.Error, 0};
T1Var2 t4_var2{"obj4_2", &obj4_2, 0, obj2_2.Error, 0};
T1Var3 t4_var3{"obj4_3", &obj4_3, 0, obj2_3.Error, 0};
T1Var4 t4_var4{"obj4_4", &obj4_4, 0, obj2_4.Error, 0};
T1Var5 t4_var5{"obj4_5", &obj4_5, 0, obj2_5.Error, 0};
T1Var6 t4_var6{"obj4_6", &obj4_6, 0, obj2_6.Error, 0};
T1Var7 t4_var7{"obj4_7", &obj4_7, 0, obj2_7.Error, 0};
T1Var8 t4_var8{"obj4_8", &obj4_8, 0, obj2_8.Error, 0};

T1Var9 t4_var9{"obj4_9", &obj4_9, 0, obj2_9.Error, 0};
T1Var10 t4_var10{"obj4_10", &obj4_10, 0, obj2_10.Error, 0};
T1Var11 t4_var11{"obj4_11", &obj4_11, 0, obj2_11.Error, 0};
T1Var12 t4_var12{"obj4_12", &obj4_12, 0, obj2_12.Error, 0};
T1Var13 t4_var13{"obj4_13", &obj4_13, 0, obj2_13.Error, 0};
T1Var14 t4_var14{"obj4_14", &obj4_14, 0, obj2_14.Error, 0};
T1Var15 t4_var15{"obj4_15", &obj4_15, 0, obj2_15.Error, 0};
T1Var16 t4_var16{"obj4_16", &obj4_16, 0, obj2_16.Error, 0};

T1Var17 t4_var17{"obj4_17", &obj4_17, 0, obj2_17.Error, 0};
T1Var18 t4_var18{"obj4_18", &obj4_18, 0, obj2_18.Error, 0};
T1Var19 t4_var19{"obj4_19", &obj4_19, 0, obj2_19.Error, 0};
T1Var20 t4_var20{"obj4_20", &obj4_20, 0, obj2_20.Error, 0};
T1Var21 t4_var21{"obj4_21", &obj4_21, 0, obj2_21.Error, 0};
T1Var22 t4_var22{"obj4_22", &obj4_22, 0, obj2_22.Error, 0};
T1Var23 t4_var23{"obj4_23", &obj4_23, 0, obj2_23.Error, 0};
T1Var24 t4_var24{"obj4_24", &obj4_24, 0, obj2_24.Error, 0};

REGISTER_TEST(t4, new TestIdRecCode<Case2, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t4_var1, t4_var2, t4_var3,
        t4_var4, t4_var5, t4_var6, t4_var7, t4_var8, t4_var9, t4_var10,
        t4_var11, t4_var12, t4_var13, t4_var14, t4_var15, t4_var16, t4_var17,
        t4_var18, t4_var19, t4_var20, t4_var21, t4_var22, t4_var23, t4_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj5_1{obj3_1};
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj5_2{obj3_2};
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj5_3{obj3_3};
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj5_4{obj3_4};
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj5_5{obj3_5};
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj5_6{obj3_6};
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj5_7{obj3_7};
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj5_8{obj3_8};

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj5_9{obj3_9};
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj5_10{obj3_10};
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj5_11{obj3_11};
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj5_12{obj3_12};
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj5_13{obj3_13};
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj5_14{obj3_14};
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj5_15{obj3_15};
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj5_16{obj3_16};

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj5_17{obj3_17};
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj5_18{obj3_18};
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj5_19{obj3_19};
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj5_20{obj3_20};
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj5_21{obj3_21};
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj5_22{obj3_22};
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj5_23{obj3_23};
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj5_24{obj3_24};

T1Var1 t5_var1{"obj5_1", &obj5_1, 0, 0, obj3_1.ErrorSystem};
T1Var2 t5_var2{"obj5_2", &obj5_2, 0, 0, obj3_2.ErrorSystem};
T1Var3 t5_var3{"obj5_3", &obj5_3, 0, 0, obj3_3.ErrorSystem};
T1Var4 t5_var4{"obj5_4", &obj5_4, 0, 0, obj3_4.ErrorSystem};
T1Var5 t5_var5{"obj5_5", &obj5_5, 0, 0, obj3_5.ErrorSystem};
T1Var6 t5_var6{"obj5_6", &obj5_6, 0, 0, obj3_6.ErrorSystem};
T1Var7 t5_var7{"obj5_7", &obj5_7, 0, 0, obj3_7.ErrorSystem};
T1Var8 t5_var8{"obj5_8", &obj5_8, 0, 0, obj3_8.ErrorSystem};

T1Var9 t5_var9{"obj5_9", &obj5_9, 0, 0, obj3_9.ErrorSystem};
T1Var10 t5_var10{"obj5_10", &obj5_10, 0, 0, obj3_10.ErrorSystem};
T1Var11 t5_var11{"obj5_11", &obj5_11, 0, 0, obj3_11.ErrorSystem};
T1Var12 t5_var12{"obj5_12", &obj5_12, 0, 0, obj3_12.ErrorSystem};
T1Var13 t5_var13{"obj5_13", &obj5_13, 0, 0, obj3_13.ErrorSystem};
T1Var14 t5_var14{"obj5_14", &obj5_14, 0, 0, obj3_14.ErrorSystem};
T1Var15 t5_var15{"obj5_15", &obj5_15, 0, 0, obj3_15.ErrorSystem};
T1Var16 t5_var16{"obj5_16", &obj5_16, 0, 0, obj3_16.ErrorSystem};

T1Var17 t5_var17{"obj5_17", &obj5_17, 0, 0, obj3_17.ErrorSystem};
T1Var18 t5_var18{"obj5_18", &obj5_18, 0, 0, obj3_18.ErrorSystem};
T1Var19 t5_var19{"obj5_19", &obj5_19, 0, 0, obj3_19.ErrorSystem};
T1Var20 t5_var20{"obj5_20", &obj5_20, 0, 0, obj3_20.ErrorSystem};
T1Var21 t5_var21{"obj5_21", &obj5_21, 0, 0, obj3_21.ErrorSystem};
T1Var22 t5_var22{"obj5_22", &obj5_22, 0, 0, obj3_22.ErrorSystem};
T1Var23 t5_var23{"obj5_23", &obj5_23, 0, 0, obj3_23.ErrorSystem};
T1Var24 t5_var24{"obj5_24", &obj5_24, 0, 0, obj3_24.ErrorSystem};

REGISTER_TEST(t5, new TestIdRecCode<Case3, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t5_var1, t5_var2, t5_var3,
        t5_var4, t5_var5, t5_var6, t5_var7, t5_var8, t5_var9, t5_var10,
        t5_var11, t5_var12, t5_var13, t5_var14, t5_var15, t5_var16, t5_var17,
        t5_var18, t5_var19, t5_var20, t5_var21, t5_var22, t5_var23, t5_var24));

basic::error::id::rec::Code<std::int8_t, 
    std::int8_t> obj6_1{std::move(obj4_1)};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint8_t> obj6_2{std::move(obj4_2)};
basic::error::id::rec::Code<std::int16_t, 
    std::int16_t> obj6_3{std::move(obj4_3)};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint16_t> obj6_4{std::move(obj4_4)};
basic::error::id::rec::Code<std::int32_t, 
    std::int32_t> obj6_5{std::move(obj4_5)};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint32_t> obj6_6{std::move(obj4_6)};
basic::error::id::rec::Code<std::int64_t, 
    std::int64_t> obj6_7{std::move(obj4_7)};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint64_t> obj6_8{std::move(obj4_8)};

basic::error::id::rec::Code<std::int8_t, 
    std::int64_t> obj6_9{std::move(obj4_9)};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint64_t> obj6_10{std::move(obj4_10)};
basic::error::id::rec::Code<std::int16_t, 
    std::int32_t> obj6_11{std::move(obj4_11)};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint32_t> obj6_12{std::move(obj4_12)};
basic::error::id::rec::Code<std::int32_t, 
    std::int16_t> obj6_13{std::move(obj4_13)};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint16_t> obj6_14{std::move(obj4_14)};
basic::error::id::rec::Code<std::int64_t, 
    std::int8_t> obj6_15{std::move(obj4_15)};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint8_t> obj6_16{std::move(obj4_16)};

basic::error::id::rec::Code<std::int8_t, 
    std::uint64_t> obj6_17{std::move(obj4_17)};
basic::error::id::rec::Code<std::uint8_t, 
    std::int64_t> obj6_18{std::move(obj4_18)};
basic::error::id::rec::Code<std::int16_t, 
    std::uint32_t> obj6_19{std::move(obj4_19)};
basic::error::id::rec::Code<std::uint16_t, 
    std::int32_t> obj6_20{std::move(obj4_20)};
basic::error::id::rec::Code<std::int32_t, 
    std::uint16_t> obj6_21{std::move(obj4_21)};
basic::error::id::rec::Code<std::uint32_t, 
    std::int16_t> obj6_22{std::move(obj4_22)};
basic::error::id::rec::Code<std::int64_t, 
    std::uint8_t> obj6_23{std::move(obj4_23)};
basic::error::id::rec::Code<std::uint64_t, 
    std::int8_t> obj6_24{std::move(obj4_24)};

T1Var1 t6_var1{"obj6_1", &obj6_1, 0, obj2_1.Error, 0};
T1Var2 t6_var2{"obj6_2", &obj6_2, 0, obj2_2.Error, 0};
T1Var3 t6_var3{"obj6_3", &obj6_3, 0, obj2_3.Error, 0};
T1Var4 t6_var4{"obj6_4", &obj6_4, 0, obj2_4.Error, 0};
T1Var5 t6_var5{"obj6_5", &obj6_5, 0, obj2_5.Error, 0};
T1Var6 t6_var6{"obj6_6", &obj6_6, 0, obj2_6.Error, 0};
T1Var7 t6_var7{"obj6_7", &obj6_7, 0, obj2_7.Error, 0};
T1Var8 t6_var8{"obj6_8", &obj6_8, 0, obj2_8.Error, 0};

T1Var9 t6_var9{"obj6_9", &obj6_9, 0, obj2_9.Error, 0};
T1Var10 t6_var10{"obj6_10", &obj6_10, 0, obj2_10.Error, 0};
T1Var11 t6_var11{"obj6_11", &obj6_11, 0, obj2_11.Error, 0};
T1Var12 t6_var12{"obj6_12", &obj6_12, 0, obj2_12.Error, 0};
T1Var13 t6_var13{"obj6_13", &obj6_13, 0, obj2_13.Error, 0};
T1Var14 t6_var14{"obj6_14", &obj6_14, 0, obj2_14.Error, 0};
T1Var15 t6_var15{"obj6_15", &obj6_15, 0, obj2_15.Error, 0};
T1Var16 t6_var16{"obj6_16", &obj6_16, 0, obj2_16.Error, 0};

T1Var17 t6_var17{"obj6_17", &obj6_17, 0, obj2_17.Error, 0};
T1Var18 t6_var18{"obj6_18", &obj6_18, 0, obj2_18.Error, 0};
T1Var19 t6_var19{"obj6_19", &obj6_19, 0, obj2_19.Error, 0};
T1Var20 t6_var20{"obj6_20", &obj6_20, 0, obj2_20.Error, 0};
T1Var21 t6_var21{"obj6_21", &obj6_21, 0, obj2_21.Error, 0};
T1Var22 t6_var22{"obj6_22", &obj6_22, 0, obj2_22.Error, 0};
T1Var23 t6_var23{"obj6_23", &obj6_23, 0, obj2_23.Error, 0};
T1Var24 t6_var24{"obj6_24", &obj6_24, 0, obj2_24.Error, 0};

T1Var1 t6_var25{"obj4_1", &obj4_1, 0, 0, 0};
T1Var2 t6_var26{"obj4_2", &obj4_2, 0, 0, 0};
T1Var3 t6_var27{"obj4_3", &obj4_3, 0, 0, 0};
T1Var4 t6_var28{"obj4_4", &obj4_4, 0, 0, 0};
T1Var5 t6_var29{"obj4_5", &obj4_5, 0, 0, 0};
T1Var6 t6_var30{"obj4_6", &obj4_6, 0, 0, 0};
T1Var7 t6_var31{"obj4_7", &obj4_7, 0, 0, 0};
T1Var8 t6_var32{"obj4_8", &obj4_8, 0, 0, 0};

T1Var9 t6_var33{"obj4_9", &obj4_9, 0, 0, 0};
T1Var10 t6_var34{"obj4_10", &obj4_10, 0, 0, 0};
T1Var11 t6_var35{"obj4_11", &obj4_11, 0, 0, 0};
T1Var12 t6_var36{"obj4_12", &obj4_12, 0, 0, 0};
T1Var13 t6_var37{"obj4_13", &obj4_13, 0, 0, 0};
T1Var14 t6_var38{"obj4_14", &obj4_14, 0, 0, 0};
T1Var15 t6_var39{"obj4_15", &obj4_15, 0, 0, 0};
T1Var16 t6_var40{"obj4_16", &obj4_16, 0, 0, 0};

T1Var17 t6_var41{"obj4_17", &obj4_17, 0, 0, 0};
T1Var18 t6_var42{"obj4_18", &obj4_18, 0, 0, 0};
T1Var19 t6_var43{"obj4_19", &obj4_19, 0, 0, 0};
T1Var20 t6_var44{"obj4_20", &obj4_20, 0, 0, 0};
T1Var21 t6_var45{"obj4_21", &obj4_21, 0, 0, 0};
T1Var22 t6_var46{"obj4_22", &obj4_22, 0, 0, 0};
T1Var23 t6_var47{"obj4_23", &obj4_23, 0, 0, 0};
T1Var24 t6_var48{"obj4_24", &obj4_24, 0, 0, 0};

REGISTER_TEST(t6, new TestIdRecCode<Case2, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t6_var1, t6_var2, t6_var3,
        t6_var4, t6_var5, t6_var6, t6_var7, t6_var8, t6_var9, t6_var10,
        t6_var11, t6_var12, t6_var13, t6_var14, t6_var15, t6_var16, t6_var17,
        t6_var18, t6_var19, t6_var20, t6_var21, t6_var22, t6_var23, t6_var24,
        t6_var25, t6_var26, t6_var27, t6_var28, t6_var29, t6_var30, t6_var31, 
        t6_var32, t6_var33, t6_var34, t6_var35, t6_var36, t6_var37, t6_var38, 
        t6_var39, t6_var40, t6_var41, t6_var42, t6_var43, t6_var44, t6_var45, 
        t6_var46, t6_var47, t6_var48));

basic::error::id::rec::Code<std::int8_t, 
    std::int8_t> obj7_1{std::move(obj5_1)};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint8_t> obj7_2{std::move(obj5_2)};
basic::error::id::rec::Code<std::int16_t, 
    std::int16_t> obj7_3{std::move(obj5_3)};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint16_t> obj7_4{std::move(obj5_4)};
basic::error::id::rec::Code<std::int32_t, 
    std::int32_t> obj7_5{std::move(obj5_5)};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint32_t> obj7_6{std::move(obj5_6)};
basic::error::id::rec::Code<std::int64_t, 
    std::int64_t> obj7_7{std::move(obj5_7)};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint64_t> obj7_8{std::move(obj5_8)};

basic::error::id::rec::Code<std::int8_t, 
    std::int64_t> obj7_9{std::move(obj5_9)};
basic::error::id::rec::Code<std::uint8_t, 
    std::uint64_t> obj7_10{std::move(obj5_10)};
basic::error::id::rec::Code<std::int16_t, 
    std::int32_t> obj7_11{std::move(obj5_11)};
basic::error::id::rec::Code<std::uint16_t, 
    std::uint32_t> obj7_12{std::move(obj5_12)};
basic::error::id::rec::Code<std::int32_t, 
    std::int16_t> obj7_13{std::move(obj5_13)};
basic::error::id::rec::Code<std::uint32_t, 
    std::uint16_t> obj7_14{std::move(obj5_14)};
basic::error::id::rec::Code<std::int64_t, 
    std::int8_t> obj7_15{std::move(obj5_15)};
basic::error::id::rec::Code<std::uint64_t, 
    std::uint8_t> obj7_16{std::move(obj5_16)};

basic::error::id::rec::Code<std::int8_t, 
    std::uint64_t> obj7_17{std::move(obj5_17)};
basic::error::id::rec::Code<std::uint8_t, 
    std::int64_t> obj7_18{std::move(obj5_18)};
basic::error::id::rec::Code<std::int16_t, 
    std::uint32_t> obj7_19{std::move(obj5_19)};
basic::error::id::rec::Code<std::uint16_t, 
    std::int32_t> obj7_20{std::move(obj5_20)};
basic::error::id::rec::Code<std::int32_t, 
    std::uint16_t> obj7_21{std::move(obj5_21)};
basic::error::id::rec::Code<std::uint32_t, 
    std::int16_t> obj7_22{std::move(obj5_22)};
basic::error::id::rec::Code<std::int64_t, 
    std::uint8_t> obj7_23{std::move(obj5_23)};
basic::error::id::rec::Code<std::uint64_t, 
    std::int8_t> obj7_24{std::move(obj5_24)};

T1Var1 t7_var1{"obj7_1", &obj7_1, 0, 0, obj3_1.ErrorSystem};
T1Var2 t7_var2{"obj7_2", &obj7_2, 0, 0, obj3_2.ErrorSystem};
T1Var3 t7_var3{"obj7_3", &obj7_3, 0, 0, obj3_3.ErrorSystem};
T1Var4 t7_var4{"obj7_4", &obj7_4, 0, 0, obj3_4.ErrorSystem};
T1Var5 t7_var5{"obj7_5", &obj7_5, 0, 0, obj3_5.ErrorSystem};
T1Var6 t7_var6{"obj7_6", &obj7_6, 0, 0, obj3_6.ErrorSystem};
T1Var7 t7_var7{"obj7_7", &obj7_7, 0, 0, obj3_7.ErrorSystem};
T1Var8 t7_var8{"obj7_8", &obj7_8, 0, 0, obj3_8.ErrorSystem};

T1Var9 t7_var9{"obj7_9", &obj7_9, 0, 0, obj3_9.ErrorSystem};
T1Var10 t7_var10{"obj7_10", &obj7_10, 0, 0, obj3_10.ErrorSystem};
T1Var11 t7_var11{"obj7_11", &obj7_11, 0, 0, obj3_11.ErrorSystem};
T1Var12 t7_var12{"obj7_12", &obj7_12, 0, 0, obj3_12.ErrorSystem};
T1Var13 t7_var13{"obj7_13", &obj7_13, 0, 0, obj3_13.ErrorSystem};
T1Var14 t7_var14{"obj7_14", &obj7_14, 0, 0, obj3_14.ErrorSystem};
T1Var15 t7_var15{"obj7_15", &obj7_15, 0, 0, obj3_15.ErrorSystem};
T1Var16 t7_var16{"obj7_16", &obj7_16, 0, 0, obj3_16.ErrorSystem};

T1Var17 t7_var17{"obj7_17", &obj7_17, 0, 0, obj3_17.ErrorSystem};
T1Var18 t7_var18{"obj7_18", &obj7_18, 0, 0, obj3_18.ErrorSystem};
T1Var19 t7_var19{"obj7_19", &obj7_19, 0, 0, obj3_19.ErrorSystem};
T1Var20 t7_var20{"obj7_20", &obj7_20, 0, 0, obj3_20.ErrorSystem};
T1Var21 t7_var21{"obj7_21", &obj7_21, 0, 0, obj3_21.ErrorSystem};
T1Var22 t7_var22{"obj7_22", &obj7_22, 0, 0, obj3_22.ErrorSystem};
T1Var23 t7_var23{"obj7_23", &obj7_23, 0, 0, obj3_23.ErrorSystem};
T1Var24 t7_var24{"obj7_24", &obj7_24, 0, 0, obj3_24.ErrorSystem};

T1Var1 t7_var25{"obj5_1", &obj5_1, 0, 0, 0};
T1Var2 t7_var26{"obj5_2", &obj5_2, 0, 0, 0};
T1Var3 t7_var27{"obj5_3", &obj5_3, 0, 0, 0};
T1Var4 t7_var28{"obj5_4", &obj5_4, 0, 0, 0};
T1Var5 t7_var29{"obj5_5", &obj5_5, 0, 0, 0};
T1Var6 t7_var30{"obj5_6", &obj5_6, 0, 0, 0};
T1Var7 t7_var31{"obj5_7", &obj5_7, 0, 0, 0};
T1Var8 t7_var32{"obj5_8", &obj5_8, 0, 0, 0};

T1Var9 t7_var33{"obj5_9", &obj5_9, 0, 0, 0};
T1Var10 t7_var34{"obj5_10", &obj5_10, 0, 0, 0};
T1Var11 t7_var35{"obj5_11", &obj5_11, 0, 0, 0};
T1Var12 t7_var36{"obj5_12", &obj5_12, 0, 0, 0};
T1Var13 t7_var37{"obj5_13", &obj5_13, 0, 0, 0};
T1Var14 t7_var38{"obj5_14", &obj5_14, 0, 0, 0};
T1Var15 t7_var39{"obj5_15", &obj5_15, 0, 0, 0};
T1Var16 t7_var40{"obj5_16", &obj5_16, 0, 0, 0};

T1Var17 t7_var41{"obj5_17", &obj5_17, 0, 0, 0};
T1Var18 t7_var42{"obj5_18", &obj5_18, 0, 0, 0};
T1Var19 t7_var43{"obj5_19", &obj5_19, 0, 0, 0};
T1Var20 t7_var44{"obj5_20", &obj5_20, 0, 0, 0};
T1Var21 t7_var45{"obj5_21", &obj5_21, 0, 0, 0};
T1Var22 t7_var46{"obj5_22", &obj5_22, 0, 0, 0};
T1Var23 t7_var47{"obj5_23", &obj5_23, 0, 0, 0};
T1Var24 t7_var48{"obj5_24", &obj5_24, 0, 0, 0};

REGISTER_TEST(t7, new TestIdRecCode<Case3, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t7_var1, t7_var2, t7_var3,
        t7_var4, t7_var5, t7_var6, t7_var7, t7_var8, t7_var9, t7_var10,
        t7_var11, t7_var12, t7_var13, t7_var14, t7_var15, t7_var16, t7_var17,
        t7_var18, t7_var19, t7_var20, t7_var21, t7_var22, t7_var23, t7_var24,
        t7_var25, t7_var26, t7_var27, t7_var28, t7_var29, t7_var30, t7_var31, 
        t7_var32, t7_var33, t7_var34, t7_var35, t7_var36, t7_var37, t7_var38, 
        t7_var39, t7_var40, t7_var41, t7_var42, t7_var43, t7_var44, t7_var45, 
        t7_var46, t7_var47, t7_var48));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj8_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj8_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj8_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj8_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj8_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj8_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj8_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj8_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj8_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj8_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj8_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj8_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj8_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj8_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj8_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj8_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj8_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj8_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj8_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj8_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj8_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj8_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj8_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj8_24;

typedef VariableTestIdRecCode<std::int8_t, std::int8_t,
    std::int8_t> T8Var1;
typedef VariableTestIdRecCode<std::uint8_t, std::uint8_t,
    std::uint8_t> T8Var2;
typedef VariableTestIdRecCode<std::int16_t, std::int16_t,
    std::int16_t> T8Var3;
typedef VariableTestIdRecCode<std::uint16_t, std::uint16_t,
    std::uint16_t> T8Var4;
typedef VariableTestIdRecCode<std::int32_t, std::int32_t,
    std::int32_t> T8Var5;
typedef VariableTestIdRecCode<std::uint32_t, std::uint32_t,
    std::uint32_t> T8Var6;
typedef VariableTestIdRecCode<std::int64_t, std::int64_t,
    std::int64_t> T8Var7;
typedef VariableTestIdRecCode<std::uint64_t, std::uint64_t,
    std::uint64_t> T8Var8;

typedef VariableTestIdRecCode<std::int8_t, std::int64_t,
    std::int8_t> T8Var9;
typedef VariableTestIdRecCode<std::uint8_t, std::uint64_t,
    std::uint8_t> T8Var10;
typedef VariableTestIdRecCode<std::int16_t, std::int32_t,
    std::int16_t> T8Var11;
typedef VariableTestIdRecCode<std::uint16_t, std::uint32_t,
    std::uint16_t> T8Var12;
typedef VariableTestIdRecCode<std::int32_t, std::int16_t,
    std::int32_t> T8Var13;
typedef VariableTestIdRecCode<std::uint32_t, std::uint16_t,
    std::uint32_t> T8Var14;
typedef VariableTestIdRecCode<std::int64_t, std::int8_t,
    std::int64_t> T8Var15;
typedef VariableTestIdRecCode<std::uint64_t, std::uint8_t,
    std::uint64_t> T8Var16;

typedef VariableTestIdRecCode<std::int8_t, std::uint64_t,
    std::int8_t> T8Var17;
typedef VariableTestIdRecCode<std::uint8_t, std::int64_t,
    std::uint8_t> T8Var18;
typedef VariableTestIdRecCode<std::int16_t, std::uint32_t,
    std::int16_t> T8Var19;
typedef VariableTestIdRecCode<std::uint16_t, std::int32_t,
    std::uint16_t> T8Var20;
typedef VariableTestIdRecCode<std::int32_t, std::uint16_t,
    std::int32_t> T8Var21;
typedef VariableTestIdRecCode<std::uint32_t, std::int16_t,
    std::uint32_t> T8Var22;
typedef VariableTestIdRecCode<std::int64_t, std::uint8_t,
    std::int64_t> T8Var23;
typedef VariableTestIdRecCode<std::uint64_t, std::int8_t,
    std::uint64_t> T8Var24;

T8Var1 t8_var1{"obj8_1", &obj8_1, code1_int8, code1_int8, 0};
T8Var2 t8_var2{"obj8_2", &obj8_2, code1_uint8, code1_uint8, 0};
T8Var3 t8_var3{"obj8_3", &obj8_3, code1_int16, code1_int16, 0};
T8Var4 t8_var4{"obj8_4", &obj8_4, code1_uint16, code1_uint16, 0};
T8Var5 t8_var5{"obj8_5", &obj8_5, code1_int32, code1_int32, 0};
T8Var6 t8_var6{"obj8_6", &obj8_6, code1_uint32, code1_uint32, 0};
T8Var7 t8_var7{"obj8_7", &obj8_7, code1_int64, code1_int64, 0};
T8Var8 t8_var8{"obj8_8", &obj8_8, code1_uint64, code1_uint64, 0};

T8Var9 t8_var9{"obj8_9", &obj8_9, code1_int8, code1_int8, 0};
T8Var10 t8_var10{"obj8_10", &obj8_10, code1_uint8, code1_uint8, 0};
T8Var11 t8_var11{"obj8_11", &obj8_11, code1_int16, code1_int16, 0};
T8Var12 t8_var12{"obj8_12", &obj8_12, code1_uint16, code1_uint16, 0};
T8Var13 t8_var13{"obj8_13", &obj8_13, code1_int32, code1_int32, 0};
T8Var14 t8_var14{"obj8_14", &obj8_14, code1_uint32, code1_uint32, 0};
T8Var15 t8_var15{"obj8_15", &obj8_15, code1_int64, code1_int64, 0};
T8Var16 t8_var16{"obj8_16", &obj8_16, code1_uint64, code1_uint64, 0};

T8Var17 t8_var17{"obj8_17", &obj8_17, code1_int8, code1_int8, 0};
T8Var18 t8_var18{"obj8_18", &obj8_18, code1_uint8, code1_uint8, 0};
T8Var19 t8_var19{"obj8_19", &obj8_19, code1_int16, code1_int16, 0};
T8Var20 t8_var20{"obj8_20", &obj8_20, code1_uint16, code1_uint16, 0};
T8Var21 t8_var21{"obj8_21", &obj8_21, code1_int32, code1_int32, 0};
T8Var22 t8_var22{"obj8_22", &obj8_22, code1_uint32, code1_uint32, 0};
T8Var23 t8_var23{"obj8_23", &obj8_23, code1_int64, code1_int64, 0};
T8Var24 t8_var24{"obj8_24", &obj8_24, code1_uint64, code1_uint64, 0};

REGISTER_TEST(t8, new TestIdRecCode<Case4, T8Var1, T8Var2, T8Var3, T8Var4, 
    T8Var5, T8Var6, T8Var7, T8Var8, T8Var9, T8Var10, T8Var11, T8Var12,
    T8Var13, T8Var14, T8Var15, T8Var16, T8Var17, T8Var18, T8Var19, T8Var20,
    T8Var21, T8Var22, T8Var23, T8Var24>(t8_var1, t8_var2, t8_var3,
        t8_var4, t8_var5, t8_var6, t8_var7, t8_var8, t8_var9, t8_var10,
        t8_var11, t8_var12, t8_var13, t8_var14, t8_var15, t8_var16, t8_var17,
        t8_var18, t8_var19, t8_var20, t8_var21, t8_var22, t8_var23, t8_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj9_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj9_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj9_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj9_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj9_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj9_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj9_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj9_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj9_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj9_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj9_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj9_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj9_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj9_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj9_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj9_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj9_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj9_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj9_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj9_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj9_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj9_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj9_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj9_24;

typedef VariableTestIdRecCode<std::int8_t, std::int8_t,
    std::int8_t> T9Var1;
typedef VariableTestIdRecCode<std::uint8_t, std::uint8_t,
    std::uint8_t> T9Var2;
typedef VariableTestIdRecCode<std::int16_t, std::int16_t,
    std::int16_t> T9Var3;
typedef VariableTestIdRecCode<std::uint16_t, std::uint16_t,
    std::uint16_t> T9Var4;
typedef VariableTestIdRecCode<std::int32_t, std::int32_t,
    std::int32_t> T9Var5;
typedef VariableTestIdRecCode<std::uint32_t, std::uint32_t,
    std::uint32_t> T9Var6;
typedef VariableTestIdRecCode<std::int64_t, std::int64_t,
    std::int64_t> T9Var7;
typedef VariableTestIdRecCode<std::uint64_t, std::uint64_t,
    std::uint64_t> T9Var8;

typedef VariableTestIdRecCode<std::int8_t, std::int64_t,
    std::int64_t> T9Var9;
typedef VariableTestIdRecCode<std::uint8_t, std::uint64_t,
    std::uint64_t> T9Var10;
typedef VariableTestIdRecCode<std::int16_t, std::int32_t,
    std::int32_t> T9Var11;
typedef VariableTestIdRecCode<std::uint16_t, std::uint32_t,
    std::uint32_t> T9Var12;
typedef VariableTestIdRecCode<std::int32_t, std::int16_t,
    std::int16_t> T9Var13;
typedef VariableTestIdRecCode<std::uint32_t, std::uint16_t,
    std::uint16_t> T9Var14;
typedef VariableTestIdRecCode<std::int64_t, std::int8_t,
    std::int8_t> T9Var15;
typedef VariableTestIdRecCode<std::uint64_t, std::uint8_t,
    std::uint8_t> T9Var16;

typedef VariableTestIdRecCode<std::int8_t, std::uint64_t,
    std::uint64_t> T9Var17;
typedef VariableTestIdRecCode<std::uint8_t, std::int64_t,
    std::int64_t> T9Var18;
typedef VariableTestIdRecCode<std::int16_t, std::uint32_t,
    std::uint32_t> T9Var19;
typedef VariableTestIdRecCode<std::uint16_t, std::int32_t,
    std::int32_t> T9Var20;
typedef VariableTestIdRecCode<std::int32_t, std::uint16_t,
    std::uint16_t> T9Var21;
typedef VariableTestIdRecCode<std::uint32_t, std::int16_t,
    std::int16_t> T9Var22;
typedef VariableTestIdRecCode<std::int64_t, std::uint8_t,
    std::uint8_t> T9Var23;
typedef VariableTestIdRecCode<std::uint64_t, std::int8_t,
    std::int8_t> T9Var24;

T9Var1 t9_var1{"obj9_1", &obj9_1, code1_int8, 0, code1_int8};
T9Var2 t9_var2{"obj9_2", &obj9_2, code1_uint8, 0, code1_uint8};
T9Var3 t9_var3{"obj9_3", &obj9_3, code1_int16, 0, code1_int16};
T9Var4 t9_var4{"obj9_4", &obj9_4, code1_uint16, 0, code1_uint16};
T9Var5 t9_var5{"obj9_5", &obj9_5, code1_int32, 0, code1_int32};
T9Var6 t9_var6{"obj9_6", &obj9_6, code1_uint32, 0, code1_uint32};
T9Var7 t9_var7{"obj9_7", &obj9_7, code1_int64, 0, code1_int64};
T9Var8 t9_var8{"obj9_8", &obj9_8, code1_uint64, 0, code1_uint64};

T9Var9 t9_var9{"obj9_9", &obj9_9, code1_int64, 0, code1_int64};
T9Var10 t9_var10{"obj9_10", &obj9_10, code1_uint64, 0, code1_uint64};
T9Var11 t9_var11{"obj9_11", &obj9_11, code1_int32, 0, code1_int32};
T9Var12 t9_var12{"obj9_12", &obj9_12, code1_uint32, 0, code1_uint32};
T9Var13 t9_var13{"obj9_13", &obj9_13, code1_int16, 0, code1_int16};
T9Var14 t9_var14{"obj9_14", &obj9_14, code1_uint16, 0, code1_uint16};
T9Var15 t9_var15{"obj9_15", &obj9_15, code1_int8, 0, code1_int8};
T9Var16 t9_var16{"obj9_16", &obj9_16, code1_uint8, 0, code1_uint8};

T9Var17 t9_var17{"obj9_17", &obj9_17, code1_uint64, 0, code1_uint64};
T9Var18 t9_var18{"obj9_18", &obj9_18, code1_int64, 0, code1_int64};
T9Var19 t9_var19{"obj9_19", &obj9_19, code1_uint32, 0, code1_uint32};
T9Var20 t9_var20{"obj9_20", &obj9_20, code1_int32, 0, code1_int32};
T9Var21 t9_var21{"obj9_21", &obj9_21, code1_uint16, 0, code1_uint16};
T9Var22 t9_var22{"obj9_22", &obj9_22, code1_int16, 0, code1_int16};
T9Var23 t9_var23{"obj9_23", &obj9_23, code1_uint8, 0, code1_uint8};
T9Var24 t9_var24{"obj9_24", &obj9_24, code1_int8, 0, code1_int8};

REGISTER_TEST(t9, new TestIdRecCode<Case5, T9Var1, T9Var2, T9Var3, T9Var4, 
    T9Var5, T9Var6, T9Var7, T9Var8, T9Var9, T9Var10, T9Var11, T9Var12,
    T9Var13, T9Var14, T9Var15, T9Var16, T9Var17, T9Var18, T9Var19, T9Var20,
    T9Var21, T9Var22, T9Var23, T9Var24>(t9_var1, t9_var2, t9_var3,
        t9_var4, t9_var5, t9_var6, t9_var7, t9_var8, t9_var9, t9_var10,
        t9_var11, t9_var12, t9_var13, t9_var14, t9_var15, t9_var16, t9_var17,
        t9_var18, t9_var19, t9_var20, t9_var21, t9_var22, t9_var23, t9_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj10_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj10_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj10_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj10_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj10_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj10_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj10_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj10_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj10_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj10_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj10_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj10_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj10_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj10_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj10_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj10_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj10_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj10_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj10_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj10_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj10_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj10_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj10_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj10_24;

typedef VariableTestIdRecCode<std::int8_t, std::int8_t,
    basic::error::id::rec::Code<std::int8_t, std::int8_t> *> T10Var1;
typedef VariableTestIdRecCode<std::uint8_t, std::uint8_t,
    basic::error::id::rec::Code<std::uint8_t, std::uint8_t> *> T10Var2;
typedef VariableTestIdRecCode<std::int16_t, std::int16_t,
    basic::error::id::rec::Code<std::int16_t, std::int16_t> *> T10Var3;
typedef VariableTestIdRecCode<std::uint16_t, std::uint16_t,
    basic::error::id::rec::Code<std::uint16_t, std::uint16_t> *> T10Var4;
typedef VariableTestIdRecCode<std::int32_t, std::int32_t,
    basic::error::id::rec::Code<std::int32_t, std::int32_t> *> T10Var5;
typedef VariableTestIdRecCode<std::uint32_t, std::uint32_t,
    basic::error::id::rec::Code<std::uint32_t, std::uint32_t> *> T10Var6;
typedef VariableTestIdRecCode<std::int64_t, std::int64_t,
    basic::error::id::rec::Code<std::int64_t, std::int64_t> *> T10Var7;
typedef VariableTestIdRecCode<std::uint64_t, std::uint64_t,
    basic::error::id::rec::Code<std::uint64_t, std::uint64_t> *> T10Var8;

typedef VariableTestIdRecCode<std::int8_t, std::int64_t,
    basic::error::id::rec::Code<std::int8_t, std::int64_t> *> T10Var9;
typedef VariableTestIdRecCode<std::uint8_t, std::uint64_t,
    basic::error::id::rec::Code<std::uint8_t, std::uint64_t> *> T10Var10;
typedef VariableTestIdRecCode<std::int16_t, std::int32_t,
    basic::error::id::rec::Code<std::int16_t, std::int32_t> *> T10Var11;
typedef VariableTestIdRecCode<std::uint16_t, std::uint32_t,
    basic::error::id::rec::Code<std::uint16_t, std::uint32_t> *> T10Var12;
typedef VariableTestIdRecCode<std::int32_t, std::int16_t,
    basic::error::id::rec::Code<std::int32_t, std::int16_t> *> T10Var13;
typedef VariableTestIdRecCode<std::uint32_t, std::uint16_t,
    basic::error::id::rec::Code<std::uint32_t, std::uint16_t> *> T10Var14;
typedef VariableTestIdRecCode<std::int64_t, std::int8_t,
    basic::error::id::rec::Code<std::int64_t, std::int8_t> *> T10Var15;
typedef VariableTestIdRecCode<std::uint64_t, std::uint8_t,
    basic::error::id::rec::Code<std::uint64_t, std::uint8_t> *> T10Var16;

typedef VariableTestIdRecCode<std::int8_t, std::uint64_t,
    basic::error::id::rec::Code<std::int8_t, std::uint64_t> *> T10Var17;
typedef VariableTestIdRecCode<std::uint8_t, std::int64_t,
    basic::error::id::rec::Code<std::uint8_t, std::int64_t> *> T10Var18;
typedef VariableTestIdRecCode<std::int16_t, std::uint32_t,
    basic::error::id::rec::Code<std::int16_t, std::uint32_t> *> T10Var19;
typedef VariableTestIdRecCode<std::uint16_t, std::int32_t,
    basic::error::id::rec::Code<std::uint16_t, std::int32_t> *> T10Var20;
typedef VariableTestIdRecCode<std::int32_t, std::uint16_t,
    basic::error::id::rec::Code<std::int32_t, std::uint16_t> *> T10Var21;
typedef VariableTestIdRecCode<std::uint32_t, std::int16_t,
    basic::error::id::rec::Code<std::uint32_t, std::int16_t> *> T10Var22;
typedef VariableTestIdRecCode<std::int64_t, std::uint8_t,
    basic::error::id::rec::Code<std::int64_t, std::uint8_t> *> T10Var23;
typedef VariableTestIdRecCode<std::uint64_t, std::int8_t,
    basic::error::id::rec::Code<std::uint64_t, std::int8_t> *> T10Var24;

T10Var1 t10_var1{"obj10_1", &obj10_1, &obj2_1, obj2_1.Error, 0};
T10Var2 t10_var2{"obj10_2", &obj10_2, &obj2_2, obj2_2.Error, 0};
T10Var3 t10_var3{"obj10_3", &obj10_3, &obj2_3, obj2_3.Error, 0};
T10Var4 t10_var4{"obj10_4", &obj10_4, &obj2_4, obj2_4.Error, 0};
T10Var5 t10_var5{"obj10_5", &obj10_5, &obj2_5, obj2_5.Error, 0};
T10Var6 t10_var6{"obj10_6", &obj10_6, &obj2_6, obj2_6.Error, 0};
T10Var7 t10_var7{"obj10_7", &obj10_7, &obj2_7, obj2_7.Error, 0};
T10Var8 t10_var8{"obj10_8", &obj10_8, &obj2_8, obj2_8.Error, 0};

T10Var9 t10_var9{"obj10_9", &obj10_9, &obj2_9, obj2_9.Error, 0};
T10Var10 t10_var10{"obj10_10", &obj10_10, &obj2_10, obj2_10.Error, 0};
T10Var11 t10_var11{"obj10_11", &obj10_11, &obj2_11, obj2_11.Error, 0};
T10Var12 t10_var12{"obj10_12", &obj10_12, &obj2_12, obj2_12.Error, 0};
T10Var13 t10_var13{"obj10_13", &obj10_13, &obj2_13, obj2_13.Error, 0};
T10Var14 t10_var14{"obj10_14", &obj10_14, &obj2_14, obj2_14.Error, 0};
T10Var15 t10_var15{"obj10_15", &obj10_15, &obj2_15, obj2_15.Error, 0};
T10Var16 t10_var16{"obj10_16", &obj10_16, &obj2_16, obj2_16.Error, 0};

T10Var17 t10_var17{"obj10_17", &obj10_17, &obj2_17, obj2_17.Error, 0};
T10Var18 t10_var18{"obj10_18", &obj10_18, &obj2_18, obj2_18.Error, 0};
T10Var19 t10_var19{"obj10_19", &obj10_19, &obj2_19, obj2_19.Error, 0};
T10Var20 t10_var20{"obj10_20", &obj10_20, &obj2_20, obj2_20.Error, 0};
T10Var21 t10_var21{"obj10_21", &obj10_21, &obj2_21, obj2_21.Error, 0};
T10Var22 t10_var22{"obj10_22", &obj10_22, &obj2_22, obj2_22.Error, 0};
T10Var23 t10_var23{"obj10_23", &obj10_23, &obj2_23, obj2_23.Error, 0};
T10Var24 t10_var24{"obj10_24", &obj10_24, &obj2_24, obj2_24.Error, 0};

REGISTER_TEST(t10, new TestIdRecCode<Case6, T10Var1, T10Var2, T10Var3, T10Var4,
    T10Var5, T10Var6, T10Var7, T10Var8, T10Var9, T10Var10, T10Var11, T10Var12,
    T10Var13, T10Var14, T10Var15, T10Var16, T10Var17, T10Var18, T10Var19, 
    T10Var20, T10Var21, T10Var22, T10Var23, T10Var24>(t10_var1, t10_var2, 
        t10_var3, t10_var4, t10_var5, t10_var6, t10_var7, t10_var8, t10_var9, 
        t10_var10, t10_var11, t10_var12, t10_var13, t10_var14, t10_var15, 
        t10_var16, t10_var17, t10_var18, t10_var19, t10_var20, t10_var21, 
        t10_var22, t10_var23, t10_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj11_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj11_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj11_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj11_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj11_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj11_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj11_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj11_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj11_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj11_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj11_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj11_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj11_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj11_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj11_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj11_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj11_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj11_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj11_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj11_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj11_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj11_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj11_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj11_24;

T10Var1 t11_var1{"obj11_1", &obj11_1, &obj3_1, 0, obj3_1.ErrorSystem};
T10Var2 t11_var2{"obj11_2", &obj11_2, &obj3_2, 0, obj3_2.ErrorSystem};
T10Var3 t11_var3{"obj11_3", &obj11_3, &obj3_3, 0, obj3_3.ErrorSystem};
T10Var4 t11_var4{"obj11_4", &obj11_4, &obj3_4, 0, obj3_4.ErrorSystem};
T10Var5 t11_var5{"obj11_5", &obj11_5, &obj3_5, 0, obj3_5.ErrorSystem};
T10Var6 t11_var6{"obj11_6", &obj11_6, &obj3_6, 0, obj3_6.ErrorSystem};
T10Var7 t11_var7{"obj11_7", &obj11_7, &obj3_7, 0, obj3_7.ErrorSystem};
T10Var8 t11_var8{"obj11_8", &obj11_8, &obj3_8, 0, obj3_8.ErrorSystem};

T10Var9 t11_var9{"obj11_9", &obj11_9, &obj3_9, 0, obj3_9.ErrorSystem};
T10Var10 t11_var10{"obj11_10", &obj11_10, &obj3_10, 0, obj3_10.ErrorSystem};
T10Var11 t11_var11{"obj11_11", &obj11_11, &obj3_11, 0, obj3_11.ErrorSystem};
T10Var12 t11_var12{"obj11_12", &obj11_12, &obj3_12, 0, obj3_12.ErrorSystem};
T10Var13 t11_var13{"obj11_13", &obj11_13, &obj3_13, 0, obj3_13.ErrorSystem};
T10Var14 t11_var14{"obj11_14", &obj11_14, &obj3_14, 0, obj3_14.ErrorSystem};
T10Var15 t11_var15{"obj11_15", &obj11_15, &obj3_15, 0, obj3_15.ErrorSystem};
T10Var16 t11_var16{"obj11_16", &obj11_16, &obj3_16, 0, obj3_16.ErrorSystem};

T10Var17 t11_var17{"obj11_17", &obj11_17, &obj3_17, 0, obj3_17.ErrorSystem};
T10Var18 t11_var18{"obj11_18", &obj11_18, &obj3_18, 0, obj3_18.ErrorSystem};
T10Var19 t11_var19{"obj11_19", &obj11_19, &obj3_19, 0, obj3_19.ErrorSystem};
T10Var20 t11_var20{"obj11_20", &obj11_20, &obj3_20, 0, obj3_20.ErrorSystem};
T10Var21 t11_var21{"obj11_21", &obj11_21, &obj3_21, 0, obj3_21.ErrorSystem};
T10Var22 t11_var22{"obj11_22", &obj11_22, &obj3_22, 0, obj3_22.ErrorSystem};
T10Var23 t11_var23{"obj11_23", &obj11_23, &obj3_23, 0, obj3_23.ErrorSystem};
T10Var24 t11_var24{"obj11_24", &obj11_24, &obj3_24, 0, obj3_24.ErrorSystem};

REGISTER_TEST(t11, new TestIdRecCode<Case7, T10Var1, T10Var2, T10Var3, T10Var4, 
    T10Var5, T10Var6, T10Var7, T10Var8, T10Var9, T10Var10, T10Var11, T10Var12,
    T10Var13, T10Var14, T10Var15, T10Var16, T10Var17, T10Var18, T10Var19, 
    T10Var20, T10Var21, T10Var22, T10Var23, T10Var24>(t11_var1, t11_var2, 
        t11_var3, t11_var4, t11_var5, t11_var6, t11_var7, t11_var8, t11_var9, 
        t11_var10, t11_var11, t11_var12, t11_var13, t11_var14, t11_var15, 
        t11_var16, t11_var17, t11_var18, t11_var19, t11_var20, t11_var21, 
        t11_var22, t11_var23, t11_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj12_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj12_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj12_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj12_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj12_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj12_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj12_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj12_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj12_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj12_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj12_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj12_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj12_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj12_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj12_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj12_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj12_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj12_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj12_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj12_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj12_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj12_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj12_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj12_24;

T10Var1 t12_var1{"obj12_1", &obj12_1, &obj6_1, obj2_1.Error, 0};
T10Var2 t12_var2{"obj12_2", &obj12_2, &obj6_2, obj2_2.Error, 0};
T10Var3 t12_var3{"obj12_3", &obj12_3, &obj6_3, obj2_3.Error, 0};
T10Var4 t12_var4{"obj12_4", &obj12_4, &obj6_4, obj2_4.Error, 0};
T10Var5 t12_var5{"obj12_5", &obj12_5, &obj6_5, obj2_5.Error, 0};
T10Var6 t12_var6{"obj12_6", &obj12_6, &obj6_6, obj2_6.Error, 0};
T10Var7 t12_var7{"obj12_7", &obj12_7, &obj6_7, obj2_7.Error, 0};
T10Var8 t12_var8{"obj12_8", &obj12_8, &obj6_8, obj2_8.Error, 0};

T10Var9 t12_var9{"obj12_9", &obj12_9, &obj6_9, obj2_9.Error, 0};
T10Var10 t12_var10{"obj12_10", &obj12_10, &obj6_10, obj2_10.Error, 0};
T10Var11 t12_var11{"obj12_11", &obj12_11, &obj6_11, obj2_11.Error, 0};
T10Var12 t12_var12{"obj12_12", &obj12_12, &obj6_12, obj2_12.Error, 0};
T10Var13 t12_var13{"obj12_13", &obj12_13, &obj6_13, obj2_13.Error, 0};
T10Var14 t12_var14{"obj12_14", &obj12_14, &obj6_14, obj2_14.Error, 0};
T10Var15 t12_var15{"obj12_15", &obj12_15, &obj6_15, obj2_15.Error, 0};
T10Var16 t12_var16{"obj12_16", &obj12_16, &obj6_16, obj2_16.Error, 0};

T10Var17 t12_var17{"obj12_17", &obj12_17, &obj6_17, obj2_17.Error, 0};
T10Var18 t12_var18{"obj12_18", &obj12_18, &obj6_18, obj2_18.Error, 0};
T10Var19 t12_var19{"obj12_19", &obj12_19, &obj6_19, obj2_19.Error, 0};
T10Var20 t12_var20{"obj12_20", &obj12_20, &obj6_20, obj2_20.Error, 0};
T10Var21 t12_var21{"obj12_21", &obj12_21, &obj6_21, obj2_21.Error, 0};
T10Var22 t12_var22{"obj12_22", &obj12_22, &obj6_22, obj2_22.Error, 0};
T10Var23 t12_var23{"obj12_23", &obj12_23, &obj6_23, obj2_23.Error, 0};
T10Var24 t12_var24{"obj12_24", &obj12_24, &obj6_24, obj2_24.Error, 0};

REGISTER_TEST(t12, new TestIdRecCode<Case8, T10Var1, T10Var2, T10Var3, T10Var4,
    T10Var5, T10Var6, T10Var7, T10Var8, T10Var9, T10Var10, T10Var11, T10Var12,
    T10Var13, T10Var14, T10Var15, T10Var16, T10Var17, T10Var18, T10Var19, 
    T10Var20, T10Var21, T10Var22, T10Var23, T10Var24>(t12_var1, t12_var2, 
        t12_var3, t12_var4, t12_var5, t12_var6, t12_var7, t12_var8, t12_var9, 
        t12_var10, t12_var11, t12_var12, t12_var13, t12_var14, t12_var15, 
        t12_var16, t12_var17, t12_var18, t12_var19, t12_var20, t12_var21, 
        t12_var22, t12_var23, t12_var24));

T1Var1 t13_var1{"obj6_1", &obj6_1, 0, 0, 0};
T1Var2 t13_var2{"obj6_2", &obj6_2, 0, 0, 0};
T1Var3 t13_var3{"obj6_3", &obj6_3, 0, 0, 0};
T1Var4 t13_var4{"obj6_4", &obj6_4, 0, 0, 0};
T1Var5 t13_var5{"obj6_5", &obj6_5, 0, 0, 0};
T1Var6 t13_var6{"obj6_6", &obj6_6, 0, 0, 0};
T1Var7 t13_var7{"obj6_7", &obj6_7, 0, 0, 0};
T1Var8 t13_var8{"obj6_8", &obj6_8, 0, 0, 0};

T1Var9 t13_var9{"obj6_9", &obj6_9, 0, 0, 0};
T1Var10 t13_var10{"obj6_10", &obj6_10, 0, 0, 0};
T1Var11 t13_var11{"obj6_11", &obj6_11, 0, 0, 0};
T1Var12 t13_var12{"obj6_12", &obj6_12, 0, 0, 0};
T1Var13 t13_var13{"obj6_13", &obj6_13, 0, 0, 0};
T1Var14 t13_var14{"obj6_14", &obj6_14, 0, 0, 0};
T1Var15 t13_var15{"obj6_15", &obj6_15, 0, 0, 0};
T1Var16 t13_var16{"obj6_16", &obj6_16, 0, 0, 0};

T1Var17 t13_var17{"obj6_17", &obj6_17, 0, 0, 0};
T1Var18 t13_var18{"obj6_18", &obj6_18, 0, 0, 0};
T1Var19 t13_var19{"obj6_19", &obj6_19, 0, 0, 0};
T1Var20 t13_var20{"obj6_20", &obj6_20, 0, 0, 0};
T1Var21 t13_var21{"obj6_21", &obj6_21, 0, 0, 0};
T1Var22 t13_var22{"obj6_22", &obj6_22, 0, 0, 0};
T1Var23 t13_var23{"obj6_23", &obj6_23, 0, 0, 0};
T1Var24 t13_var24{"obj6_24", &obj6_24, 0, 0, 0};

REGISTER_TEST(t13, new TestIdRecCode<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t13_var1, t13_var2, t13_var3,
        t13_var4, t13_var5, t13_var6, t13_var7, t13_var8, t13_var9, t13_var10,
        t13_var11, t13_var12, t13_var13, t13_var14, t13_var15, t13_var16, 
        t13_var17, t13_var18, t13_var19, t13_var20, t13_var21, t13_var22, 
        t13_var23, t13_var24));

basic::error::id::rec::Code<std::int8_t, std::int8_t> obj14_1;
basic::error::id::rec::Code<std::uint8_t, std::uint8_t> obj14_2;
basic::error::id::rec::Code<std::int16_t, std::int16_t> obj14_3;
basic::error::id::rec::Code<std::uint16_t, std::uint16_t> obj14_4;
basic::error::id::rec::Code<std::int32_t, std::int32_t> obj14_5;
basic::error::id::rec::Code<std::uint32_t, std::uint32_t> obj14_6;
basic::error::id::rec::Code<std::int64_t, std::int64_t> obj14_7;
basic::error::id::rec::Code<std::uint64_t, std::uint64_t> obj14_8;

basic::error::id::rec::Code<std::int8_t, std::int64_t> obj14_9;
basic::error::id::rec::Code<std::uint8_t, std::uint64_t> obj14_10;
basic::error::id::rec::Code<std::int16_t, std::int32_t> obj14_11;
basic::error::id::rec::Code<std::uint16_t, std::uint32_t> obj14_12;
basic::error::id::rec::Code<std::int32_t, std::int16_t> obj14_13;
basic::error::id::rec::Code<std::uint32_t, std::uint16_t> obj14_14;
basic::error::id::rec::Code<std::int64_t, std::int8_t> obj14_15;
basic::error::id::rec::Code<std::uint64_t, std::uint8_t> obj14_16;

basic::error::id::rec::Code<std::int8_t, std::uint64_t> obj14_17;
basic::error::id::rec::Code<std::uint8_t, std::int64_t> obj14_18;
basic::error::id::rec::Code<std::int16_t, std::uint32_t> obj14_19;
basic::error::id::rec::Code<std::uint16_t, std::int32_t> obj14_20;
basic::error::id::rec::Code<std::int32_t, std::uint16_t> obj14_21;
basic::error::id::rec::Code<std::uint32_t, std::int16_t> obj14_22;
basic::error::id::rec::Code<std::int64_t, std::uint8_t> obj14_23;
basic::error::id::rec::Code<std::uint64_t, std::int8_t> obj14_24;

T10Var1 t14_var1{"obj14_1", &obj14_1, &obj7_1, 0, obj3_1.ErrorSystem};
T10Var2 t14_var2{"obj14_2", &obj14_2, &obj7_2, 0, obj3_2.ErrorSystem};
T10Var3 t14_var3{"obj14_3", &obj14_3, &obj7_3, 0, obj3_3.ErrorSystem};
T10Var4 t14_var4{"obj14_4", &obj14_4, &obj7_4, 0, obj3_4.ErrorSystem};
T10Var5 t14_var5{"obj14_5", &obj14_5, &obj7_5, 0, obj3_5.ErrorSystem};
T10Var6 t14_var6{"obj14_6", &obj14_6, &obj7_6, 0, obj3_6.ErrorSystem};
T10Var7 t14_var7{"obj14_7", &obj14_7, &obj7_7, 0, obj3_7.ErrorSystem};
T10Var8 t14_var8{"obj14_8", &obj14_8, &obj7_8, 0, obj3_8.ErrorSystem};

T10Var9 t14_var9{"obj14_9", &obj14_9, &obj7_9, 0, obj3_9.ErrorSystem};
T10Var10 t14_var10{"obj14_10", &obj14_10, &obj7_10, 0, obj3_10.ErrorSystem};
T10Var11 t14_var11{"obj14_11", &obj14_11, &obj7_11, 0, obj3_11.ErrorSystem};
T10Var12 t14_var12{"obj14_12", &obj14_12, &obj7_12, 0, obj3_12.ErrorSystem};
T10Var13 t14_var13{"obj14_13", &obj14_13, &obj7_13, 0, obj3_13.ErrorSystem};
T10Var14 t14_var14{"obj14_14", &obj14_14, &obj7_14, 0, obj3_14.ErrorSystem};
T10Var15 t14_var15{"obj14_15", &obj14_15, &obj7_15, 0, obj3_15.ErrorSystem};
T10Var16 t14_var16{"obj14_16", &obj14_16, &obj7_16, 0, obj3_16.ErrorSystem};

T10Var17 t14_var17{"obj14_17", &obj14_17, &obj7_17, 0, obj3_17.ErrorSystem};
T10Var18 t14_var18{"obj14_18", &obj14_18, &obj7_18, 0, obj3_18.ErrorSystem};
T10Var19 t14_var19{"obj14_19", &obj14_19, &obj7_19, 0, obj3_19.ErrorSystem};
T10Var20 t14_var20{"obj14_20", &obj14_20, &obj7_20, 0, obj3_20.ErrorSystem};
T10Var21 t14_var21{"obj14_21", &obj14_21, &obj7_21, 0, obj3_21.ErrorSystem};
T10Var22 t14_var22{"obj14_22", &obj14_22, &obj7_22, 0, obj3_22.ErrorSystem};
T10Var23 t14_var23{"obj14_23", &obj14_23, &obj7_23, 0, obj3_23.ErrorSystem};
T10Var24 t14_var24{"obj14_24", &obj14_24, &obj7_24, 0, obj3_24.ErrorSystem};

REGISTER_TEST(t14, new TestIdRecCode<Case9, T10Var1, T10Var2, T10Var3, T10Var4,
    T10Var5, T10Var6, T10Var7, T10Var8, T10Var9, T10Var10, T10Var11, T10Var12,
    T10Var13, T10Var14, T10Var15, T10Var16, T10Var17, T10Var18, T10Var19, 
    T10Var20, T10Var21, T10Var22, T10Var23, T10Var24>(t14_var1, t14_var2, 
        t14_var3, t14_var4, t14_var5, t14_var6, t14_var7, t14_var8, t14_var9, 
        t14_var10, t14_var11, t14_var12, t14_var13, t14_var14, t14_var15, 
        t14_var16, t14_var17, t14_var18, t14_var19, t14_var20, t14_var21, 
        t14_var22, t14_var23, t14_var24));

T1Var1 t15_var1{"obj7_1", &obj7_1, 0, 0, 0};
T1Var2 t15_var2{"obj7_2", &obj7_2, 0, 0, 0};
T1Var3 t15_var3{"obj7_3", &obj7_3, 0, 0, 0};
T1Var4 t15_var4{"obj7_4", &obj7_4, 0, 0, 0};
T1Var5 t15_var5{"obj7_5", &obj7_5, 0, 0, 0};
T1Var6 t15_var6{"obj7_6", &obj7_6, 0, 0, 0};
T1Var7 t15_var7{"obj7_7", &obj7_7, 0, 0, 0};
T1Var8 t15_var8{"obj7_8", &obj7_8, 0, 0, 0};

T1Var9 t15_var9{"obj7_9", &obj7_9, 0, 0, 0};
T1Var10 t15_var10{"obj7_10", &obj7_10, 0, 0, 0};
T1Var11 t15_var11{"obj7_11", &obj7_11, 0, 0, 0};
T1Var12 t15_var12{"obj7_12", &obj7_12, 0, 0, 0};
T1Var13 t15_var13{"obj7_13", &obj7_13, 0, 0, 0};
T1Var14 t15_var14{"obj7_14", &obj7_14, 0, 0, 0};
T1Var15 t15_var15{"obj7_15", &obj7_15, 0, 0, 0};
T1Var16 t15_var16{"obj7_16", &obj7_16, 0, 0, 0};

T1Var17 t15_var17{"obj7_17", &obj7_17, 0, 0, 0};
T1Var18 t15_var18{"obj7_18", &obj7_18, 0, 0, 0};
T1Var19 t15_var19{"obj7_19", &obj7_19, 0, 0, 0};
T1Var20 t15_var20{"obj7_20", &obj7_20, 0, 0, 0};
T1Var21 t15_var21{"obj7_21", &obj7_21, 0, 0, 0};
T1Var22 t15_var22{"obj7_22", &obj7_22, 0, 0, 0};
T1Var23 t15_var23{"obj7_23", &obj7_23, 0, 0, 0};
T1Var24 t15_var24{"obj7_24", &obj7_24, 0, 0, 0};

REGISTER_TEST(t15, new TestIdRecCode<Case1, T1Var1, T1Var2, T1Var3, T1Var4, 
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18, T1Var19, T1Var20,
    T1Var21, T1Var22, T1Var23, T1Var24>(t15_var1, t15_var2, t15_var3,
        t15_var4, t15_var5, t15_var6, t15_var7, t15_var8, t15_var9, 
        t15_var10, t15_var11, t15_var12, t15_var13, t15_var14, t15_var15, 
        t15_var16, t15_var17, t15_var18, t15_var19, t15_var20, t15_var21, 
        t15_var22, t15_var23, t15_var24));

int main()
{
    RUN_TEST();
}

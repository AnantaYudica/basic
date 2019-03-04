#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/CString.h"
#include "test/cstr/out/Argument.h"

#include "error/id/rec/ErrorSystem.h"

#include <cstdint>
#include <utility>

struct TestCategoryValue {};
struct TestCodeValue {};
struct TestCodeValueAssignment {};
struct TestCopyAssignment {};
struct TestMoveAssignment {};
struct TestAliasTypeCategoryValue {};
struct TestAliasTypeCodeValue {};

template<typename TCategoryValue, typename TCodeValue, 
    typename TAssignValue = int>
using VariableTestIdRecErrorSystem = basic::test::Variable<
    TCategoryValue,
    TCodeValue,
    TAssignValue,
    basic::error::id::rec::ErrorSystem<TCategoryValue, TCodeValue>,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::id::rec::ErrorSystem<
        TCategoryValue, TCodeValue> *>,
    basic::test::Value<TAssignValue>,
    basic::test::Value<TCategoryValue>,
    basic::test::Value<TCodeValue>>;

constexpr std::size_t ICategoryValueType = 0;
constexpr std::size_t ICodeValueType = 1;
constexpr std::size_t IAssignValueType = 2;
constexpr std::size_t IIdRecErrorSystemType = 3;
constexpr std::size_t IObjName = 4;
constexpr std::size_t IObjValue = 5;
constexpr std::size_t IAssignValue = 6;
constexpr std::size_t ICategoryValue = 7;
constexpr std::size_t ICodeValue = 8;

typedef basic::test::msg::Argument<TestCategoryValue,
    basic::test::msg::arg::type::Name<IIdRecErrorSystemType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICategoryValueType>,
    basic::test::msg::arg::Value<ICategoryValue>> ArgTestCategoryValue;

typedef basic::test::msg::Base<TestCategoryValue, char, 
    ArgTestCategoryValue, ArgTestCategoryValue, 
    ArgTestCategoryValue> MessageBaseTestCategoryValue;

typedef basic::test::msg::Argument<TestCodeValue,
    basic::test::msg::arg::type::Name<IIdRecErrorSystemType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::Value<ICodeValue>> ArgTestCodeValue;

typedef basic::test::msg::Base<TestCodeValue, char, 
    ArgTestCodeValue, ArgTestCodeValue, 
    ArgTestCodeValue> MessageBaseTestCodeValue;
    
typedef basic::test::msg::Argument<TestCodeValueAssignment,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IAssignValueType>,
    basic::test::msg::arg::Value<IAssignValue>> 
        ArgTestCodeValueAssignment;

typedef basic::test::msg::Argument<TestCodeValueAssignment,
    basic::test::msg::arg::Value<IObjName>> 
        ArgErrorTestCodeValueAssignment;

typedef basic::test::msg::Base<TestCodeValueAssignment, char, 
    ArgTestCodeValueAssignment, ArgTestCodeValueAssignment, 
    ArgErrorTestCodeValueAssignment> MessageBaseTestCodeValueAssignment;

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
    
typedef basic::test::msg::Argument<TestAliasTypeCategoryValue,
    basic::test::msg::arg::type::Name<IIdRecErrorSystemType>,
    basic::test::msg::arg::type::Name<ICategoryValueType>> 
        ArgTestAliasTypeCategoryValue;

typedef basic::test::msg::Base<TestAliasTypeCategoryValue, char, 
    ArgTestAliasTypeCategoryValue, ArgTestAliasTypeCategoryValue, 
    ArgTestAliasTypeCategoryValue> MessageBaseTestAliasTypeCategoryValue;
    
typedef basic::test::msg::Argument<TestAliasTypeCodeValue,
    basic::test::msg::arg::type::Name<IIdRecErrorSystemType>,
    basic::test::msg::arg::type::Name<ICodeValueType>> 
        ArgTestAliasTypeCodeValue;

typedef basic::test::msg::Base<TestAliasTypeCodeValue, char, 
    ArgTestAliasTypeCodeValue, ArgTestAliasTypeCodeValue, 
    ArgTestAliasTypeCodeValue> MessageBaseTestAliasTypeCodeValue;
    
template<typename TCases, typename... TVariables>
class TestIdRecErrorSystem :
    public MessageBaseTestCategoryValue,
    public MessageBaseTestCodeValue,
    public MessageBaseTestCodeValueAssignment,
    public MessageBaseTestCopyAssignment,
    public MessageBaseTestMoveAssignment,
    public MessageBaseTestAliasTypeCategoryValue,
    public MessageBaseTestAliasTypeCodeValue,
    public basic::test::Message<BASIC_TEST, TestIdRecErrorSystem<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdRecErrorSystem<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdRecErrorSystem<TCases, TVariables...>, 
        TVariables...>
{
public:
    using MessageBaseTestCategoryValue::Format;
    using MessageBaseTestCategoryValue::SetFormat;
    using MessageBaseTestCategoryValue::Argument;
    using MessageBaseTestCodeValue::Format;
    using MessageBaseTestCodeValue::SetFormat;
    using MessageBaseTestCodeValue::Argument;
    using MessageBaseTestCodeValueAssignment::Format;
    using MessageBaseTestCodeValueAssignment::SetFormat;
    using MessageBaseTestCodeValueAssignment::Argument;
    using MessageBaseTestCopyAssignment::Format;
    using MessageBaseTestCopyAssignment::SetFormat;
    using MessageBaseTestCopyAssignment::Argument;
    using MessageBaseTestMoveAssignment::Format;
    using MessageBaseTestMoveAssignment::SetFormat;
    using MessageBaseTestMoveAssignment::Argument;
    using MessageBaseTestAliasTypeCategoryValue::Format;
    using MessageBaseTestAliasTypeCategoryValue::SetFormat;
    using MessageBaseTestAliasTypeCategoryValue::Argument;
    using MessageBaseTestAliasTypeCodeValue::Format;
    using MessageBaseTestAliasTypeCodeValue::SetFormat;
    using MessageBaseTestAliasTypeCodeValue::Argument;
    using basic::test::Case<TestIdRecErrorSystem<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdRecErrorSystem<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdRecErrorSystem(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdRecErrorSystem<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdRecErrorSystem<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdRecErrorSystem<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestCategoryValue testCategoryValue;
        basic::test::msg::Format<char> formatCategoryValue("Test return value "
            "%s::Category() {%s} is equal with %s {%d}\n");
        SetFormat(debug, testCategoryValue, formatCategoryValue);
        SetFormat(info, testCategoryValue, std::move(formatCategoryValue));
        SetFormat(error, testCategoryValue, "Error return value "
            "%s::Category() {%s} is not equal with %s {%d}\n");
            
        TestCodeValue testCodeValue;
        basic::test::msg::Format<char> formatCodeValue("Test return value "
            "%s::Code() {%s} is equal with %s {%d}\n");
        SetFormat(debug, testCodeValue, formatCodeValue);
        SetFormat(info, testCodeValue, std::move(formatCodeValue));
        SetFormat(error, testCodeValue, "Error return value "
            "%s::Code() {%s} is not equal with %s {%d}\n");
            
        TestCodeValueAssignment testCodeValueAssignment;
        basic::test::msg::Format<char> formatCodeValueAssignment("Assign "
            "%s with %s {%d}\n");
        SetFormat(debug, testCodeValueAssignment, formatCodeValueAssignment);
        SetFormat(info, testCodeValueAssignment, 
            std::move(formatCodeValueAssignment));
        SetFormat(error, testCodeValueAssignment, "Error %s is nullptr\n");
        
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
        
        TestAliasTypeCategoryValue testAliasTypeCategoryValue;
        basic::test::msg::Format<char> formatAliasTypeCategoryValue("Test "
            "alias type %s::CategoryValueType is same type with %s\n");
        SetFormat(debug, testAliasTypeCategoryValue, 
            formatAliasTypeCategoryValue);
        SetFormat(info, testAliasTypeCategoryValue, 
            std::move(formatAliasTypeCategoryValue));
        SetFormat(error, testAliasTypeCategoryValue, "Error alias type "
            "%s::CategoryValueType is not same type with %s\n");
            
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
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestCategoryValue &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
            TAssignValue> & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->Category() ==
            basic::test::var::At<ICategoryValue>(var).Get().Get();
    }
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestCodeValue &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
            TAssignValue> & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->Code() ==
            basic::test::var::At<ICodeValue>(var).Get().Get();
    }
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestCodeValueAssignment &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
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
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestCopyAssignment &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
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
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestMoveAssignment &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
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
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestAliasTypeCategoryValue &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
            TAssignValue> & var)
    {
        return typeid(typename basic::error::id::rec::
            ErrorSystem<TCategoryValue, TCodeValue>::CategoryValueType).
            hash_code() ==  typeid(TCategoryValue).hash_code();
    }
    template<typename TCategoryValue, typename TCodeValue, 
        typename TAssignValue>
    bool Result(const TestAliasTypeCodeValue &, 
        VariableTestIdRecErrorSystem<TCategoryValue, TCodeValue, 
            TAssignValue> & var)
    {
        return typeid(typename basic::error::id::rec::
            ErrorSystem<TCategoryValue, TCodeValue>::CodeValueType).
            hash_code() == typeid(TCodeValue).hash_code();
    }
};

using Case1 = basic::test::type::Parameter<TestAliasTypeCategoryValue,
    TestAliasTypeCodeValue, TestCategoryValue, TestCodeValue>;
using Case2 = basic::test::type::Parameter<TestAliasTypeCategoryValue,
    TestAliasTypeCodeValue, TestCodeValueAssignment, TestCategoryValue, 
    TestCodeValue>;
using Case3 = basic::test::type::Parameter<TestAliasTypeCategoryValue,
    TestAliasTypeCodeValue, TestCopyAssignment, TestCategoryValue, 
    TestCodeValue>;
using Case4 = basic::test::type::Parameter<TestAliasTypeCategoryValue,
    TestAliasTypeCodeValue, TestMoveAssignment, TestCategoryValue, 
    TestCodeValue>;

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
struct basic::test::type::Name<basic::error::id::rec::ErrorSystem<TArg1, 
    TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::rec::ErrorSystem<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};

typedef VariableTestIdRecErrorSystem<std::int8_t, std::int8_t> T1Var1;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint8_t> T1Var2;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int16_t> T1Var3;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint16_t> T1Var4;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int32_t> T1Var5;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint32_t> T1Var6;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int64_t> T1Var7;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint64_t> T1Var8;

typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int8_t> T1Var9;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint8_t> T1Var10;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int16_t> T1Var11;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint16_t> T1Var12;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int32_t> T1Var13;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint32_t> T1Var14;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int64_t> T1Var15;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint64_t> T1Var16;

std::int8_t categ1_int8 = -117;
std::uint64_t categ1_uint64 = 4611686018427387903ull;

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj1_1{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj1_2{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj1_3{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj1_4{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj1_5{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj1_6{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj1_7{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj1_8{categ1_int8};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj1_9{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj1_10{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj1_11{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj1_12{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj1_13{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj1_14{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj1_15{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj1_16{categ1_uint64};

T1Var1 t1_var1{"obj1_1", &obj1_1, 0, categ1_int8, 0};
T1Var2 t1_var2{"obj1_2", &obj1_2, 0, categ1_int8, 0};
T1Var3 t1_var3{"obj1_3", &obj1_3, 0, categ1_int8, 0};
T1Var4 t1_var4{"obj1_4", &obj1_4, 0, categ1_int8, 0};
T1Var5 t1_var5{"obj1_5", &obj1_5, 0, categ1_int8, 0};
T1Var6 t1_var6{"obj1_6", &obj1_6, 0, categ1_int8, 0};
T1Var7 t1_var7{"obj1_7", &obj1_7, 0, categ1_int8, 0};
T1Var8 t1_var8{"obj1_8", &obj1_8, 0, categ1_int8, 0};

T1Var9 t1_var9{"obj1_9", &obj1_9, 0, categ1_uint64, 0};
T1Var10 t1_var10{"obj1_10", &obj1_10, 0, categ1_uint64, 0};
T1Var11 t1_var11{"obj1_11", &obj1_11, 0, categ1_uint64, 0};
T1Var12 t1_var12{"obj1_12", &obj1_12, 0, categ1_uint64, 0};
T1Var13 t1_var13{"obj1_13", &obj1_13, 0, categ1_uint64, 0};
T1Var14 t1_var14{"obj1_14", &obj1_14, 0, categ1_uint64, 0};
T1Var15 t1_var15{"obj1_15", &obj1_15, 0, categ1_uint64, 0};
T1Var16 t1_var16{"obj1_16", &obj1_16, 0, categ1_uint64, 0};

REGISTER_TEST(t1, new TestIdRecErrorSystem<Case1, T1Var1, T1Var2, T1Var3, 
    T1Var4, T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16>(t1_var1, t1_var2, t1_var3,
        t1_var4, t1_var5, t1_var6, t1_var7, t1_var8, t1_var9, t1_var10,
        t1_var11, t1_var12, t1_var13, t1_var14, t1_var15, t1_var16));

std::int8_t errorSystem1_int8 = -127;
std::uint8_t errorSystem1_uint8 = 255;
std::int16_t errorSystem1_int16 = -32767;
std::uint16_t errorSystem1_uint16 = 65535;
std::int32_t errorSystem1_int32 = -2147483641l;
std::uint32_t errorSystem1_uint32 = 4294967295ul;
std::int64_t errorSystem1_int64 = -9223372036854775807ll;
std::uint64_t errorSystem1_uint64 = 18446744073709551615ull;

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj2_1{categ1_int8, errorSystem1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj2_2{categ1_int8, errorSystem1_uint8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj2_3{categ1_int8, errorSystem1_int16};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj2_4{categ1_int8, errorSystem1_uint16};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj2_5{categ1_int8, errorSystem1_int32};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj2_6{categ1_int8, errorSystem1_uint32};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj2_7{categ1_int8, errorSystem1_int64};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj2_8{categ1_int8, errorSystem1_uint64};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj2_9{categ1_uint64, errorSystem1_int8};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj2_10{categ1_uint64, errorSystem1_uint8};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj2_11{categ1_uint64, errorSystem1_int16};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj2_12{categ1_uint64, errorSystem1_uint16};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj2_13{categ1_uint64, errorSystem1_int32};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj2_14{categ1_uint64, errorSystem1_uint32};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj2_15{categ1_uint64, errorSystem1_int64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj2_16{categ1_uint64, errorSystem1_uint64};

T1Var1 t2_var1{"obj2_1", &obj2_1, 0, categ1_int8, errorSystem1_int8};
T1Var2 t2_var2{"obj2_2", &obj2_2, 0, categ1_int8, errorSystem1_uint8};
T1Var3 t2_var3{"obj2_3", &obj2_3, 0, categ1_int8, errorSystem1_int16};
T1Var4 t2_var4{"obj2_4", &obj2_4, 0, categ1_int8, errorSystem1_uint16};
T1Var5 t2_var5{"obj2_5", &obj2_5, 0, categ1_int8, errorSystem1_int32};
T1Var6 t2_var6{"obj2_6", &obj2_6, 0, categ1_int8, errorSystem1_uint32};
T1Var7 t2_var7{"obj2_7", &obj2_7, 0, categ1_int8, errorSystem1_int64};
T1Var8 t2_var8{"obj2_8", &obj2_8, 0, categ1_int8, errorSystem1_uint64};

T1Var9 t2_var9{"obj2_9", &obj2_9, 0, categ1_uint64, errorSystem1_int8};
T1Var10 t2_var10{"obj2_10", &obj2_10, 0, categ1_uint64, errorSystem1_uint8};
T1Var11 t2_var11{"obj2_11", &obj2_11, 0, categ1_uint64, errorSystem1_int16};
T1Var12 t2_var12{"obj2_12", &obj2_12, 0, categ1_uint64, 
    errorSystem1_uint16};
T1Var13 t2_var13{"obj2_13", &obj2_13, 0, categ1_uint64, errorSystem1_int32};
T1Var14 t2_var14{"obj2_14", &obj2_14, 0, categ1_uint64, 
    errorSystem1_uint32};
T1Var15 t2_var15{"obj2_15", &obj2_15, 0, categ1_uint64, errorSystem1_int64};
T1Var16 t2_var16{"obj2_16", &obj2_16, 0, categ1_uint64, 
    errorSystem1_uint64};

REGISTER_TEST(t2, new TestIdRecErrorSystem<Case1, T1Var1, T1Var2, T1Var3, 
    T1Var4, T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16>(t2_var1, t2_var2, t2_var3,
        t2_var4, t2_var5, t2_var6, t2_var7, t2_var8, t2_var9, t2_var10,
        t2_var11, t2_var12, t2_var13, t2_var14, t2_var15, t2_var16));

basic::error::id::rec::ErrorSystem<std::int8_t, std::int8_t> obj3_1{obj2_1};
basic::error::id::rec::ErrorSystem<std::int8_t, std::uint8_t> obj3_2{obj2_2};
basic::error::id::rec::ErrorSystem<std::int8_t, std::int16_t> obj3_3{obj2_3};
basic::error::id::rec::ErrorSystem<std::int8_t, std::uint16_t> obj3_4{obj2_4};
basic::error::id::rec::ErrorSystem<std::int8_t, std::int32_t> obj3_5{obj2_5};
basic::error::id::rec::ErrorSystem<std::int8_t, std::uint32_t> obj3_6{obj2_6};
basic::error::id::rec::ErrorSystem<std::int8_t, std::int64_t> obj3_7{obj2_7};
basic::error::id::rec::ErrorSystem<std::int8_t, std::uint64_t> obj3_8{obj2_8};

basic::error::id::rec::ErrorSystem<std::uint64_t, std::int8_t> obj3_9{obj2_9};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj3_10{obj2_10};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj3_11{obj2_11};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj3_12{obj2_12};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj3_13{obj2_13};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj3_14{obj2_14};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj3_15{obj2_15};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj3_16{obj2_16};

T1Var1 t3_var1{"obj3_1", &obj3_1, 0, categ1_int8, errorSystem1_int8};
T1Var2 t3_var2{"obj3_2", &obj3_2, 0, categ1_int8, errorSystem1_uint8};
T1Var3 t3_var3{"obj3_3", &obj3_3, 0, categ1_int8, errorSystem1_int16};
T1Var4 t3_var4{"obj3_4", &obj3_4, 0, categ1_int8, errorSystem1_uint16};
T1Var5 t3_var5{"obj3_5", &obj3_5, 0, categ1_int8, errorSystem1_int32};
T1Var6 t3_var6{"obj3_6", &obj3_6, 0, categ1_int8, errorSystem1_uint32};
T1Var7 t3_var7{"obj3_7", &obj3_7, 0, categ1_int8, errorSystem1_int64};
T1Var8 t3_var8{"obj3_8", &obj3_8, 0, categ1_int8, errorSystem1_uint64};

T1Var9 t3_var9{"obj3_9", &obj3_9, 0, categ1_uint64, errorSystem1_int8};
T1Var10 t3_var10{"obj3_10", &obj3_10, 0, categ1_uint64, errorSystem1_uint8};
T1Var11 t3_var11{"obj3_11", &obj3_11, 0, categ1_uint64, errorSystem1_int16};
T1Var12 t3_var12{"obj3_12", &obj3_12, 0, categ1_uint64, 
    errorSystem1_uint16};
T1Var13 t3_var13{"obj3_13", &obj3_13, 0, categ1_uint64, errorSystem1_int32};
T1Var14 t3_var14{"obj3_14", &obj3_14, 0, categ1_uint64, 
    errorSystem1_uint32};
T1Var15 t3_var15{"obj3_15", &obj3_15, 0, categ1_uint64, errorSystem1_int64};
T1Var16 t3_var16{"obj3_16", &obj3_16, 0, categ1_uint64, 
    errorSystem1_uint64};

REGISTER_TEST(t3, new TestIdRecErrorSystem<Case1, T1Var1, T1Var2, T1Var3, 
    T1Var4, T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16>(t3_var1, t3_var2, t3_var3,
        t3_var4, t3_var5, t3_var6, t3_var7, t3_var8, t3_var9, t3_var10,
        t3_var11, t3_var12, t3_var13, t3_var14, t3_var15, t3_var16));

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj3_1_c{obj3_1};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj3_2_c{obj3_2};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj3_3_c{obj3_3};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj3_4_c{obj3_4};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj3_5_c{obj3_5};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj3_6_c{obj3_6};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj3_7_c{obj3_7};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj3_8_c{obj3_8};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj3_9_c{obj3_9};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj3_10_c{obj3_10};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj3_11_c{obj3_11};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj3_12_c{obj3_12};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj3_13_c{obj3_13};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj3_14_c{obj3_14};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj3_15_c{obj3_15};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj3_16_c{obj3_16};

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj4_1{std::move(obj3_1_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj4_2{std::move(obj3_2_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj4_3{std::move(obj3_3_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj4_4{std::move(obj3_4_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj4_5{std::move(obj3_5_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj4_6{std::move(obj3_6_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj4_7{std::move(obj3_7_c)};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj4_8{std::move(obj3_8_c)};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj4_9{std::move(obj3_9_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj4_10{std::move(obj3_10_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj4_11{std::move(obj3_11_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj4_12{std::move(obj3_12_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj4_13{std::move(obj3_13_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj4_14{std::move(obj3_14_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj4_15{std::move(obj3_15_c)};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj4_16{std::move(obj3_16_c)};

T1Var1 t4_var1{"obj4_1", &obj4_1, 0, categ1_int8, errorSystem1_int8};
T1Var2 t4_var2{"obj4_2", &obj4_2, 0, categ1_int8, errorSystem1_uint8};
T1Var3 t4_var3{"obj4_3", &obj4_3, 0, categ1_int8, errorSystem1_int16};
T1Var4 t4_var4{"obj4_4", &obj4_4, 0, categ1_int8, errorSystem1_uint16};
T1Var5 t4_var5{"obj4_5", &obj4_5, 0, categ1_int8, errorSystem1_int32};
T1Var6 t4_var6{"obj4_6", &obj4_6, 0, categ1_int8, errorSystem1_uint32};
T1Var7 t4_var7{"obj4_7", &obj4_7, 0, categ1_int8, errorSystem1_int64};
T1Var8 t4_var8{"obj4_8", &obj4_8, 0, categ1_int8, errorSystem1_uint64};

T1Var9 t4_var9{"obj4_9", &obj4_9, 0, categ1_uint64, errorSystem1_int8};
T1Var10 t4_var10{"obj4_10", &obj4_10, 0, categ1_uint64, errorSystem1_uint8};
T1Var11 t4_var11{"obj4_11", &obj4_11, 0, categ1_uint64, errorSystem1_int16};
T1Var12 t4_var12{"obj4_12", &obj4_12, 0, categ1_uint64, 
    errorSystem1_uint16};
T1Var13 t4_var13{"obj4_13", &obj4_13, 0, categ1_uint64, errorSystem1_int32};
T1Var14 t4_var14{"obj4_14", &obj4_14, 0, categ1_uint64, 
    errorSystem1_uint32};
T1Var15 t4_var15{"obj4_15", &obj4_15, 0, categ1_uint64, errorSystem1_int64};
T1Var16 t4_var16{"obj4_16", &obj4_16, 0, categ1_uint64, 
    errorSystem1_uint64};

T1Var1 t4_var17{"obj3_1", &obj3_1_c, 0, categ1_int8, 0};
T1Var2 t4_var18{"obj3_2", &obj3_2_c, 0, categ1_int8, 0};
T1Var3 t4_var19{"obj3_3", &obj3_3_c, 0, categ1_int8, 0};
T1Var4 t4_var20{"obj3_4", &obj3_4_c, 0, categ1_int8, 0};
T1Var5 t4_var21{"obj3_5", &obj3_5_c, 0, categ1_int8, 0};
T1Var6 t4_var22{"obj3_6", &obj3_6_c, 0, categ1_int8, 0};
T1Var7 t4_var23{"obj3_7", &obj3_7_c, 0, categ1_int8, 0};
T1Var8 t4_var24{"obj3_8", &obj3_8_c, 0, categ1_int8, 0};

T1Var9 t4_var25{"obj3_9", &obj3_9_c, 0, categ1_uint64, 0};
T1Var10 t4_var26{"obj3_10", &obj3_10_c, 0, categ1_uint64, 0};
T1Var11 t4_var27{"obj3_11", &obj3_11_c, 0, categ1_uint64, 0};
T1Var12 t4_var28{"obj3_12", &obj3_12_c, 0, categ1_uint64, 0};
T1Var13 t4_var29{"obj3_13", &obj3_13_c, 0, categ1_uint64, 0};
T1Var14 t4_var30{"obj3_14", &obj3_14_c, 0, categ1_uint64, 0};
T1Var15 t4_var31{"obj3_15", &obj3_15_c, 0, categ1_uint64, 0};
T1Var16 t4_var32{"obj3_16", &obj3_16_c, 0, categ1_uint64, 0};

REGISTER_TEST(t4, new TestIdRecErrorSystem<Case1, T1Var1, T1Var2, T1Var3, 
    T1Var4, T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var1, T1Var2, T1Var3, T1Var4, T1Var5,
    T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12, T1Var13, 
    T1Var14, T1Var15, T1Var16>(t4_var1, t4_var2, t4_var3, t4_var4, t4_var5, 
        t4_var6, t4_var7, t4_var8, t4_var9, t4_var10, t4_var11, t4_var12, 
        t4_var13, t4_var14, t4_var15, t4_var16, t4_var17, t4_var18, t4_var19, 
        t4_var20, t4_var21, t4_var22, t4_var23, t4_var24, t4_var25, t4_var26, 
        t4_var27, t4_var28, t4_var29, t4_var30, t4_var31, t4_var32));

typedef VariableTestIdRecErrorSystem<std::int8_t, std::int8_t, 
    std::int8_t> T5Var1;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint8_t,
    std::uint8_t> T5Var2;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int16_t,
    std::int16_t> T5Var3;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint16_t,
    std::uint16_t> T5Var4;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int32_t,
    std::int32_t> T5Var5;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint32_t,
    std::uint32_t> T5Var6;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int64_t,
    std::int64_t> T5Var7;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint64_t,
    std::uint64_t> T5Var8;

typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int8_t,
    std::int8_t> T5Var9;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint8_t,
    std::uint8_t> T5Var10;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int16_t,
    std::int16_t> T5Var11;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint16_t,
    std::uint16_t> T5Var12;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int32_t,
    std::int32_t> T5Var13;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint32_t,
    std::uint32_t> T5Var14;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int64_t,
    std::int64_t> T5Var15;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint64_t,
    std::uint64_t> T5Var16;

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj5_1{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj5_2{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj5_3{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj5_4{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj5_5{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj5_6{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj5_7{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj5_8{categ1_int8};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj5_9{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj5_10{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj5_11{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj5_12{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj5_13{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj5_14{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj5_15{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj5_16{categ1_uint64};

T5Var1 t5_var1{"obj5_1", &obj5_1, errorSystem1_int8, categ1_int8, 
    errorSystem1_int8};
T5Var2 t5_var2{"obj5_2", &obj5_2, errorSystem1_uint8, categ1_int8, 
    errorSystem1_uint8};
T5Var3 t5_var3{"obj5_3", &obj5_3, errorSystem1_int16, categ1_int8, 
    errorSystem1_int16};
T5Var4 t5_var4{"obj5_4", &obj5_4, errorSystem1_uint16, categ1_int8, 
    errorSystem1_uint16};
T5Var5 t5_var5{"obj5_5", &obj5_5, errorSystem1_int32, categ1_int8, 
    errorSystem1_int32};
T5Var6 t5_var6{"obj5_6", &obj5_6, errorSystem1_uint32, categ1_int8, 
    errorSystem1_uint32};
T5Var7 t5_var7{"obj5_7", &obj5_7, errorSystem1_int64, categ1_int8, 
    errorSystem1_int64};
T5Var8 t5_var8{"obj5_8", &obj5_8, errorSystem1_uint64, categ1_int8, 
    errorSystem1_uint64};

T5Var9 t5_var9{"obj5_9", &obj5_9, errorSystem1_int8, categ1_uint64, 
    errorSystem1_int8};
T5Var10 t5_var10{"obj5_10", &obj5_10, errorSystem1_uint8, categ1_uint64, 
    errorSystem1_uint8};
T5Var11 t5_var11{"obj5_11", &obj5_11, errorSystem1_int16, categ1_uint64, 
    errorSystem1_int16};
T5Var12 t5_var12{"obj5_12", &obj5_12, errorSystem1_uint16, categ1_uint64, 
    errorSystem1_uint16};
T5Var13 t5_var13{"obj5_13", &obj5_13, errorSystem1_int32, categ1_uint64, 
    errorSystem1_int32};
T5Var14 t5_var14{"obj5_14", &obj5_14, errorSystem1_uint32, categ1_uint64, 
    errorSystem1_uint32};
T5Var15 t5_var15{"obj5_15", &obj5_15, errorSystem1_int64, categ1_uint64, 
    errorSystem1_int64};
T5Var16 t5_var16{"obj5_16", &obj5_16, errorSystem1_uint64, categ1_uint64, 
    errorSystem1_uint64};

REGISTER_TEST(t5, new TestIdRecErrorSystem<Case2, T5Var1, T5Var2, T5Var3, 
    T5Var4, T5Var5, T5Var6, T5Var7, T5Var8, T5Var9, T5Var10, T5Var11, T5Var12,
    T5Var13, T5Var14, T5Var15, T5Var16>(t5_var1, t5_var2, t5_var3,
        t5_var4, t5_var5, t5_var6, t5_var7, t5_var8, t5_var9, t5_var10,
        t5_var11, t5_var12, t5_var13, t5_var14, t5_var15, t5_var16));

typedef VariableTestIdRecErrorSystem<std::int8_t, std::int8_t, 
    basic::error::id::rec::ErrorSystem<std::int8_t, std::int8_t> *> T6Var1;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint8_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::uint8_t> *> T6Var2;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int16_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::int16_t> *> T6Var3;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint16_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::uint16_t> *> T6Var4;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int32_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::int32_t> *> T6Var5;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint32_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::uint32_t> *> T6Var6;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::int64_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::int64_t> *> T6Var7;
typedef VariableTestIdRecErrorSystem<std::int8_t, std::uint64_t,
    basic::error::id::rec::ErrorSystem<std::int8_t, std::uint64_t> *> T6Var8;

typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int8_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, std::int8_t> *> T6Var9;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint8_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, std::uint8_t> *> T6Var10;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int16_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, std::int16_t> *> T6Var11;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint16_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> *> T6Var12;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int32_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, std::int32_t> *> T6Var13;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint32_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> *> T6Var14;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::int64_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, std::int64_t> *> T6Var15;
typedef VariableTestIdRecErrorSystem<std::uint64_t, std::uint64_t,
    basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> *> T6Var16;

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj6_1{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj6_2{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj6_3{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj6_4{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj6_5{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj6_6{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj6_7{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj6_8{categ1_int8};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj6_9{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj6_10{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj6_11{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj6_12{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj6_13{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj6_14{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj6_15{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj6_16{categ1_uint64};

T6Var1 t6_var1{"obj6_1", &obj6_1, &obj5_1, categ1_int8, 
    errorSystem1_int8};
T6Var2 t6_var2{"obj6_2", &obj6_2, &obj5_2, categ1_int8, 
    errorSystem1_uint8};
T6Var3 t6_var3{"obj6_3", &obj6_3, &obj5_3, categ1_int8, 
    errorSystem1_int16};
T6Var4 t6_var4{"obj6_4", &obj6_4, &obj5_4, categ1_int8, 
    errorSystem1_uint16};
T6Var5 t6_var5{"obj6_5", &obj6_5, &obj5_5, categ1_int8, 
    errorSystem1_int32};
T6Var6 t6_var6{"obj6_6", &obj6_6, &obj5_6, categ1_int8, 
    errorSystem1_uint32};
T6Var7 t6_var7{"obj6_7", &obj6_7, &obj5_7, categ1_int8, 
    errorSystem1_int64};
T6Var8 t6_var8{"obj6_8", &obj6_8, &obj5_8, categ1_int8, 
    errorSystem1_uint64};

T6Var9 t6_var9{"obj6_9", &obj6_9, &obj5_9, categ1_uint64, 
    errorSystem1_int8};
T6Var10 t6_var10{"obj6_10", &obj6_10, &obj5_10, categ1_uint64, 
    errorSystem1_uint8};
T6Var11 t6_var11{"obj6_11", &obj6_11, &obj5_11, categ1_uint64, 
    errorSystem1_int16};
T6Var12 t6_var12{"obj6_12", &obj6_12, &obj5_12, categ1_uint64, 
    errorSystem1_uint16};
T6Var13 t6_var13{"obj6_13", &obj6_13, &obj5_13, categ1_uint64, 
    errorSystem1_int32};
T6Var14 t6_var14{"obj6_14", &obj6_14, &obj5_14, categ1_uint64, 
    errorSystem1_uint32};
T6Var15 t6_var15{"obj6_15", &obj6_15, &obj5_15, categ1_uint64, 
    errorSystem1_int64};
T6Var16 t6_var16{"obj6_16", &obj6_16, &obj5_16, categ1_uint64, 
    errorSystem1_uint64};

REGISTER_TEST(t6, new TestIdRecErrorSystem<Case3, T6Var1, T6Var2, T6Var3, 
    T6Var4, T6Var5, T6Var6, T6Var7, T6Var8, T6Var9, T6Var10, T6Var11, T6Var12,
    T6Var13, T6Var14, T6Var15, T6Var16>(t6_var1, t6_var2, t6_var3,
        t6_var4, t6_var5, t6_var6, t6_var7, t6_var8, t6_var9, t6_var10,
        t6_var11, t6_var12, t6_var13, t6_var14, t6_var15, t6_var16));

basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int8_t> obj7_1{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint8_t> obj7_2{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int16_t> obj7_3{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint16_t> obj7_4{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int32_t> obj7_5{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint32_t> obj7_6{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::int64_t> obj7_7{categ1_int8};
basic::error::id::rec::ErrorSystem<std::int8_t, 
    std::uint64_t> obj7_8{categ1_int8};

basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int8_t> obj7_9{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint8_t> obj7_10{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int16_t> obj7_11{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint16_t> obj7_12{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int32_t> obj7_13{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint32_t> obj7_14{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::int64_t> obj7_15{categ1_uint64};
basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> obj7_16{categ1_uint64};

T6Var1 t7_var1{"obj7_1", &obj7_1, &obj6_1, categ1_int8, 
    errorSystem1_int8};
T6Var2 t7_var2{"obj7_2", &obj7_2, &obj6_2, categ1_int8, 
    errorSystem1_uint8};
T6Var3 t7_var3{"obj7_3", &obj7_3, &obj6_3, categ1_int8, 
    errorSystem1_int16};
T6Var4 t7_var4{"obj7_4", &obj7_4, &obj6_4, categ1_int8, 
    errorSystem1_uint16};
T6Var5 t7_var5{"obj7_5", &obj7_5, &obj6_5, categ1_int8, 
    errorSystem1_int32};
T6Var6 t7_var6{"obj7_6", &obj7_6, &obj6_6, categ1_int8, 
    errorSystem1_uint32};
T6Var7 t7_var7{"obj7_7", &obj7_7, &obj6_7, categ1_int8, 
    errorSystem1_int64};
T6Var8 t7_var8{"obj7_8", &obj7_8, &obj6_8, categ1_int8, 
    errorSystem1_uint64};

T6Var9 t7_var9{"obj7_9", &obj7_9, &obj6_9, categ1_uint64, 
    errorSystem1_int8};
T6Var10 t7_var10{"obj7_10", &obj7_10, &obj6_10, categ1_uint64, 
    errorSystem1_uint8};
T6Var11 t7_var11{"obj7_11", &obj7_11, &obj6_11, categ1_uint64, 
    errorSystem1_int16};
T6Var12 t7_var12{"obj7_12", &obj7_12, &obj6_12, categ1_uint64, 
    errorSystem1_uint16};
T6Var13 t7_var13{"obj7_13", &obj7_13, &obj6_13, categ1_uint64, 
    errorSystem1_int32};
T6Var14 t7_var14{"obj7_14", &obj7_14, &obj6_14, categ1_uint64, 
    errorSystem1_uint32};
T6Var15 t7_var15{"obj7_15", &obj7_15, &obj6_15, categ1_uint64, 
    errorSystem1_int64};
T6Var16 t7_var16{"obj7_16", &obj7_16, &obj6_16, categ1_uint64, 
    errorSystem1_uint64};

REGISTER_TEST(t7, new TestIdRecErrorSystem<Case4, T6Var1, T6Var2, T6Var3, 
    T6Var4, T6Var5, T6Var6, T6Var7, T6Var8, T6Var9, T6Var10, T6Var11, T6Var12,
    T6Var13, T6Var14, T6Var15, T6Var16>(t7_var1, t7_var2, t7_var3,
        t7_var4, t7_var5, t7_var6, t7_var7, t7_var8, t7_var9, t7_var10,
        t7_var11, t7_var12, t7_var13, t7_var14, t7_var15, t7_var16));

T1Var1 t8_var1{"obj6_1", &obj6_1, 0, categ1_int8, 0};
T1Var2 t8_var2{"obj6_2", &obj6_2, 0, categ1_int8, 0};
T1Var3 t8_var3{"obj6_3", &obj6_3, 0, categ1_int8, 0};
T1Var4 t8_var4{"obj6_4", &obj6_4, 0, categ1_int8, 0};
T1Var5 t8_var5{"obj6_5", &obj6_5, 0, categ1_int8, 0};
T1Var6 t8_var6{"obj6_6", &obj6_6, 0, categ1_int8, 0};
T1Var7 t8_var7{"obj6_7", &obj6_7, 0, categ1_int8, 0};
T1Var8 t8_var8{"obj6_8", &obj6_8, 0, categ1_int8, 0};

T1Var9 t8_var9{"obj6_9", &obj6_9, 0, categ1_uint64, 0};
T1Var10 t8_var10{"obj6_10", &obj6_10, 0, categ1_uint64, 0};
T1Var11 t8_var11{"obj6_11", &obj6_11, 0, categ1_uint64, 0};
T1Var12 t8_var12{"obj6_12", &obj6_12, 0, categ1_uint64, 0};
T1Var13 t8_var13{"obj6_13", &obj6_13, 0, categ1_uint64, 0};
T1Var14 t8_var14{"obj6_14", &obj6_14, 0, categ1_uint64, 0};
T1Var15 t8_var15{"obj6_15", &obj6_15, 0, categ1_uint64, 0};
T1Var16 t8_var16{"obj6_16", &obj6_16, 0, categ1_uint64, 0};

REGISTER_TEST(t8, new TestIdRecErrorSystem<Case1, T1Var1, T1Var2, T1Var3, 
    T1Var4, T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16>(t8_var1, t8_var2, t8_var3,
        t8_var4, t8_var5, t8_var6, t8_var7, t8_var8, t8_var9, t8_var10,
        t8_var11, t8_var12, t8_var13, t8_var14, t8_var15, t8_var16));



int main()
{
    return RUN_TEST();
}

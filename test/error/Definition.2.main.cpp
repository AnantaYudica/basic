#include <cstdint>
#include <string>
#include <sstream>

typedef std::int16_t BasicErrorCharType;

#define BASIC_ERROR_CHAR_TYPE BasicErrorCharType

typedef std::uint32_t BasicErrorCodeValueType;

#define BASIC_ERROR_CODE_VALUE_TYPE BasicErrorCodeValueType

typedef std::uint32_t BasicErrorSystemCodeValueType;

#define BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE BasicErrorSystemCodeValueType

typedef std::uint32_t BasicErrorSystemConditionValueType;

#define BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE\
    BasicErrorSystemConditionValueType

typedef std::uint16_t BasicErrorSystemCategoryValueType;

#define BASIC_ERROR_SYSTEM_CATEG_VALUE_TYPE\
    BasicErrorSystemCategoryValueType

typedef std::char_traits<std::int16_t> BasicErrorOutputChartraitType;

#define BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE BasicErrorOutputChartraitType

typedef std::basic_iostream<char> BasicErrorOutputType;

#define BASIC_ERROR_OUTPUT_TYPE BasicErrorOutputType

struct RecordId
{};

typedef RecordId BasicErrorIdentificationRecordType;

#define BASIC_ERROR_IDENTIFICATION_RECORD_TYPE\
    BasicErrorIdentificationRecordType

std::basic_stringstream<char> strout;

#define BASIC_ERROR_OUTPUT strout

#include <vector>

typedef std::vector<char> BasicErrorMsgStrStorageType;

#define BASIC_ERROR_MSG_STR_STORAGE_TYPE BasicErrorMsgStrStorageType

constexpr int key = 14;

#define BASIC_ERROR_OUTPUT_OPERATOR(OUTPUT_NAME, ARG,...)\
    OUTPUT_NAME << " " << key << " " << ARG,##__VA_ARGS__

#include "Definition.test.h"

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<std::basic_iostream<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::basic_iostream<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};

BASIC_TEST_TYPE_NAME("std::vector<char>", std::vector<char>);
BASIC_TEST_TYPE_NAME("RecordId", RecordId);

BASIC_TEST_CONSTRUCT;

using Case1 = basic::test::type::
    Parameter<TestIsSameType>;
using Case2 = basic::test::type::
    Parameter<TestCallOutputOperator>;

typedef VariableIsSameType<basic::error::defn::type::Char, 
    BasicErrorCharType> T1Var1;

T1Var1 t1_var1{"basic::error::defn::type::Char", "BasicErrorCharType"};

REGISTER_TEST(t1, new TestDefinition<Case1, 
    typename T1Var1::BaseType>(t1_var1));

typedef VariableIsSameType<basic::error::defn::type::Output, 
    BasicErrorOutputType> T2Var1;

T2Var1 t2_var1{"basic::error::defn::type::Output", 
    "BasicErrorOutputType"};

REGISTER_TEST(t2, new TestDefinition<Case1,
    typename T2Var1::BaseType>(t2_var1));

typedef VariableIsSameType<basic::error::defn::type::code::Value,
    BasicErrorCodeValueType> T3Var1;

T3Var1 t3_var1{"basic::error::defn::type::code::Value", 
    "BasicErrorCodeValueType"};

REGISTER_TEST(t3, new TestDefinition<Case1,
    typename T3Var1::BaseType>(t3_var1));

typedef VariableIsSameType<basic::error::defn::type::id::Record,
    BasicErrorIdentificationRecordType> T4Var1;

T4Var1 t4_var1{"basic::error::defn::type::id::Record", 
    "BasicErrorIdentificationRecordType"};

REGISTER_TEST(t4, new TestDefinition<Case1,
    typename T4Var1::BaseType>(t4_var1));

typedef VariableIsSameType<basic::error::defn::type::msg::str::Storage,
    BasicErrorMsgStrStorageType> T5Var1;

T5Var1 t5_var1{"basic::error::defn::type::msg::str::Storage", 
    "BasicErrorMsgStrStorageType"};

REGISTER_TEST(t5, new TestDefinition<Case1,
    typename T5Var1::BaseType>(t5_var1));

typedef VariableIsSameType<basic::error::defn::type::output::Char,
    BasicErrorCharType> T6Var1;

T6Var1 t6_var1{"basic::error::defn::type::output::Char", 
    "BasicErrorCharType"};

REGISTER_TEST(t6, new TestDefinition<Case1,
    typename T6Var1::BaseType>(t6_var1));

typedef VariableIsSameType<basic::error::defn::type::output::CharTrait,
    BasicErrorOutputChartraitType> T7Var1;

T7Var1 t7_var1{"basic::error::defn::type::output::CharTrait", 
    "BasicErrorOutputChartraitType"};

REGISTER_TEST(t7, new TestDefinition<Case1,
    typename T7Var1::BaseType>(t7_var1));

typedef VariableIsSameType<basic::error::defn::type::system::categ::Value,
    BasicErrorSystemCategoryValueType> T8Var1;

T8Var1 t8_var1{"basic::error::defn::type::system::categ::Value", 
    "BasicErrorSystemCategoryValueType"};

REGISTER_TEST(t8, new TestDefinition<Case1,
    typename T8Var1::BaseType>(t8_var1));

typedef VariableIsSameType<basic::error::defn::type::system::code::Value,
    BasicErrorSystemCodeValueType> T9Var1;

T9Var1 t9_var1{"basic::error::defn::type::system::code::Value", 
    "BasicErrorSystemCodeValueType"};

REGISTER_TEST(t9, new TestDefinition<Case1,
    typename T9Var1::BaseType>(t9_var1));

typedef VariableIsSameType<basic::error::defn::type::system::condition::Value,
    BasicErrorSystemCodeValueType> T10Var1;

T10Var1 t10_var1{"basic::error::defn::type::system::condition::Value", 
    "BasicErrorSystemCodeValueType"};

REGISTER_TEST(t10, new TestDefinition<Case1,
    typename T10Var1::BaseType>(t10_var1));

typedef VariableCallOutputOperator<BASIC_ERROR_OUTPUT_TYPE, 
    std::stringstream , const char *> T11Var1;
    
typedef VariableCallOutputOperator<BASIC_ERROR_OUTPUT_TYPE, 
    std::stringstream , const char *, int> T11Var2;
    
typedef VariableCallOutputOperator<BASIC_ERROR_OUTPUT_TYPE, 
    std::stringstream , const char *, int, float> T11Var3;

const char str1[] = "str1";
int int1 = 4;
float float1 = 3.14;
std::stringstream strstream1;
std::stringstream strstream2;
std::stringstream strstream3;

bool Result1(std::stringstream & out)
{
    std::string l_str;
    int l_key1;
    out >> l_key1 >> l_str;
    return l_str.compare(str1) == 0 && l_key1 == key;
}

bool Result2(std::stringstream & out)
{
    std::string l_str;
    int l_int;
    int l_key1, l_key2;
    out >> l_key1 >> l_str >> l_key2 >> l_int;
    return l_str.compare(str1) == 0 && l_int == int1 &&
        l_key1 == key && l_key2 == key;
}

bool Result3(std::stringstream & out)
{
    std::string l_str;
    int l_int;
    float l_float;
    int l_key1, l_key2, l_key3;
    out >> l_key1 >> l_str >> l_key2 >> l_int;
    out >> l_key3 >> l_float;
    return l_str.compare(str1) == 0 && l_int == int1 && l_float == float1 &&
        l_key1 == key && l_key2 == key && l_key3 == key;
}

T11Var1 t11_var1{"basic::error::output::Operator", 
    basic::error::defn::func::output::Operator, "Result1", Result1, 
    strstream1, std::move(str1)};

T11Var2 t11_var2{"basic::error::output::Operator", 
    basic::error::defn::func::output::Operator, "Result2", Result2, strstream2,
    std::move(str1), std::move(int1)};

T11Var3 t11_var3{"basic::error::output::Operator", 
    basic::error::defn::func::output::Operator, "Result3", Result3, strstream3,
    std::move(str1), std::move(int1), std::move(float1)};

REGISTER_TEST(t11, new TestDefinition<Case2, 
    typename T11Var1::BaseType, typename T11Var2::BaseType,
    typename T11Var3::BaseType>(t11_var1, t11_var2, t11_var3));

int main()
{
    return RUN_TEST();
}

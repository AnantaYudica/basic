
#include "Definition.test.h"

BASIC_TEST_CONSTRUCT;

#include <typeinfo>
#include <utility>
#include <sstream>
#include <string>

using Case1 = basic::test::type::
    Parameter<TestIsSameType>;
using Case2 = basic::test::type::
    Parameter<TestCallOutputOperator>;

typedef VariableIsSameType<basic::error::defn::type::Char,
    BASIC_ERROR_CHAR_TYPE> T1Var1;

T1Var1 t1_var1{"basic::error::defn::type::Char", "BASIC_ERROR_CHAR_TYPE"};

REGISTER_TEST(t1, new TestDefinition<Case1, 
    typename T1Var1::BaseType>(t1_var1));

typedef VariableIsSameType<basic::error::defn::type::Output,
    BASIC_ERROR_OUTPUT_TYPE> T2Var1;

T2Var1 t2_var1{"basic::error::defn::type::Output", "BASIC_ERROR_OUTPUT_TYPE"};

REGISTER_TEST(t2, new TestDefinition<Case1,
    typename T2Var1::BaseType>(t2_var1));

typedef VariableIsSameType<basic::error::defn::type::code::Value,
    BASIC_ERROR_CODE_VALUE_TYPE> T3Var1;

T3Var1 t3_var1{"basic::error::defn::type::code::Value", 
    "BASIC_ERROR_CODE_VALUE_TYPE"};

REGISTER_TEST(t3, new TestDefinition<Case1,
    typename T3Var1::BaseType>(t3_var1));

typedef VariableIsSameType<basic::error::defn::type::id::Record,
    BASIC_ERROR_IDENTIFICATION_RECORD_TYPE> T4Var1;

T4Var1 t4_var1{"basic::error::defn::type::id::Record", 
    "BASIC_ERROR_IDENTIFICATION_RECORD_TYPE"};

REGISTER_TEST(t4, new TestDefinition<Case1,
    typename T4Var1::BaseType>(t4_var1));

typedef VariableIsSameType<basic::error::defn::type::msg::str::Storage,
    BASIC_ERROR_MSG_STR_STORAGE_TYPE> T5Var1;

T5Var1 t5_var1{"basic::error::defn::type::msg::str::Storage", 
    "BASIC_ERROR_MSG_STR_STORAGE_TYPE"};

REGISTER_TEST(t5, new TestDefinition<Case1,
    typename T5Var1::BaseType>(t5_var1));

typedef VariableIsSameType<basic::error::defn::type::output::Char,
    BASIC_ERROR_CHAR_TYPE> T6Var1;

T6Var1 t6_var1{"basic::error::defn::type::output::Char", 
    "BASIC_ERROR_CHAR_TYPE"};

REGISTER_TEST(t6, new TestDefinition<Case1,
    typename T6Var1::BaseType>(t6_var1));

typedef VariableIsSameType<basic::error::defn::type::output::CharTrait,
    BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE> T7Var1;

T7Var1 t7_var1{"basic::error::defn::type::output::CharTrait", 
    "BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE"};

REGISTER_TEST(t7, new TestDefinition<Case1,
    typename T7Var1::BaseType>(t7_var1));

typedef VariableIsSameType<basic::error::defn::type::sys::categ::Value,
    BASIC_ERROR_SYS_CATEG_VALUE_TYPE> T8Var1;

T8Var1 t8_var1{"basic::error::defn::type::sys::categ::Value", 
    "BASIC_ERROR_SYS_CATEG_VALUE_TYPE"};

REGISTER_TEST(t8, new TestDefinition<Case1,
    typename T8Var1::BaseType>(t8_var1));

typedef VariableIsSameType<basic::error::defn::type::sys::code::Value,
    BASIC_ERROR_SYS_CODE_VALUE_TYPE> T9Var1;

T9Var1 t9_var1{"basic::error::defn::type::sys::code::Value", 
    "BASIC_ERROR_SYS_CODE_VALUE_TYPE"};

REGISTER_TEST(t9, new TestDefinition<Case1,
    typename T9Var1::BaseType>(t9_var1));

typedef VariableIsSameType<basic::error::defn::type::sys::cond::Value,
    BASIC_ERROR_SYS_COND_VALUE_TYPE> T10Var1;

T10Var1 t10_var1{"basic::error::defn::type::sys::cond::Value", 
    "BASIC_ERROR_SYS_COND_VALUE_TYPE"};

REGISTER_TEST(t10, new TestDefinition<Case1,
    typename T10Var1::BaseType>(t10_var1));

typedef VariableCallOutputOperator<BASIC_ERROR_OUTPUT_TYPE, 
    std::stringstream, const char *> T11Var1;
    
typedef VariableCallOutputOperator<BASIC_ERROR_OUTPUT_TYPE, 
    std::stringstream, const char *, const char *, int> T11Var2;
    
typedef VariableCallOutputOperator<BASIC_ERROR_OUTPUT_TYPE, 
    std::stringstream, const char *, const char *, int, const char *, 
    float> T11Var3;

const char str1[] = "str1";
int int1 = 4;
float float1 = 3.14;
std::stringstream strstream1;
std::stringstream strstream2;
std::stringstream strstream3;

bool Result1(std::stringstream & out)
{
    return out.str().compare(str1) == 0;
}

bool Result2(std::stringstream & out)
{
    std::string l_str;
    int l_int;
    out >> l_str >> l_int;
    return l_str.compare(str1) == 0 && l_int == int1;
}

bool Result3(std::stringstream & out)
{
    std::string l_str;
    int l_int;
    float l_float;
    out >> l_str >> l_int >> l_float;
    return l_str.compare(str1) == 0 && l_int == int1 && l_float == float1;
}

T11Var1 t11_var1{"basic::error::output::Operator", 
    basic::error::defn::func::output::Operator, "Result1", Result1, 
    strstream1, std::move(str1)};

T11Var2 t11_var2{"basic::error::output::Operator", 
    basic::error::defn::func::output::Operator, "Result2", Result2, strstream2,
    std::move(str1), std::move(" "), std::move(int1)};

T11Var3 t11_var3{"basic::error::output::Operator", 
    basic::error::defn::func::output::Operator, "Result3", Result3, strstream3,
    std::move(str1), std::move(" "), std::move(int1), 
    std::move(" "), std::move(float1)};

REGISTER_TEST(t11, new TestDefinition<Case2, 
    typename T11Var1::BaseType, typename T11Var2::BaseType,
    typename T11Var3::BaseType>(t11_var1, t11_var2, t11_var3));

int main()
{
    return RUN_TEST();
}


#include "Definition.test.h"

BASIC_TEST_CONSTRUCT;

#include <typeinfo>
#include <utility>

typedef VariableIsSameType<basic::error::defn::type::Char,
    BASIC_ERROR_CHAR_TYPE> Var1Type;

Var1Type var1{"basic::error::defn::type::Char", "BASIC_ERROR_CHAR_TYPE"};

REGISTER_TEST(t1, new TestDefinition<Var1Type>(var1));

typedef VariableIsSameType<basic::error::defn::type::Output,
    BASIC_ERROR_OUTPUT_TYPE> Var2Type;

Var2Type var2{"basic::error::defn::type::Char", "BASIC_ERROR_OUTPUT_TYPE"};

REGISTER_TEST(t2, new TestDefinition<Var2Type>(var2));

typedef VariableIsSameType<basic::error::defn::type::code::Value,
    BASIC_ERROR_CODE_VALUE_TYPE> Var3Type;

Var3Type var3{"basic::error::defn::type::code::Value", 
    "BASIC_ERROR_CODE_VALUE_TYPE"};

REGISTER_TEST(t3, new TestDefinition<Var3Type>(var3));

typedef VariableIsSameType<basic::error::defn::type::id::Record,
    BASIC_ERROR_IDENTIFICATION_RECORD_TYPE> Var4Type;

Var4Type var4{"basic::error::defn::type::id::Record", 
    "BASIC_ERROR_IDENTIFICATION_RECORD_TYPE"};

REGISTER_TEST(t4, new TestDefinition<Var4Type>(var4));

typedef VariableIsSameType<basic::error::defn::type::msg::str::Storage,
    BASIC_ERROR_MSG_STR_STORAGE_TYPE> Var5Type;

Var5Type var5{"basic::error::defn::type::msg::str::Storage", 
    "BASIC_ERROR_MSG_STR_STORAGE_TYPE"};

REGISTER_TEST(t5, new TestDefinition<Var5Type>(var5));

typedef VariableIsSameType<basic::error::defn::type::output::Char,
    BASIC_ERROR_CHAR_TYPE> Var6Type;

Var6Type var6{"basic::error::defn::type::output::Char", 
    "BASIC_ERROR_CHAR_TYPE"};

REGISTER_TEST(t6, new TestDefinition<Var6Type>(var6));

typedef VariableIsSameType<basic::error::defn::type::output::CharTrait,
    BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE> Var7Type;

Var7Type var7{"basic::error::defn::type::output::CharTrait", 
    "BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE"};

REGISTER_TEST(t7, new TestDefinition<Var7Type>(var7));

typedef VariableIsSameType<basic::error::defn::type::system::category::Value,
    BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE> Var8Type;

Var8Type var8{"basic::error::defn::type::system::category::Value", 
    "BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE"};

REGISTER_TEST(t8, new TestDefinition<Var8Type>(var8));

typedef VariableIsSameType<basic::error::defn::type::system::code::Value,
    BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE> Var9Type;

Var9Type var9{"basic::error::defn::type::system::code::Value", 
    "BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE"};

REGISTER_TEST(t9, new TestDefinition<Var9Type>(var9));

typedef VariableIsSameType<basic::error::defn::type::system::condition::Value,
    BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE> Var10Type;

Var10Type var10{"basic::error::defn::type::system::condition::Value", 
    "BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE"};

REGISTER_TEST(t10, new TestDefinition<Var10Type>(var10));

int main()
{
    RUN_TEST();
}

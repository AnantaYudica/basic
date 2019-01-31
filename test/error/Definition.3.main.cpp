#define USING_BASIC_ERROR_MSG_STR_STORAGE_AUTOMATIC

#include "Definition.test.h"

BASIC_TEST_CONSTRUCT;

using Case1 = basic::test::type::
    Parameter<TestIsSameType, TestSizeofAType>;

BASIC_TEST_TYPE_NAME("char[N]",
    char[BASIC_ERROR_MSG_STR_STORAGE_AUTOMATIC_SIZE]);

typedef VariableIsSameAndSizeofAType<basic::error::defn::type::
    Char[BASIC_ERROR_MSG_STR_STORAGE_AUTOMATIC_SIZE], 
    BASIC_ERROR_MSG_STR_STORAGE_TYPE> T1Var1;

T1Var1 t1_var1{"basic::error::defn::type::Char[N]", 
    "BASIC_ERROR_MSG_STR_STORAGE_TYPE", 
    (sizeof(basic::error::defn::type::Char) * 
    BASIC_ERROR_MSG_STR_STORAGE_AUTOMATIC_SIZE) };

REGISTER_TEST(t1, new TestDefinition<Case1, 
    typename T1Var1::BaseType>(t1_var1));

int main()
{
    return RUN_TEST();
}
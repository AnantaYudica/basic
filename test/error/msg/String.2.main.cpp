#define USING_BASIC_ERROR_MSG_STR_STORAGE_DYNAMIC

#include <cstddef>
#include <string>
#include <utility>

#include "String.test.h"

BASIC_TEST_CONSTRUCT;

using namespace basic::error::msg::str;

typedef basic::test::type::Parameter<TestAliasCharType, TestAliasStorageType,
    TestValueValue, TestCastToBool, TestBasiOfIntefaceExit, TestCleanUp> Case1;
typedef basic::test::type::Parameter<TestCopyAssignment, TestValueValue,
    TestCastToBool> Case2;
typedef basic::test::type::Parameter<TestMoveAssignment, TestValueValue,
    TestCastToBool> Case3;

typedef VariableTestMsgString T1Var1;

const char * char_val = "test2";
const std::string string_val = "test3";

basic::error::msg::String obj1_1{};
basic::error::msg::String obj1_2{"test"};
basic::error::msg::String obj1_3{char_val};
basic::error::msg::String obj1_4{string_val};

T1Var1 t1_var1{"obj1_1", &obj1_1, "", false, 1, false, "", nullptr};
T1Var1 t1_var2{"obj1_2", &obj1_2, "test", true, 1, false, "", nullptr};
T1Var1 t1_var3{"obj1_3", &obj1_3, "test2", true, 1, false, "", nullptr};
T1Var1 t1_var4{"obj1_4", &obj1_4, "test3", true, 1, false, "", nullptr};

REGISTER_TEST(t1, new TestMsgString<Case1, T1Var1, T1Var1, T1Var1,
    T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4));

basic::error::msg::String obj2_1{obj1_1};
basic::error::msg::String obj2_2{obj1_2};
basic::error::msg::String obj2_3{obj1_3};
basic::error::msg::String obj2_4{obj1_4};

T1Var1 t2_var1{"obj2_1", &obj2_1, "", false, 1, false, "", nullptr};
T1Var1 t2_var2{"obj2_2", &obj2_2, "test", true, 1, false, "", nullptr};
T1Var1 t2_var3{"obj2_3", &obj2_3, "test2", true, 1, false, "", nullptr};
T1Var1 t2_var4{"obj2_4", &obj2_4, "test3", true, 1, false, "", nullptr};

REGISTER_TEST(t2, new TestMsgString<Case1, T1Var1, T1Var1, T1Var1,
    T1Var1>(t2_var1, t2_var2, t2_var3, t2_var4));

basic::error::msg::String obj2_1_c{obj2_1};
basic::error::msg::String obj2_2_c{obj2_2};
basic::error::msg::String obj2_3_c{obj2_3};
basic::error::msg::String obj2_4_c{obj2_4};

basic::error::msg::String obj3_1{std::move(obj2_1_c)};
basic::error::msg::String obj3_2{std::move(obj2_2_c)};
basic::error::msg::String obj3_3{std::move(obj2_3_c)};
basic::error::msg::String obj3_4{std::move(obj2_4_c)};

T1Var1 t3_var1{"obj3_1", &obj3_1, "", false, 1, false, "", nullptr};
T1Var1 t3_var2{"obj3_2", &obj3_2, "test", true, 1, false, "", nullptr};
T1Var1 t3_var3{"obj3_3", &obj3_3, "test2", true, 1, false, "", nullptr};
T1Var1 t3_var4{"obj3_4", &obj3_4, "test3", true, 1, false, "", nullptr};

REGISTER_TEST(t3, new TestMsgString<Case1, T1Var1, T1Var1, T1Var1,
    T1Var1>(t3_var1, t3_var2, t3_var3, t3_var4));

T1Var1 t4_var1{"obj2_1_c", &obj2_1_c, "", false, 1, false, "", nullptr};
T1Var1 t4_var2{"obj2_2_c", &obj2_2_c, "", false, 1, false, "", nullptr};
T1Var1 t4_var3{"obj2_3_c", &obj2_3_c, "", false, 1, false, "", nullptr};
T1Var1 t4_var4{"obj2_4_c", &obj2_4_c, "", false, 1, false, "", nullptr};

REGISTER_TEST(t4, new TestMsgString<Case1, T1Var1, T1Var1, T1Var1,
    T1Var1>(t4_var1, t4_var2, t4_var3, t4_var4));

basic::error::msg::String obj5_1{};
basic::error::msg::String obj5_1_1{"test"};

T1Var1 t5_var1{"obj5_1", &obj5_1, "test", true, 1, true, "obj5_1_1",
     &obj5_1_1};

REGISTER_TEST(t5, new TestMsgString<Case2, T1Var1>(t5_var1));

basic::error::msg::String obj6_1{};
basic::error::msg::String obj6_1_1{"test"};

T1Var1 t6_var1{"obj6_1", &obj6_1, "test", true, 1, true, "obj6_1_1",
    &obj6_1_1};

REGISTER_TEST(t6, new TestMsgString<Case3, T1Var1>(t6_var1));

T1Var1 t7_var1{"obj6_1_1", &obj6_1_1, "", false, 1, false, "", nullptr};

REGISTER_TEST(t7, new TestMsgString<Case1, T1Var1>(t7_var1));

int main()
{
    return RUN_TEST();
}
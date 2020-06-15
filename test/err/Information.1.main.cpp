#undef USING_BASIC_ERR_FILE_AND_LINE

#include "Information.test.h"

#include "err/Information.h"

#include <utility>

typedef basic::test::type::Parameter<
    TestBaseOfIntfOutput,
    TestAliasOutputType,
    TestValueIdentification,
    TestValueFile,
    TestValueLine,
    TestValueOutput> Case1;

typedef VariableTestInformation T1Var1;

basic::err::Identification id1{};
basic::err::Identification id2{4};
basic::err::Information info1{};
basic::err::Information info2{id2};
basic::err::Information info3{info2};
basic::err::Information info4{info3};
basic::err::Information info5{std::move(info4)};

const char * file1 = "";
std::size_t line1 = -1;
const char * out1 = "";
const char * out2 = "id 0x000004";

T1Var1 t1_var1{&info1, &id1, file1, line1, out1};
T1Var1 t1_var2{&info2, &id2, file1, line1, out2};
T1Var1 t1_var3{&info3, &id2, file1, line1, out2};
T1Var1 t1_var4{&info4, &id2, file1, line1, out2};
T1Var1 t1_var5{&info5, &id2, file1, line1, out2};

REGISTER_TEST(t1, new TestInformation<Case1, T1Var1, T1Var1, T1Var1, T1Var1,
    T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

int main()
{
    return RUN_TEST();
}

#define USING_BASIC_ERR_FILE_AND_LINE

#include "Information.test.h"

#include "err/Information.h"

typedef basic::test::type::Parameter<
    TestBaseOfIntfOutput,
    TestAliasOutputType,
    TestValueIdentification,
    TestValueFile,
    TestValueLine,
    TestValueOutput> Case1;

typedef VariableTestInformation T1Var1;

#define FILE_NAME_STR "file_name"
#define FILE_LINE 4
#define FILE_LINE_STR "4"

const char * file_name = FILE_NAME_STR;
std::size_t file_line = FILE_LINE;

basic::err::Identification id1{};
basic::err::Identification id2{4};
basic::err::Information info1{};
basic::err::Information info2{id2, file_name, file_line};
basic::err::Information info3{info2};
basic::err::Information info4{info3};
basic::err::Information info5{std::move(info4)};

const char * file1 = nullptr;
const char * file2 = FILE_NAME_STR;
std::size_t line1 = -1;
std::size_t line2 = FILE_LINE;
const char * out1 = "";
char out2[] = "id 0x000004 file " FILE_NAME_STR " line " FILE_LINE_STR;

T1Var1 t1_var1{&info1, &id1, file1, line1, out1};
T1Var1 t1_var2{&info2, &id2, file2, line2, out2};
T1Var1 t1_var3{&info3, &id2, file2, line2, out2};
T1Var1 t1_var4{&info4, &id2, file2, line2, out2};
T1Var1 t1_var5{&info5, &id2, file2, line2, out2};

REGISTER_TEST(t1, new TestInformation<Case1, T1Var1, T1Var1, T1Var1, T1Var1,
    T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

int main()
{
    return RUN_TEST();
}

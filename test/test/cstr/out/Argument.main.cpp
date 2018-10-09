#include "test/cstr/out/Argument.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>

#define VALUE1_CSTR "test1"
#define VALUE2_CSTR "test2"

int main()
{
    basic::test::out::Argument<
        basic::test::CString<char>> out_arg1;
    basic::test::out::Argument<
        basic::test::CString<const char>> out_arg2;

    basic::test::CString<char> cstr1 = VALUE1_CSTR;
    printf("out_arg1.Value(cstr1) : %s\n", out_arg1.Value(cstr1));
    assert(strcmp(VALUE1_CSTR, out_arg1.Value(cstr1)) == 0);

    const auto cstr2 = cstr1;
    printf("out_arg1.Value(cstr2) : %s\n", out_arg1.Value(cstr2));
    assert(strcmp(VALUE1_CSTR, out_arg1.Value(cstr2)) == 0);

    auto cpy1_cstr1 = cstr1;
    auto cpy2_cstr1 = cstr1;
    printf("out_arg1.Value(std::move(cpy1_cstr1)) : %s\n", 
            out_arg1.Value(std::move(cpy1_cstr1)));
    assert(strcmp(VALUE1_CSTR, out_arg1.Value(cpy2_cstr1)) == 0);

    basic::test::CString<const char> cstr3 = VALUE2_CSTR;
    printf("out_arg2.Value(cstr3) : %s\n", out_arg2.Value(cstr3));
    assert(strcmp(VALUE2_CSTR, out_arg2.Value(cstr3)) == 0);

    const auto cstr4 = cstr3;
    printf("out_arg2.Value(cstr4) : %s\n", out_arg2.Value(cstr4));
    assert(strcmp(VALUE2_CSTR, out_arg2.Value(cstr4)) == 0);

    auto cpy1_cstr3 = cstr3;
    auto cpy2_cstr3 = cstr3;
    printf("out_arg2.Value(std::move(cpy1_cstr3)) : %s\n",
        out_arg2.Value(std::move(cpy1_cstr3)));
    assert(strcmp(VALUE2_CSTR, out_arg2.Value(cpy2_cstr3)) == 0);
}

#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/cstr/Format.h"

#include <cstdio>

int main()
{
    auto ch1 = basic::test::cstr::Format(10, "%d", 1234);
    printf("%s\n", *ch1);
    auto ch2 = basic::test::cstr::Format(2, "%d", 1234);
    printf("%s\n", *ch2);
    auto ch3 = basic::test::cstr::Format(0, "%d", 1234);
    printf("%s\n", *ch3);
    int i = 14;
    auto ch4 = basic::test::cstr::Format(10, "%s = %d", "int i", i);
    printf("%s\n", *ch4);
    auto ch5 = basic::test::cstr::Format(5, "%s = %d");
    printf("%s\n", *ch5);
}
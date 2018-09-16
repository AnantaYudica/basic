#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/CString.h"

#include <cstdio>

int main()
{
    basic::test::CString<char> ch1;
    ch1 = "test0";
    printf("%s\n", *ch1);
    
    basic::test::CString<char> ch2("test1");
    printf("%s\n", *ch2);

    char* cstr1 = new char[6];
    cstr1[0] = 't';
    cstr1[1] = 'e';
    cstr1[2] = 's';
    cstr1[3] = 't';
    cstr1[4] = '2';
    cstr1[5] = '\0';
    
    basic::test::CString<char> ch3(std::move(cstr1), 6);
    printf("%s\n", *ch3);

    basic::test::CString<char> ch4(ch1);
    printf("%s\n", *ch4);

    basic::test::CString<char> ch5(static_cast<basic::test::CString<const char>>(ch2));
    printf("%s\n", *ch5);

    basic::test::CString<char> ch6(std::move(ch3));
    printf("%s\n", *ch6);

    basic::test::CString<char> ch7;

    ch7 = static_cast<basic::test::CString<const char>>(ch4);
    printf("%s\n", *ch7);

    ch7 = ch5;
    printf("%s\n", *ch7);

    ch7 = std::move(ch6);
    printf("%s\n", *ch7);

    const basic::test::CString<char> ch8 = ch4;
    for (std::size_t i = 0; i < ch8.Size(); i++)
    {
        if (i != 0)
            printf(", %c", ch8[i]);
        else
            printf("%c", ch8[i]);
    }
    printf("\n");

    basic::test::CString<char> ch9 = ch5;
    for (std::size_t i = 0; i < ch9.Size(); i++)
    {
        if (i != 0)
            printf(", %c", ch9[i]);
        else
            printf("%c", ch9[i]);
    }
    printf("\n");

    basic::test::CString<const char> ch10("const test1");
    printf("%s\n", *ch10);

    const char * cstr2 = "const test2";
    basic::test::CString<const char> ch11(cstr2, 12);
    printf("%s\n", *ch11);

    basic::test::CString<const char> ch12(ch9);
    printf("%s\n", *ch12);

    basic::test::CString<const char> ch13(ch10);
    printf("%s\n", *ch13);

    const basic::test::CString<const char> ch14 = ch11;
    for (std::size_t i = 0; i < ch14.Size(); i++)
    {
        if (i != 0)
            printf(", %c", ch14[i]);
        else
            printf("%c", ch14[i]);
    }
    printf("\n");


}

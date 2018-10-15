#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/CString.h"

#include <cstdio>
#include <cassert>
#include <cstring>

const char Test0_cstr[] = "test0";
const char Test1_cstr[] = "test1";
const char Test2_cstr[] = "test2";
const char ConstTest0_cstr[] = "const test0";
const char ConstTest1_cstr[] = "const test1";

int main()
{
    basic::test::CString<char> cstring1;
    cstring1 = Test0_cstr;
    printf("%s\n", *cstring1);
    assert(std::strcmp(Test0_cstr, *cstring1) == 0);
    
    basic::test::CString<char> cstring2(Test1_cstr);
    printf("%s\n", *cstring2);
    assert(std::strcmp(Test1_cstr, *cstring2) == 0);

    char* cstr1 = new char[sizeof(Test2_cstr)];
    memcpy(cstr1, Test2_cstr, sizeof(Test2_cstr));
    basic::test::CString<char> cstring3(std::move(cstr1), sizeof(Test2_cstr));
    printf("%s\n", *cstring3);
    assert(std::strcmp(Test2_cstr, *cstring3) == 0);

    basic::test::CString<char> cstring4(cstring1);
    printf("%s\n", *cstring4);
    assert(std::strcmp(*cstring1, *cstring4) == 0);

    basic::test::CString<char> cstring5(static_cast<basic::test::
        CString<const char>>(cstring2));
    printf("%s\n", *cstring5);
    assert(std::strcmp(*cstring2, *cstring5) == 0);

    basic::test::CString<char> cstring6(std::move(cstring3));
    printf("%s\n", *cstring6);
    assert(*cstring3 == NULL);
    assert(std::strcmp(Test2_cstr, *cstring6) == 0);

    basic::test::CString<char> cstring7;
    cstring7 = static_cast<basic::test::CString<const char>>(cstring4);
    printf("%s\n", *cstring7);
    assert(std::strcmp(*cstring4, *cstring7) == 0);

    cstring7 = cstring5;
    printf("%s\n", *cstring7);
    assert(std::strcmp(*cstring5, *cstring7) == 0);

    cstring7 = std::move(cstring6);
    printf("%s\n", *cstring7);
    assert(*cstring6 == NULL);
    assert(std::strcmp(Test2_cstr, *cstring7) == 0);

    const basic::test::CString<char> cstring8 = cstring4;
    for (std::size_t i = 0; i < cstring8.Size(); i++)
    {
        assert(cstring8[i] == cstring4[i]);
        if (i != 0)
            printf(", %c", cstring8[i]);
        else
            printf("%c", cstring8[i]);
    }
    printf("\n");

    basic::test::CString<char> cstring9 = cstring5;
    for (std::size_t i = 0; i < cstring9.Size(); i++)
    {
        assert(cstring9[i] == cstring5[i]);
        if (i != 0)
            printf(", %c", cstring9[i]);
        else
            printf("%c", cstring9[i]);
    }
    printf("\n");

    basic::test::CString<const char> cstring10(ConstTest0_cstr);
    printf("%s\n", *cstring10);
    assert(std::strcmp(ConstTest0_cstr, *cstring10) == 0);

    const char * cstr2 = ConstTest1_cstr;
    basic::test::CString<const char> cstring11(cstr2, sizeof(ConstTest1_cstr));
    printf("%s\n", *cstring11);
    assert(std::strcmp(ConstTest1_cstr, *cstring11) == 0);

    basic::test::CString<const char> cstring12(cstring9);
    printf("%s\n", *cstring12);
    assert(std::strcmp(*cstring9, *cstring12) == 0);

    basic::test::CString<const char> cstring13(cstring10);
    printf("%s\n", *cstring13);
    assert(std::strcmp(*cstring10, *cstring13) == 0);

    const basic::test::CString<const char> cstring14 = cstring11;
    for (std::size_t i = 0; i < cstring14.Size(); i++)
    {
        assert(cstring14[i] == cstring11[i]);
        if (i != 0)
            printf(", %c", cstring14[i]);
        else
            printf("%c", cstring14[i]);
    }
    printf("\n");

}

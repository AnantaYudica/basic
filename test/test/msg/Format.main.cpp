#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/msg/Format.h"

#include <cstdio>
#include <cassert>
#include <cstring>

char _true_cstr[] = "true";
char _false_cstr[] = "false";

#define PRINT_FORMAT(__VAR_NAME__)\
printf("name : %s, size : %zd, cstr : \"%s\", IsNull : %s, IsEmpty : %s\n",\
    #__VAR_NAME__, __VAR_NAME__.Size(), *__VAR_NAME__,\
    (!__VAR_NAME__ ? _true_cstr : _false_cstr),\
    (__VAR_NAME__.IsEmpty() ? _true_cstr : _false_cstr))

#define EMPTY_CSTR ""

#define VALUE1_INT 4
#define VALUE1_CSTR "4"

#define FORMAT_CSTR_CSTR "%s"
#define FORMAT_INT_CSTR "%d"

#define FORMAT_CSTR "format"
#define COLON_CSTR ":"
#define SPACE_CSTR " "
#define TYPE_CSTR "Type"
#define OPEN_POINTY_CSTR "<"
#define CLOSE_POINTY_CSTR ">"
#define OPEN_ROUND_CSTR "("
#define CLOSE_ROUND_CSTR ")"
#define TEMPLATE_CSTR "template"
#define FOO1_CSTR "Foo1"
#define TEST1_CSTR "test1"
#define TEST2_CSTR "test2"
#define TEST_CSTR "test"
#define CSTR_CSTR "cstr"
#define CONST_CSTR "const"

int main()
{
    basic::test::msg::Format<char> f1;
    PRINT_FORMAT(f1);
    assert(f1.Size() == 0);
    assert(strcmp(*f1, EMPTY_CSTR) == 0);
    assert((bool)f1 == false);
    assert(f1.IsEmpty() == false);

    basic::test::msg::Format<char> f1_1(EMPTY_CSTR);
    PRINT_FORMAT(f1_1);
    assert(f1_1.Size() == 1);
    assert(strcmp(*f1_1, EMPTY_CSTR) == 0);
    assert((bool)f1_1 == true);
    assert(f1_1.IsEmpty() == true);

    char format1[] = FORMAT_CSTR SPACE_CSTR COLON_CSTR SPACE_CSTR
        FORMAT_CSTR_CSTR;
    basic::test::msg::Format<char> f2(format1);
    PRINT_FORMAT(f2);
    assert(f2.Size() == sizeof(format1));
    assert(strcmp(*f2, format1) == 0);
    assert((bool)f2 == true);
    assert(f2.IsEmpty() == false);

    const char * format2_arg1 = FORMAT_CSTR_CSTR COLON_CSTR COLON_CSTR 
        FORMAT_CSTR_CSTR;
    char format2[] = FORMAT_CSTR SPACE_CSTR COLON_CSTR SPACE_CSTR
        FORMAT_CSTR_CSTR COLON_CSTR COLON_CSTR FORMAT_CSTR_CSTR;
    basic::test::msg::Format<char> f3(f2, f2.Size() + 4, format2_arg1);
    PRINT_FORMAT(f3);
    assert(f3.Size() == sizeof(format2));
    assert(strcmp(*f3, format2) == 0);
    assert((bool)f3 == true);
    assert(f3.IsEmpty() == false);

    const char * format3_arg1 = TYPE_CSTR OPEN_POINTY_CSTR FORMAT_CSTR_CSTR
        CLOSE_POINTY_CSTR;
    const char * format3_arg2 = TEMPLATE_CSTR SPACE_CSTR FOO1_CSTR
        OPEN_POINTY_CSTR FORMAT_CSTR_CSTR CLOSE_POINTY_CSTR OPEN_ROUND_CSTR
        FORMAT_CSTR_CSTR CLOSE_ROUND_CSTR;
    char format3[] = FORMAT_CSTR SPACE_CSTR COLON_CSTR SPACE_CSTR
        TYPE_CSTR OPEN_POINTY_CSTR FORMAT_CSTR_CSTR CLOSE_POINTY_CSTR 
        COLON_CSTR COLON_CSTR TEMPLATE_CSTR SPACE_CSTR FOO1_CSTR
        OPEN_POINTY_CSTR FORMAT_CSTR_CSTR CLOSE_POINTY_CSTR OPEN_ROUND_CSTR
        FORMAT_CSTR_CSTR CLOSE_ROUND_CSTR;
    basic::test::msg::Format<char> f4(f3, f3.Size() + 25, 
        format3_arg1, format3_arg2);
    PRINT_FORMAT(f4);
    assert(f4.Size() == sizeof(format3));
    assert(strcmp(*f4, format3) == 0);
    assert((bool)f4 == true);
    assert(f4.IsEmpty() == false);

    char format4[] = FORMAT_CSTR SPACE_CSTR COLON_CSTR 
        SPACE_CSTR FORMAT_INT_CSTR;
    basic::test::msg::Format<char> f5(format4);
    PRINT_FORMAT(f5);
    assert(f5.Size() == sizeof(format4));
    assert(strcmp(*f5, format4) == 0);
    assert((bool)f5 == true);
    assert(f5.IsEmpty() == false);
    
    char format5[] = FORMAT_CSTR SPACE_CSTR COLON_CSTR
        SPACE_CSTR VALUE1_CSTR;
    basic::test::msg::Format<char> f6(f5, f5.Size() + 10, 4);
    PRINT_FORMAT(f6);
    assert(f6.Size() == sizeof(format4) + 10);
    assert(strcmp(*f6, format5) == 0);
    assert((bool)f6 == true);
    assert(f6.IsEmpty() == false);

    basic::test::msg::Format<char> f7(f4);
    PRINT_FORMAT(f7);
    assert(f7.Size() == sizeof(format3));
    assert(strcmp(*f7, format3) == 0);
    assert((bool)f7 == true);
    assert(f7.IsEmpty() == false);

    basic::test::msg::Format<char> f8(std::move(f7));
    PRINT_FORMAT(f8);
    assert(f8.Size() == sizeof(format3));
    assert(strcmp(*f8, format3) == 0);
    assert((bool)f8 == true);
    assert(f8.IsEmpty() == false);
    PRINT_FORMAT(f7);
    assert(f7.Size() == 0);
    assert(strcmp(*f7, EMPTY_CSTR) == 0);
    assert((bool)f7 == false);
    assert(f7.IsEmpty() == false);

    basic::test::msg::Format<char> f9(TEST1_CSTR);
    PRINT_FORMAT(f9);
    assert(f9.Size() == sizeof(TEST1_CSTR));
    assert(strcmp(*f9, TEST1_CSTR) == 0);
    assert((bool)f8 == true);
    assert(f9.IsEmpty() == false);
    f9 = f4;
    PRINT_FORMAT(f9); 
    assert(f9.Size() == sizeof(format3));
    assert(strcmp(*f9, format3) == 0);
    assert((bool)f9 == true);
    assert(f9.IsEmpty() == false);

    basic::test::msg::Format<char> f10;
    f10 = std::move(f9);
    PRINT_FORMAT(f10);
    assert(f10.Size() == sizeof(format3));
    assert(strcmp(*f10, format3) == 0);
    assert((bool)f10 == true);
    assert(f10.IsEmpty() == false);
    PRINT_FORMAT(f9);
    assert(f9.Size() == 0);
    assert(strcmp(*f9, EMPTY_CSTR) == 0);
    assert((bool)f9 == false);
    assert(f9.IsEmpty() == false);

    basic::test::msg::Format<char> f11(TEST2_CSTR, 14);
    PRINT_FORMAT(f11);
    assert(f11.Size() == 14);
    assert(strcmp(*f11, TEST2_CSTR) == 0);
    assert((bool)f11 == true);
    assert(f11.IsEmpty() == false);

    char format6[] = TEST_CSTR SPACE_CSTR CSTR_CSTR;
    basic::test::msg::Format<char> f12(basic::test::
        CString<char>(std::move(format6)));
    PRINT_FORMAT(f12);
    assert(f12.Size() == sizeof(format6));
    assert(strcmp(*f12, format6) == 0);
    assert((bool)f12 == true);
    assert(f12.IsEmpty() == false);

    char format7[] = TEST_CSTR SPACE_CSTR CSTR_CSTR SPACE_CSTR CONST_CSTR;
    basic::test::msg::Format<char> f13(basic::test::
        CString<const char>(std::move(format7)));
    PRINT_FORMAT(f13);
    assert(f13.Size() == sizeof(format7));
    assert(strcmp(*f13, format7) == 0);
    assert((bool)f13 == true);
    assert(f13.IsEmpty() == false);

    char format8[] = TEST_CSTR SPACE_CSTR CSTR_CSTR;
    basic::test::msg::Format<char> f14(std::move(basic::test::
        CString<char>(std::move(format8))));
    PRINT_FORMAT(f14);
    assert(f14.Size() == sizeof(format8));
    assert(strcmp(*f14, format8) == 0);
    assert((bool)f14 == true);
    assert(f14.IsEmpty() == false);

    basic::test::msg::Format<char> f15(std::move(basic::test::
        CString<const char>(std::move(format8))));
    PRINT_FORMAT(f15);
    assert(f15.Size() == sizeof(format8));
    assert(strcmp(*f15, format8) == 0);
    assert((bool)f15 == true);
    assert(f15.IsEmpty() == false);

}

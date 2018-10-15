#include "test/out/Argument.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>

#define BUFFER_SIZE 1024

#define VALUE1_INT 4
#define VALUE1_CHAR '4'
#define VALUE1_CSTR "4"
#define VALUE2_INT 14
#define VALUE2_SHORT short(14)
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_INT 114
#define VALUE4_LONG 114l
#define VALUE4_CSTR "114"
#define VALUE5_LONGLONG 14441ll
#define VALUE5_CSTR "14441"
#define VALUE6_FLOAT 3.14f
#define VALUE6_CSTR "3.14"
#define VALUE7_DOUBLE 3.1428
#define VALUE7_CSTR "3.1428"
#define VALUE8_LONGDOUBLE 3.142857L
#define VALUE8_CSTR "3.142857"
#define TEST_CSTR "test"

#define FORMAT_CHAR_CSTR "%c"
#define FORMAT_SHORT_CSTR "%hd"
#define FORMAT_INT_CSTR "%d"
#define FORMAT_LONG_CSTR "%ld"
#define FORMAT_LONGLONG_CSTR "%lld"

#define FORMAT_U_CHAR_CSTR "%c"
#define FORMAT_U_SHORT_CSTR "%hu"
#define FORMAT_U_INT_CSTR "%u"
#define FORMAT_U_LONG_CSTR "%lu"
#define FORMAT_U_LONGLONG_CSTR "%llu"

#define FORMAT_FLOAT_CSTR "%.2f"
#define FORMAT_DOUBLE_CSTR "%.4f"
#define FORMAT_LONGDOUBLE_CSTR "%.6Lf"

#define FORMAT_CSTR_CSTR "%s"
#define FORMAT_PTR_CSTR "%p"

int main()
{
    char * buffer = new char[BUFFER_SIZE];
    std::size_t buff_size = BUFFER_SIZE;

    char c = VALUE1_CHAR;
    printf("char c = " FORMAT_CHAR_CSTR "\n", c);
    snprintf(buffer, buff_size, FORMAT_CHAR_CSTR,
        basic::test::out::Argument<char>::Value(c));
    assert(strcmp(VALUE1_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_CHAR_CSTR,
        basic::test::out::Argument<char>::Value(VALUE1_CHAR));
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    short s = VALUE2_SHORT;
    printf("short s = " FORMAT_SHORT_CSTR "\n", s);
    snprintf(buffer, buff_size, FORMAT_SHORT_CSTR,
        basic::test::out::Argument<short>::Value(s));
    assert(strcmp(VALUE2_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_SHORT_CSTR,
        basic::test::out::Argument<short>::Value(VALUE2_SHORT));
    assert(strcmp(VALUE2_CSTR, buffer) == 0);

    int i = VALUE3_INT;
    printf("int i = " FORMAT_INT_CSTR "\n", i);
    snprintf(buffer, buff_size, FORMAT_INT_CSTR,
        basic::test::out::Argument<int>::Value(i));
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_INT_CSTR,
        basic::test::out::Argument<int>::Value(VALUE3_INT));
    assert(strcmp(VALUE3_CSTR, buffer) == 0);

    long l = VALUE4_LONG;
    printf("long l = " FORMAT_LONG_CSTR "\n", l);
    snprintf(buffer, buff_size, FORMAT_LONG_CSTR,
        basic::test::out::Argument<long>::Value(l));
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_LONG_CSTR,
        basic::test::out::Argument<long>::Value(VALUE4_LONG));
    assert(strcmp(VALUE4_CSTR, buffer) == 0);

    long long ll = VALUE5_LONGLONG;
    printf("long long ll = " FORMAT_LONGLONG_CSTR "\n", ll);
    snprintf(buffer, buff_size, FORMAT_LONGLONG_CSTR,
        basic::test::out::Argument<long long>::Value(ll));
    assert(strcmp(VALUE5_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_LONGLONG_CSTR,
        basic::test::out::Argument<long long>::Value(VALUE5_LONGLONG));
    assert(strcmp(VALUE5_CSTR, buffer) == 0);

    unsigned char uc = VALUE1_CHAR;
    printf("unsigned char uc = " FORMAT_U_CHAR_CSTR "\n", uc);
    snprintf(buffer, buff_size, FORMAT_U_CHAR_CSTR,
        basic::test::out::Argument<unsigned char>::Value(uc));
    assert(strcmp(VALUE1_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_U_CHAR_CSTR,
        basic::test::out::Argument<unsigned char>::
        Value((unsigned char)VALUE1_CHAR));
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    unsigned short us = VALUE2_SHORT;
    printf("unsigned short us = " FORMAT_U_SHORT_CSTR "\n", us);
    snprintf(buffer, buff_size, FORMAT_U_SHORT_CSTR,
        basic::test::out::Argument<unsigned short>::Value(us));
    assert(strcmp(VALUE2_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_U_SHORT_CSTR,
        basic::test::out::Argument<unsigned short>::
        Value((unsigned short)VALUE2_SHORT));
    assert(strcmp(VALUE2_CSTR, buffer) == 0);

    unsigned int ui = VALUE3_INT;
    printf("unsgined int ui = " FORMAT_U_INT_CSTR "\n", ui);
    snprintf(buffer, buff_size, FORMAT_U_INT_CSTR,
        basic::test::out::Argument<unsigned int>::Value(ui));
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_U_INT_CSTR,
        basic::test::out::Argument<unsigned int>::
        Value((unsigned int)VALUE3_INT));
    assert(strcmp(VALUE3_CSTR, buffer) == 0);

    unsigned long ul = VALUE4_LONG;
    printf("unsigned long ul = " FORMAT_U_LONG_CSTR "\n", ul);
    snprintf(buffer, buff_size, FORMAT_U_LONG_CSTR,
        basic::test::out::Argument<unsigned long>::Value(ul));
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_U_LONG_CSTR,
        basic::test::out::Argument<unsigned long>::
        Value((unsigned long)VALUE4_LONG));
    assert(strcmp(VALUE4_CSTR, buffer) == 0);

    unsigned long long ull = VALUE5_LONGLONG;
    printf("unsigned long long ull = " FORMAT_U_LONGLONG_CSTR "\n", ull);
    snprintf(buffer, buff_size, FORMAT_U_LONGLONG_CSTR,
        basic::test::out::Argument<unsigned long long>::Value(ull));
    assert(strcmp(VALUE5_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_U_LONGLONG_CSTR,
        basic::test::out::Argument<unsigned long long>::
        Value((unsigned long long)VALUE5_LONGLONG));
    assert(strcmp(VALUE5_CSTR, buffer) == 0);

    float f = VALUE6_FLOAT;
    printf("float f = " FORMAT_FLOAT_CSTR "\n", f);
    snprintf(buffer, buff_size, FORMAT_FLOAT_CSTR,
        basic::test::out::Argument<float>::Value(f));
    assert(strcmp(VALUE6_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_FLOAT_CSTR,
        basic::test::out::Argument<float>::Value(VALUE6_FLOAT));
    assert(strcmp(VALUE6_CSTR, buffer) == 0);

    double d = VALUE7_DOUBLE;
    printf("double d = " FORMAT_DOUBLE_CSTR "\n", d);
    snprintf(buffer, buff_size, FORMAT_DOUBLE_CSTR,
        basic::test::out::Argument<double>::Value(d));
    assert(strcmp(VALUE7_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_DOUBLE_CSTR,
        basic::test::out::Argument<double>::Value(VALUE7_DOUBLE));
    assert(strcmp(VALUE7_CSTR, buffer) == 0);

    long double ld = VALUE8_LONGDOUBLE;
    printf("long double ld = " FORMAT_LONGDOUBLE_CSTR "\n", ld);
    snprintf(buffer, buff_size, FORMAT_LONGDOUBLE_CSTR,
        basic::test::out::Argument<long double>::Value(ld));
    assert(strcmp(VALUE8_CSTR, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_LONGDOUBLE_CSTR,
        basic::test::out::Argument<long double>::
        Value(VALUE8_LONGDOUBLE));
    assert(strcmp(VALUE8_CSTR, buffer) == 0);

    void * p1 = &c;
    char * pointer_cstr = new char[BUFFER_SIZE];
    snprintf(pointer_cstr, buff_size, "%p", p1);
    printf("void * p1 = " FORMAT_CSTR_CSTR "\n", pointer_cstr);
    snprintf(buffer, buff_size, FORMAT_PTR_CSTR,
        basic::test::out::Argument<void*>::Value(p1));
    assert(strcmp(pointer_cstr, buffer) == 0);

    snprintf(pointer_cstr, buff_size, "%p", nullptr);
    printf("void * p2 = " FORMAT_CSTR_CSTR "\n", pointer_cstr);
    snprintf(buffer, buff_size, FORMAT_PTR_CSTR,
        basic::test::out::Argument<void*>::Value(nullptr));
    assert(strcmp(pointer_cstr, buffer) == 0);

    char * cstr1 = new char[sizeof(TEST_CSTR)];
    memcpy(cstr1, TEST_CSTR, sizeof(TEST_CSTR));
    const char * cstr2 = TEST_CSTR;
    printf("const char * cstr = \"" FORMAT_CSTR_CSTR "\"\n", cstr1);
    snprintf(buffer, buff_size, FORMAT_CSTR_CSTR,
        basic::test::out::Argument<char*>::Value(cstr1));
    assert(strcmp(cstr1, buffer) == 0);
    snprintf(buffer, buff_size, FORMAT_CSTR_CSTR,
        basic::test::out::Argument<const char*>::
        Value(std::move(cstr2)));
    assert(strcmp(cstr2, buffer) == 0);

    delete[] cstr1;
    delete[] pointer_cstr;
    delete[] buffer;
}

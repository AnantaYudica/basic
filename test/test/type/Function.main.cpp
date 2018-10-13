#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Function.h"

#include <cstdio>
#include <cassert>
#include <cstring>

char * gbuffer;

#define EMPTY_CSTR ""

#define VALUE1_INT 4
#define VALUE1_CHAR '4'
#define VALUE1_CSTR "4"
#define VALUE2_INT 14
#define VALUE2_SHORT short(14)
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_INT 114
#define VALUE4_LONG 114
#define VALUE4_CSTR "114"

#define BEFFER_SIZE 1024

int Foo1()
{
    snprintf(gbuffer, BEFFER_SIZE, EMPTY_CSTR);
    return 1;
}

void Foo2(char c)
{
    snprintf(gbuffer, BEFFER_SIZE, "%c", c);
}

void Foo3(char c, short s)
{
    snprintf(gbuffer, BEFFER_SIZE, "%c%hd", c, s);
}

void Foo3(char c, short s, int i)
{
    snprintf(gbuffer, BEFFER_SIZE, "%c%hd%d", c, s, i);
}

int Foo4(char c, short s, int i, long l)
{
    snprintf(gbuffer, BEFFER_SIZE, "%c%hd%d%ld", c, s, i, l);
    return 1;
}

int main()
{
    gbuffer = new char[BEFFER_SIZE];

    typedef basic::test::type::Function<int(), &Foo1> Function1;
    Function1::Pointer();
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);
    Function1 f1;
    f1.Call();
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);
    assert(Function1::Pointer == f1.Get());

    typedef basic::test::type::Function<decltype(Foo2), &Foo2> Function2;
    Function2::Pointer(VALUE1_CHAR);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);
    Function2 f2;
    f2.Call(VALUE1_CHAR);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);
    assert(Function2::Pointer == f2.Get());

    typedef basic::test::type::Function<void(char, short), &Foo3> Function3;
    Function3::Pointer(VALUE1_CHAR, VALUE2_SHORT);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);
    Function3 f3;
    f3.Call(VALUE1_CHAR, VALUE2_SHORT);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);
    assert(Function3::Pointer == f3.Get());

    typedef basic::test::type::Function<void(char, short, int), 
        &Foo3> Function4;
    Function4::Pointer(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);
    Function4 f4;
    f4.Call(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);
    assert(Function4::Pointer == f4.Get());

    typedef basic::test::type::Function<decltype(Foo4), &Foo4> Function5;
    Function5::Pointer(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, 
        gbuffer) == 0);
    Function5 f5;
    f5.Call(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, 
        gbuffer) == 0);
    assert(Function5::Pointer == f5.Get());

    delete[] gbuffer;
}

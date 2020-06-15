#include "test/val/Function.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

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

#define BUFFER_SIZE 1024

void Foo1()
{
    snprintf(gbuffer, BUFFER_SIZE, EMPTY_CSTR);
}

int Foo2(char c)
{
    snprintf(gbuffer, BUFFER_SIZE, "%c", c);
    return 1;
}

void Foo3(char c, short s)
{
    snprintf(gbuffer, BUFFER_SIZE, "%c%hd", c, s);
}

void Foo3(char c, short s, int i)
{
    snprintf(gbuffer, BUFFER_SIZE, "%c%hd%d", c, s, i);
}

int Foo4(char c, short s, int i, long l)
{
    snprintf(gbuffer, BUFFER_SIZE, "%c%hd%d%ld", c, s, i, l);
    return 1;
}

int main()
{
    gbuffer = new char[BUFFER_SIZE];

    basic::test::val::Function<void()> f0_1;
    assert(f0_1 == false);
    f0_1.Get() = &Foo1;
    assert(f0_1 == true);
    assert(f0_1.Get() == &Foo1);
    const basic::test::val::Function<void()> f0_2(f0_1);
    assert(f0_2.Get() == &Foo1);
    f0_2.Call();
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(gbuffer, EMPTY_CSTR) == 0);
    basic::test::val::Function<void()> f0_3(std::move(f0_1));
    assert(f0_3.Get() == &Foo1);
    basic::test::val::Function<void()> f0_4;
    f0_4 = f0_3;
    assert(f0_4.Get() == &Foo1);
    basic::test::val::Function<void()> f0_5;
    f0_5 = std::move(f0_3);
    assert(f0_5.Get() == &Foo1);

    basic::test::val::Function<int(char)> f1(&Foo2);
    assert(f1 == true);
    assert(f1.Get() == &Foo2);
    f1.Call(VALUE1_CHAR);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(gbuffer, VALUE1_CSTR) == 0);

    basic::test::val::Function<void(char, short)>
        f2([](char c, short s) {return Foo3(c, s); });
    assert(f2 == true);
    f2.Call(VALUE1_CHAR, VALUE2_SHORT);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(gbuffer, VALUE1_CSTR VALUE2_CSTR) == 0);

    basic::test::val::Function<void(char, short, int)> f3(&Foo3);
    assert(f3 == true);
    f3.Get() = static_cast<void(*)(char, short, int)>(&Foo3);
    assert(f3.Get() == static_cast<void(*)(char, short, int)>(&Foo3));
    f3.Call(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(gbuffer, VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR) == 0);

    basic::test::val::Function<decltype(Foo4)> f4(&Foo4);
    assert(f4 == true);
    f4.Get() = &Foo4;
    assert(f4.Get() == &Foo4);
    f4.Call(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(gbuffer, VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR) == 0);

    delete[] gbuffer;
}

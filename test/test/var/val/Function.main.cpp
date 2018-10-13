#include "test/Variable.h"
#include "test/var/val/Function.h"
#include "test/val/Function.h"

#include <iostream>

#include "test/var/At.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>

char * gbuffer;

#define BUFFER_SIZE 1024

#define FOO1_CSTR "foo1"
#define FOO2_CSTR "foo2"
#define FOO3_CSTR "foo3"
#define FOO4_CSTR "foo4"

void Foo1()
{
    snprintf(gbuffer, BUFFER_SIZE, FOO1_CSTR);
}

void Foo2()
{
    snprintf(gbuffer, BUFFER_SIZE, FOO2_CSTR);
}

void Foo3()
{
    snprintf(gbuffer, BUFFER_SIZE, FOO3_CSTR);
}

void Foo4()
{
    snprintf(gbuffer, BUFFER_SIZE, FOO4_CSTR);
}

int main()
{

    gbuffer = new char[BUFFER_SIZE];

    basic::test::Variable<
        basic::test::val::Function<void()>> var1(&Foo1);
    var1.Get().Call();
    assert(strcmp(gbuffer, FOO1_CSTR) == 0);
    const basic::test::Variable<
        basic::test::val::Function<void()>>& var1_1(var1);
    gbuffer[0] = '\0';
    var1_1.Get().Call();
    assert(strcmp(gbuffer, FOO1_CSTR) == 0);

    basic::test::Variable<
        basic::test::val::Function<void()>,
        basic::test::val::Function<void()>> var2(&Foo1, &Foo2);
    gbuffer[0] = '\0';
    var2.Get().Call();
    assert(strcmp(gbuffer, FOO1_CSTR) == 0);
    basic::test::var::At<1>(var2).Get().Call();
    assert(strcmp(gbuffer, FOO2_CSTR) == 0);

    basic::test::Variable<
        basic::test::val::Function<void()>,
        basic::test::val::Function<void()>,
        basic::test::val::Function<void()>> var3(&Foo1, &Foo2, &Foo3);
    var3.Get().Call();
    assert(strcmp(gbuffer, FOO1_CSTR) == 0);
    basic::test::var::At<1>(var3).Get().Call();
    assert(strcmp(gbuffer, FOO2_CSTR) == 0);
    basic::test::var::At<2>(var3).Get().Call();
    assert(strcmp(gbuffer, FOO3_CSTR) == 0);

    basic::test::Variable<
        basic::test::val::Function<void()>,
        basic::test::val::Function<void()>,
        basic::test::val::Function<void()>,
        basic::test::val::Function<void()>> var4(&Foo1, &Foo2, 
            &Foo3, &Foo4);
    var4.Get().Call();
    assert(strcmp(gbuffer, FOO1_CSTR) == 0);
    basic::test::var::At<1>(var4).Get().Call();
    assert(strcmp(gbuffer, FOO2_CSTR) == 0);
    basic::test::var::At<2>(var4).Get().Call();
    assert(strcmp(gbuffer, FOO3_CSTR) == 0);
    basic::test::var::At<3>(var4).Get().Call();
    assert(strcmp(gbuffer, FOO4_CSTR) == 0);

    delete[] gbuffer;
}

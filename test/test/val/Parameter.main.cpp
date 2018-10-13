#include "test/val/Parameter.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>
#include <typeinfo>

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

struct A
{
    A()
    {
        snprintf(gbuffer, BUFFER_SIZE, EMPTY_CSTR);
    }

    A(char c)
    {
        snprintf(gbuffer, BUFFER_SIZE, "%c", c);
    }

    A(char c, short s)
    {
        snprintf(gbuffer, BUFFER_SIZE, "%c%hd", c, s);
    }

    A(char c, short s, int i)
    {
        snprintf(gbuffer, BUFFER_SIZE, "%c%hd%d", c, s, i);
    }

    A(char c, short s, int i, long l)
    {
        snprintf(gbuffer, BUFFER_SIZE, "%c%hd%d%ld", c, s, i, l);
    }

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
};

int main()
{
    gbuffer = new char[BUFFER_SIZE];

    typedef basic::test::val::Parameter<> ParamVal0;
    typedef basic::test::val::Parameter<char> ParamVal1;
    typedef basic::test::val::Parameter<char, short> ParamVal2;
    typedef basic::test::val::Parameter<char, short, int> ParamVal3;
    typedef basic::test::val::Parameter<char, short, int, long> ParamVal4;

    A a0;
    ParamVal0 paramVal0;
    paramVal0.Fill<void>(&Foo1);
    printf("Function Fill : \"%s\"\n", gbuffer);
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal0.Fill<void>(&A::Foo1, a0);
    printf("Function member Fill : \"%s\"\n", gbuffer);
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal0.Fill<void>(&A::Foo1, &a0);
    printf("Function member Fill (p): \"%s\"\n", gbuffer);
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    A a0_1 = paramVal0.Fill<A>();
    printf("Constructor Fill : \"%s\"\n", gbuffer);
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;

    ParamVal1 paramVal1(0);
    paramVal1.template At<0>() = VALUE1_CHAR;
    paramVal1.Fill<int>(&Foo2);
    printf("Function Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal1.Fill<int>(&A::Foo2, a0);
    printf("Function member Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal1.Fill<int>(&A::Foo2, &a0);
    printf("Function member Fill (p): \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    A a1_1 = paramVal1.Fill<A>();
    printf("Constructor Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;

    assert(paramVal1.template At<0>() == VALUE1_CHAR);
    assert(static_cast<const ParamVal1&>(paramVal1).template At<0>() == 
        VALUE1_CHAR);

    ParamVal2 paramVal2(VALUE1_CHAR, VALUE2_SHORT);
    paramVal2.Fill<void>(static_cast<void(*)(char, short)>(&Foo3));
    printf("Function Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal2.Fill<void>(static_cast<void(A::*)(char, short)>(&A::Foo3), a0);
    printf("Function member Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal2.Fill<void>(static_cast<void(A::*)(char, short)>(&A::Foo3), &a0);
    printf("Function member Fill (p): \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    A a2_1 = std::move(paramVal2.Fill<A>());
    printf("Constructor Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;

    assert(paramVal2.template At<0>() == VALUE1_CHAR);
    assert(static_cast<const ParamVal2&>(paramVal2).template At<0>() ==
        VALUE1_CHAR);
    assert(paramVal2.template At<1>() == VALUE2_SHORT);
    assert(static_cast<const ParamVal2&>(paramVal2).template At<1>() ==
        VALUE2_SHORT);

    ParamVal3 paramVal3(0, 0, 0);
    paramVal3 = ParamVal3(VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT);

    paramVal3.Fill<void>(static_cast<void(*)(char, short, int)>(&Foo3));
    printf("Function Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal3.Fill<void>(static_cast<void(A::*)(char, short, 
        int)>(&A::Foo3), a0);
    printf("Function member Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal3.Fill<void>(static_cast<void(A::*)(char, short, 
        int)>(&A::Foo3), &a0);
    printf("Function member Fill (p): \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    A a3_1 = std::move(paramVal3.Fill<A>());
    printf("Constructor Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;

    assert(paramVal3.template At<0>() == VALUE1_CHAR);
    assert(static_cast<const ParamVal3&>(paramVal3).template At<0>() ==
        VALUE1_CHAR);
    assert(paramVal3.template At<1>() == VALUE2_SHORT);
    assert(static_cast<const ParamVal3&>(paramVal3).template At<1>() ==
        VALUE2_SHORT);
    assert(paramVal3.template At<2>() == VALUE3_INT);
    assert(static_cast<const ParamVal3&>(paramVal3).template At<2>() ==
        VALUE3_INT);

    ParamVal4 paramVal4(0, 0, 0, 0);
    paramVal4 = std::move(ParamVal4(VALUE1_CHAR, VALUE2_SHORT, 
        VALUE3_INT, VALUE4_LONG));

    paramVal4.Fill<int>(&Foo4);
    printf("Function Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal4.Fill<int>(&A::Foo4, a0);
    printf("Function member Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    paramVal4.Fill<int>(&A::Foo4, &a0);
    printf("Function member Fill (p): \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;
    A a4_1 = std::move(paramVal4.Fill<A>());
    printf("Constructor Fill : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, gbuffer) == 0);
    gbuffer[0] = NULL;

    assert(paramVal4.template At<0>() == VALUE1_CHAR);
    assert(static_cast<const ParamVal4&>(paramVal4).template At<0>() ==
        VALUE1_CHAR);
    assert(paramVal4.template At<1>() == VALUE2_SHORT);
    assert(static_cast<const ParamVal4&>(paramVal4).template At<1>() ==
        VALUE2_SHORT);
    assert(paramVal4.template At<2>() == VALUE3_INT);
    assert(static_cast<const ParamVal4&>(paramVal4).template At<2>() ==
        VALUE3_INT);
    assert(paramVal4.template At<3>() == VALUE4_LONG);
    assert(static_cast<const ParamVal4&>(paramVal4).template At<3>() ==
        VALUE4_LONG);

    delete[] gbuffer;

}

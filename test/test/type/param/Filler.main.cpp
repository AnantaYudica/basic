#include "Test.h"

#include "test/type/param/Filler.h"

#include <cstdio>
#include <cassert>

char * gbuffer;

#define BUFFER_SIZE 1024

#define A_CSTR "A"
#define TARGS_CSTR "TArgs"
#define INT_CSTR "int"
#define CHAR_CSTR "char"
#define FLOAT_CSTR "float"
#define COMMA_CSTR ","
#define SPACE_CSTR " "
#define OPEN_POINTY_CSTR "<"
#define CLOSE_POINTY_CSTR ">"
#define ELLIPSIS_CSTR "..."

template<typename... TArgs>
struct A
{
    static void Print()
    {
        snprintf(gbuffer, BUFFER_SIZE, 
            A_CSTR OPEN_POINTY_CSTR TARGS_CSTR ELLIPSIS_CSTR
            CLOSE_POINTY_CSTR);
    }
};

template<>
struct A<int ,char, float>
{
    static void Print()
    {
        snprintf(gbuffer, BUFFER_SIZE,
            A_CSTR OPEN_POINTY_CSTR INT_CSTR COMMA_CSTR SPACE_CSTR
            CHAR_CSTR COMMA_CSTR SPACE_CSTR FLOAT_CSTR CLOSE_POINTY_CSTR);
    }
};

int main()
{
    gbuffer = new char[BUFFER_SIZE];
    typedef basic::test::type::param::Filler<
        basic::test::type::Parameter<int, char, float>> F1;
    typedef basic::test::type::param::Filler<
        basic::test::type::Parameter<int, int, int>> F2;
    typedef basic::test::type::param::Filler<
        basic::test::type::Parameter<>> F3;

    F1::template Type<A>::Print();
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(A_CSTR OPEN_POINTY_CSTR INT_CSTR COMMA_CSTR SPACE_CSTR
        CHAR_CSTR COMMA_CSTR SPACE_CSTR FLOAT_CSTR CLOSE_POINTY_CSTR,
        gbuffer) == 0);

    F2::template Type<A>::Print();
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(A_CSTR OPEN_POINTY_CSTR TARGS_CSTR ELLIPSIS_CSTR
        CLOSE_POINTY_CSTR, gbuffer) == 0);

    F3::template Type<A>::Print();
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(A_CSTR OPEN_POINTY_CSTR TARGS_CSTR ELLIPSIS_CSTR
        CLOSE_POINTY_CSTR, gbuffer) == 0);

    delete[] gbuffer;
}

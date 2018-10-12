#include "Test.h"

#include "test/type/param/Function.h"

#include <cstdio>
#include <cassert>
#include <cstring>

char * gbuffer;

#define BUFFER_SIZE 1024

#define EMPTY_CSTR ""
#define VALUE1_INT 14
#define VALUE1_CSTR "14"
#define VALUE2_CHAR '4'
#define VALUE2_CSTR "4"
#define VALUE3_FLOAT 3.14f
#define VALUE3_CSTR "3.14"

void Print()
{
    snprintf(gbuffer, BUFFER_SIZE, EMPTY_CSTR);
}

int Print(int i)
{
    snprintf(gbuffer, BUFFER_SIZE, "%d", i);
    return 1;
}

int Print(int i, char c)
{
    snprintf(gbuffer, BUFFER_SIZE, "%d%c", i, c);
    return 1;
}

void Print(int i, char c, float f)
{
    snprintf(gbuffer, BUFFER_SIZE, "%d%c%.2f", i, c, f);
}

int main()
{
    gbuffer = new char[BUFFER_SIZE];

    typedef basic::test::type::Parameter<> P0;
    typedef basic::test::type::Parameter<int> P1;
    typedef basic::test::type::Parameter<int, char> P2;
    typedef basic::test::type::Parameter<int, char, float> P3;

    typedef basic::test::type::param::Function<P0> PF0;
    typedef basic::test::type::param::Function<P1> PF1;
    typedef basic::test::type::param::Function<P2> PF2;
    typedef basic::test::type::param::Function<P3> PF3;

    PF0::Call<void>(&Print);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(EMPTY_CSTR, gbuffer) == 0);

    PF1::Call<int>(&Print, VALUE1_INT);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR, gbuffer) == 0);

    PF2::Call<int>(&Print, VALUE1_INT, VALUE2_CHAR);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR, gbuffer) == 0);

    PF3::Call<void>(&Print, VALUE1_INT, VALUE2_CHAR, VALUE3_FLOAT);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR, gbuffer) == 0);

    delete[] gbuffer;
}

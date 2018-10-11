#include "test/type/param/mmbr/Function.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>

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

#define FORMAT_CSTR "%c%hd%d%ld"

#define FUNC_MMBR_CSTR ""
#define FUNC_LVAL_MMBR_CSTR "&"
#define FUNC_RVAL_MMBR_CSTR "&&"
#define FUNC_CONST_MMBR_CSTR "const"
#define FUNC_VOLATILE_MMBR_CSTR "volatile"
#define FUNC_CONSTVOLATILE_MMBR_CSTR "const volatile"

#define BUFFER_SIZE 1024

char * gbuffer;

struct TestA
{
    void Print1(char c, short s, int i, long l)
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_MMBR_CSTR FORMAT_CSTR,
            c, s, i, l);
    }
    int Print2(char c, short s, int i, long l)
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_MMBR_CSTR FORMAT_CSTR,
            c, s, i, l);
        return 1;
    }
    int Print2(char c, short s, int i, long l) const
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_CONST_MMBR_CSTR FORMAT_CSTR,
            c, s, i, l);
        return 1;
    }
    int Print2(char c, short s, int i, long l) volatile
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_VOLATILE_MMBR_CSTR FORMAT_CSTR,
            c, s, i, l);
        return 1;
    }
    int Print2(char c, short s, int i, long l) const volatile
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_CONSTVOLATILE_MMBR_CSTR 
            FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) &
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_MMBR_CSTR FUNC_LVAL_MMBR_CSTR 
            FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) const &
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_CONST_MMBR_CSTR FUNC_LVAL_MMBR_CSTR
            FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) volatile &
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_VOLATILE_MMBR_CSTR
            FUNC_LVAL_MMBR_CSTR FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) const volatile &
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_CONSTVOLATILE_MMBR_CSTR
            FUNC_LVAL_MMBR_CSTR FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) &&
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_MMBR_CSTR FUNC_RVAL_MMBR_CSTR
            FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) const &&
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_CONST_MMBR_CSTR FUNC_RVAL_MMBR_CSTR
            FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) volatile &&
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_VOLATILE_MMBR_CSTR
            FUNC_RVAL_MMBR_CSTR FORMAT_CSTR, c, s, i, l);
        return 1;
    }
    int Print3(char c, short s, int i, long l) const volatile &&
    {
        snprintf(gbuffer, BUFFER_SIZE, FUNC_CONSTVOLATILE_MMBR_CSTR
            FUNC_RVAL_MMBR_CSTR FORMAT_CSTR, c, s, i, l);
        return 1;
    }
};

int main()
{
    gbuffer = new char[BUFFER_SIZE];

    typedef basic::test::type::Parameter<char, short, int, long> Param1;
    typedef basic::test::type::param::mmbr::Function<Param1> Func1;

    TestA testa;
    Func1::Call<void>(&TestA::Print1, testa, VALUE1_CHAR, VALUE2_SHORT, 
        VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR 
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<void>(&TestA::Print1, &testa, VALUE1_CHAR, VALUE2_SHORT,
        VALUE3_INT, VALUE4_LONG);
    assert(strcmp(FUNC_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int>(Func1::PointerType<int, TestA>(&TestA::Print2), testa, 
        VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerType<int, TestA>(&TestA::Print2), &testa,
        VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    assert(strcmp(FUNC_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int>(Func1::PointerConstType<int, TestA>(&TestA::Print2), 
        testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_CONST_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerConstType<int, TestA>(&TestA::Print2), 
        &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    assert(strcmp(FUNC_CONST_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int>(Func1::PointerVolatileType<int, TestA>(&TestA::Print2),
        testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_VOLATILE_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerVolatileType<int, TestA>(&TestA::Print2),
        &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    assert(strcmp(FUNC_VOLATILE_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int>(Func1::PointerConstVolatileType<int, 
        TestA>(&TestA::Print2), testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, 
        VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_CONSTVOLATILE_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerConstVolatileType<int, 
        TestA>(&TestA::Print2), &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, 
        VALUE4_LONG);
    assert(strcmp(FUNC_CONSTVOLATILE_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&>(Func1::PointerLValType<int, TestA>(&TestA::Print3), testa,
        VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerLValType<int, 
        TestA>(&TestA::Print3), &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, 
        VALUE4_LONG);
    assert(strcmp(FUNC_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&>(Func1::PointerConstLValType<int, TestA>(&TestA::Print3),
        testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_CONST_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR 
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerConstLValType<int, TestA>(&TestA::Print3),
        &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    assert(strcmp(FUNC_CONST_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR 
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&>(Func1::PointerVolatileLValType<int,
        TestA>(&TestA::Print3), testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, 
        VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_VOLATILE_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerVolatileLValType<int, 
        TestA>(&TestA::Print3), &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT,
        VALUE4_LONG);
    assert(strcmp(FUNC_VOLATILE_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&>(Func1::PointerConstVolatileLValType<int,
        TestA>(&TestA::Print3), testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT,
        VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_CONSTVOLATILE_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    Func1::Call<int>(Func1::PointerConstVolatileLValType<int,
        TestA>(&TestA::Print3), &testa, VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT,
        VALUE4_LONG);
    assert(strcmp(FUNC_CONSTVOLATILE_MMBR_CSTR FUNC_LVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    /* todo un-comment if bug #63 fix

    Func1::Call<int, TestA&&>(Func1::PointerRValType<int, TestA>(&TestA::Print3), 
        std::move(testa), VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_MMBR_CSTR FUNC_RVAL_MMBR_CSTR VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&&>(Func1::PointerConstRValType<int, TestA>(&TestA::Print3),
        std::move(testa), VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_CONST_MMBR_CSTR FUNC_RVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&&>(Func1::PointerVolatileRValType<int,
        TestA>(&TestA::Print3), std::move(testa), VALUE1_CHAR, VALUE2_SHORT,
        VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_VOLATILE_MMBR_CSTR FUNC_RVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);

    Func1::Call<int, TestA&&>(Func1::PointerConstVolatileRValType<int,
        TestA>(&TestA::Print3), std::move(testa), VALUE1_CHAR, VALUE2_SHORT,
        VALUE3_INT, VALUE4_LONG);
    printf("output : \"%s\"\n", gbuffer);
    assert(strcmp(FUNC_CONSTVOLATILE_MMBR_CSTR FUNC_RVAL_MMBR_CSTR VALUE1_CSTR
        VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR, gbuffer) == 0);
    */

    delete[] gbuffer;
}

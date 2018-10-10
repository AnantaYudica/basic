#include "test/msg/arg/val/param/At.h"
#include "test/val/Parameter.h"
#include "test/var/val/Parameter.h"

#include "test/type/Index.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>

struct TestA
{
    template<typename... TArgs>
    void Call(char* buffer, const std::size_t& size,
        const char* format, TArgs&&... args)
    {
        snprintf(buffer, size, format,
            basic::test::out::Argument<TArgs>::Value(args)...);
    }
};

template<typename... TArgs>
int Call(char* buffer, const std::size_t& size,
    const char* format, TArgs&&... args)
{
    snprintf(buffer, size, format,
        basic::test::out::Argument<TArgs>::Value(args)...);
    return 1;
}

struct Case1 {};

#define BUFFER_SIZE 1024

#define VALUE1_CHAR '4'
#define VALUE1_CSTR "4"
#define VALUE2_SHORT (short)14
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_LONG 114
#define VALUE4_CSTR "114"

int main()
{
    char * buffer = new char[BUFFER_SIZE];
    std::size_t buff_size = BUFFER_SIZE;
    TestA testa1;

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::val::param::At<0, 0>> arg1;

    const char * format1 = "%c";
    basic::test::Variable<
        basic::test::val::Parameter<char>> var1(VALUE1_CHAR);
    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);
    assert(arg1.Get(var1) == VALUE1_CHAR);

    const char * format2 = "%hd";
    basic::test::Variable<
        basic::test::val::Parameter<short>> var2(VALUE2_SHORT);
    arg1.Call<int>(&Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE2_CSTR, buffer) == 0);
    assert(arg1.Get(var2) == VALUE2_SHORT);

    const char * format3 = "%hd";
    basic::test::type::Index<Case1, 0> case1_index0;
    basic::test::Variable<
        basic::test::val::Parameter<int>> var3(VALUE3_INT);
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg1.Get(var3) == VALUE3_INT);

    const char * format4 = "%ld";
    basic::test::Variable<
        basic::test::val::Parameter<long>> var4(VALUE4_LONG);
    arg1.Call<int>(case1_index0, &Call, var4, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg1.Get(var4) == VALUE4_LONG);

    basic::test::type::Index<Case1, 4> case1_index4;
    arg1.Call<void>(case1_index4, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg1.Get(var3) == VALUE3_INT);

    arg1.Call<int>(case1_index0, &Call, var4, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg1.Get(var4) == VALUE4_LONG);

    basic::test::Variable<
        basic::test::val::Parameter<char, short, int, long>> var5(VALUE1_CHAR,
            VALUE2_SHORT, VALUE3_INT, VALUE4_LONG);

    arg1.Call<void>(&TestA::Call, testa1, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);
    assert(arg1.Get(var5) == VALUE1_CHAR);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::val::param::At<0, 1>> arg2;
    arg2.Call<int>(&Call, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE2_CSTR, buffer) == 0);
    assert(arg2.Get(var5) == VALUE2_SHORT);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::val::param::At<0, 2>> arg3;
    arg3.Call<void>(case1_index0, &TestA::Call, testa1, var5,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg3.Get(var5) == VALUE3_INT);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::val::param::At<0, 3>> arg4;
    arg4.Call<int>(case1_index0, &Call, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg4.Get(var5) == VALUE4_LONG);

    arg3.Call<void>(case1_index4, &TestA::Call, testa1, var5,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg3.Get(var5) == VALUE3_INT);

    arg4.Call<int>(case1_index0, &Call, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg4.Get(var5) == VALUE4_LONG);

    const char* format5 = "%c%hd%d%ld";

    basic::test::Variable<
        basic::test::val::Parameter<char>,
        basic::test::val::Parameter<short>,
        basic::test::val::Parameter<int>,
        basic::test::val::Parameter<long>> var6(VALUE1_CHAR, VALUE2_SHORT,
            VALUE3_INT, VALUE4_LONG);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::val::param::At<0, 0>,
        basic::test::msg::arg::val::param::At<1, 0>,
        basic::test::msg::arg::val::param::At<2, 0>,
        basic::test::msg::arg::val::param::At<3, 0>> arg5;

    arg5.Call<void>(&TestA::Call, testa1, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format5));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, buffer) == 0);

    arg5.Call<int>(&Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format5));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, buffer) == 0);

    arg5.Call<void>(case1_index0, &TestA::Call, testa1, var6,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format5));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, buffer) == 0);

    arg5.Call<int>(case1_index0, &Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format5));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, buffer) == 0);

    arg5.Call<void>(case1_index4, &TestA::Call, testa1, var6,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format5));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, buffer) == 0);

    arg5.Call<int>(case1_index0, &Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format5));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR, buffer) == 0);

    assert(arg5.Get(var6) == VALUE1_CHAR);

    delete[] buffer;
}

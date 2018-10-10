#include "test/msg/arg/type/Value.h"
#include "test/type/Value.h"
#include "test/var/type/Value.h"

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
        snprintf(buffer, size, format, std::forward<TArgs>(args)...);
    }
};

template<typename... TArgs>
int Call(char* buffer, const std::size_t& size,
    const char* format, TArgs&&... args)
{
    snprintf(buffer, size, format, std::forward<TArgs>(args)...);
    return 1;
}

struct Case1 {};

#define BUFFER_SIZE 1024

#define VALUE1_INT 4
#define VALUE1_CSTR "4"
#define VALUE2_INT 14
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_INT 114
#define VALUE4_CSTR "114"

int main()
{
    char * buffer = new char[BUFFER_SIZE];
    std::size_t buff_size = BUFFER_SIZE;
    TestA testa1;

    const char* format1 = "%d";

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Value<0>> arg1;

    basic::test::Variable<
        basic::test::type::Value<int, VALUE1_INT>> var1;
    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    basic::test::Variable<
        basic::test::type::Value<int, VALUE2_INT>> var2;
    arg1.Call<int>(&Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE2_CSTR, buffer) == 0);
    assert(arg1.Get(var2) == VALUE2_INT);

    basic::test::type::Index<Case1, 0> case1_index0;
    basic::test::Variable<
        basic::test::type::Value<int, VALUE3_INT>> var3;
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg1.Get(var3) == VALUE3_INT);

    basic::test::Variable<
        basic::test::type::Value<int, VALUE4_INT>> var4;
    arg1.Call<int>(case1_index0, &Call, var4, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg1.Get(var4) == VALUE4_INT);

    basic::test::type::Index<Case1, 4> case1_index4;
    basic::test::Variable<
        basic::test::type::Value<int, VALUE3_INT>> var5;
    arg1.Call<void>(case1_index4, &TestA::Call, testa1, var5,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg1.Get(var5) == VALUE3_INT);

    basic::test::Variable<
        basic::test::type::Value<int, VALUE4_INT>> var6;
    arg1.Call<int>(case1_index0, &Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg1.Get(var6) == VALUE4_INT);

    const char* format2 = "%d%d%d%d";
    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Value<0>,
        basic::test::msg::arg::type::Value<1>,
        basic::test::msg::arg::type::Value<2>,
        basic::test::msg::arg::type::Value<3>> arg2;
    basic::test::Variable<
        basic::test::type::Value<int, VALUE1_INT>,
        basic::test::type::Value<int, VALUE2_INT>,
        basic::test::type::Value<int, VALUE3_INT>,
        basic::test::type::Value<int, VALUE4_INT>> var7;

    arg2.Call<void>(&TestA::Call, testa1, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(&Call, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index4, &TestA::Call, testa1, var7,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index4, &Call, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    assert(arg2.Get(var7) == VALUE1_INT);

    delete[] buffer;
}

#include "test/msg/arg/val/Sequence.h"
#include "test/val/Sequence.h"
#include "test/var/val/Sequence.h"

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
        basic::test::msg::arg::val::Sequence<0>> arg1;

    basic::test::Variable<
        basic::test::val::Sequence<int, 1>> var1(VALUE1_INT);
    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);
    assert(arg1.template Get<0>(var1) == VALUE1_INT);

    basic::test::Variable<
        basic::test::val::Sequence<int, 1>> var2(VALUE2_INT);
    arg1.Call<int>(&Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE2_CSTR, buffer) == 0);
    assert(arg1.template Get<0>(var2) == VALUE2_INT);

    basic::test::type::Index<Case1, 0> case1_index0;
    basic::test::Variable<
        basic::test::val::Sequence<int, 1>> var3(VALUE3_INT);
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg1.template Get<0>(var3) == VALUE3_INT);

    basic::test::Variable<
        basic::test::val::Sequence<int, 1>> var4(VALUE4_INT);
    arg1.Call<int>(case1_index0, &Call, var4, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg1.template Get<0>(var4) == VALUE4_INT);

    basic::test::type::Index<Case1, 4> case1_index4;
    arg1.Call<void>(case1_index4, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE3_CSTR, buffer) == 0);
    assert(arg1.template Get<0>(var3) == VALUE3_INT);

    arg1.Call<int>(case1_index0, &Call, var4, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);
    assert(arg1.template Get<0>(var4) == VALUE4_INT);

    const char* format2 = "%d%d%d%d";

    basic::test::Variable<
        basic::test::val::Sequence<int, 4>> var5(VALUE1_INT, VALUE2_INT,
            VALUE3_INT, VALUE4_INT);

    arg1.Call<void>(&TestA::Call, testa1, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg1.Call<int>(&Call, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var5,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg1.Call<int>(case1_index0, &Call, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg1.Call<void>(case1_index4, &TestA::Call, testa1, var5,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg1.Call<int>(case1_index0, &Call, var5, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    assert(arg1.template Get<0>(var5) == VALUE1_INT);
    assert(arg1.template Get<1>(var5) == VALUE2_INT);
    assert(arg1.template Get<2>(var5) == VALUE3_INT);
    assert(arg1.template Get<3>(var5) == VALUE4_INT);

    basic::test::Variable<
        basic::test::val::Sequence<int, 1>,
        basic::test::val::Sequence<int, 1>,
        basic::test::val::Sequence<int, 1>,
        basic::test::val::Sequence<int, 1>> var6(VALUE1_INT, 
            VALUE2_INT, VALUE3_INT, VALUE4_INT);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::val::Sequence<0>,
        basic::test::msg::arg::val::Sequence<1>,
        basic::test::msg::arg::val::Sequence<2>,
        basic::test::msg::arg::val::Sequence<3>> arg2;

    arg2.Call<void>(&TestA::Call, testa1, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(&Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index0, &TestA::Call, testa1, var6,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index0, &Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index4, &TestA::Call, testa1, var6,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index0, &Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    assert(arg2.template Get<0>(var6) == VALUE1_INT);

    delete[] buffer;
}

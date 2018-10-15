#include "test/msg/arg/type/Function.h"
#include "test/type/Function.h"
#include "test/var/type/Function.h"

#include "test/type/Index.h"
#include "test/var/At.h"

#include "test/msg/arg/Value.h"
#include "test/var/Value.h"

#include "test/msg/arg/val/Sequence.h"
#include "test/msg/arg/val/seq/At.h"
#include "test/msg/arg/type/Index.h"
#include "test/val/Sequence.h"

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
char * gbuffer;

#define FORMAT0_CSTR "format0"

const char* Foo0()
{
    return FORMAT0_CSTR;
}

template<typename... TArgs>
char* Foo1(const char*&& format, TArgs&&... args)
{
    snprintf(gbuffer, BUFFER_SIZE, format, 
        std::forward<TArgs>(args)...);
    return gbuffer;
}

#define FORMAT1_CSTR "format1"
#define FORMAT2_CSTR "format2"
#define FORMAT3_CSTR "format3"
#define FORMAT4_CSTR "format4"
#define FORMAT5_CSTR "format5"
#define FORMAT6_CSTR "format6"

#define FORMAT7_CSTR "%d%d%d%d"
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
    gbuffer = new char[BUFFER_SIZE];
    std::size_t buff_size = BUFFER_SIZE;
    TestA testa1;

    const char* format1 = "%s";

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Function<0>> arg0;

    basic::test::Variable<
        basic::test::type::Function<const char*(), &Foo0>> var0;

    arg0.Call<void>(&TestA::Call, testa1, var0, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT0_CSTR, buffer) == 0);

    arg0.Call<int>(&Call, var0, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT0_CSTR, buffer) == 0);

    basic::test::type::Index<Case1, 0> case1_index0;
    arg0.Call<void>(case1_index0, &TestA::Call, testa1, var0,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT0_CSTR, buffer) == 0);

    arg0.Call<int>(case1_index0, &Call, var0, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT0_CSTR, buffer) == 0);

    basic::test::type::Index<Case1, 4> case1_index4;
    arg0.Call<void>(case1_index4, &TestA::Call, testa1, var0,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT0_CSTR, buffer) == 0);

    arg0.Call<int>(case1_index0, &Call, var0, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT0_CSTR, buffer) == 0);

    assert(strcmp(arg0.Get(var0), FORMAT0_CSTR) == 0);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Function<0,
        basic::test::msg::arg::Value<1>>> arg1;

    const char* cstr1 = FORMAT1_CSTR;
    basic::test::Variable<
        basic::test::type::Function<char*(const char*&&), &Foo1>,
        basic::test::Value<const char*>> var1(cstr1);

    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT1_CSTR, buffer) == 0);
    assert(strcmp(arg1.Get(var1), FORMAT1_CSTR) == 0);

    const char* cstr2 = FORMAT2_CSTR;
    basic::test::var::At<1>(var1).Get().Get() = cstr2;
    arg1.Call<int>(&Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT2_CSTR, buffer) == 0);
    assert(strcmp(arg1.Get(var1), FORMAT2_CSTR) == 0);

    const char* cstr4 = FORMAT3_CSTR;
    basic::test::var::At<1>(var1).Get().Get() = cstr4;
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT3_CSTR, buffer) == 0);
    assert(strcmp(arg1.Get(var1), FORMAT3_CSTR) == 0);

    const char* cstr5 = FORMAT4_CSTR;
    basic::test::var::At<1>(var1).Get().Get() = cstr5;
    arg1.Call<int>(case1_index0, &Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT4_CSTR, buffer) == 0);
    assert(strcmp(arg1.Get(var1), FORMAT4_CSTR) == 0);

    const char* cstr6 = FORMAT5_CSTR;
    basic::test::var::At<1>(var1).Get().Get() = cstr6;
    arg1.Call<void>(case1_index4, &TestA::Call, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT5_CSTR, buffer) == 0);
    assert(strcmp(arg1.Get(var1), FORMAT5_CSTR) == 0);

    const char* cstr7 = FORMAT6_CSTR;
    basic::test::var::At<1>(var1).Get().Get() = cstr7;
    arg1.Call<int>(case1_index0, &Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(FORMAT6_CSTR, buffer) == 0);
    assert(strcmp(arg1.Get(var1), FORMAT6_CSTR) == 0);

    const char* cstr3 = FORMAT7_CSTR;
    basic::test::Variable<
        basic::test::type::Function<char*(const char*&&, int&&, 
            int&&, int&&, int&&), &Foo1>,
        basic::test::Value<const char*>,
        basic::test::Value<int>,
        basic::test::Value<int>,
        basic::test::Value<int>,
        basic::test::Value<int>> var2(cstr3, VALUE1_INT, VALUE2_INT,
            VALUE3_INT, VALUE4_INT);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Function<0,
        basic::test::msg::arg::Value<1>,
        basic::test::msg::arg::Value<2>,
        basic::test::msg::arg::Value<3>,
        basic::test::msg::arg::Value<4>,
        basic::test::msg::arg::Value<5>>> arg2;

    arg2.Call<void>(&TestA::Call, testa1, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(&Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index0, &TestA::Call, testa1, var2,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index0, &Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index4, &TestA::Call, testa1, var2,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index4, &Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR, buffer) == 0);

    assert(strcmp(arg2.Get(var2), VALUE1_CSTR VALUE2_CSTR
        VALUE3_CSTR VALUE4_CSTR) == 0);

    const char* cstr8 = "%d";
    basic::test::Variable<
        basic::test::type::Function<char*(const char*&&, int&&), &Foo1>,
        basic::test::Value<const char*>,
        basic::test::val::Sequence<int, 4>> var3(cstr8, VALUE1_INT,
            VALUE2_INT, VALUE3_INT, VALUE4_INT);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Function<0,
        basic::test::msg::arg::Value<1>,
        basic::test::msg::arg::type::Index<2,
            basic::test::msg::arg::val::seq::At>>> arg3;

    arg3.Call<void>(&TestA::Call, testa1, var3, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    arg3.Call<int>(&Call, var3, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    arg3.Call<void>(case1_index0, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    arg3.Call<int>(case1_index0, &Call, var3, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE1_CSTR, buffer) == 0);

    basic::test::type::Index<Case1, 3> case1_index3;
    arg3.Call<void>(case1_index3, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);

    arg3.Call<int>(case1_index3, &Call, var3, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE4_CSTR, buffer) == 0);

    assert(strcmp(arg3.Get(var3), VALUE1_CSTR) == 0);
    assert(strcmp(arg3.template Get<1>(var3), VALUE2_CSTR) == 0);
    assert(strcmp(arg3.template Get<2>(var3), VALUE3_CSTR) == 0);
    assert(strcmp(arg3.template Get<3>(var3), VALUE4_CSTR) == 0);

    delete[] buffer;
    delete[] gbuffer;
}


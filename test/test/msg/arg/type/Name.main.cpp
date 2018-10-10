#include "test/msg/arg/type/Name.h"
#include "test/type/Name.h"
#include "test/Variable.h"

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

#define CHAR_CSTR "char"
#define SHORT_CSTR "short"
#define INT_CSTR "int"
#define LONG_CSTR "long"

template<>
struct basic::test::type::Name<char>
{
    template<typename TChar = char>
    static test::CString<const TChar> CStr()
    {
        static TChar cstr[] = CHAR_CSTR;
        return { cstr };
    }
};

template<>
struct basic::test::type::Name<short>
{
    template<typename TChar = char>
    static test::CString<const TChar> CStr()
    {
        static TChar cstr[] = SHORT_CSTR;
        return { cstr };
    }
};

template<>
struct basic::test::type::Name<int>
{
    template<typename TChar = char>
    static test::CString<const TChar> CStr()
    {
        static TChar cstr[] = INT_CSTR;
        return { cstr };
    }
};

template<>
struct basic::test::type::Name<long>
{
    template<typename TChar = char>
    static test::CString<const TChar> CStr()
    {
        static TChar cstr[] = LONG_CSTR;
        return { cstr };
    }
};

int main()
{
    char * buffer = new char[BUFFER_SIZE];
    std::size_t buff_size = BUFFER_SIZE;
    TestA testa1;

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Name<0>> arg1;

    const char* format1 = "%s";

    basic::test::Variable<char> var1;
    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR, buffer) == 0);
    assert(strcmp(*arg1.Get(var1), CHAR_CSTR) == 0);

    basic::test::Variable<short> var2;
    arg1.Call<int>(&Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(SHORT_CSTR, buffer) == 0);
    assert(strcmp(*arg1.Get(var2), SHORT_CSTR) == 0);

    basic::test::type::Index<Case1, 0> case1_index0;
    basic::test::Variable<int> var3;
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var3,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(INT_CSTR, buffer) == 0);
    assert(strcmp(*arg1.Get(var3), INT_CSTR) == 0);

    basic::test::Variable<long> var4;
    arg1.Call<int>(case1_index0, &Call, var4, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(LONG_CSTR, buffer) == 0);
    assert(strcmp(*arg1.Get(var4), LONG_CSTR) == 0);

    basic::test::type::Index<Case1, 3> case1_index3;
    basic::test::Variable<int> var5;
    arg1.Call<void>(case1_index3, &TestA::Call, testa1, var5,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(INT_CSTR, buffer) == 0);
    assert(strcmp(*arg1.Get(var5), INT_CSTR) == 0);

    basic::test::Variable<long> var6;
    arg1.Call<int>(case1_index3, &Call, var6, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(LONG_CSTR, buffer) == 0);
    assert(strcmp(*arg1.Get(var6), LONG_CSTR) == 0);


    basic::test::Variable <char, short, int, long> var7;

    basic::test::msg::Argument <Case1,
        basic::test::msg::arg::type::Name<0>,
        basic::test::msg::arg::type::Name<1>,
        basic::test::msg::arg::type::Name<2>,
        basic::test::msg::arg::type::Name<3>> arg2;

    const char* format2 = "%s%s%s%s";

    arg2.Call<void>(&TestA::Call, testa1, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR SHORT_CSTR INT_CSTR LONG_CSTR, buffer) == 0);

    arg2.Call<int>(&Call, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR SHORT_CSTR INT_CSTR LONG_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index0, &TestA::Call, testa1, var7,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR SHORT_CSTR INT_CSTR LONG_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index0, &Call, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR SHORT_CSTR INT_CSTR LONG_CSTR, buffer) == 0);

    arg2.Call<void>(case1_index3, &TestA::Call, testa1, var7,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR SHORT_CSTR INT_CSTR LONG_CSTR, buffer) == 0);

    arg2.Call<int>(case1_index3, &Call, var7, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR SHORT_CSTR INT_CSTR LONG_CSTR, buffer) == 0);

    assert(strcmp(*arg2.Get(var7), CHAR_CSTR) == 0);

    delete[] buffer;
}

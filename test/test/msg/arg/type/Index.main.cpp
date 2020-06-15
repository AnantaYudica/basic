#include "test/msg/arg/type/Index.h"
#include "test/type/Index.h"

#include "test/msg/arg/type/param/Name.h"
#include "test/msg/arg/type/param/name/At.h"
#include "test/msg/arg/type/val/Sequence.h"
#include "test/msg/arg/type/val/seq/At.h"
#include "test/msg/arg/val/Sequence.h"
#include "test/msg/arg/val/seq/At.h"
#include "test/msg/arg/val/Parameter.h"
#include "test/msg/arg/val/param/At.h"

#include "test/var/At.h"

#include "test/cstr/out/Argument.h"

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

    basic::test::Variable<
        basic::test::type::Parameter<char, short, int, long>,
        basic::test::type::val::Sequence<int, VALUE1_INT, VALUE2_INT,
            VALUE3_INT, VALUE4_INT>,
        basic::test::val::Sequence<int, 4>,
        basic::test::val::Parameter<int, int, int, int>> var1(VALUE1_INT, 
            VALUE2_INT, VALUE3_INT, VALUE4_INT, VALUE1_INT, VALUE2_INT,
            VALUE3_INT, VALUE4_INT);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Index<0,
            basic::test::msg::arg::type::param::name::At>,
        basic::test::msg::arg::type::Index<1,
            basic::test::msg::arg::type::val::seq::At>,
        basic::test::msg::arg::type::Index<2,
            basic::test::msg::arg::val::seq::At>,
        basic::test::msg::arg::type::Index<3,
            basic::test::msg::arg::val::param::At>> arg1;

    const char* format1 = "%s%d%d%d";

    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR VALUE1_CSTR VALUE1_CSTR VALUE1_CSTR, buffer) == 0);

    arg1.Call<int>(&Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR VALUE1_CSTR VALUE1_CSTR VALUE1_CSTR, buffer) == 0);

    basic::test::type::Index<Case1, 0> case1_index0;
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR VALUE1_CSTR VALUE1_CSTR VALUE1_CSTR, buffer) == 0);

    arg1.Call<int>(case1_index0, &Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(CHAR_CSTR VALUE1_CSTR VALUE1_CSTR VALUE1_CSTR, buffer) == 0);

    basic::test::type::Index<Case1, 3> case1_index3;
    arg1.Call<void>(case1_index3, &TestA::Call, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(LONG_CSTR VALUE4_CSTR VALUE4_CSTR VALUE4_CSTR, buffer) == 0);

    arg1.Call<int>(case1_index3, &Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(LONG_CSTR VALUE4_CSTR VALUE4_CSTR VALUE4_CSTR, buffer) == 0);

    assert(strcmp(*arg1.Get<0>(var1), CHAR_CSTR) == 0);
    assert(strcmp(*arg1.Get<1>(var1), SHORT_CSTR) == 0);
    assert(strcmp(*arg1.Get<2>(var1), INT_CSTR) == 0);
    assert(strcmp(*arg1.Get<3>(var1), LONG_CSTR) == 0);

    delete[] buffer;
}

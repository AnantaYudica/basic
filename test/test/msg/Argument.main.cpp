#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/msg/Argument.h"
#include "test/msg/arg/type/Name.h"
#include "test/msg/arg/type/Value.h"
#include "test/msg/arg/type/Function.h"
#include "test/msg/arg/type/Index.h"
#include "test/msg/arg/type/val/Sequence.h"
#include "test/msg/arg/type/val/seq/At.h"
#include "test/msg/arg/type/param/Name.h"
#include "test/msg/arg/type/param/name/At.h"
#include "test/msg/arg/Value.h"
#include "test/msg/arg/val/Function.h"
#include "test/msg/arg/val/Sequence.h"
#include "test/msg/arg/val/seq/At.h"
#include "test/msg/arg/val/Parameter.h"
#include "test/msg/arg/val/param/At.h"

#include "test/type/Index.h"

#include "test/CString.h"
#include "test/cstr/out/Argument.h"

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

#define FORMAT0_CSTR ""

const char* Foo0()
{
    return FORMAT0_CSTR;
}

#define BUFFER_SIZE 1024

#define VALUE_EMPTY_CSTR ""

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

#define CHAR_CSTR "char"
#define SHORT_CSTR "short"
#define INT_CSTR "int"
#define LONG_CSTR "long"
#define CONJ_CSTR ", "

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

    const char * format0 = VALUE_EMPTY_CSTR;
    basic::test::Variable<> var1;
    basic::test::msg::Argument<Case1> arg1;
    
    arg1.Call<void>(&TestA::Call, testa1, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format0));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE_EMPTY_CSTR, buffer) == 0);

    arg1.Call<int>(&Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format0));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE_EMPTY_CSTR, buffer) == 0);
    
    basic::test::type::Index<Case1, 0> case1_index0;
    arg1.Call<void>(case1_index0, &TestA::Call, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format0));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE_EMPTY_CSTR, buffer) == 0);

    arg1.Call<int>(case1_index0, &Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format0));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE_EMPTY_CSTR, buffer) == 0);

    basic::test::type::Index<Case1, 3> case1_index3;
    arg1.Call<void>(case1_index3, &TestA::Call, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format0));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE_EMPTY_CSTR, buffer) == 0);

    arg1.Call<int>(case1_index3, &Call, var1, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format0));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(VALUE_EMPTY_CSTR, buffer) == 0);

    basic::test::Variable<
        char, /*0*/
        basic::test::type::Parameter<char, short, int, long>, /*1*/
        basic::test::type::Value<int, VALUE1_INT>,  /*2*/
        basic::test::type::val::Sequence<int, VALUE1_INT,
            VALUE2_INT, VALUE3_INT, VALUE4_INT>,  /*3*/
        basic::test::type::Function<const char*(), &Foo0>,  /*4*/
        basic::test::Value<int>,  /*5*/
        basic::test::val::Sequence<int, 4>,  /*6*/
        basic::test::val::Parameter<char, short, int, long>, /*7*/
        basic::test::val::Function<const char*()> /*8*/> var2(VALUE1_INT,
            VALUE1_INT, VALUE2_INT, VALUE3_INT, VALUE4_INT, VALUE1_CHAR,
            VALUE2_SHORT, VALUE3_INT, VALUE4_LONG, &Foo0);

    basic::test::msg::Argument<Case1,
        basic::test::msg::arg::type::Name<0>, // %s
        basic::test::msg::arg::type::Value<2>, // %d
        basic::test::msg::arg::type::Function<4>, // %s
        basic::test::msg::arg::type::Index<3,
            basic::test::msg::arg::type::val::seq::At>, // %d
        basic::test::msg::arg::type::val::Sequence<3>, // %d%d%d%d
        basic::test::msg::arg::type::val::seq::At<3, 2>, // %d
        basic::test::msg::arg::type::param::Name<1>, // %s
        basic::test::msg::arg::type::param::name::At<1, 3>, // %s
        basic::test::msg::arg::Value<5>, // %d
        basic::test::msg::arg::val::Function<8>, // %s
        basic::test::msg::arg::val::Sequence<6>, // %d%d%d%d
        basic::test::msg::arg::val::seq::At<6, 2>, // %d
        basic::test::msg::arg::val::Parameter<7>, // %c%hd%d%ld
        basic::test::msg::arg::val::param::At<7, 3>> arg2; // %ld

    const char * format1 = "%s%d%s%d%d%d%d%d%d%s%s%d%s%d%d%d%d%d%c%hd%d%ld%ld";

    const char * compare_index0_cstr = CHAR_CSTR VALUE1_CSTR FORMAT0_CSTR 
        VALUE1_CSTR VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR VALUE3_CSTR
        CHAR_CSTR CONJ_CSTR SHORT_CSTR CONJ_CSTR INT_CSTR CONJ_CSTR LONG_CSTR
        LONG_CSTR VALUE1_CSTR FORMAT0_CSTR VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR VALUE3_CSTR VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR
        VALUE4_CSTR;

    const char * compare_index3_cstr = CHAR_CSTR VALUE1_CSTR FORMAT0_CSTR
        VALUE4_CSTR VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR VALUE3_CSTR
        CHAR_CSTR CONJ_CSTR SHORT_CSTR CONJ_CSTR INT_CSTR CONJ_CSTR LONG_CSTR
        LONG_CSTR VALUE1_CSTR FORMAT0_CSTR VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR
        VALUE4_CSTR VALUE3_CSTR VALUE1_CSTR VALUE2_CSTR VALUE3_CSTR VALUE4_CSTR
        VALUE4_CSTR;

    arg2.Call<void>(&TestA::Call, testa1, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(compare_index0_cstr, buffer) == 0);

    arg2.Call<int>(&Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(compare_index0_cstr, buffer) == 0);

    arg2.Call<void>(case1_index0, &TestA::Call, testa1, var2,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(compare_index0_cstr, buffer) == 0);

    arg2.Call<int>(case1_index0, &Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(compare_index0_cstr, buffer) == 0);

    arg2.Call<void>(case1_index3, &TestA::Call, testa1, var2,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(compare_index3_cstr, buffer) == 0);

    arg2.Call<int>(case1_index3, &Call, var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size), std::move(format1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(compare_index3_cstr, buffer) == 0);

    delete[] buffer;
}

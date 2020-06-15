#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/CString.h"
#include "test/cstr/Format.h"
#include "test/type/Name.h"
#include "test/type/param/Name.h"

#include <cstdio>
#include <cassert>
#include <cstring>

#define A_CSTR "A"
#define CHAR_CSTR "char"
#define SHORT_CSTR "short"
#define INT_CSTR "int"
#define LONG_CSTR "long"
#define CONJ_CSTR ", "
#define SPACE_CSTR " "
#define COMMA_CSTR ","
#define OPEN_POINTY_CSTR "<"
#define CLOSE_POINTY_CSTR ">"

#define FORMAT_CSTR_CSTR "%s"

template<typename... TArgs>
struct A
{};

template<typename... TArgs>
struct basic::test::type::Name<A<TArgs...>>
{
    static basic::test::CString<char> CStr()
    {
        basic::test::CString<char> param =
            std::move(basic::test::type::param::Name<
                basic::test::type::Parameter<TArgs...>>::CStr());
        return basic::test::cstr::Format<char>(4 + (param.Size() - 1),
            A_CSTR OPEN_POINTY_CSTR FORMAT_CSTR_CSTR CLOSE_POINTY_CSTR, 
            *param);
    }
};

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
    basic::test::CString<char> cstr1  =
        std::move(basic::test::type::Name<A<>>::CStr());
    printf("name : \"%s\"\n", *cstr1);
    assert(strcmp(*cstr1, A_CSTR OPEN_POINTY_CSTR CLOSE_POINTY_CSTR) == 0);

    basic::test::CString<char> cstr2 =
        std::move(basic::test::type::Name<A<char>>::CStr());
    printf("name : \"%s\"\n", *cstr2);
    assert(strcmp(*cstr2, A_CSTR OPEN_POINTY_CSTR CHAR_CSTR 
        CLOSE_POINTY_CSTR) == 0);

    basic::test::CString<char> cstr3 =
        std::move(basic::test::type::Name<A<char, short>>::CStr());
    printf("name : \"%s\"\n", *cstr3);
    assert(strcmp(*cstr3, A_CSTR OPEN_POINTY_CSTR CHAR_CSTR COMMA_CSTR
        SPACE_CSTR SHORT_CSTR CLOSE_POINTY_CSTR) == 0);

    basic::test::CString<char> cstr4 = 
        std::move(basic::test::type::Name<A<char, short, int>>::CStr());
    printf("name : \"%s\"\n", *cstr4);
    assert(strcmp(*cstr4, A_CSTR OPEN_POINTY_CSTR CHAR_CSTR COMMA_CSTR
        SPACE_CSTR SHORT_CSTR COMMA_CSTR SPACE_CSTR INT_CSTR
        CLOSE_POINTY_CSTR) == 0);

    basic::test::CString<char> cstr5 =
        std::move(basic::test::type::Name<A<char, short, int, long>>::CStr());
    printf("name : \"%s\"\n", *cstr5);
    assert(strcmp(*cstr5, A_CSTR OPEN_POINTY_CSTR CHAR_CSTR COMMA_CSTR
        SPACE_CSTR SHORT_CSTR COMMA_CSTR SPACE_CSTR INT_CSTR COMMA_CSTR
        SPACE_CSTR LONG_CSTR CLOSE_POINTY_CSTR) == 0);
}

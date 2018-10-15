#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Name.h"

#include <cstdio>
#include <cassert>
#include <cstring>

struct A {};

#define A_CSTR "A"
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

template<>
struct basic::test::type::Name<A>
{
    template<typename TChar = char>
    static basic::test::CString<TChar> CStr()
    {
        static char _A[] = A_CSTR;
        return {_A};
    }
};

int main()
{
    printf("name : \"%s\"\n", *basic::test::type::Name<A>::CStr());
    assert(strcmp(*basic::test::type::Name<A>::CStr(), A_CSTR) == 0);

    printf("name : \"%s\"\n", *basic::test::type::Name<char>::CStr());
    assert(strcmp(*basic::test::type::Name<char>::CStr(), 
        CHAR_CSTR) == 0);

    printf("name : \"%s\"\n", *basic::test::type::Name<short>::CStr());
    assert(strcmp(*basic::test::type::Name<short>::CStr(), 
        SHORT_CSTR) == 0);

    printf("name : \"%s\"\n", *basic::test::type::Name<int>::CStr());
    assert(strcmp(*basic::test::type::Name<int>::CStr(), 
        INT_CSTR) == 0);

    printf("name : \"%s\"\n", *basic::test::type::Name<long>::CStr());
    assert(strcmp(*basic::test::type::Name<long>::CStr(), 
        LONG_CSTR) == 0);
}

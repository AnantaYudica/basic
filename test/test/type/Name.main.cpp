#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Name.h"

#include <cstdio>

struct A {};

template<>
struct basic::test::type::Name<char>
{
    static basic::test::CString<const char> CStr()
    {
        static char _char[] = "char";
        return {_char};
    }
};

template<>
struct basic::test::type::Name<A>
{
    static basic::test::CString<const char> CStr()
    {
        static char _A[] = "A";
        return {_A};
    }
};

int main()
{
    printf("%s\n", *basic::test::type::Name<char>::CStr());
    printf("%s\n", *basic::test::type::Name<A>::CStr());
}

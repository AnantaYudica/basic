#include "Test.h"

#include "test/type/param/Size.h"

#include <cstdio>
#include <cassert>


template<typename...>
struct Param1{};

int main()
{
    typedef basic::test::type::Parameter<> P0;
    typedef basic::test::type::Parameter<char> P1;
    typedef basic::test::type::Parameter<char, short> P2;
    typedef basic::test::type::Parameter<char, short, int> P3;
    typedef basic::test::type::Parameter<char, short, int, long> P4;

    printf("Size : %zd\n", basic::test::type::param::Size<P0>::Value);
    assert(basic::test::type::param::Size<P0>::Value == 0);
    printf("Size : %zd\n", basic::test::type::param::Size<P1>::Value);
    assert(basic::test::type::param::Size<P1>::Value == 1);
    printf("Size : %zd\n", basic::test::type::param::Size<P2>::Value);
    assert(basic::test::type::param::Size<P2>::Value == 2);
    printf("Size : %zd\n", basic::test::type::param::Size<P3>::Value);
    assert(basic::test::type::param::Size<P3>::Value == 3);
    printf("Size : %zd\n", basic::test::type::param::Size<P4>::Value);
    assert(basic::test::type::param::Size<P4>::Value == 4);

    typedef Param1<> Pa0;
    typedef Param1<char> Pa1;
    typedef Param1<char, short> Pa2;
    typedef Param1<char, short, int> Pa3;
    typedef Param1<char, short, int, long> Pa4;

    printf("Size : %zd\n", basic::test::type::param::Size<Pa0>::Value);
    assert(basic::test::type::param::Size<Pa0>::Value == 0);
    printf("Size : %zd\n", basic::test::type::param::Size<Pa1>::Value);
    assert(basic::test::type::param::Size<Pa1>::Value == 1);
    printf("Size : %zd\n", basic::test::type::param::Size<Pa2>::Value);
    assert(basic::test::type::param::Size<Pa2>::Value == 2);
    printf("Size : %zd\n", basic::test::type::param::Size<Pa3>::Value);
    assert(basic::test::type::param::Size<Pa3>::Value == 3);
    printf("Size : %zd\n", basic::test::type::param::Size<Pa4>::Value);
    assert(basic::test::type::param::Size<Pa4>::Value == 4);

}

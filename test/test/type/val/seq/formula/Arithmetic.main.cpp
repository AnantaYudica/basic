#include "test/type/val/seq/formula/Arithmetic.h"

#include <cstdio>
#include <cassert>

int main()
{
    typedef basic::test::type::val::seq::formula::
        Arithmetic<int, int, 1> Dplus1;

    int start_value = 0;
    int term = 0;
    printf("Dplus1 at %d : %d\n", term, Dplus1::Formula(start_value, term));
    assert(Dplus1::Formula(start_value, term++) == 0);
    printf("Dplus1 at %d : %d\n", term, Dplus1::Formula(start_value, term));
    assert(Dplus1::Formula(start_value, term++) == 1);
    printf("Dplus1 at %d : %d\n", term, Dplus1::Formula(start_value, term));
    assert(Dplus1::Formula(start_value, term++) == 2);
    printf("Dplus1 at %d : %d\n", term, Dplus1::Formula(start_value, term));
    assert(Dplus1::Formula(start_value, term++) == 3);
    printf("Dplus1 at %d : %d\n", term, Dplus1::Formula(start_value, term));
    assert(Dplus1::Formula(start_value, term++) == 4);

    typedef basic::test::type::val::seq::formula::
        Arithmetic<int, int, 4> Dplus4;

    start_value = 0;
    term = 0;

    printf("Dplus4 at %d : %d\n", term, Dplus4::Formula(start_value, term));
    assert(Dplus4::Formula(start_value, term++) == 0);
    printf("Dplus4 at %d : %d\n", term, Dplus4::Formula(start_value, term));
    assert(Dplus4::Formula(start_value, term++) == 4);
    printf("Dplus4 at %d : %d\n", term, Dplus4::Formula(start_value, term));
    assert(Dplus4::Formula(start_value, term++) == 8);
    printf("Dplus4 at %d : %d\n", term, Dplus4::Formula(start_value, term));
    assert(Dplus4::Formula(start_value, term++) == 12);
    printf("Dplus4 at %d : %d\n", term, Dplus4::Formula(start_value, term));
    assert(Dplus4::Formula(start_value, term++) == 16);

    typedef basic::test::type::val::seq::formula::
        Arithmetic<int, int, -1> Dmin1;

    start_value = 0;
    term = 0;

    printf("Dmin1 at %d : %d\n", term, Dmin1::Formula(start_value, term));
    assert(Dmin1::Formula(start_value, term++) == 0);
    printf("Dmin1 at %d : %d\n", term, Dmin1::Formula(start_value, term));
    assert(Dmin1::Formula(start_value, term++) == -1);
    printf("Dmin1 at %d : %d\n", term, Dmin1::Formula(start_value, term));
    assert(Dmin1::Formula(start_value, term++) == -2);
    printf("Dmin1 at %d : %d\n", term, Dmin1::Formula(start_value, term));
    assert(Dmin1::Formula(start_value, term++) == -3);
    printf("Dmin1 at %d : %d\n", term, Dmin1::Formula(start_value, term));
    assert(Dmin1::Formula(start_value, term++) == -4);

    typedef basic::test::type::val::seq::formula::
        Arithmetic<int, int, -4> Dmin4;

    start_value = 0;
    term = 0;

    printf("Dmin4 at %d : %d\n", term, Dmin4::Formula(start_value, term));
    assert(Dmin4::Formula(start_value, term++) == 0);
    printf("Dmin4 at %d : %d\n", term, Dmin4::Formula(start_value, term));
    assert(Dmin4::Formula(start_value, term++) == -4);
    printf("Dmin4 at %d : %d\n", term, Dmin4::Formula(start_value, term));
    assert(Dmin4::Formula(start_value, term++) == -8);
    printf("Dmin4 at %d : %d\n", term, Dmin4::Formula(start_value, term));
    assert(Dmin4::Formula(start_value, term++) == -12);
    printf("Dmin4 at %d : %d\n", term, Dmin4::Formula(start_value, term));
    assert(Dmin4::Formula(start_value, term++) == -16);

}

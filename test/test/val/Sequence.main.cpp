#include "test/val/Sequence.h"

#include <cstdio>
#include <cstring>
#include <cassert>

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
    typedef basic::test::val::Sequence<int, 0> ValSeq0;
    printf("seq0 size : %zd\n", ValSeq0::Size);
    assert(ValSeq0::Size == 0);
    ValSeq0 seq0;

    typedef basic::test::val::Sequence<int, 1> ValSeq1;
    printf("seq1 size : %zd\n", ValSeq1::Size);
    assert(ValSeq1::Size == 1);
    ValSeq1 seq1(VALUE1_INT);
    printf("seq1 at 0 : %d\n", seq1.template At<0>());
    assert(seq1.template At<0>() == VALUE1_INT);

    typedef basic::test::val::Sequence<int, 4> ValSeq4;
    printf("seq2 size : %zd\n", ValSeq4::Size);
    assert(ValSeq4::Size == 4);

    ValSeq4 seq2(VALUE1_INT, VALUE2_INT, VALUE3_INT, VALUE4_INT);
    printf("seq2 at 0 : %d\n", seq2.template At<0>());
    assert(seq2.template At<0>() == VALUE1_INT);
    printf("seq2 at 1 : %d\n", seq2.template At<1>());
    assert(seq2.template At<1>() == VALUE2_INT);
    printf("seq2 at 2 : %d\n", seq2.template At<2>());
    assert(seq2.template At<2>() == VALUE3_INT);
    printf("seq2 at 3 : %d\n", seq2.template At<3>());
    assert(seq2.template At<3>() == VALUE4_INT);

    ValSeq4 seq3(seq2);
    printf("seq3 at 0 : %d\n", seq3.template At<0>());
    assert(seq3.template At<0>() == VALUE1_INT);
    printf("seq3 at 1 : %d\n", seq3.template At<1>());
    assert(seq3.template At<1>() == VALUE2_INT);
    printf("seq3 at 2 : %d\n", seq3.template At<2>());
    assert(seq3.template At<2>() == VALUE3_INT);
    printf("seq3 at 3 : %d\n", seq3.template At<3>());
    assert(seq3.template At<3>() == VALUE4_INT);

    ValSeq4 seq4(std::move(seq2));
    printf("seq4 at 0 : %d\n", seq4.template At<0>());
    assert(seq4.template At<0>() == VALUE1_INT);
    printf("seq4 at 1 : %d\n", seq4.template At<1>());
    assert(seq4.template At<1>() == VALUE2_INT);
    printf("seq4 at 2 : %d\n", seq4.template At<2>());
    assert(seq4.template At<2>() == VALUE3_INT);
    printf("seq4 at 3 : %d\n", seq4.template At<3>());
    assert(seq4.template At<3>() == VALUE4_INT);

    ValSeq4 seq5;
    seq5 = seq3;
    printf("seq5 at 0 : %d\n", seq5.template At<0>());
    assert(seq5.template At<0>() == VALUE1_INT);
    printf("seq5 at 1 : %d\n", seq5.template At<1>());
    assert(seq5.template At<1>() == VALUE2_INT);
    printf("seq5 at 2 : %d\n", seq5.template At<2>());
    assert(seq5.template At<2>() == VALUE3_INT);
    printf("seq5 at 3 : %d\n", seq5.template At<3>());
    assert(seq5.template At<3>() == VALUE4_INT);

    ValSeq4 seq6;
    seq6 = std::move(seq5);
    printf("seq6 at 0 : %d\n", seq6.template At<0>());
    assert(seq6.template At<0>() == VALUE1_INT);
    printf("seq6 at 1 : %d\n", seq6.template At<1>());
    assert(seq6.template At<1>() == VALUE2_INT);
    printf("seq6 at 2 : %d\n", seq6.template At<2>());
    assert(seq6.template At<2>() == VALUE3_INT);
    printf("seq6 at 3 : %d\n", seq6.template At<3>());
    assert(seq6.template At<3>() == VALUE4_INT);

    const ValSeq4 seq7(seq6);
    printf("seq7 at 0 : %d\n", seq7.template At<0>());
    assert(seq7.template At<0>() == VALUE1_INT);
    printf("seq7 at 1 : %d\n", seq7.template At<1>());
    assert(seq7.template At<1>() == VALUE2_INT);
    printf("seq7 at 2 : %d\n", seq7.template At<2>());
    assert(seq7.template At<2>() == VALUE3_INT);
    printf("seq7 at 3 : %d\n", seq7.template At<3>());
    assert(seq7.template At<3>() == VALUE4_INT);
}

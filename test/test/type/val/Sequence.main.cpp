#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/val/Sequence.h"

#include <cstdio>
#include <cassert>

int main()
{
    typedef basic::test::type::val::Sequence<int> ValSeqInt0;
    printf("Size : %zd\n", ValSeqInt0::Size);
    assert(ValSeqInt0::Size == 0);

    typedef basic::test::type::val::Sequence<int, 4> ValSeqInt1;
    ValSeqInt1 i1;
    printf("[0] : %d\n", ValSeqInt1{}.At<0>());
    assert(ValSeqInt1{}.At<0>() == 4);
    printf("[0] : %d\n", i1.At<0>());
    assert(i1.At<0>() == 4);
    printf("Size : %zd\n", ValSeqInt1::Size);
    assert(ValSeqInt1::Size == 1);

    typedef basic::test::type::val::Sequence<int, 4, 6, 11, 14> ValSeqInt4;
    ValSeqInt4 i4;
    printf("[0] : %d\n", ValSeqInt4{}.At<0>());
    assert(ValSeqInt4{}.At<0>() == 4);
    printf("[1] : %d\n", ValSeqInt4{}.At<1>());
    assert(ValSeqInt4{}.At<1>() == 6);
    printf("[2] : %d\n", ValSeqInt4{}.At<2>());
    assert(ValSeqInt4{}.At<2>() == 11);
    printf("[3] : %d\n", ValSeqInt4{}.At<3>());
    assert(ValSeqInt4{}.At<3>() == 14);
    printf("[0] : %d\n", i4.At<0>());
    assert(i4.At<0>() == 4);
    printf("[1] : %d\n", i4.At<1>());
    assert(i4.At<1>() == 6);
    printf("[2] : %d\n", i4.At<2>());
    assert(i4.At<2>() == 11);
    printf("[3] : %d\n", i4.At<3>());
    assert(i4.At<3>() == 14);
    printf("Size : %zd\n", ValSeqInt4::Size);
    assert(ValSeqInt4::Size == 4);
}

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/val/seq/Make.h"
#include "test/type/val/seq/formula/Arithmetic.h"

#include <cstdio>
#include <cassert>

int main()
{
    typedef basic::test::type::val::seq::formula::Arithmetic<int, int, 1>
        IncrementInt;
    typedef typename basic::test::type::val::seq::Make<int, 0, 
        10, IncrementInt>::Type SequenceInt10;

    printf("[0] : %d\n", SequenceInt10{}.At<0>());
    assert(SequenceInt10{}.At<0>() == 0);
    printf("[1] : %d\n", SequenceInt10{}.At<1>());
    assert(SequenceInt10{}.At<1>() == 1);
    printf("[2] : %d\n", SequenceInt10{}.At<2>());
    assert(SequenceInt10{}.At<2>() == 2);
    printf("[3] : %d\n", SequenceInt10{}.At<3>());
    assert(SequenceInt10{}.At<3>() == 3);
    printf("[4] : %d\n", SequenceInt10{}.At<4>());
    assert(SequenceInt10{}.At<4>() == 4);
    printf("[5] : %d\n", SequenceInt10{}.At<5>());
    assert(SequenceInt10{}.At<5>() == 5);
    printf("[6] : %d\n", SequenceInt10{}.At<6>());
    assert(SequenceInt10{}.At<6>() == 6);
    printf("[7] : %d\n", SequenceInt10{}.At<7>());
    assert(SequenceInt10{}.At<7>() == 7);
    printf("[8] : %d\n", SequenceInt10{}.At<8>());
    assert(SequenceInt10{}.At<8>() == 8);
    printf("[9] : %d\n", SequenceInt10{}.At<9>());
    assert(SequenceInt10{}.At<9>() == 9);
    printf("Size : %zi\n", SequenceInt10::Size);
    assert(SequenceInt10::Size == 10);
    
}

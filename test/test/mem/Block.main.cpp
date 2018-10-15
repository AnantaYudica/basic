#define USING_BASIC_TEST_MEMORY
#include "test/mem/Block.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <utility>

int main()
{
    basic::test::mem::Block block1;
    assert(block1.Pointer() == NULL);
    assert(block1.Size() == 0);
    assert(block1.File() == NULL);
    assert(block1.Line() == -1);

    int * int1 = new int(4);
    basic::test::mem::Block block2(int1, sizeof(int));
    assert(block2.Pointer() == int1);
    assert(block2.Size() == sizeof(int));
    assert(block2.File() == NULL);
    assert(block2.Line() == -1);

    int * int2 = new int(14);
    int line = __LINE__ + 1;
    basic::test::mem::Block block3(int2, sizeof(int), __FILE__, line);
    assert(block3.Pointer() == int2);
    assert(block3.Size() == sizeof(int));
    assert(strcmp(block3.File(), __FILE__) == 0);
    assert(block3.Line() == line);

    basic::test::mem::Block block4;
    block4 = std::move(block3);
    assert(block4.Pointer() == int2);
    assert(block4.Size() == sizeof(int));
    assert(strcmp(block4.File(), __FILE__) == 0);
    assert(block4.Line() == line);

    assert(block3.Pointer() == NULL);
    assert(block3.Size() == 0);
    assert(block3.File() == NULL);
    assert(block3.Line() == -1);

    delete int1;
    delete int2;
}

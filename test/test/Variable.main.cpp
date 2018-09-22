#include "test/Variable.h"

#include <iostream>

int main()
{
    basic::test::Variable<> var1;
    basic::test::Variable<int> var2;
    basic::test::Variable<int, char> var3;
    basic::test::Variable<int, char, float> var3;
}

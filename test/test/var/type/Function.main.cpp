#include "test/Variable.h"
#include "test/var/type/Function.h"
#include "test/type/Function.h"

#include <iostream>

void Foo1()
{
    printf("Foo1()\n");
}

int main()
{
    basic::test::Variable<basic::test::type::Function<void(), 
        &Foo1>> var1;
    var1.Get().Call();
    basic::test::Variable<int, basic::test::type::
        Function<void(), &Foo1>> var2;
    basic::test::Variable<basic::test::type::Function<void(), &Foo1>, int,
        basic::test::type::Function<void(), &Foo1>, char> var3;
}

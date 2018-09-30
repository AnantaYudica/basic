#include "test/Variable.h"
#include "test/var/val/Function.h"
#include "test/val/Function.h"

#include <iostream>

void Foo1()
{
    printf("Foo1()\n");
}

int Foo2(int i , char c, float f)
{
    return printf("Foo2(i = %i, c = %c, f = %f)\n", i, c, f);
}

int main()
{
    basic::test::Variable<basic::test::val::Function<void()>> var1(&Foo1);
    var1.Get().Call();
    basic::test::Variable<int, basic::test::val::Function<void()>> var2(&Foo1);
    basic::test::Variable<basic::test::val::Function<int(int, char, float)>, int,
        basic::test::val::Function<void()>, char> var3(&Foo2, &Foo1);
    var3.Get().Call(4, 'a', 3.14);

}

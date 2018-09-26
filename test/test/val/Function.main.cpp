#include "test/val/Function.h"

#include <iostream>

void Foo1()
{
    std::cout << "Foo1()" << std::endl; 
}

int Foo2(int i)
{
    std::cout << "Foo2(i = " << i << ")" << std::endl;
    return i;
}

int main()
{
    std::cout << std::boolalpha;
    basic::test::val::Function<void()> f0;
    std::cout << f0 << std::endl;
    basic::test::val::Function<void()> f1(&Foo1);
    std::cout << f1 << std::endl;
    f1.Call();
    (f1.Get())();
    const auto f2 = f1;
    std::cout << f2 << std::endl;
    f2.Call();
    (f2.Get())();
    auto f3 = std::move(f1);
    std::cout << f3 << std::endl;
    f3.Call();
    (f3.Get())();
    basic::test::val::Function<int(int)> f4(&Foo2);
    std::cout << f4 << std::endl;
    f4.Call(2);
    (f4.Get())(4);
    basic::test::val::Function<int()> f5([](){return Foo2(14);});
    std::cout << f5 << std::endl;
    f5.Call();
    (f5.Get())();
}

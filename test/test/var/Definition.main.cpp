#include "test/var/Definition.h"
#include "test/Variable.h"

#include <iostream>
#include <typeinfo>


int main()
{
    typedef basic::test::Variable<> TVar1;
    typedef basic::test::Variable<int> TVar2;
    typedef basic::test::Variable<int, char> TVar3;
    typedef basic::test::Variable<int, char, float> TVar4;


    std::cout << "TVar1 : " << typeid(TVar1).name() << std::endl;
    std::cout << "TVar1 At 0 : " << typeid(typename basic::test::var::
        Definition<0, TVar1>::Type).name() << std::endl;
        
    std::cout << "TVar2 : " << typeid(TVar2).name() << std::endl;
    std::cout << "TVar2 At 0 : " << typeid(typename basic::test::var::
        Definition<0, TVar2>::Type).name() << std::endl;
    std::cout << "TVar2 At 1 : " << typeid(typename basic::test::var::
        Definition<1, TVar2>::Type).name() << std::endl;
        
    std::cout << "TVar3 : " << typeid(TVar3).name() << std::endl;
    std::cout << "TVar3 At 0 : " << typeid(typename basic::test::var::
        Definition<0, TVar3>::Type).name() << std::endl;
    std::cout << "TVar3 At 1 : " << typeid(typename basic::test::var::
        Definition<1, TVar3>::Type).name() << std::endl;
    std::cout << "TVar3 At 2 : " << typeid(typename basic::test::var::
        Definition<2, TVar3>::Type).name() << std::endl;
        
    std::cout << "TVar4 : " << typeid(TVar4).name() << std::endl;
    std::cout << "TVar4 At 0 : " << typeid(typename basic::test::var::
        Definition<0, TVar4>::Type).name() << std::endl;
    std::cout << "TVar4 At 1 : " << typeid(typename basic::test::var::
        Definition<1, TVar4>::Type).name() << std::endl;
    std::cout << "TVar4 At 2 : " << typeid(typename basic::test::var::
        Definition<2, TVar4>::Type).name() << std::endl;
    std::cout << "TVar4 At 3 : " << typeid(typename basic::test::var::
        Definition<3, TVar4>::Type).name() << std::endl;
}

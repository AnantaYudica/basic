#include "test/Variable.h"
#include "test/var/At.h"
#include "test/var/type/Value.h"
#include "test/var/type/val/Sequence.h"
#include "test/var/Parameter.h"
#include "test/var/Value.h"
#include "test/var/val/Sequence.h"

#include <iostream>
#include <typeinfo>


int main()
{
    typedef basic::test::Variable<
        int, 
        basic::test::type::Value<int, 4>,
        basic::test::type::val::Sequence<int, 1, 2, 3, 4>,
        basic::test::Parameter<int, int, int>,
        basic::test::Value<int>,
        basic::test::val::Sequence<int,2>> Var1;

    Var1 var1(4, 6, 14, 1, 4, 11);
    std::cout << "var::At<1, Var1> Variable : " << 
        basic::test::var::At<1>(var1).Get().Get() << std::endl;

    std::cout << "var::At<2, Var1> : { " << std::endl;
    std::cout << basic::test::var::At<2>(var1).Get().At<0>() << std::endl;
    std::cout << basic::test::var::At<2>(var1).Get().At<1>() << std::endl;
    std::cout << basic::test::var::At<2>(var1).Get().At<2>() << std::endl;
    std::cout << basic::test::var::At<2>(var1).Get().At<3>() <<
        "}" << std::endl;
    
    std::cout << "var::At<3, Var1> : { " << std::endl;
    std::cout << basic::test::var::At<3>(var1).Get().At<0>() << std::endl;
    std::cout << basic::test::var::At<3>(var1).Get().At<1>() << std::endl;
    std::cout << basic::test::var::At<3>(var1).Get().At<2>() <<
        "}" << std::endl;
    
    std::cout << "var::At<4, Var1> Variable : " << 
        basic::test::var::At<4>(var1).Get().Get() << std::endl;
    
    std::cout << "var::At<5, Var1> : { " << std::endl;
    std::cout << basic::test::var::At<5>(var1).Get().At<0>() << std::endl;
    std::cout << basic::test::var::At<5>(var1).Get().At<1>() <<
        "}" << std::endl;

}
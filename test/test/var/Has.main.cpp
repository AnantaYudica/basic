#include "test/var/Has.h"
#include "test/Variable.h"
#include "test/var/Value.h"
#include "test/var/Parameter.h"
#include "test/var/type/Value.h"
#include "test/var/type/val/Sequence.h"
#include "test/var/val/Sequence.h"

#include <iostream>
#include <typeinfo>

int main()
{
    typedef basic::test::Variable<
        int, 
        basic::test::type::Value<int, 4>,
        basic::test::type::val::Sequence<int, 1, 2, 3, 4>,
        basic::test::Parameter<basic::test::type::Parameter<int, int, int>>,
        basic::test::Value<int>,
        basic::test::val::Sequence<int,2>> Var1;
    std::cout << std::boolalpha;
    std::cout << "Var1 at 0 : { " << std::endl;
    std::cout << " Value : ";
    std::cout << basic::test::var::Has<0, Var1>::Value << std::endl;
    std::cout << " LValue : ";
    std::cout << basic::test::var::Has<0, Var1>::LValue << std::endl;
    std::cout << " RValue : ";
    std::cout << basic::test::var::Has<0, Var1>::RValue << "}" << std::endl;
    
    std::cout << "Var1 at 1 : { " << std::endl;
    std::cout << " Value : ";
    std::cout << basic::test::var::Has<1, Var1>::Value << std::endl;
    std::cout << " LValue : ";
    std::cout << basic::test::var::Has<1, Var1>::LValue << std::endl;
    std::cout << " RValue : ";
    std::cout << basic::test::var::Has<1, Var1>::RValue << "}" << std::endl;

    std::cout << "Var1 at 2 : { " << std::endl;
    std::cout << " Value : ";
    std::cout << basic::test::var::Has<2, Var1>::Value << std::endl;
    std::cout << " LValue : ";
    std::cout << basic::test::var::Has<2, Var1>::LValue << std::endl;
    std::cout << " RValue : ";
    std::cout << basic::test::var::Has<2, Var1>::RValue << "}" << std::endl;

    std::cout << "Var1 at 3 : { " << std::endl;
    std::cout << " Value : ";
    std::cout << basic::test::var::Has<3, Var1>::Value << std::endl;
    std::cout << " LValue : ";
    std::cout << basic::test::var::Has<3, Var1>::LValue << std::endl;
    std::cout << " RValue : ";
    std::cout << basic::test::var::Has<3, Var1>::RValue << "}" << std::endl;
    
    std::cout << "Var1 at 4 : { " << std::endl;
    std::cout << " Value : ";
    std::cout << basic::test::var::Has<4, Var1>::Value << std::endl;
    std::cout << " LValue : ";
    std::cout << basic::test::var::Has<4, Var1>::LValue << std::endl;
    std::cout << " RValue : ";
    std::cout << basic::test::var::Has<4, Var1>::RValue << "}" << std::endl;
    
    std::cout << "Var1 at 5 : { " << std::endl;
    std::cout << " Value : ";
    std::cout << basic::test::var::Has<5, Var1>::Value << std::endl;
    std::cout << " LValue : ";
    std::cout << basic::test::var::Has<5, Var1>::LValue << std::endl;
    std::cout << " RValue : ";
    std::cout << basic::test::var::Has<5, Var1>::RValue << "}" << std::endl;
}

#include "test/var/Definition.h"

#include <iostream>


int main()
{
    std::cout << std::boolalpha;
    std::cout << basic::test::var::Definition<0, int, 
        char, short>::has_value << std::endl;
    std::cout << basic::test::var::Definition<1, int, 
        char, short>::has_value << std::endl;
    std::cout << basic::test::var::Definition<2, int, 
        char, short>::has_value << std::endl;
    std::cout << basic::test::var::Definition<3, int, 
        char, short>::has_value << std::endl;
    
    std::cout << basic::test::var::Definition<0, int, 
        basic::test::var::Value<char>, short>::has_value << std::endl;
    std::cout << basic::test::var::Definition<1, int, 
        basic::test::var::Value<char>, short>::has_value << std::endl;
    std::cout << basic::test::var::Definition<2, int, 
        basic::test::var::Value<char>, short>::has_value << std::endl;
    std::cout << basic::test::var::Definition<3, int, 
        basic::test::var::Value<char>, short>::has_value << std::endl;

    typename basic::test::var::Definition<1, int, 
        basic::test::var::Value<char>, short>::type val_def = 'a';

    std::cout << val_def << std::endl;
}

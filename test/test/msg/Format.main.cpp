#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BasicTestConstruct;

#include "test/msg/Format.h"

#include <iostream>

int main()
{
    basic::test::msg::Format f1("format : %s");

    std::cout << f1.Size() << std::endl;
    std::cout << f1.Value() << std::endl;

    basic::test::msg::Format f2(f1, f1.Size() + 4, "%s::%s");
    std::cout << f2.Size() << std::endl;
    std::cout << f2.Value() << std::endl;

    basic::test::msg::Format f3(f2, f1.Size() + 25, "Type<%s>", "template Foo1<%s>(%s)");
    std::cout << f3.Size() << std::endl;
    std::cout << f3.Value() << std::endl;

    basic::test::msg::Format f4("format : %d");
    std::cout << f4.Size() << std::endl;
    std::cout << f4.Value() << std::endl;

    basic::test::msg::Format f5(f4, f4.Size() + 10, 4);
    std::cout << f5.Size() << std::endl;
    std::cout << f5.Value() << std::endl;

    basic::test::msg::Format f6(f3);
    std::cout << f6.Size() << std::endl;
    std::cout << f6.Value() << std::endl;

    basic::test::msg::Format f7(std::move(f6));
    std::cout << f7.Size() << std::endl;
    std::cout << f7.Value() << std::endl;
    std::cout << f6.Size() << std::endl;
    if (f6)
        std::cout << f6.Value() << std::endl;

    basic::test::msg::Format f8("test");
    std::cout << f8.Size() << std::endl;
    std::cout << f8.Value() << std::endl;
    f8 = f3;
    std::cout << f8.Size() << std::endl;
    std::cout << f8.Value() << std::endl;

    basic::test::msg::Format f9;
    f9 = std::move(f8);
    std::cout << f8.Size() << std::endl;
    if (f8)
        std::cout << f8.Value() << std::endl;
    std::cout << f9.Size() << std::endl;
    std::cout << f9.Value() << std::endl;
    
    basic::test::msg::Format f10 ("testddd : %d", 14);
    std::cout << f10.Size() << std::endl;
    std::cout << f10.Value() << std::endl;

}

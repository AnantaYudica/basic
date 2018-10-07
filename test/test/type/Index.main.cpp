#include "Test.h"

#include "test/type/Index.h"
#include <cstdio>
#include <typeinfo>

int main()
{
    typedef basic::test::type::Index<int, 2> Int_At2;
    printf("%s %zd", typeid(typename Int_At2::Type).name(), 
        Int_At2::Value);
}

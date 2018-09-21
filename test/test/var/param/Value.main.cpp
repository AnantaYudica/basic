#include "test/var/param/Value.h"

#include <cstdio>
#include <typeinfo>

void PrintEmpty()
{
    printf("func print(empty)\n");
}

void Print(const int& i, const char* cstr, float f)
{
    printf("func print(i = %d, cstr = %s, f = %f)\n", i, cstr, f);
}

struct A
{
    A()
    {
        printf("constructor A (empty)\n");  
    }
    A(const int& i, const char* cstr, const float& f)
    {
        printf("constructor A(i = %d, cstr = %s, f = %f)\n", i, cstr, f);
    }
    void Print(int i, const char* cstr, const float& f)
    {
        
        printf("A::Print(i = %d, cstr = %s, f = %f)\n", i, cstr, f);
    }
    void PrintEmpty()
    {
        printf("A::Print(empty)\n");
    }
};

int main()
{
    
    typedef basic::test::var::param::Value<
        basic::test::type::Parameter<>> ParamVal0;
    typedef basic::test::var::param::Value<
        basic::test::type::Parameter<int, const char*, float>> ParamVal1;

    A a;
    ParamVal0 paramVal0;
    paramVal0.Fill<void>(&PrintEmpty);
    paramVal0.Fill<void>(&A::PrintEmpty, a);
    paramVal0.Fill<void>(&A::PrintEmpty, &a);
    A a0 = paramVal0.Fill<A>();

    ParamVal1 paramVal(1, "test", 3.14);
    paramVal.Fill<void>(&Print);
    paramVal.Fill<void>(&A::Print, a);
    paramVal.Fill<void>(&A::Print, &a);
    A a1 = paramVal.Fill<A>();

    printf("i = %d\n", paramVal.Get<0>());
    printf("cstr = %s\n", paramVal.Get<1>());
    printf("f = %f\n", paramVal.Get<2>());
    
    paramVal.Get<0>() = 4;
    paramVal.Get<2>() = (float)(22.0 / 7.0);

    printf("i = %d\n", paramVal.Get<0>());
    printf("cstr = %s\n", paramVal.Get<1>());
    printf("f = %f\n", paramVal.Get<2>());

    const ParamVal1 cpyParamVal1 = paramVal; 
    printf("i = %d\n", cpyParamVal1.Get<0>());
    printf("cstr = %s\n", cpyParamVal1.Get<1>());
    printf("f = %f\n", cpyParamVal1.Get<2>());

    const ParamVal1 cpyParamVal2 = std::move(paramVal); 
    printf("i = %d\n", cpyParamVal1.Get<0>());
    printf("cstr = %s\n", cpyParamVal1.Get<1>());
    printf("f = %f\n", cpyParamVal1.Get<2>());
    

}

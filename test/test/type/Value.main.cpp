#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Value.h"

#include <cstdio>
#include <cassert>

#define VALUE1_INT 4
#define VALUE1_CHAR '4'
#define VALUE1_CSTR "4"
#define VALUE2_INT 14
#define VALUE2_SHORT short(14)
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_INT 114
#define VALUE4_LONG 114
#define VALUE4_CSTR "114"

template<char val>
struct CharConstant
{
    static constexpr char Value = val;
};

template<short val>
struct ShortConstant
{
    static constexpr short Value = val;
};

template<int val>
struct IntConstant
{
    static constexpr int Value = val;
};

template<long val>
struct LongConstant
{
    static constexpr long Value = val;
};

int main()
{
    typedef basic::test::type::Value<char, VALUE1_CHAR> Value1;
    Value1 value1;
    printf("value1 : %c\n", Value1{}.Get());
    assert(value1.Get() == VALUE1_CHAR);
    assert(Value1{}.Get() == VALUE1_CHAR);
    assert(CharConstant<Value1{}.Get()>::Value == VALUE1_CHAR);

    typedef basic::test::type::Value<short, VALUE2_SHORT> Value2;
    Value2 value2;
    printf("value2 : %hd\n", Value2{}.Get());
    assert(value2.Get() == VALUE2_SHORT);
    assert(Value2{}.Get() == VALUE2_SHORT);
    assert(ShortConstant<Value2{}.Get()>::Value == VALUE2_SHORT);

    typedef basic::test::type::Value<int, VALUE3_INT> Value3;
    Value3 value3;
    printf("value3 : %d\n", Value3{}.Get());
    assert(value3.Get() == VALUE3_INT);
    assert(Value3{}.Get() == VALUE3_INT);
    assert(IntConstant<Value3{}.Get()>::Value == VALUE3_INT);

    typedef basic::test::type::Value<long, VALUE4_LONG> Value4;
    Value4 value4;
    printf("value4 : %ld\n", Value4{}.Get());
    assert(value4.Get() == VALUE4_LONG);
    assert(Value4{}.Get() == VALUE4_LONG);
    assert(LongConstant<Value4{}.Get()>::Value == VALUE4_LONG);
    
}

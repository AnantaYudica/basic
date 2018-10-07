#include "Test.h"

#include "test/type/param/Function.h"

#include <cstdio>

typedef basic::test::type::Parameter<int, char, float> P1;

void Print(int i, char c, float f)
{
    printf("%d, %c, %f\n", i, c, f);
}

int main()
{
    typedef basic::test::type::param::Function<P1> PF1;

    PF1::Call<void>(&Print, 1, 'a', 3.14f);

}

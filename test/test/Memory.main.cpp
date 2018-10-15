#define USING_BASIC_TEST_MEMORY
#include "test/Memory.h"

#include <cstdio>
#include <cassert>
#include <utility>

struct Output
{
    template<typename... TArgs>
    void Debug(const char* format, TArgs&&... args)
    {
        printf(format, std::forward<TArgs>(args)...);
    }
    template<typename... TArgs>
    void Error(const char* format, TArgs&&... args)
    {
        printf(format, std::forward<TArgs>(args)...);
    }
};

typedef basic::test::Memory<Output> Memory;

int main()
{
    Output out;
    Memory mem1(out);

    char ch1;

    mem1.Register(&ch1, sizeof(char));
    assert(mem1.HasRegister(&ch1) == true);
    mem1.Unregister(&ch1);
    assert(mem1.HasRegister(&ch1) == false);

    Memory mem2(std::move(mem1));
    mem2.Set(out);

    mem2.Register(&ch1, sizeof(char), __FILE__, __LINE__);
    assert(mem2.HasRegister(&ch1) == true);
    mem2.Unregister(&ch1);
    assert(mem2.HasRegister(&ch1) == false);
}

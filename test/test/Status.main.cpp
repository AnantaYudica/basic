#include "test/Status.h"

#include <cstdlib>
#include <cassert>

int main()
{
    basic::test::Status status1;
    assert(status1.Get() == EXIT_SUCCESS);
    status1.Error();
    assert(status1.Get() == EXIT_FAILURE);
}

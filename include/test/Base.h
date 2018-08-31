#ifndef BASIC_TEST_BASE_H_
#define BASIC_TEST_BASE_H_

namespace basic
{
namespace test
{

struct Base
{
    virtual ~Base() {};
    virtual void Test() = 0;
};

} //!test

} //!basic

#endif //!BASIC_TEST_BASE_H_

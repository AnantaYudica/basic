#ifndef BASIC_TEST_MSG_BASE_H_
#define BASIC_TEST_MSG_BASE_H_

#include "Format.h"

namespace basic
{
namespace test
{
namespace msg
{

template<typename TCaseId>
class Base
{
public:
    virtual ~Base() {}
    virtual const Format& Info(TCaseId&&) const = 0;
    virtual const Format& Debug(TCaseId&&) const = 0;
    virtual const Format& Error(TCaseId&&) const = 0;
};

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_BASE_H_
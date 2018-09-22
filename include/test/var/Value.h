#ifndef BASIC_TEST_VAR_VALUE_H_
#define BASIC_TEST_VAR_VALUE_H_

// todo : Remove when next release
#ifndef REMOVED_DEPRECATED
#define REMOVED_DEPRECATED
#endif //!REMOVED_DEPRECATED

#include "../Value.h"

namespace basic
{
namespace test
{
namespace var
{

template<typename T>
using Value = basic::test::Value<T>;

} //!var

} //!test

} //!basic

// end todo

#endif //!BASIC_TEST_VAR_VALUE_H_
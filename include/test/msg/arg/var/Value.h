#ifndef BASIC_TEST_MSG_ARG_VAR_VALUE_H_
#define BASIC_TEST_MSG_ARG_VAR_VALUE_H_

// todo : Remove when next release
#ifndef REMOVED_DEPRECATED
#define REMOVED_DEPRECATED
#endif //!REMOVED_DEPRECATED

#include "../Value.h"

namespace basic
{
namespace test
{
namespace msg
{
namespace arg
{
namespace var
{

template<std::size_t I>
using Value = basic::test::msg::arg::Value<I>;

} //!val

} //!arg

} //!msg

} //!test

} //!basic

// end todo

#endif //!BASIC_TEST_MSG_ARG_VAR_VALUE_H_

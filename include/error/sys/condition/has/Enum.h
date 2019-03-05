#ifndef BASIC_ERROR_SYS_CONDITION_HAS_ENUM_H_
#define BASIC_ERROR_SYS_CONDITION_HAS_ENUM_H_

namespace basic
{
namespace error
{
namespace sys
{
namespace condition
{
namespace has
{

template<typename TConditionEnum>
struct Enum
{
    static constexpr bool Value = false;
};

} //!has

} //!condition

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_CONDITION_HAS_ENUM_H_

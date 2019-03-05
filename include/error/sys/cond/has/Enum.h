#ifndef BASIC_ERROR_SYS_COND_HAS_ENUM_H_
#define BASIC_ERROR_SYS_COND_HAS_ENUM_H_

namespace basic
{
namespace error
{
namespace sys
{
namespace cond
{
namespace has
{

template<typename TConditionEnum>
struct Enum
{
    static constexpr bool Value = false;
};

} //!has

} //!cond

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_COND_HAS_ENUM_H_

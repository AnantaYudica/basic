#ifndef BASIC_ERR_SYS_COND_HAS_ENUM_H_
#define BASIC_ERR_SYS_COND_HAS_ENUM_H_

namespace basic
{
namespace err
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

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_COND_HAS_ENUM_H_

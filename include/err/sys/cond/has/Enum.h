#ifndef BASIC_ERR_SYS_COND_HAS_ENUM_H_
#define BASIC_ERR_SYS_COND_HAS_ENUM_H_

#include "../../categ/Generic.h"
#include "../../categ/Future.h"

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

template<>
struct Enum<std::future_errc>
{
    static constexpr bool Value = true;
};

template<>
struct Enum<std::errc>
{
    static constexpr bool Value = true;
};

} //!has

} //!cond

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_COND_HAS_ENUM_H_

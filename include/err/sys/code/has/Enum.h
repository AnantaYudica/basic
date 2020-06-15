#ifndef BASIC_ERR_SYS_CODE_HAS_ENUM_H_
#define BASIC_ERR_SYS_CODE_HAS_ENUM_H_

#include "../../categ/Generic.h"
#include "../../categ/Future.h"

namespace basic
{
namespace err
{
namespace sys
{
namespace code
{
namespace has
{

template<typename TCodeEnum>
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

} //!code

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_CODE_HAS_ENUM_H_

#ifndef BASIC_ERROR_SYS_CODE_HAS_ENUM_H_
#define BASIC_ERROR_SYS_CODE_HAS_ENUM_H_

namespace basic
{
namespace error
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

} //!has

} //!code

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_CODE_HAS_ENUM_H_

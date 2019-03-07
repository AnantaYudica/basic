#ifndef BASIC_ERR_SYS_CODE_HAS_ENUM_H_
#define BASIC_ERR_SYS_CODE_HAS_ENUM_H_

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

} //!has

} //!code

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_CODE_HAS_ENUM_H_

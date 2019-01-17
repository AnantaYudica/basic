#ifndef BASIC_ERROR_SYSTEM_CODE_HAS_ENUM_H_
#define BASIC_ERROR_SYSTEM_CODE_HAS_ENUM_H_

namespace basic
{
namespace error
{
namespace system
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

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CODE_HAS_ENUM_H_

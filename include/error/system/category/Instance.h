#ifndef BASIC_ERROR_SYSTEM_CATEGORY_INSTANCE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_INSTANCE_H_

#include "has/st/mmbr/func/Instance.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

template<typename TCategoryTrait>
typename std::enable_if<has::st::mmbr::func::Instance<TCategoryTrait>::Value,
    TCategoryTrait>::type Instance() noexcept
{
    return TCategoryTrait::Instance();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::st::mmbr::func::Instance<TCategoryTrait>::Value,
    TCategoryTrait>::type Instance() noexcept
{
    return {};
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_INSTANCE_H_

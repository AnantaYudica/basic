#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_INSTANCE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_INSTANCE_H_

#include "has/st/mmbr/func/Instance.h"
#include "../Category.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
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

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_INSTANCE_H_

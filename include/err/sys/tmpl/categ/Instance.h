#ifndef BASIC_ERR_SYS_TMPL_CATEG_INSTANCE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_INSTANCE_H_

#include "has/st/mmbr/func/Instance.h"

#include <type_traits>
#include <utility>

namespace basic
{
namespace err
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
typename std::enable_if<has::st::mmbr::func::Instance<TCategoryTrait>::Value,
    TCategoryTrait>::type Instance() noexcept
{
    return std::move(TCategoryTrait::Instance());
}

template<typename TCategoryTrait>
typename std::enable_if<!has::st::mmbr::func::Instance<TCategoryTrait>::Value,
    TCategoryTrait>::type Instance() noexcept
{
    return std::move(TCategoryTrait{});
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_INSTANCE_H_

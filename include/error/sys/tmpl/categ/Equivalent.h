#ifndef BASIC_ERROR_SYS_TMPL_CATEG_EQUIVALENT_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_EQUIVALENT_H_

#include "has/mmbr/func/Equivalent.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait, typename TCode, typename TCondition>
typename std::enable_if<has::mmbr::func::Equivalent<TCategoryTrait,
    TCode, TCondition>::Value, bool>::type  
Equivalent(const TCategoryTrait& categ_trait, const TCode& code,
    const TCondition& cond) noexcept
{
    return categ_trait.Equivalent(code, cond);
}

template<typename TCategoryTrait, typename TCode, typename TCondition>
typename std::enable_if<!has::mmbr::func::Equivalent<TCategoryTrait,
    TCode, TCondition>::Value, bool>::type   
Equivalent(const TCategoryTrait& categ_trait, const TCode& code,
    const TCondition& cond) noexcept
{
    return false;
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic


#endif //!BASIC_ERROR_SYS_TMPL_CATEG_EQUIVALENT_H_

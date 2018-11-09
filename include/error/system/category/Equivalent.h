#ifndef BASIC_ERROR_SYSTEM_CATEGORY_EQUIVALENT_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_EQUIVALENT_H_

#include "has/mmbr/func/Equivalent.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

template<typename TCategoryTrait, typename TCode, typename TCondition>
typename std::enable_if<has::mmbr::func::Equivalent<TCategoryTrait,
    TCode, TCondition>::Value, bool>::type  
Equivalent(const TCategoryTrait& category_trait, const TCode& code,
    const TCondition& condition)
{
    return category_trait.Equivalent(code, condition);
}

template<typename TCategoryTrait, typename TCode, typename TCondition>
typename std::enable_if<!has::mmbr::func::Equivalent<TCategoryTrait,
    TCode, TCondition>::Value, bool>::type   
Equivalent(const TCategoryTrait& category_trait, const TCode& code,
    const TCondition& condition)
{
    return false;
}

} //!category

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_CATEGORY_EQUIVALENT_H_

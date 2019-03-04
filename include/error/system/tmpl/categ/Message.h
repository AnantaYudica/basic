#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_MESSAGE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_MESSAGE_H_

#include "../../../msg/String.h"
#include "msg/tag/Code.h"
#include "msg/tag/Condition.h"
#include "has/mmbr/func/Message.h"

#include <type_traits>
#include <utility>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace categ
{

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<has::mmbr::func::Message<TCategoryTrait,
    error::msg::String, TTag, TValue>::Value, error::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<has::mmbr::func::Message<TCategoryTrait,
    error::msg::String, TValue>::Value, error::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value) noexcept
{
    return std::move(categ_trait.Message(value));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<!has::mmbr::func::Message<TCategoryTrait,
    error::msg::String, TTag, TValue>::Value && !has::mmbr::func::
    Message<TCategoryTrait, error::msg::String, TValue>::Value, 
    error::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value) noexcept
{
    return std::move(error::msg::String{});
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_MESSAGE_H_

#ifndef BASIC_ERR_SYS_TMPL_CATEG_MESSAGE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_MESSAGE_H_

#include "../../../msg/String.h"
#include "msg/tag/Code.h"
#include "msg/tag/Condition.h"
#include "has/mmbr/func/Message.h"

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

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<has::mmbr::func::Message<TCategoryTrait,
    err::msg::String, TTag, TValue>::Value, err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<has::mmbr::func::Message<TCategoryTrait,
    err::msg::String, TValue>::Value, err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value) noexcept
{
    return std::move(categ_trait.Message(value));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<!has::mmbr::func::Message<TCategoryTrait,
    err::msg::String, TTag, TValue>::Value && !has::mmbr::func::
    Message<TCategoryTrait, err::msg::String, TValue>::Value, 
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value) noexcept
{
    return std::move(err::msg::String{});
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic


#endif //!BASIC_ERR_SYS_TMPL_CATEG_MESSAGE_H_

#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_MESSAGE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_MESSAGE_H_

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
namespace category
{

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<has::mmbr::func::Message<TCategoryTrait,
    error::msg::String, TTag, TValue>::Value, error::msg::String>::type  
Message(const TCategoryTrait & category_trait, const TValue & value) noexcept
{
    return std::move(category_trait.Message(TTag{}, value));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<!has::mmbr::func::Message<TCategoryTrait,
    error::msg::String, TTag, TValue>::Value, error::msg::String>::type  
Message(const TCategoryTrait & category_trait, const TValue & value) noexcept
{
    return std::move(msg::String{});
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_MESSAGE_H_

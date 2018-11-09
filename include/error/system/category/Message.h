#ifndef BASIC_ERROR_SYSTEM_CATEGORY_MESSAGE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_MESSAGE_H_

#include "has/mmbr/func/Message.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

template<typename TCategoryTrait, typename TValue>
typename std::enable_if<has::mmbr::func::Message<TCategoryTrait,
    TValue>::Value, const char *>::type  
Message(const TCategoryTrait& category_trait, const TValue& value) noexcept
{
    return category_trait.Message(value);
}

template<typename TCategoryTrait, typename TValue>
typename std::enable_if<!has::mmbr::func::Message<TCategoryTrait,
    TValue>::Value, const char *>::type  
Message(const TCategoryTrait& category_trait, const TValue& value) noexcept
{
    return "";
}

} //!category

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_CATEGORY_MESSAGE_H_

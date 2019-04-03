#ifndef BASIC_ERR_SYS_TMPL_CATEG_MESSAGE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_MESSAGE_H_

#include "../../../msg/String.h"
#include "msg/tag/Code.h"
#include "msg/tag/Condition.h"
#include "has/mmbr/func/Message.h"
#include "../../Condition.defn.h"
#include "../../Code.defn.h"
#include "../../../defn/type/sys/cond/Value.h"
#include "../../../defn/type/sys/code/Value.h"
#include "../Category.defn.h"

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
inline typename std::enable_if<
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, TValue>::Value,
        err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(value));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        TValue>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, TTag,
        TValue>::Value, err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const TValue & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Code>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::code::Value>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Code, err::defn::type::sys::code::Value>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, 
    const err::defn::type::sys::code::Value & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Condition>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Condition, err::defn::type::sys::cond::Value>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, 
    const err::defn::type::sys::cond::Value & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Code>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::code::Value>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Code, err::defn::type::sys::code::Value>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Code>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, 
    const err::defn::type::sys::code::Value & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(sys::Code{value, categ_instance}));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Condition>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Condition, err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Condition>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, 
    const err::defn::type::sys::cond::Value & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(sys::Condition{value, 
        categ_instance}));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Code>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::code::Value>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const sys::Code & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(value.Value()));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Condition>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::cond::Value>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const sys::Condition & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(value.Value()));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Code>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Code>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::code::Value>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Code, err::defn::type::sys::code::Value>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const sys::Code & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value.Value()));
}

template<typename TTag, typename TCategoryTrait>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Condition>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Condition>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Condition, err::defn::type::sys::cond::Value>::Value,
    err::msg::String>::type  
Message(const TCategoryTrait & categ_trait, const sys::Condition & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.Message(TTag{}, value.Value()));
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Code>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Code>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::code::Value>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Code, err::defn::type::sys::code::Value>::Value,
    err::msg::String>::type
Message(const TCategoryTrait & categ_trait, const TValue & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(err::msg::String{});
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<
    std::is_same<TTag, msg::tag::Condition>::value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        sys::Condition>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Message<TCategoryTrait, err::msg::String, 
        msg::tag::Condition, err::defn::type::sys::cond::Value>::Value,
    err::msg::String>::type
Message(const TCategoryTrait & categ_trait, const TValue & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(err::msg::String{});
}

template<typename TTag, typename TCategoryTrait, typename TValue>
inline typename std::enable_if<
    !std::is_same<TTag, msg::tag::Code>::value &&
    !std::is_same<TTag, msg::tag::Condition>::value,
    err::msg::String>::type
Message(const TCategoryTrait & categ_trait, const TValue & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(err::msg::String{});
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_MESSAGE_H_

#ifndef BASIC_ERR_SYS_TMPL_CATEG_EQUIVALENT_H_
#define BASIC_ERR_SYS_TMPL_CATEG_EQUIVALENT_H_

#include "../Category.defn.h"

#include "has/mmbr/func/Equivalent.h"
#include "../../Condition.defn.h"
#include "../../Code.defn.h"
#include "../../../defn/type/sys/cond/Value.h"
#include "../../../defn/type/sys/code/Value.h"

#include <type_traits>

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

template<typename TCategoryTrait, typename TCode, typename TCondition>
typename std::enable_if<has::mmbr::func::Equivalent<TCategoryTrait,
    TCode, TCondition>::Value, bool>::type  
Equivalent(const TCategoryTrait& categ_trait, 
    const TCode& code, const TCondition& cond, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const sys::Code & code, const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const sys::Code & code, const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const sys::Code & code, const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, 
        sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), 
        sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, cond);
}


template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, 
        cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, 
        sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait, typename TCode, typename TCondition>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type   
Equivalent(const TCategoryTrait& categ_trait,
    const TCode& code, const TCondition& cond, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return false;
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic


#endif //!BASIC_ERR_SYS_TMPL_CATEG_EQUIVALENT_H_

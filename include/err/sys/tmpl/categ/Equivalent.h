#ifndef BASIC_ERR_SYS_TMPL_CATEG_EQUIVALENT_H_
#define BASIC_ERR_SYS_TMPL_CATEG_EQUIVALENT_H_

#include "../Category.defn.h"

#include "has/mmbr/func/Equivalent.h"
#include "has/mmbr/defn/type/CodeEnum.h"
#include "has/mmbr/defn/type/ConditionEnum.h"
#include "../../Condition.defn.h"
#include "../../Code.defn.h"
#include "../../../defn/type/sys/cond/Value.h"
#include "../../../defn/type/sys/code/Value.h"
#include "defn/type/code/set/Value.h"
#include "defn/type/cond/set/Value.h"
#include "ToCodeValue.h"
#include "ToConditionValue.h"

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
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const sys::Code & code, const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return code.Value() == cond.Value();
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
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return code.Value() == cond;
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
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return code == cond.Value();
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

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return code == cond;
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, ToConditionValue(categ_trait, 
        cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value, 
    bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value  &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, categ::defn::type::cond::set::Value<TCategoryTrait>>::Value, 
    bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, cond);
}


template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value  &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), 
        ToConditionValue(categ_trait, cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value  &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), 
        sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value  &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, 
        ToConditionValue(categ_trait, cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value  &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, 
        sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value  &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return ToCodeValue(categ_trait, code) == 
        ToConditionValue(categ_trait, cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), 
        sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, 
        sys::Condition{cond, categ_instance});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const err::defn::type::sys::cond::Value & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return ToCodeValue(categ_trait, code) == cond;
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(ToCodeValue(categ_trait, code), 
        cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code}, cond.Value());
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        categ::defn::type::code::set::Value<TCategoryTrait>,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        sys::Code, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const categ::defn::type::code::set::Value<TCategoryTrait> & code, 
    const sys::Condition & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return ToCodeValue(categ_trait, code) == cond.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value, 
    bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, 
        cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, 
    bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, ToConditionValue(categ_trait, 
        cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value, 
    bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, 
        ToConditionValue(categ_trait, cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(sys::Code{code, categ_instance}, 
        sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait,
        err::defn::type::sys::code::Value, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        sys::Code, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return code == ToConditionValue(categ_trait, cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), cond);
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, 
        ToConditionValue(categ_trait, cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        err::defn::type::sys::cond::Value>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code, sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), 
        ToConditionValue(categ_trait, cond));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
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
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return categ_trait.Equivalent(code.Value(), sys::Condition{cond});
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        categ::defn::type::cond::set::Value<TCategoryTrait>>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, sys::Code, 
        sys::Condition>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value,
        err::defn::type::sys::cond::Value>::Value &&
    !has::mmbr::func::Equivalent<TCategoryTrait, 
        err::defn::type::sys::code::Value, sys::Condition>::Value, bool>::type
Equivalent(const TCategoryTrait& categ_trait, const sys::Code & code, 
    const categ::defn::type::cond::set::Value<TCategoryTrait> & cond,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return code.Value() == ToConditionValue(categ_trait, cond);
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_EQUIVALENT_H_

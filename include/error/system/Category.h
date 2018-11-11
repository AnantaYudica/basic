#ifndef BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_
#define BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

namespace basic
{
namespace error
{
namespace system
{

template<typename TCategoryTrait>
class Category;

} //!system

} //!error

} //!basic

#ifndef BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_

#include "Code.h"

#endif //!BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_

#include "Condition.h"

#endif //!BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_

#include "Category.h"

#else //else BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_SYSTEM_CATEGORY_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_H_

#include "../../Error.h"
#include "defn/type/category/Value.h"
#include "defn/type/Code/Value.h"
#include "defn/type/Condition/Value.h"
#include "category/defn/type/code/set/Value.h"
#include "category/defn/type/condition/set/Value.h"
#include "category/DefaultCode.h"
#include "category/DefaultCondition.h"
#include "category/Equivalent.h"
#include "category/Instance.h"
#include "category/Message.h"
#include "category/Name.h"
#include "category/Value.h"

#include <cstdint>
#include <utility>
#include <type_traits>
#include <system_error>

namespace basic
{
namespace error
{
namespace system
{

template<typename TCategoryTrait>
class Category
{
public:
    typedef TCategoryTrait TraitType;
public:
    typedef system::defn::type::category::Value ValueType;
    typedef system::defn::type::code::Value CodeValueType;
    typedef system::defn::type::condition ConditionValueType;
public:
    typedef typename category::defn::type::code::set::
        Value<TCategoryTrait>::Type CodeSetValueType;
    typedef typename category::defn::type::condition::set::
        Value<TCategoryTrait>::Type ConditionSetValueType;
public:
    typedef typename Code<TCategoryTrait> CodeType;
    typedef typename Condition<TCategoryTrait> ConditionType;
private:
    TraitType m_trait;
public:
    Category() noexcept;
public:
    Category(const Category<TCategoryTrait>& cpy) noexcept;
    Category(Category<TCategoryTrait>&& mov) noexcept;
public:
    ~Category();
public:
    Category<TCategoryTrait>& 
        operator=(const Category<TCategoryTrait>&) = delete;
    Category<TCategoryTrait>& 
        operator=(Category<TCategoryTrait>&&) = delete;
public:
    ValueType Value() const noexcept;
public:
    const char* Name() const noexcept;
public:
    CodeType DefaultCode() const noexcept;
    CodeType DefaultCode(const CodeSetValueType& code_val) 
        const noexcept;
public:
    ConditionType DefaultCondition() const noexcept; 
    ConditionType DefaultCondition(const CodeSetValueType& code_val) 
        const noexcept;
    ConditionType DefaultCondition(const CodeType& code) 
        const noexcept;
public:
    bool Equivalent(const CodeValueType& code_val, 
        const ConditionType& cond) const noexcept;
    bool Equivalent(const CodeType& code,
        const ConditionValueType& cond_val) const noexcept;
public:
    const char* Message(const CodeType& code) const noexcept;
    const char* Message(const ConditionType& cond) const noexcept;
};

template<typename TCategoryTrait>
Category<TCategoryTrait>::Category() noexcept :
    m_trait(category::Instance<TCategoryTrait>())
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::
    Category(const Category<TCategoryTrait>& cpy) noexcept :
        m_trait(cpy.m_trait)
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::Category(Category<TCategoryTrait>&& mov) noexcept :
    m_trait(std::move(mov))
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::~Category()
{}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ValueType 
Category<TCategoryTrait>::Value() const noexcept
{
    return category::Value(m_trait);
}

template<typename TCategoryTrait>
const char* Category<TCategoryTrait>::Name() const noexcept
{
    return category::Name(m_trait);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeType 
Category<TCategoryTrait>::DefaultCode() const noexcept
{
    return CodeType(category::DefaultCode(m_trait));
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeType 
Category<TCategoryTrait>::
    DefaultCode(const CodeSetValueType& code_val) const noexcept
{
    return CodeType(code_val);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::DefaultCondition() const noexcept
{
    return ConditionType(DefaultCode());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::DefaultCondition(const CodeSetValueType& code_val)
    const noexcept
{
    return ConditionType(DefaultCode(code_val));
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::DefaultCondition(const CodeType& code) const noexcept
{
    return ConditionType(category::DefaultCondition(m_trait, code));
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeValueType& code_val, 
    const ConditionType& cond) const noexcept
{
    return category::Equivalent(m_trait, code_val, cond);
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeType& code,
    const ConditionValueType& cond_val) const noexcept
{
    return category::Equivalent(m_trait, code_val, cond);
}

template<typename TCategoryTrait>
const char* Category<TCategoryTrait>::
    Message(const CodeType& code) const noexcept
{
    return category::Message(m_trait, code);
}

template<typename TCategoryTrait>
const char* Category<TCategoryTrait>::
    Message(const ConditionType& cond) const noexcept
{
    return category::Message(m_trait, cond);
}

} //!system

} //!error

} //!basic

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::
    Category<TCategoryTraitA>& category_a, const basic::error::system::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return category_a.Value() == category_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::
    Category<TCategoryTraitA>& category_a, const basic::error::system::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return !(category_a == category_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::
    Category<TCategoryTraitA>& category_a, const basic::error::system::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return category_a.Value() < category_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::
    Category<TCategoryTraitA>& category_a, const basic::error::system::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return category_b < category_a;
}

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_H_

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

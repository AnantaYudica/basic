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
#include "category/Definition.h"

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
    typedef category::Definition<TCategoryTrait> DefinitionType;
public:
    typedef typename DefinitionType::CategoryValueType ValueType;
    typedef typename DefinitionType::CodeValueType CodeValueType;
    typedef typename DefinitionType::ConditionValueType ConditionValueType;
public:
    typedef typename DefinitionType::CodeEnumType CodeEnumType;
    typedef typename DefinitionType::ConditionEnumType ConditionEnumType;
public:
    typedef typename Code<TCategoryTrait> CodeType;
    typedef typename Condition<TCategoryTrait> ConditionType;
private:
    const TraitType m_trait;
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
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<!category::Definition<_TCategoryTrait>::
        HasCodeEnum, CodeType>::type 
    DefaultCode(const CodeValueType& code_val) const noexcept;
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<category::Definition<_TCategoryTrait>::HasCodeEnum,
        CodeType>::type 
    DefaultCode(const CodeEnumType& code_enum)const noexcept;
public:
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<!category::Definition<_TCategoryTrait>::
        HasCodeEnum, ConditionType>::type 
    DefaultCondition(const CodeValueType& code_val) const noexcept;
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<category::Definition<_TCategoryTrait>::
        HasCodeEnum, ConditionType>::type 
    DefaultCondition(const CodeEnumType& code_enum) const noexcept;
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
    m_trait(TraitType::Instance())
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
    return m_trait.Value();
}

template<typename TCategoryTrait>
const char* Category<TCategoryTrait>::Name() const noexcept
{
    return m_trait.Name();
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeType 
    Category<TCategoryTrait>::DefaultCode() const noexcept
{
    return CodeType(m_trait.DefaultCode());
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<!category::Definition<_TCategoryTrait>::HasCodeEnum, 
    typename Category<TCategoryTrait>::CodeType>::type 
Category<TCategoryTrait>::
    DefaultCode(const CodeValueType& code_val) const noexcept
{
    return CodeType(code_val);
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<category::Definition<_TCategoryTrait>::HasCodeEnum,
    typename Category<TCategoryTrait>::CodeType>::type 
Category<TCategoryTrait>::
    DefaultCode(const CodeEnumType& code_enum) const noexcept
{
    return CodeType(code_enum);
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<!category::Definition<_TCategoryTrait>::
    HasCodeEnum, typename Category<TCategoryTrait>::ConditionType>::type 
Category<TCategoryTrait>::
    DefaultCondition(const CodeValueType& code_val) const noexcept
{
    return ConditionType(DefaultCode(code_val));
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<category::Definition<_TCategoryTrait>::
    HasCodeEnum, typename Category<TCategoryTrait>::ConditionType>::type 
Category<TCategoryTrait>::
    DefaultCondition(const CodeEnumType& code_enum) const noexcept
{
    return ConditionType(DefaultCode(code_enum));
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeValueType& code_val, 
    const ConditionType& cond) const noexcept
{
    return m_trait.Equivalent(code_val, cond);
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeType& code,
    const ConditionValueType& cond_val) const noexcept
{
    return m_trait.Equivalent(code, cond_val);
}

template<typename TCategoryTrait>
const char* Category<TCategoryTrait>::
    Message(const CodeType& code) const noexcept
{
    return m_trait.Message(code);
}

template<typename TCategoryTrait>
const char* Category<TCategoryTrait>::
    Message(const ConditionType& cond) const noexcept
{
    return m_trait.Message(cond);
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

#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_BASE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_BASE_H_

#include "Instance.h"

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

template<typename TCategoryTrait>
class Base
{
private:
    TCategoryTrait m_category;
protected:
    Base() noexcept;
public:
    Base(const Base<TCategoryTrait> & cpy) noexcept = delete; 
    Base(Base<TCategoryTrait> && mov) noexcept;
public:
    ~Base() noexcept;
public:
    Base<TCategoryTrait> & 
        operator=(const Base<TCategoryTrait> & cpy) noexcept = delete;
    Base<TCategoryTrait> & 
        operator=(Base<TCategoryTrait> && mov) noexcept = delete;
protected:
    const TCategoryTrait & GetCategoryTrait() const noexcept;
    TCategoryTrait & GetCategoryTrait() noexcept;
};

template<typename TCategoryTrait>
Base<TCategoryTrait>::Base() noexcept :
    m_category(std::move(category::Instance<TCategoryTrait>()))
{}

template<typename TCategoryTrait>
Base<TCategoryTrait>::Base(Base<TCategoryTrait> && mov) noexcept :
    m_category(std::move(mov.m_category))
{}

template<typename TCategoryTrait>
Base<TCategoryTrait>::~Base() noexcept
{}

template<typename TCategoryTrait>
const TCategoryTrait & Base<TCategoryTrait>::
    GetCategoryTrait() const noexcept
{
    return this->m_category;
}

template<typename TCategoryTrait>
TCategoryTrait & Base<TCategoryTrait>::GetCategoryTrait() noexcept
{
    return this->m_category;
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_BASE_H_
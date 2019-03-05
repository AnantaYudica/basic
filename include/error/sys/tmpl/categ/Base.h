#ifndef BASIC_ERROR_SYS_TMPL_CATEG_BASE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_BASE_H_

#include "Instance.h"

#include <utility>

namespace basic
{
namespace error
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
class Base
{
private:
    TCategoryTrait m_categ;
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
    m_categ(std::move(categ::Instance<TCategoryTrait>()))
{}

template<typename TCategoryTrait>
Base<TCategoryTrait>::Base(Base<TCategoryTrait> && mov) noexcept :
    m_categ(std::move(mov.m_categ))
{}

template<typename TCategoryTrait>
Base<TCategoryTrait>::~Base() noexcept
{}

template<typename TCategoryTrait>
const TCategoryTrait & Base<TCategoryTrait>::
    GetCategoryTrait() const noexcept
{
    return this->m_categ;
}

template<typename TCategoryTrait>
TCategoryTrait & Base<TCategoryTrait>::GetCategoryTrait() noexcept
{
    return this->m_categ;
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_BASE_H_
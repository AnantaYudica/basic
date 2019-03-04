#ifndef BASIC_ERROR_SYSTEM_MAKE_CATEGORY_H_
#define BASIC_ERROR_SYSTEM_MAKE_CATEGORY_H_

#include "../Category.h"
#include "../tmpl/Category.h"
#include "../categ/Default.h"
#include "../categ/Generic.h"
#include "../categ/Future.h"

namespace basic
{
namespace error
{
namespace system
{
namespace make
{

template<typename TCodeEnum>
inline const system::Category & Category(const TCodeEnum &) noexcept
{
    return tmpl::Category<system::categ::Default>::GetInstance();
}

inline const system::Category & Category(const std::future_errc &) noexcept
{
    return tmpl::Category<system::categ::Future>::GetInstance();
}

inline const system::Category & Category(const std::errc &) noexcept
{
    return tmpl::Category<system::categ::Generic>::GetInstance();
}

} //!make

} //!system

} //!error

} //!basic


#endif //BASIC_ERROR_SYSTEM_MAKE_CATEGORY_H_

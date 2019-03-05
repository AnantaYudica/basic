#ifndef BASIC_ERROR_SYS_MAKE_CATEGORY_H_
#define BASIC_ERROR_SYS_MAKE_CATEGORY_H_

#include "../Category.h"
#include "../tmpl/Category.h"
#include "../categ/Default.h"
#include "../categ/Generic.h"
#include "../categ/Future.h"

namespace basic
{
namespace error
{
namespace sys
{
namespace make
{

template<typename TCodeEnum>
inline const sys::Category & Category(const TCodeEnum &) noexcept
{
    return tmpl::Category<sys::categ::Default>::GetInstance();
}

inline const sys::Category & Category(const std::future_errc &) noexcept
{
    return tmpl::Category<sys::categ::Future>::GetInstance();
}

inline const sys::Category & Category(const std::errc &) noexcept
{
    return tmpl::Category<sys::categ::Generic>::GetInstance();
}

} //!make

} //!sys

} //!error

} //!basic


#endif //BASIC_ERROR_SYS_MAKE_CATEGORY_H_

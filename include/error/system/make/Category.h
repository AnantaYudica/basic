#ifndef BASIC_ERROR_SYSTEM_MAKE_CATEGORY_H_
#define BASIC_ERROR_SYSTEM_MAKE_CATEGORY_H_

#include "../Category.h"
#include "../tmpl/Category.h"
#include "../category/Default.h"
#include "../category/Generic.h"
#include "../category/Future.h"

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
    return tmpl::Category<system::category::Default>::GetInstance();
}

inline const system::Category & Category(const std::future_errc &) noexcept
{
    return tmpl::Category<system::category::Future>::GetInstance();
}

inline const system::Category & Category(const std::errc &) noexcept
{
    return tmpl::Category<system::category::Generic>::GetInstance();
}

} //!make

} //!system

} //!error

} //!basic


#endif //BASIC_ERROR_SYSTEM_MAKE_CATEGORY_H_

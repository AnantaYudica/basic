#ifndef BASIC_ERR_SYS_MAKE_CATEGORY_H_
#define BASIC_ERR_SYS_MAKE_CATEGORY_H_

#include "../Category.h"
#include "../tmpl/Category.h"
#include "../categ/Default.h"
#include "../categ/Generic.h"
#include "../categ/Future.h"

namespace basic
{
namespace err
{
namespace sys
{
namespace make
{

template<typename T>
struct Category
{
    Category() = delete;
    static const sys::Category & GetInstance() noexcept
    {
        return tmpl::Category<sys::categ::Default>::GetInstance();
    }
};

template<>
struct Category<std::future_errc>
{
    Category() = delete;
    static const sys::Category & GetInstance() noexcept
    {
        return tmpl::Category<sys::categ::Future>::GetInstance();
    }
};

template<>
struct Category<std::errc>
{
    Category() = delete;
    static const sys::Category & GetInstance() noexcept
    {
        return tmpl::Category<sys::categ::Generic>::GetInstance();
    }
};

} //!make

} //!sys

} //!err

} //!basic


#endif //BASIC_ERR_SYS_MAKE_CATEGORY_H_

#ifndef BASIC_CONSTANT_ERROR_SYS_CATEGORY_H_
#define BASIC_CONSTANT_ERROR_SYS_CATEGORY_H_

#include "../../../error/defn/type/sys/categ/Value.h"

namespace basic
{
namespace constant
{
namespace error
{
namespace sys
{
    
enum : basic::error::defn::type::sys::categ::Value
{
    generic_category = 1,
    system_category = 2,
    iostream_category = 3,
    future_category = 4
};

} //!sys

} //!error

} //!constant

} //!basic

#endif //!BASIC_CONSTANT_ERROR_SYS_CATEGORY_H_
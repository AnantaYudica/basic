#ifndef BASIC_CONSTANT_ERROR_SYSTEM_CATEGORY_H_
#define BASIC_CONSTANT_ERROR_SYSTEM_CATEGORY_H_

#include "../../../error/defn/type/system/category/Value.h"

namespace basic
{
namespace constant
{
namespace error
{
namespace system
{
    
enum : basic::error::defn::type::system::category::Value
{
    generic_category = 1,
    system_category = 2,
    iostream_category = 3,
    future_category = 4
};

} //!system

} //!error

} //!constant

} //!basic

#endif //!BASIC_CONSTANT_ERROR_SYSTEM_CATEGORY_H_
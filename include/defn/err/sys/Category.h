#ifndef BASIC_DEFN_ERR_SYS_CATEGORY_H_
#define BASIC_DEFN_ERR_SYS_CATEGORY_H_

#include "../../../err/defn/type/sys/categ/Value.h"

namespace basic
{
namespace defn
{
namespace err
{
namespace sys
{
    
enum : basic::err::defn::type::sys::categ::Value
{
    generic_category = 1,
    system_category = 2,
    iostream_category = 3,
    future_category = 4
};

} //!sys

} //!err

} //!defn

} //!basic

#endif //!BASIC_DEFN_ERR_SYS_CATEGORY_H_
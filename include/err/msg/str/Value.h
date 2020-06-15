#ifndef BASIC_ERR_MSG_STR_VALUE_H_
#define BASIC_ERR_MSG_STR_VALUE_H_

#include "../../defn/type/Char.h"
#include "IsDefault.h"

namespace basic
{
namespace err
{
namespace msg
{
namespace str
{

inline const defn::type::Char * 
Value(const defn::type::Char *cstr) noexcept
{
    static defn::type::Char empty[1] = {'\0'};
    if (IsDefault(cstr))
        return empty;
    return cstr;
}

template<std::size_t N>
const defn::type::Char * 
Value(const defn::type::Char (&arr_str)[N]) noexcept
{
    return arr_str;
}

} //!str

} //!msg

} //!err

} //!basic

#endif //!BASIC_ERR_MSG_STR_VALUE_H_

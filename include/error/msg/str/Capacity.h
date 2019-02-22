#ifndef BASIC_ERROR_MSG_STR_CAPACITY_H_
#define BASIC_ERROR_MSG_STR_CAPACITY_H_

#include "../../defn/type/Char.h"

#include <cstddef>

namespace basic
{
namespace error
{
namespace msg
{
namespace str
{

inline std::size_t Capacity(const defn::type::Char *cstr) noexcept
{
    std::size_t index = 0;
    while(cstr[index] != '\0')
        ++index;
    return index + 1;
}

template<std::size_t N>
std::size_t Capacity(const defn::type::Char (&arr_str)[N]) noexcept
{
    return N;
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_CAPACITY_H_
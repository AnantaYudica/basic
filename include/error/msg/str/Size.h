#ifndef BASIC_ERROR_MSG_STR_SIZE_H_
#define BASIC_ERROR_MSG_STR_SIZE_H_

#include "../../defn/type/Char.h"
#include "IsDefault.h"

#include <string>
#include <cstddef>

namespace basic
{
namespace error
{
namespace msg
{
namespace str
{

inline std::size_t Size(const defn::type::Char *cstr) noexcept
{
    if(IsDefault(cstr)) return 0;
    std::size_t index = 0;
    while(cstr[index] != '\0')
        ++index;
    return index;
}

inline std::size_t Size(const std::string &str) noexcept
{
    return str.size();
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_SIZE_H_

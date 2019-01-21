#ifndef BASIC_ERROR_MSG_STR_COPY_H_
#define BASIC_ERROR_MSG_STR_COPY_H_

#include "../../defn/type/Char.h"
#include "../../defn/type/msg/str/Storage.h"
#include "IsDefault.h"
#include "At.h"

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

void Copy(defn::type::msg::str::Storage &storage_ref, 
    const std::size_t& size, const defn::type::Char *cstr) noexcept
{
    if (IsDefault(storage_ref))
        return;
    std::size_t index = 0;
    const auto *it = cstr, *end = cstr + size;
    while(*it != '\0' && it != end && index < size)
        At(storage_ref, index++) = *(it++);
}

void Copy(defn::type::msg::str::Storage &storage_ref, 
    const std::size_t &size, const std::string &str) noexcept
{
    if (IsDefault(storage_ref))
        return;
    std::size_t index = 0;
    auto it = str.begin();
    while(*it != '\0' && it != str.end() && index < size)
        At(storage_ref, index++) = *(it++);
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_ALLOCATE_H_

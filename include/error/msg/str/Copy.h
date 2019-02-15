#ifndef BASIC_ERROR_MSG_STR_COPY_H_
#define BASIC_ERROR_MSG_STR_COPY_H_

#include "../../defn/type/Char.h"
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

inline void Copy(defn::type::Char * (&storage_ref), 
    const std::size_t& size, const defn::type::Char *cstr) noexcept
{
    if (IsDefault(storage_ref))
        return;
    std::size_t index = 0;
    const auto *it = cstr, *end = cstr + size;
    while(*it != '\0' && it != end && index < size)
        At(storage_ref, index++) = *(it++);
}

inline void Copy(defn::type::Char * (&storage_ref), 
    const std::size_t &size, const std::string &str) noexcept
{
    if (IsDefault(storage_ref))
        return;
    std::size_t index = 0;
    auto it = str.begin();
    while(*it != '\0' && it != str.end() && index < size)
        At(storage_ref, index++) = *(it++);
}

template<std::size_t N>
void Copy(defn::type::Char (&storage_ref)[N], 
    const std::size_t& size, const defn::type::Char *cstr) noexcept
{
    if (IsDefault(storage_ref))
        return;
    std::size_t index = 0;
    const std::size_t max_size = (size < N ? size : N);
    const auto *it = cstr, *end = cstr + max_size;
    while(*it != '\0' && it != end && index < max_size)
        At(storage_ref, index++) = *(it++);
}

template<std::size_t N>
void Copy(defn::type::Char (&storage_ref)[N], 
    const std::size_t &size, const std::string &str) noexcept
{
    if (IsDefault(storage_ref))
        return;
    std::size_t index = 0;
    const std::size_t max_size = (size < N ? size : N);
    auto it = str.begin();
    while(*it != '\0' && it != str.end() && index < max_size)
        At(storage_ref, index++) = *(it++);
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_ALLOCATE_H_

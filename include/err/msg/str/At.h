#ifndef BASIC_ERR_MSG_STR_AT_H_
#define BASIC_ERR_MSG_STR_AT_H_

#include "../../defn/type/Char.h"

#include <cstddef>

namespace basic
{
namespace err
{
namespace msg
{
namespace str
{

inline defn::type::Char& At(defn::type::Char *(&storage_ref),
    const std::size_t& index) noexcept
{
    return *(storage_ref + index);
}

inline const defn::type::Char& At(const defn::type::Char *(&storage_ref),
    const std::size_t& index) noexcept
{
    return *(storage_ref + index);
}

template<std::size_t N>
defn::type::Char& At(defn::type::Char (&storage_ref)[N], 
    const std::size_t& index) noexcept
{
    return storage_ref[index % N];
}

template<std::size_t N>
const defn::type::Char& At(const defn::type::Char (&storage_ref)[N], 
    const std::size_t& index) noexcept
{
    return storage_ref[index % N];
}

} //!str

} //!msg

} //!err

} //!basic

#endif //!BASIC_ERR_MSG_STR_AT_H_
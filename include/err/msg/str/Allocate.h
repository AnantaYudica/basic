#ifndef BASIC_ERR_MSG_STR_ALLOCATE_H_
#define BASIC_ERR_MSG_STR_ALLOCATE_H_

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

inline void Allocate(defn::type::Char *(&storage_ref), 
    const std::size_t& size) noexcept
{
    storage_ref = new defn::type::Char[size];
    if (storage_ref != nullptr)
        storage_ref[0] = '\0';
}

template<std::size_t N>
void Allocate(defn::type::Char (&storage_ref)[N], 
    const std::size_t& size) noexcept
{
    storage_ref[0] = '\0';
}

} //!str

} //!msg

} //!err

} //!basic

#endif //!BASIC_ERR_MSG_STR_ALLOCATE_H_

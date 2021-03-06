#ifndef BASIC_ERR_MSG_STR_DEFAULT_H_
#define BASIC_ERR_MSG_STR_DEFAULT_H_

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

inline void Default(defn::type::Char *(&storage_ref)) noexcept
{
    storage_ref = nullptr;
}

template<std::size_t N>
void Default(defn::type::Char (&storage_ref)[N]) noexcept
{
    storage_ref[0] = '\0';
}

} //!str

} //!msg

} //!err

} //!basic

#endif //!BASIC_ERR_MSG_STR_DEFAULT_H_

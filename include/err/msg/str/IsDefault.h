#ifndef BASIC_ERR_MSG_STR_ISDEFAULT_H_
#define BASIC_ERR_MSG_STR_ISDEFAULT_H_

#include "../../defn/type/Char.h"

namespace basic
{
namespace err
{
namespace msg
{
namespace str
{

inline bool IsDefault(const defn::type::Char *storage_ref) noexcept
{
    return storage_ref == nullptr;
}

template<std::size_t N>
bool IsDefault(const defn::type::Char (&storage_ref)[N]) noexcept
{
    return storage_ref[0] == '\0';
}

} //!str

} //!msg

} //!err

} //!basic

#endif //!BASIC_ERR_MSG_STR_ISDEFAULT_H_

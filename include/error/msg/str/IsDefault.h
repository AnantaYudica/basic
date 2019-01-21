#ifndef BASIC_ERROR_MSG_STR_ISDEFAULT_H_
#define BASIC_ERROR_MSG_STR_ISDEFAULT_H_

#include "../../defn/type/Char.h"

namespace basic
{
namespace error
{
namespace msg
{
namespace str
{

bool IsDefault(const defn::type::Char *storage_ref) noexcept
{
    return storage_ref == nullptr;
}

template<std::size_t N>
bool IsDefault(const defn::type::Char (&storage_ref)[N]) noexcept
{
    return false;
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_ISDEFAULT_H_

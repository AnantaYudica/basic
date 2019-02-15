#ifndef BASIC_ERROR_MSG_STR_MOVE_H_
#define BASIC_ERROR_MSG_STR_MOVE_H_

#include "../../defn/type/Char.h"
#include "IsDefault.h"
#include "Default.h"
#include "Deallocate.h"
#include "Copy.h"

#include <cstddef>
#include <utility>

namespace basic
{
namespace error
{
namespace msg
{
namespace str
{

inline void Move(defn::type::Char *(&storage_ref),
    defn::type::Char *(&&cstr)) noexcept
{
    if (!IsDefault(storage_ref))
        Deallocate(storage_ref);
    storage_ref = cstr;
    Default(cstr);
}

template<std::size_t N>
void Move(defn::type::Char (&storage_ref)[N],
    defn::type::Char (&&cstr_arr)[N]) noexcept
{
    Copy(storage_ref, N, cstr_arr);
    Default(cstr_arr);
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_MOVE_H_
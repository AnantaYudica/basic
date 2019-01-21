#ifndef BASIC_ERROR_MSG_STR_DEALLOCATE_H_
#define BASIC_ERROR_MSG_STR_DEALLOCATE_H_

#include "../../defn/type/Char.h"
#include "Default.h"

#include <cstddef>

namespace basic
{
namespace error
{
namespace msg
{
namespace str
{

void Deallocate(defn::type::Char *(&storage_ref)) noexcept
{
    if (storage_ref == nullptr)
        return;
    delete[] storage_ref;
    Default(storage_ref);
}

template<std::size_t N>
void Deallocate(defn::type::Char (&storage_ref)[N]) noexcept
{
    Default(storage_ref);
}

} //!str

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STR_DEALLOCATE_H_

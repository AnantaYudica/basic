#ifndef BASIC_ERROR_ID_SIZE_H_
#define BASIC_ERROR_ID_SIZE_H_

#include <cstddef>

namespace basic
{
namespace error
{
namespace id
{

template<typename TIdentification>
constexpr std::size_t Size() noexcept
{
    return sizeof(typename TIdentification::FlagType) +
        sizeof(typename TIdentification::RecordType::UnionCodeType) +
        sizeof(typename TIdentification::RecordType::
            ErrorSystemCategoryValueType);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_SIZE_H_

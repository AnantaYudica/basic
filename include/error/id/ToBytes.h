#ifndef BASIC_ERROR_ID_TOBYTES_H_
#define BASIC_ERROR_ID_TOBYTES_H_

#include "Size.h"

#include <cstring>
#include <cstdint>

namespace basic
{
namespace error
{
namespace id
{

template<typename TIdentification>
std::uint8_t* ToBytes(const TIdentification& id, 
    uint8_t (&bytes)[id::Size<TIdentification>()]) noexcept
{
    typedef typename TIdentification::RecordType RecordType;
    typedef typename RecordType::ErrorSystemCategoryValueType
       SystemCategoryValueType;
    typedef typename RecordType::UnionCodeType UnionCodeType;
    const id::Flag& flag = static_cast<const id::Flag&>(id);
    SystemCategoryValueType system_category_val{};
    UnionCodeType uni_code_val{};
    if (id.IsSystem())
    {
        const auto error_system = id.ErrorSystem();
        system_category_val = error_system.Category();
        uni_code_val.ErrorSystem = error_system.Code();
    }
    else
    {
        system_category_val = 0; 
        uni_code_val.ErrorSystem = id.Error().Code();
    }
    
    memcpy(bytes, (const char*)&flag, sizeof(flag));
    memcpy(bytes + sizeof(flag), (const char*)&system_category_val, 
        sizeof(SystemCategoryValueType));
    memcpy(bytes + sizeof(flag) + sizeof(SystemCategoryValueType),
        (const char*)&uni_code_val, sizeof(UnionCodeType));
    return bytes;
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_TOBYTES_H_

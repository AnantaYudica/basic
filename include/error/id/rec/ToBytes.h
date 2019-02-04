#ifndef BASIC_ERROR_ID_REC_TOBYTES_H_
#define BASIC_ERROR_ID_REC_TOBYTES_H_

#include "../Record.h"
#include "../Flag.h"

#include <cstdint>
#include <cstring>

namespace basic
{
namespace error
{
namespace id
{
namespace rec
{

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
inline std::size_t ToBytes(const id::Record<TErrorCodeValue, 
    TErrorSystemCategoryValue, TErrorSystemCodeValue> & record,
    std::uint8_t * block_ptr, const std::size_t & block_size) noexcept
{
    if (block_ptr == nullptr) return 0;

    constexpr std::size_t flag_size = sizeof(id::Flag::ValueType);
    constexpr std::size_t error_code_size = sizeof(TErrorCodeValue);
    constexpr std::size_t error_size = flag_size + error_code_size;
    constexpr std::size_t system_error_category_size = 
        sizeof(TErrorSystemCategoryValue);
    constexpr std::size_t system_error_code_size = 
        sizeof(TErrorSystemCodeValue);
    constexpr std::size_t system_error_size = flag_size +
        system_error_category_size + system_error_code_size;

    const auto & rec_flag = record.Flag();
    const auto & rec_error = record.Error();
    const auto & rec_error_system = record.ErrorSystem();
    
    const uint8_t * flag_block = (const uint8_t *) &rec_flag;
    const uint8_t * error_code_block = (const uint8_t *) &rec_error.Code();
    const uint8_t * system_error_category_block = 
        (const uint8_t *) &rec_error_system.Category();
    const uint8_t * system_error_code_block = 
        (const uint8_t *) &rec_error_system.Code();

    const std::uint16_t one_uint16 = 1;
    const bool IsBigEndian = ((std::uint8_t *)(&one_uint16))[1] == 1;

    std::size_t i = 0;
    if (block_size < flag_size) return 0;
    if (IsBigEndian)
        for (std::size_t j = 0; j < flag_size; ++j, ++i)
            block_ptr[i] = flag_block[j];
    else
        for (std::size_t j = flag_size; j > 0; --j, ++i)
            block_ptr[i] = flag_block[j - 1];

    if (record.Flag().IsSystem())
    {
        if (block_size < system_error_size) return flag_size;
        if (IsBigEndian)
            for (std::size_t j = 0; j < system_error_category_size; ++j, ++i)
                block_ptr[i] = system_error_category_block[j];
        else
            for (std::size_t j = system_error_category_size; j > 0; --j, ++i)
                block_ptr[i] = system_error_category_block[j - 1];
        if (IsBigEndian)
            for (std::size_t j = 0; j < system_error_code_size; ++j, ++i)
                block_ptr[i] = system_error_code_block[j];
        else
            for (std::size_t j = system_error_code_size; j > 0; --j, ++i)
                block_ptr[i] = system_error_code_block[j - 1];
    }
    else
    {
        if (block_size < error_size) return flag_size;
        if (IsBigEndian)
            for (std::size_t j = 0; j < error_code_size; ++j, ++i)
                block_ptr[i] = error_code_block[j];
        else
            for (std::size_t j = error_code_size; j > 0; --j, ++i)
                block_ptr[i] = error_code_block[j - 1];
    }

    return record.Flag().IsDefault() ? flag_size : 
        (record.Flag().IsSystem() ? system_error_size : error_size);
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_TOBYTES_H_

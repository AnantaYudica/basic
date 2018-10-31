#ifndef BASIC_ERROR_IDENTIFICATION_H_
#define BASIC_ERROR_IDENTIFICATION_H_

#include <cstdint>

namespace basic
{
namespace error
{
namespace id
{

typedef uint32_t NumberType;

} //!id

struct Identification
{
    struct
    {
        uint8_t Zero : 1;
        uint8_t Standard : 1;
        uint8_t Catch : 1;

    } Flag;
    uint16_t Error; // 0 - 65535
    constexpr Identification(const uint8_t& is_zero, 
        const uint8_t& is_standard, const uint8_t& is_catch, 
        const uint16_t& id_error);
};

constexpr Identification::Identification(const uint8_t& is_zero, 
    const uint8_t& is_standard, const uint8_t& is_catch,
    const uint16_t& id_error) :
        Flag{is_zero, is_standard, is_catch},
        Error(id_error)
{}

namespace id
{

NumberType Number(const Identification& id_)
{
    return reinterpret_cast<const NumberType&>(id_);
}

constexpr Identification Default()
{
    return Identification{1, 1, 1, (uint16_t)-1};
}

template<typename TException>
constexpr Identification Get(const TException e)
{
    return Default();
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_IDENTIFICATION_H_

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

class Identification
{
public:
    const struct
    {
        uint8_t Default : 1;
        uint8_t Standard : 1;
        uint8_t Catch : 1;

    } Flag;
    const uint16_t Error;
public:
    constexpr Identification();
    constexpr Identification(const uint16_t& id_error);
protected:
    constexpr Identification(const uint8_t& is_default, 
        const uint8_t& is_standard, const uint8_t& is_catch, 
        const uint16_t& id_error);
public:
    constexpr Identification(const Identification& cpy);
    constexpr Identification(Identification&& mov);
};

constexpr Identification::Identification() :
    Flag{1, 1, 1},
    Error{static_cast<uint16_t>(-1)}
{}

constexpr Identification::Identification(const uint16_t& id_error) :
    Flag{0, 0, 0},
    Error{id_error}
{}

constexpr Identification::Identification(const uint8_t& is_default, 
    const uint8_t& is_standard, const uint8_t& is_catch,
    const uint16_t& id_error) :
        Flag{is_default, is_standard, is_catch},
        Error{id_error}
{}

Identification::Identification(const Identification& cpy) :
    Flag{cpy.Flag},
    Error{cpy.Error}
{}

Identification::Identification(Identification&& mov) :
    Flag{mov.Flag},
    Error{mov.Error}
{}

} //!error

} //!basic

#endif //!BASIC_ERROR_IDENTIFICATION_H_

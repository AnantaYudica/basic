#ifndef BASIC_ERROR_ID_REC_CODE_H_
#define BASIC_ERROR_ID_REC_CODE_H_

#include "../code/defn/type/Value.h"
#include "../system/defn/type/code/Value.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{
namespace rec
{

union Code
{
    error::code::defn::type::Value Error;
    error::system::defn::type::code::Value SystemError;
    constexpr Code() noexcept;
    constexpr Code(const error::code::defn::type::Value& error,
        const error::system::defn::type::code::Value& system_error) noexcept;
    constexpr Code(const Code& cpy) noexcept;
    constexpr Code(Code&& mov) noexcept;
};

constexpr Code::Code() noexcept :
    Error(0),
    SystemError(0)
{}

constexpr Code::Code(const error::code::defn::type::Value& error,
    const error::system::defn::type::code::Value& system_error) noexcept :
        Error(error),
        SystemError(SystemError | system_error)
{}

constexpr Code::Code(const Code& cpy) noexcept :
    Error(cpy.Error),
    SystemError(SystemError | cpy.SystemError)
{}

constexpr Code::Code(Code&& mov) noexcept :
    Error(mov.Error),
    SystemError(SystemError | mov.SystemError)
{}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_CODE_H_

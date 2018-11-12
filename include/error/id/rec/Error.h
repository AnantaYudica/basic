#ifndef BASIC_ERROR_ID_REC_ERROR_H_
#define BASIC_ERROR_ID_REC_ERROR_H_

#include "../code/defn/type/Value.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{
namespace rec
{

class Error
{
public:
    typedef code::defn::type::Value CodeValueType;
private:
    CodeValueType m_codeValue;
public:
    Error() noexcept;
    Error(const CodeValueType& code_value) noexcept;
public:
    Error(const Error& cpy) noexcept;
    Error(Error&& mov) noexcept;
public:
    const CodeValueType& Code() const noexcept;
};

Error::Error() noexcept :
    m_codeValue(0)
{}

Error::Error(const CodeValueType& code_value) noexcept :
    m_codeValue(code_value)
{}

Error::Error(const Error& cpy) noexcept :
    m_codeValue(cpy.m_codeValue)
{}

Error::Error(Error&& mov) noexcept :
    m_codeValue(std::move(mov.m_codeValue))
{}

const typename Error::CodeValueType& Error::Code() const noexcept
{
    return m_codeValue;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_ERROR_H_

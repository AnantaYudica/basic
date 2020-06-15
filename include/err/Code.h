#ifndef BASIC_ERR_CODE_H_
#define BASIC_ERR_CODE_H_

#include "defn/type/code/Value.h"

#include <utility>

namespace basic
{
namespace err
{

class Code
{
public:
    typedef defn::type::code::Value CodeValueType;
private:
    CodeValueType m_value;
public:
    constexpr Code() noexcept;
    constexpr Code(const CodeValueType& value) noexcept;
public:
    inline Code(const Code& cpy) noexcept;
    inline Code(Code&& mov) noexcept;
public:
    inline Code& operator=(const Code& cpy) noexcept;
    inline Code& operator=(Code&& mov) noexcept;
public:
    inline Code& operator=(const CodeValueType& value) noexcept;
public:
    inline CodeValueType Value() const noexcept;
};

constexpr Code::Code() noexcept :
    m_value(0)
{}

constexpr Code::Code(const CodeValueType& value) noexcept :
    m_value(value)
{}

inline Code::Code(const Code& cpy) noexcept :
    m_value(cpy.m_value)
{}

inline Code::Code(Code&& mov) noexcept :
    m_value(std::move(mov.m_value)) 
{
    mov.m_value = 0;
}

inline Code& Code::operator=(const Code& cpy) noexcept
{
    this->m_value = cpy.m_value;
    return *this;
}

inline Code& Code::operator=(Code&& mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    mov.m_value = 0;
    return *this;
}

inline Code& Code::operator=(const CodeValueType& value) noexcept
{
    this->m_value = value;
    return *this;
}

inline typename Code::CodeValueType Code::Value() const noexcept
{
    return this->m_value;
}

} //!err

} //!basic

inline bool operator==(const basic::err::Code& code, 
    const basic::err::Code& code_other)
{
    return code.Value() == code_other.Value();
}

template<typename TValueCode>
inline bool operator==(const basic::err::Code& code, 
    const TValueCode& code_val)
{
    return code.Value() == code_val;
}

template<typename TValueCode>
inline bool operator==(const TValueCode& code_val, 
    const basic::err::Code& code_other)
{
    return code_val == code_other.Value();
}

inline bool operator!=(const basic::err::Code& code, 
    const basic::err::Code& code_other)
{
    return !(code == code_other);
}

template<typename TValueCode>
inline bool operator!=(const basic::err::Code& code, 
    const TValueCode& code_val)
{
    return !(code == code_val);
}

template<typename TValueCode>
inline bool operator!=(const TValueCode& code_val, 
    const basic::err::Code& code_other)
{
    return !(code_val == code_other);
}

#endif //!BASIC_ERR_CODE_H_

#ifndef BASIC_ERROR_CODE_H_
#define BASIC_ERROR_CODE_H_

#include <cstdint>
#include <type_traits>
#include <utility>

namespace basic
{
namespace error
{

template<typename TInteger = std::uint16_t,
    TInteger DefaultInteger = 0>
class Code
{
    static_assert(std::is_integral<TInteger>::value, 
        "check integer type");
public:
    typedef TInteger IntegerType;
public:
    static constexpr IntegerType DefaultValue = DefaultInteger;
private:
    IntegerType m_value;
public:
    constexpr Code();
    constexpr Code(const IntegerType& value);
public:
    Code(const Code<TInteger, DefaultInteger>& cpy);
    Code(Code<TInteger, DefaultInteger>&& mov);
public:
    ~Code();
public:
    Code<TInteger, DefaultInteger>& 
        operator=(const Code<TInteger, DefaultInteger>& cpy);
    Code<TInteger, DefaultInteger>& 
        operator=(Code<TInteger, DefaultInteger>&& mov);
public:
    Code<TInteger, DefaultInteger>& operator=(const TInteger& value);
public:
    operator TInteger&();
    operator const TInteger&() const;
public:
    bool operator==(const Code<TInteger, DefaultInteger>& other) const;
    bool operator!=(const Code<TInteger, DefaultInteger>& other) const;
    template<typename TIntegerOther>
    bool operator==(const TIntegerOther& other) const;
    template<typename TIntegerOther>
    bool operator!=(const TIntegerOther& other) const;
};

template<typename TInteger, TInteger DefaultInteger>
constexpr Code<TInteger, DefaultInteger>::Code() :
    m_value(DefaultInteger)
{}

template<typename TInteger, TInteger DefaultInteger>
constexpr Code<TInteger, DefaultInteger>::Code(const IntegerType& value) :
    m_value(value)
{}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>::Code(const Code<TInteger, 
    DefaultInteger>& cpy) :
        m_value(cpy.m_value)
{}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>::Code(Code<TInteger, DefaultInteger>&& mov) :
    m_value(std::move(mov.m_value))
{
    mov.m_value = DefaultInteger;
}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>::~Code()
{}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>& Code<TInteger, DefaultInteger>::
    operator=(const Code<TInteger, DefaultInteger>& cpy)
{
    this->m_value = cpy.m_value;
    return *this;
}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>& Code<TInteger, DefaultInteger>::
    operator=(Code<TInteger, DefaultInteger>&& mov)
{
    this->m_value = std::move(mov.m_value);
    mov.m_value = DefaultInteger;
    return *this;
}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>& Code<TInteger, DefaultInteger>::
    operator=(const TInteger& value)
{
    this->m_value = value;
    return *this;
}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>::operator TInteger&()
{
    return this->m_value;
}

template<typename TInteger, TInteger DefaultInteger>
Code<TInteger, DefaultInteger>::operator const TInteger&() const
{
    return this->m_value;
}

template<typename TInteger, TInteger DefaultInteger>
bool Code<TInteger, DefaultInteger>::
    operator==(const Code<TInteger, DefaultInteger>& other) const
{
    return this->m_value == other.m_value;
}

template<typename TInteger, TInteger DefaultInteger>
bool Code<TInteger, DefaultInteger>::
    operator!=(const Code<TInteger, DefaultInteger>& other) const
{
    return !(*this == other);
}

template<typename TInteger, TInteger DefaultInteger>
template<typename TIntegerOther>
bool Code<TInteger, DefaultInteger>::
    operator==(const TIntegerOther& other) const
{
    return this->m_value == other;
}

template<typename TInteger, TInteger DefaultInteger>
template<typename TIntegerOther>
bool Code<TInteger, DefaultInteger>::
    operator!=(const TIntegerOther& other) const
{
    return !(*this == other);
}

} //!error

} //!basic

template<typename TInteger, typename TIntegerOther, 
    TIntegerOther DefaultIntegerOther>
bool operator==(const TInteger& code, 
    const basic::error::Code<TIntegerOther, DefaultIntegerOther>& code_other)
{
    return code_other == code;
}

template<typename TInteger, typename TIntegerOther,
    TIntegerOther DefaultIntegerOther>
bool operator!=(const TInteger& code, 
    const basic::error::Code<TIntegerOther, DefaultIntegerOther>& code_other)
{
    return code_other == code;
}

#endif //!BASIC_ERROR_CODE_H_

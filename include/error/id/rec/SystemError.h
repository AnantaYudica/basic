#ifndef BASIC_ERROR_ID_REC_SYSTEMERROR_H_
#define BASIC_ERROR_ID_REC_SYSTEMERROR_H_

#include "../system/defn/type/category/Value.h"
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

class SystemError
{
public:
    typedef system::defn::type::code::Value CodeValueType;
    typedef system::defn::type::category::Value CategoryValueType;
private:
    CategoryValueType m_categoryValue;
    CodeValueType m_codeValue;
public:
    SystemError() noexcept;
    SystemError(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept;
public:
    SystemError(const SystemError& cpy) noexcept;
    SystemError(SystemError&& mov) noexcept;
public:
    const CategoryValueType& Category() const noexcept;
    const CodeValueType& Code() const noexcept;
};

SystemError::SystemError() noexcept :
    m_categoryValue(0),
    m_codeValue(0)
{}

SystemError::SystemError(const CategoryValueType& category_value, 
    const CodeValueType& code_value) noexcept :
        m_categoryValue(category_value),
        m_codeValue(code_value)
{}

SystemError::SystemError(const SystemError& cpy) noexcept :
    m_categoryValue(cpy.m_categoryValue),
    m_codeValue(cpy.m_codeValue)
{}

SystemError::SystemError(SystemError&& mov) noexcept :
    m_categoryValue(std::move(mov.m_categoryValue)),
    m_codeValue(std::move(mov.m_codeValue))
{}

const typename SystemError::CategoryValueType& 
    SystemError::Category() const noexcept
{
    return m_categoryValue;
}

const typename SystemError::CodeValueType& SystemError::Code() const noexcept
{
    return m_codeValue;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_SYSTEMERROR_H_

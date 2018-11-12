#ifndef BASIC_ERROR_ID_RECORD_H_
#define BASIC_ERROR_ID_RECORD_H_

#include "../code/defn/type/Value.h"
#include "../system/defn/type/category/Value.h"
#include "../system/defn/type/code/Value.h"
#include "Flag.h"

#include "rec/Code.h"
#include "rec/Error.h"
#include "rec/SystemError.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

class Record : public Flag 
{
public:
    typedef error::code::defn::type::Value CodeType;
    typedef error::system::defn::type::category::Value SystemCategoryType;
    typedef error::system::defn::type::code::Value SystemCodeType;
public:
    typedef rec::Error ErrorType;
    typedef rec::SystemError SystemErrorType;
public:
    typedef rec::Code UnionCodeType;
private:
    const SystemCategoryType m_systemCategory;
    const UnionCodeType m_code;
public:
    constexpr Record() noexcept;
    constexpr Record(const Flag& flag, const CodeType& code) noexcept;
    constexpr Record(const id::flag::System&, const Flag& flag,
        const SystemCategoryType& system_category, 
        const SystemCodeType& system_code) noexcept;
public:
    Record(const Record& cpy) noexcept;
    Record(Record&& mov) noexcept;
public:
    ErrorType Error() const noexcept;
    SystemErrorType SystemError() const noexcept;
};

constexpr Record::Record() noexcept :
    m_systemCategory{0},
    m_code()
{}

constexpr Record::Record(const Flag& flag, const CodeType& code) noexcept :
    Flag(flag),
    m_systemCategory{0},
    m_code(code, 0)
{}

constexpr Record::Record(const id::flag::System&, const Flag& flag,
    const SystemCategoryType& system_category, 
    const SystemCodeType& system_code) noexcept :
        Flag(flag),
        m_systemCategory{system_category},
        m_code(0, system_code)
{}

Record::Record(const Record& cpy) noexcept :
    Flag(cpy),
    m_systemCategory(cpy.m_systemCategory),
    m_code(cpy.m_code)
{}

Record::Record(Record&& mov) noexcept :
    Flag(std::move(mov)),
    m_systemCategory(std::move(mov.m_systemCategory)),
    m_code(std::move(mov.m_code))
{}

typename Record::ErrorType Record::Error() const noexcept
{
    return ErrorType(m_code.Error);
}

typename Record::SystemErrorType Record::SystemError() const noexcept
{
    return SystemErrorType(m_systemCategory, m_code.SystemError);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_RECORD_H_

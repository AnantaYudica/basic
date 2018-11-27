#ifndef BASIC_ERROR_INFORMATION_H_
#define BASIC_ERROR_INFORMATION_H_

#include "Identification.h"
#include "id/ToBytes.h"
#include "output/Interface.h"
#include "output/Operator.h"
#include "defn/type/Output.h"

#include <ostream>
#include <cstddef>

namespace basic
{
namespace error
{

class Information :
    public output::Interface
{
public:
    typedef defn::type::Output OutputValueType;
private:
    const error::Identification m_id;
    const char* m_file;
    const std::size_t m_line;
public:
    constexpr Information() noexcept;
    constexpr Information(const error::Identification& id, const char* file,
        const std::size_t& line) noexcept;
public:
    Information(const Information& cpy) noexcept;
    Information(Information&& mov) noexcept;
public:
    Information& operator=(const Information& cpy) = delete;
    Information& operator=(Information&& mov) = delete;
public:
    const error::Identification& Identification() const noexcept;
    const char* File() const noexcept;
    const std::size_t& Line() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

constexpr Information::Information() noexcept :
    m_id(),
    m_file(nullptr),
    m_line((std::size_t)-1)
{}

constexpr Information::Information(const error::Identification& id, 
    const char* file, const std::size_t& line) noexcept :
        m_id(id),
        m_file(file),
        m_line(line)
{}

Information::Information(const Information& cpy) noexcept :
    m_id(cpy.m_id),
    m_file(cpy.m_file),
    m_line(cpy.m_line)
{}

Information::Information(Information&& mov) noexcept :
    m_id(mov.m_id),
    m_file(mov.m_file),
    m_line(mov.m_line)
{}

const error::Identification& Information::Identification() const noexcept
{
    return m_id;
}

const char* Information::File() const noexcept
{
    return m_file;
}

const std::size_t& Information::Line() const noexcept
{
    return m_line;
}

typename Information::OutputValueType& 
Information::Output(OutputValueType& out) const noexcept
{
    if (!this->m_id.IsDefault())
    {
        if (!this->m_id.IsCatch())
            output::Operator(out, "id ", this->m_id);
        output::Operator(out, "file ", this->m_file);
        output::Operator(out, "line ", this->m_file);
    }
    return out;
}

} //!error

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::error::Information& info)
{
    static_cast<const basic::error::output::Interface&>(info).Output(out);
    return out;
}

#endif //!BASIC_ERROR_INFORMATION_H_

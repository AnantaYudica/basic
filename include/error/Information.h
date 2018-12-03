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
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    const char * m_file;
    const std::size_t m_line;
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
public:
    constexpr Information() noexcept;
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    constexpr Information(const error::Identification& id, const char* file,
        const std::size_t& line) noexcept;
#else
    constexpr Information(const error::Identification& id) noexcept;
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
public:
    Information(const Information& cpy) noexcept;
    Information(Information&& mov) noexcept;
public:
    Information& operator=(const Information& cpy) = delete;
    Information& operator=(Information&& mov) = delete;
public:
    const error::Identification& Identification() const noexcept;
    const char * File() const noexcept;
    std::size_t Line() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

constexpr Information::Information() noexcept :
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    m_file(nullptr),
    m_line(static_cast<std::size_t>(-1)),
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
    m_id()
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE
constexpr Information::Information(const error::Identification& id, 
    const char* file, const std::size_t& line) noexcept :
        m_file(file),
        m_line(line),
        m_id(id)
{}
#else
constexpr Information::Information(const error::Identification& id) noexcept :
    m_id(id)
{}
#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Information::Information(const Information& cpy) noexcept :
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    m_file(cpy.m_file),
    m_line(cpy.m_line),
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
    m_id(cpy.m_id)
{}

Information::Information(Information&& mov) noexcept :
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    m_file(mov.m_file),
    m_line(mov.m_line),
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
    m_id(mov.m_id)
{}

const error::Identification& Information::Identification() const noexcept
{
    return m_id;
}

const char* Information::File() const noexcept
{
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    return m_file;
#else  
    return "";
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
}

std::size_t Information::Line() const noexcept
{
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
    return m_line;
#else
    return static_cast<std::size_t>(-1);
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
}

typename Information::OutputValueType& 
Information::Output(OutputValueType& out) const noexcept
{
    if (!this->m_id.IsDefault())
    {
        if (!this->m_id.IsCatch())
            output::Operator(out, "id ", this->m_id);
#ifdef USING_BASIC_ERROR_FILE_AND_LINE
        output::Operator(out, "file ", this->m_file);
        output::Operator(out, "line ", this->m_file);
#endif //!USING_BASIC_ERROR_FILE_AND_LINE
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

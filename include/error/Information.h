#ifndef BASIC_ERROR_INFORMATION_H_
#define BASIC_ERROR_INFORMATION_H_

#include "Identification.h"
#include "id/ToBytes.h"
#include "../Error.h"

#include <ostream>
#include <cstddef>

namespace basic
{
namespace error
{

class Information
{
private:
    const Identification m_id;
    const char* m_file;
    const std::size_t m_line;
public:
    constexpr Information();
    constexpr Information(const Identification& id, const char* file,
        const std::size_t& line);
public:
    Information(const Information& cpy);
    Information(Information&& mov);
public:
    Information& operator=(const Information& cpy) = delete;
    Information& operator=(Information&& mov) = delete;
public:
    const Identification& GetIdentification() const;
    const char* GetFile() const;
    const std::size_t& GetLine() const;
};

constexpr Information::Information() :
    m_id(),
    m_file(nullptr),
    m_line((std::size_t)-1)
{}

constexpr Information::Information(const Identification& id, 
    const char* file, const std::size_t& line) :
        m_id(id),
        m_file(file),
        m_line(line)
{}

Information::Information(const Information& cpy) :
    m_id(cpy.m_id),
    m_file(cpy.m_file),
    m_line(cpy.m_line)
{}

Information::Information(Information&& mov) :
    m_id(mov.m_id),
    m_file(mov.m_file),
    m_line(mov.m_line)
{}

const Identification& Information::GetIdentification() const
{
    return m_id;
}

const char* Information::GetFile() const
{
    return m_file;
}

const std::size_t& Information::GetLine() const
{
    return m_line;
}

} //!error

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::error::Information& info)
{
    if (!info.GetIdentification().Flag.Default)
    {
        if (!info.GetIdentification().Flag.Catch)
        {
            const auto flags = out.flags();
            out << std::hex << std::uppercase;
            out << "code " << info.GetIdentification();
        }
        else
            out << "\nin catch";
        out << " file " << info.GetFile();
        out << " line " << info.GetLine();
    }
    return out;
}

#endif //!BASIC_ERROR_INFORMATION_H_

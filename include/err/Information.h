#ifndef BASIC_ERR_INFORMATION_H_
#define BASIC_ERR_INFORMATION_H_

#include "Identification.h"
#include "intf/Output.h"
#include "defn/func/output/Operator.h"
#include "defn/type/Output.h"

#include <ostream>
#include <cstddef>

namespace basic
{
namespace err
{

class Information : public intf::Output
{
public:
    typedef defn::type::Output OutputType;
private:
    const err::Identification m_id;
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    const char * m_file;
    const std::size_t m_line;
#endif //!USING_BASIC_ERR_FILE_AND_LINE
public:
    inline constexpr Information() noexcept;
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    inline constexpr Information(const err::Identification& id, 
        const char* file, const std::size_t& line) noexcept;
#else
    inline constexpr Information(const err::Identification& id) noexcept;
#endif //!USING_BASIC_ERR_FILE_AND_LINE
public:
    inline Information(const Information& cpy) noexcept;
    inline Information(Information&& mov) noexcept;
public:
    Information& operator=(const Information& cpy) = delete;
    Information& operator=(Information&& mov) = delete;
public:
    inline const err::Identification& Identification() const noexcept;
    inline const char * File() const noexcept;
    inline std::size_t Line() const noexcept;
protected:
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline constexpr Information::Information() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    m_file(nullptr),
    m_line(static_cast<std::size_t>(-1)),
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    m_id()
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE
inline constexpr Information::Information(const err::Identification& id, 
    const char* file, const std::size_t& line) noexcept :
        m_file(file),
        m_line(line),
        m_id(id)
{}
#else
inline constexpr Information::
    Information(const err::Identification & id) noexcept :
        m_id(id)
{}
#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Information::Information(const Information & cpy) noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    m_file(cpy.m_file),
    m_line(cpy.m_line),
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    m_id(cpy.m_id)
{}

inline Information::Information(Information && mov) noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    m_file(mov.m_file),
    m_line(mov.m_line),
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    m_id(mov.m_id)
{}

inline const err::Identification& Information::
    Identification() const noexcept
{
    return m_id;
}

inline const char* Information::File() const noexcept
{
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    return m_file;
#else  
    return "";
#endif //!USING_BASIC_ERR_FILE_AND_LINE
}

inline std::size_t Information::Line() const noexcept
{
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    return m_line;
#else
    return static_cast<std::size_t>(-1);
#endif //!USING_BASIC_ERR_FILE_AND_LINE
}

inline const err::intf::Output & Information::
    operator>>(OutputType & out) const noexcept
{
    if (!this->m_id.IsDefault())
    {
        if (!this->m_id.IsCatch())
            defn::func::output::Operator(out, "id ", this->m_id);
#ifdef USING_BASIC_ERR_FILE_AND_LINE
        defn::func::output::Operator(out, "file ", this->m_file);
        defn::func::output::Operator(out, "line ", this->m_file);
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    }
    return *this;
}

} //!err

} //!basic

#endif //!BASIC_ERR_INFORMATION_H_

#ifndef BASIC_TEST_MSG_FORMAT_H_
#define BASIC_TEST_MSG_FORMAT_H_

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <utility>

namespace basic
{
namespace test
{
namespace msg
{

class Format
{
private:
    char* m_value;
    std::size_t m_size;
public:
    Format();
    template<std::size_t S>
    Format(const char (&cstr)[S]);
    Format(const char* cstr, const std::size_t& size);
    template<typename... TArgs>
    Format(const Format& format, const std::size_t& size,
        TArgs&&... args);
    Format(const Format&);
    Format(Format&&);
    ~Format();
public:
    Format& operator=(const Format&);
    Format& operator=(Format&&);
public:
    const char* Value() const;
    std::size_t Size() const;
    bool IsEmpty() const;
    operator bool() const;
};

inline Format::Format() :
    m_size(0),
    m_value(nullptr)
{}

template<std::size_t S>
inline Format::Format(const char (&cstr)[S]) :
    m_size(S),
    m_value(new char[S])
{
    memcpy(m_value, cstr, S);
}

inline Format::Format(const char* cstr, const std::size_t& size) :
    m_size(size),
    m_value(new char[size])
{
    memcpy(m_value, cstr, size);
}

template<typename... TArgs>
inline Format::Format(const Format& format, const std::size_t& size, 
    TArgs&&... args) : 
        m_size(size),
        m_value(new char[size])
{
    if (size != 0)
    {
        int ret = snprintf(m_value, m_size, format.Value(), 
            std::forward<TArgs>(args)...);
        if (ret < 0)
        {
            *(m_value) = '\0';
        }
        else if(ret >= m_size)
        {
            *(m_value + (m_size - 1)) = '\0';
        }
    }
}

inline Format::Format(const Format& cpy)
{
    if (cpy.operator bool())
    {
        m_value = new char[cpy.m_size];
        m_size = cpy.m_size;
        memcpy(m_value, cpy.m_value, cpy.m_size);
    }
    else
    {
        m_value = nullptr;
        m_size = 0;
    }
       
}

inline Format::Format(Format&& mov)
{
    if (mov.operator bool())
    {
        m_value = mov.m_value;
        m_size = mov.m_size;
        mov.m_value = nullptr;
        mov.m_size = 0;
    }
    else
    {
        m_value = nullptr;
        m_size = 0;
    }
}

inline Format::~Format()
{
    if (operator bool())
    {
        delete[] m_value;
        m_value = nullptr;
        m_size = 0;
    }
}

inline Format& Format::operator=(const Format& cpy)
{
    if (operator bool())
        delete[] m_value;
    if (cpy.operator bool())
    {
        m_value = new char[cpy.m_size];
        m_size = cpy.m_size;
        memcpy(m_value, cpy.m_value, cpy.m_size);
    }
    else
        m_size = 0;
}

inline Format& Format::operator=(Format&& mov)
{
    if (operator bool())
        delete[] m_value;
    if (mov.operator bool())
    {
        m_value = mov.m_value;
        m_size = mov.m_size;
        mov.m_value = nullptr;
        mov.m_size = 0;
    }
    else
        m_size = 0;
}

inline const char* Format::Value() const
{
    if (operator bool()) 
        return m_value;
    return nullptr;
}

inline std::size_t Format::Size() const
{
    if (operator bool()) 
        return m_size;
    return 0;
}

inline bool Format::IsEmpty() const
{
    if (operator bool() && m_value[0] == '\0')
        return false;
    return true;
}

inline Format::operator bool() const
{
    return m_value != nullptr; 
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_FORMAT_H_

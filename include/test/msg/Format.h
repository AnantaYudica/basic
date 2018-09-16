#ifndef BASIC_TEST_MSG_FORMAT_H_
#define BASIC_TEST_MSG_FORMAT_H_

#include "../CString.h"
#include "../cstr/Format.h"

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace msg
{

template<typename TChar = char>
class Format
{
public:
    typedef typename std::remove_const<TChar>::type CharType;
    typedef std::size_t SizeType;
private:
    test::CString<CharType> m_cstr;
public:
    Format();
    template<std::size_t S>
    Format(const CharType (&cstr)[S]);
    Format(const CharType* cstr, const SizeType& size);
    Format(const test::CString<CharType>& cstr);
    Format(const test::CString<const CharType>& cstr);
    Format(test::CString<CharType>&& cstr);
    Format(test::CString<const CharType>&& cstr);
    template<typename... TArgs>
    Format(const Format<TChar>& format, const SizeType& size,
        TArgs&&... args);
    Format(const Format<TChar>&);
    Format(Format<TChar>&&);
    ~Format();
public:
    Format<TChar>& operator=(const Format<TChar>&);
    Format<TChar>& operator=(Format<TChar>&&);
public:
    operator bool() const;
    const TChar* operator*() const;
    typename Format<TChar>::SizeType Size() const;
    bool IsEmpty() const;
};

template<typename TChar>
Format<TChar>::Format()
{}

template<typename TChar>
template<std::size_t S>
Format<TChar>::Format(const CharType (&cstr)[S]) :
    m_cstr(cstr)
{}

template<typename TChar>
Format<TChar>::Format(const CharType* cstr, const SizeType& size) :
    m_cstr(cstr, size)
{}

template<typename TChar>
Format<TChar>::Format(const test::CString<CharType>& cstr) :
    m_cstr(cstr)
{}

template<typename TChar>
Format<TChar>::Format(const test::CString<const CharType>& cstr) :
    m_cstr(cstr)
{}

template<typename TChar>
Format<TChar>::Format(test::CString<CharType>&& cstr) :
    m_cstr(std::move(cstr))
{}

template<typename TChar>
Format<TChar>::Format(test::CString<const CharType>&& cstr) :
    m_cstr(std::move(cstr))
{}

template<typename TChar>
template<typename... TArgs>
Format<TChar>::Format(const Format<TChar>& format, const SizeType& size, 
    TArgs&&... args) : 
        m_cstr(std::move(test::cstr::Format<CharType>(size, *format, 
            std::forward<TArgs>(args)...)))
{}

template<typename TChar>
Format<TChar>::Format(const Format<TChar>& cpy) :
    m_cstr(cpy.m_cstr)
{}

template<typename TChar>
Format<TChar>::Format(Format<TChar>&& mov) :
    m_cstr(std::move(mov.m_cstr))
{}

template<typename TChar>
Format<TChar>::~Format()
{}

template<typename TChar>
Format<TChar>& Format<TChar>::operator=(const Format<TChar>& cpy)
{
    m_cstr = cpy.m_cstr;
    return *this;
}

template<typename TChar>
Format<TChar>& Format<TChar>::operator=(Format<TChar>&& mov)
{
    m_cstr = std::move(mov.m_cstr);
    return *this;
}

template<typename TChar>
Format<TChar>::operator bool() const
{
    return *m_cstr != nullptr; 
}

template<typename TChar>
const TChar* Format<TChar>::operator*() const
{
    if (operator bool())
        return *m_cstr;
    return "";
}

template<typename TChar>
typename Format<TChar>::SizeType Format<TChar>::Size() const
{
    return m_cstr.Size();
}

template<typename TChar>
bool Format<TChar>::IsEmpty() const
{
    if (!operator bool() || m_cstr[0] != '\0')
        return false;
    return true;
}


} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_FORMAT_H_

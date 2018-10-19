#ifndef BASIC_CSTR_ELEMENT_H_
#define BASIC_CSTR_ELEMENT_H_

#include <cstddef>
#include <utility>
#include <string>
#include <type_traits>

#include "ch/Trait.h"

namespace basic
{
namespace cstr
{

template<typename TChar, typename TCharTrait = 
    std::char_traits<typename std::remove_const<TChar>::type>>
class Element : public Element<const TChar, TCharTrait>
{
public:
    typedef Element<const TChar, TCharTrait> ConstElementType;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
public:
    typedef std::ptrdiff_t DifferenceType;
    typedef std::size_t SizeType;
public:
    typedef typename ch::Trait<TCharTrait>::CharType CharType;
    typedef typename ch::Trait<TCharTrait>::IntType IntType;
public:
    Element();
    Element(CharType*& dptr, SizeType& size, 
        const SizeType& pos = 0);
public:
    Element(const Element<TChar, TCharTrait>& cpy);
    Element(Element<TChar, TCharTrait>&& mov);
    ~Element();
public:
    Element<TChar, TCharTrait>& operator=(const CharType& ch);
    Element<TChar, TCharTrait>& 
        operator=(const Element<TChar, TCharTrait>& elem);
    Element<TChar, TCharTrait>& 
        operator=(Element<TChar, TCharTrait>&& elem);
public:
    Element<TChar, TCharTrait>& operator++();
    Element<TChar, TCharTrait> operator++(int);
    Element<TChar, TCharTrait>& operator--();
    Element<TChar, TCharTrait> operator--(int);
public:
    Element<TChar, TCharTrait>& operator+=(const DifferenceType& diff);
    Element<TChar, TCharTrait>& operator-=(const DifferenceType& diff);
public:
    Element<TChar, TCharTrait> operator+(const DifferenceType& diff);
    Element<TChar, TCharTrait> operator-(const DifferenceType& diff);
    DifferenceType operator-(const Element<TChar, TCharTrait>& elem);
public:
    CharType* Get();
    const CharType* Get() const;
};

template<typename TChar, typename TCharTrait>
class Element<const TChar, TCharTrait>
{
    friend class Element<TChar, TCharTrait>;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
public:
    typedef std::ptrdiff_t DifferenceType;
    typedef std::size_t SizeType;
public:
    typedef typename TCharTrait::char_type CharType;
    typedef typename TCharTrait::int_type IntType;
private:
    CharType** m_dptr;
    SizeType* m_size;
    SizeType m_pos;
public:
    Element();
    Element(const CharType*& dptr, const SizeType& size,
        const SizeType& pos = 0);
protected:
    Element(CharType** dptr, SizeType* size, 
        const SizeType& pos);
public:
    Element(const Element<const TChar, TCharTrait>& cpy);
    Element(Element<const TChar, TCharTrait>&& mov);
    ~Element();
private:
    bool IsEnd() const;
public:
    Element<const TChar, TCharTrait>& 
        operator=(const Element<const TChar, TCharTrait>& cpy) = delete;
    Element<const TChar, TCharTrait>& 
        operator=(Element<const TChar, TCharTrait>&& mov) = delete;
public:
    Element<const TChar, TCharTrait>& operator++();
    Element<const TChar, TCharTrait> operator++(int);
    Element<const TChar, TCharTrait>& operator--();
    Element<const TChar, TCharTrait> operator--(int);
public:
    Element<const TChar, TCharTrait>& operator+=(const DifferenceType& diff);
    Element<const TChar, TCharTrait>& operator-=(const DifferenceType& diff);
public:
    Element<const TChar, TCharTrait> operator+(const DifferenceType& diff);
    Element<const TChar, TCharTrait> operator-(const DifferenceType& diff);
    DifferenceType operator-(const Element<const TChar, TCharTrait>& elem);
public:
    const CharType& operator*() const;
public:
    const CharType* Get() const;
public:
    bool operator==(const CharType& ch) const;
    bool operator==(const Element<const TChar, TCharTrait>& elem) const;
    bool operator!=(const CharType& ch) const;
    bool operator!=(const Element<const TChar, TCharTrait>& elem) const;
    bool operator<(const CharType& ch) const;
    bool operator<(const Element<const TChar, TCharTrait>& elem) const;
    bool operator>(const CharType& ch) const;
    bool operator>(const Element<const TChar, TCharTrait>& elem) const;
    bool operator<=(const CharType& ch) const;
    bool operator<=(const Element<const TChar, TCharTrait>& elem) const;
    bool operator>=(const CharType& ch) const;
    bool operator>=(const Element<const TChar, TCharTrait>& elem) const;
public:
    operator bool() const;
};


template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>::Element() :
    Element<const TChar, TCharTrait>(nullptr, nullptr, 0)
{}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>::Element(CharType*& dptr, SizeType& size,
    const SizeType& pos) :
        Element<const TChar, TCharTrait>(&dptr, &size, pos)
{}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>::Element(const Element<TChar, TCharTrait>& cpy) :
    Element<const TChar, TCharTrait>(cpy)
{}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>::Element(Element<TChar, TCharTrait>&& mov) :
    Element<const TChar, TCharTrait>(std::move(mov))
{}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>::~Element()
{}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::
    operator=(const CharType& ch)
{
    if (!this->IsEnd())
        ch::Trait<TCharTrait>::Assign(
            (*ConstElementType::m_dptr)[ConstElementType::m_pos], ch);
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::
    operator=(const Element<TChar, TCharTrait>& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Copy((*ConstElementType::m_dptr) + 
            ConstElementType::m_pos, elem.m_dptr + elem.m_pos, 1);
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::
    operator=(Element<TChar, TCharTrait>&& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Move((*ConstElementType::m_dptr) + 
            ConstElementType::m_pos, (*elem.m_dptr) + elem.m_pos, 1);
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::operator++()
{
    ConstElementType::operator++();
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait> Element<TChar, TCharTrait>::operator++(int)
{
    if (!this->IsEnd())
    {
        Element<TChar, TCharTrait> cpy(*this);
        ConstElementType::operator++();
        return cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::operator--()
{
    ConstElementType::operator--();
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait> Element<TChar, TCharTrait>::operator--(int)
{
    if (!this->IsEnd())
    {
        Element<TChar, TCharTrait> cpy(*this);
        ConstElementType::operator--();
        return cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::
    operator+=(const DifferenceType& diff)
{
    ConstElementType::operator+=(diff);
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait>& Element<TChar, TCharTrait>::
    operator-=(const DifferenceType& diff)
{
    ConstElementType::operator-=(diff);
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait> Element<TChar, TCharTrait>::
    operator+(const DifferenceType& diff)
{
    Element<TChar, TCharTrait> cpy(*this);
    cpy += diff;
    return cpy;
}

template<typename TChar, typename TCharTrait>
Element<TChar, TCharTrait> Element<TChar, TCharTrait>::
    operator-(const DifferenceType& diff)
{
    Element<TChar, TCharTrait> cpy(*this);
    cpy -= diff;
    return cpy;
}

template<typename TChar, typename TCharTrait>
typename Element<TChar, TCharTrait>::DifferenceType 
    Element<TChar, TCharTrait>::operator-(const Element<TChar, 
        TCharTrait>& elem)
{
    return std::move(ConstElementType::operator-(elem));
}

template<typename TChar, typename TCharTrait>
typename Element<TChar, TCharTrait>::CharType* 
    Element<TChar, TCharTrait>::Get()
{
    if (!this->IsEnd())
        return &((*ConstElementType::m_dptr)[ConstElementType::m_pos]);
    return nullptr;
}

template<typename TChar, typename TCharTrait>
const typename Element<TChar, TCharTrait>::CharType* 
    Element<TChar, TCharTrait>::Get() const
{
    if (!this->IsEnd())
        return &((*ConstElementType::m_dptr)[ConstElementType::m_pos]);
    return nullptr;
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::Element() :
    m_dptr(nullptr),
    m_size(nullptr),
    m_pos(0)
{}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::
    Element(const CharType*& dptr, const SizeType& size, const SizeType& pos) :
        m_dptr(const_cast<CharType**>(&dptr)),
        m_size(const_cast<SizeType*>(&size)),
        m_pos((pos <= size ? pos : size))
{}
    
template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::
    Element(CharType** dptr, SizeType* size, const SizeType& pos) :
        m_dptr(dptr),
        m_size(size),
        m_pos((size == nullptr ? 0 : (pos <= *size ? pos : *size)))
{}
    
template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::
    Element(const Element<const TChar, TCharTrait>& cpy) :
        m_dptr(cpy.m_dptr),
        m_size(cpy.m_size),
        m_pos(cpy.m_pos)
{}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::
    Element(Element<const TChar, TCharTrait>&& mov) :
        m_dptr(std::move(mov.m_dptr)),
        m_size(std::move(mov.m_size)),
        m_pos(std::move(mov.m_pos))
{
    mov.m_dptr = nullptr;
    mov.m_size = nullptr;
    mov.m_pos = 0;
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::~Element()
{
    m_dptr = nullptr;
    m_size = nullptr;
    m_pos = 0;
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::IsEnd() const
{
    return !(*this && this->m_pos != *(this->m_size)); 
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>& 
    Element<const TChar, TCharTrait>::operator++()
{
    if (!this->IsEnd())
        if (*m_size > m_pos)
            ++m_pos;
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait> 
    Element<const TChar, TCharTrait>::operator++(int)
{
    if (!this->IsEnd())
    {
        Element<const TChar, TCharTrait> cpy(*this);
        return ++cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>& 
    Element<const TChar, TCharTrait>::operator--()
{
    if (!this->IsEnd())
        if (0 < m_pos)
            --m_pos;
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait> 
    Element<const TChar, TCharTrait>::operator--(int)
{
    if (!this->IsEnd())
    {
        Element<const TChar, TCharTrait> cpy(*this);
        return --cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>& 
    Element<const TChar, TCharTrait>::operator+=(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        if (diff >= 0)
        {
            if (SizeType(m_pos + diff) < *m_size)
                m_pos += diff;
            else
                m_pos = *m_size;
        }
        else
            Element<const TChar, TCharTrait>::operator-=(-diff);
    }
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>& 
    Element<const TChar, TCharTrait>::operator-=(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        if (diff >= 0)
        {
            if ((SizeType)diff < m_pos)
                m_pos -= diff;
            else
                m_pos = 0;
        }
        else
            Element<const TChar, TCharTrait>::operator+=(-diff);
    }
    return *this;
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait> 
    Element<const TChar, TCharTrait>::operator+(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        Element<const TChar, TCharTrait> cpy(*this);
        return cpy += diff;
    }
    return {};
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait> 
    Element<const TChar, TCharTrait>::operator-(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        Element<const TChar, TCharTrait> cpy(*this);
        return cpy -= diff;
    }
    return {};
}

template<typename TChar, typename TCharTrait>
typename Element<const TChar, TCharTrait>::DifferenceType
    Element<const TChar, TCharTrait>::
        operator-(const Element<const TChar, TCharTrait>& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        if (*(this->m_dptr) == *(elem.m_dptr))
            return (DifferenceType)m_pos - elem.m_pos;
    if (this->IsEnd())
        return 0;
    return (DifferenceType)m_pos - *m_size;
}

template<typename TChar, typename TCharTrait>
const typename Element<const TChar, TCharTrait>::CharType& 
    Element<const TChar, TCharTrait>::operator*() const
{
    if (!this->IsEnd())
        return (*m_dptr)[m_pos];
    return std::move(CharType('\0'));
}

template<typename TChar, typename TCharTrait>
const typename Element<const TChar, TCharTrait>::CharType*
    Element<const TChar, TCharTrait>::Get() const
{
    if (!this->IsEnd())
        return &(*m_dptr)[m_pos];
    return nullptr;
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::operator==(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::Equal((*m_dptr)[m_pos], ch);
    return false;
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::
    operator==(const Element<const TChar, TCharTrait>& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (*(this->m_dptr) != *(elem.m_dptr))
            return operator==(*elem);
        return this->m_pos == elem.m_pos;
    }
    return this->IsEnd() && elem.IsEnd();
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::operator!=(const CharType& ch) const
{
    return !operator==(ch);
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::
    operator!=(const Element<const TChar, TCharTrait>& elem) const
{
    return !operator==(elem);
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::operator<(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::LessThan(*(m_dptr)[m_pos], ch);
    return false;
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::
    operator<(const Element<const TChar, TCharTrait>& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (*(this->m_dptr) != *(elem.m_dptr) || this->m_pos != elem.m_pos)
            return operator<(*elem);
        return false;
    }
    return !this->IsEnd();
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::operator>(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::LessThan(ch, (*m_dptr)[m_pos]);
    return false;
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::
    operator>(const Element<const TChar, TCharTrait>& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (*(this->m_dptr) != *(elem.m_dptr) || this->m_pos != elem.m_pos)
            return operator>(*elem);
        return false;
    }
    return !elem.IsEnd();
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::operator<=(const CharType& ch) const
{
    return operator<(ch) || operator==(ch);
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::
    operator<=(const Element<const TChar, TCharTrait>& elem) const
{
    return operator<(elem) || operator==(elem);
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::operator>=(const CharType& ch) const
{
    return operator>(ch) || operator==(ch);
}

template<typename TChar, typename TCharTrait>
bool Element<const TChar, TCharTrait>::
    operator>=(const Element<const TChar, TCharTrait>& elem) const
{
    return operator>(elem) || operator==(elem);
}

template<typename TChar, typename TCharTrait>
Element<const TChar, TCharTrait>::operator bool() const
{
    return m_dptr != nullptr && *m_dptr != nullptr;
}

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ELEMENT_H_

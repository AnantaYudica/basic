#ifndef BASIC_CSTR_ELEMENT_H_
#define BASIC_CSTR_ELEMENT_H_

#include <cstddef>
#include <utility>
#include <string>
#include <type_traits>

#include "ch/Trait.h"
#include "elem/Forward.h"

namespace basic
{
namespace cstr
{

template<typename TChar, typename TCharTrait = 
    std::char_traits<typename std::remove_const<TChar>::type>,
    typename TElemTrait = cstr::elem::Forward<std::size_t, std::ptrdiff_t>>
class Element : public Element<const TChar, TCharTrait, TElemTrait>
{
public:
    typedef Element<const TChar, TCharTrait, TElemTrait> ConstElementType;
    typedef Element<TChar, TCharTrait, TElemTrait> ElementType;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    typedef TElemTrait ElementTraitType;
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
    Element(const ElementType& cpy);
    Element(ElementType&& mov);
    ~Element();
public:
    ElementType& operator=(const CharType& ch);
    ElementType& operator=(const ElementType& elem);
    ElementType& operator=(ElementType&& elem);
public:
    ElementType& operator++();
    ElementType operator++(int);
    ElementType& operator--();
    ElementType operator--(int);
public:
    ElementType& operator+=(const DifferenceType& diff);
    ElementType& operator-=(const DifferenceType& diff);
public:
    ElementType operator+(const DifferenceType& diff);
    ElementType operator-(const DifferenceType& diff);
    DifferenceType operator-(const ElementType& elem);
public:
    CharType* Get();
    const CharType* Get() const;
};

template<typename TChar, typename TCharTrait, typename TElemTrait>
class Element<const TChar, TCharTrait, TElemTrait>
{
    friend class Element<TChar, TCharTrait, TElemTrait>;
public:
    typedef Element<const TChar, TCharTrait, TElemTrait> ConstElementType;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    typedef TElemTrait ElementTraitType;
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
    Element(const ConstElementType& cpy);
    Element(ConstElementType&& mov);
    ~Element();
private:
    bool IsEnd() const;
public:
    ConstElementType& operator=(const ConstElementType& cpy) = delete;
    ConstElementType& operator=(ConstElementType&& mov) = delete;
public:
    ConstElementType& operator++();
    ConstElementType operator++(int);
    ConstElementType& operator--();
    ConstElementType operator--(int);
public:
    ConstElementType& operator+=(const DifferenceType& diff);
    ConstElementType& operator-=(const DifferenceType& diff);
public:
    ConstElementType operator+(const DifferenceType& diff);
    ConstElementType operator-(const DifferenceType& diff);
    DifferenceType operator-(const ConstElementType& elem);
public:
    const CharType& operator*() const;
public:
    const CharType* Get() const;
public:
    bool operator==(const CharType& ch) const;
    bool operator==(const ConstElementType& elem) const;
    bool operator!=(const CharType& ch) const;
    bool operator!=(const ConstElementType& elem) const;
    bool operator<(const CharType& ch) const;
    bool operator<(const ConstElementType& elem) const;
    bool operator>(const CharType& ch) const;
    bool operator>(const ConstElementType& elem) const;
    bool operator<=(const CharType& ch) const;
    bool operator<=(const ConstElementType& elem) const;
    bool operator>=(const CharType& ch) const;
    bool operator>=(const ConstElementType& elem) const;
public:
    operator bool() const;
};

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<TChar, TCharTrait, TElemTrait>::Element() :
    ConstElementType(nullptr, nullptr, 0)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<TChar, TCharTrait, TElemTrait>::Element(CharType*& dptr, 
    SizeType& size, const SizeType& pos) :
        ConstElementType(&dptr, &size, pos)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<TChar, TCharTrait, TElemTrait>::Element(const ElementType& cpy) :
    ConstElementType(cpy)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<TChar, TCharTrait, TElemTrait>::Element(ElementType&& mov) :
    ConstElementType(std::move(mov))
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<TChar, TCharTrait, TElemTrait>::~Element()
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator=(const CharType& ch)
{
    if (!this->IsEnd())
        ch::Trait<TCharTrait>::Assign(
            (*ConstElementType::m_dptr)[ElementTraitType::
                Position(ConstElementType::m_pos, 
                    *ConstElementType::m_size)], ch);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator=(const ElementType& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Copy((*ConstElementType::m_dptr) + 
            ElementTraitType::Position(ConstElementType::m_pos,
            *ConstElementType::m_size), elem.m_dptr + 
            ElementTraitType::Position(elem.m_pos, *elem.m_size), 1);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator=(ElementType&& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Move((*ConstElementType::m_dptr) + 
            ElementTraitType::Position(ConstElementType::m_pos,
            *ConstElementType::m_size), (*elem.m_dptr) + 
            ElementTraitType::Position(elem.m_pos, *elem.m_size), 1);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator++()
{
    ConstElementType::operator++();
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType 
    Element<TChar, TCharTrait, TElemTrait>::operator++(int)
{
    if (!this->IsEnd())
    {
        ElementType cpy(*this);
        ConstElementType::operator++();
        return cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator--()
{
    ConstElementType::operator--();
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType 
    Element<TChar, TCharTrait, TElemTrait>::operator--(int)
{
    if (!this->IsEnd())
    {
        ElementType cpy(*this);
        ConstElementType::operator--();
        return cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::
        operator+=(const DifferenceType& diff)
{
    ConstElementType::operator+=(diff);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::
        operator-=(const DifferenceType& diff)
{
    ConstElementType::operator-=(diff);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType 
    Element<TChar, TCharTrait, TElemTrait>::
        operator+(const DifferenceType& diff)
{
    ElementType cpy(*this);
    cpy += diff;
    return cpy;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType 
    Element<TChar, TCharTrait, TElemTrait>::
        operator-(const DifferenceType& diff)
{
    ElementType cpy(*this);
    cpy -= diff;
    return cpy;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::DifferenceType 
    Element<TChar, TCharTrait, TElemTrait>::operator-(const ElementType& elem)
{
    return std::move(ConstElementType::operator-(elem));
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::CharType* 
    Element<TChar, TCharTrait, TElemTrait>::Get()
{
    if (!this->IsEnd())
        return &((*ConstElementType::m_dptr)[ElementTraitType::
            Position(ConstElementType::m_pos, *ConstElementType::m_size)]);
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<TChar, TCharTrait, TElemTrait>::CharType* 
    Element<TChar, TCharTrait, TElemTrait>::Get() const
{
    if (!this->IsEnd())
        return &((*ConstElementType::m_dptr)[ElementTraitType::
            Position(ConstElementType::m_pos, *ConstElementType::m_size)]);
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::Element() :
    m_dptr(nullptr),
    m_size(nullptr),
    m_pos(0)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(const CharType*& dptr, const SizeType& size, const SizeType& pos) :
        m_dptr(const_cast<CharType**>(&dptr)),
        m_size(const_cast<SizeType*>(&size)),
        m_pos((pos <= size ? pos : size))
{}
    
template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(CharType** dptr, SizeType* size, const SizeType& pos) :
        m_dptr(dptr),
        m_size(size),
        m_pos((size == nullptr ? 0 : (pos <= *size ? pos : *size)))
{}
    
template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(const ConstElementType& cpy) :
        m_dptr(cpy.m_dptr),
        m_size(cpy.m_size),
        m_pos(cpy.m_pos)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(ConstElementType&& mov) :
        m_dptr(std::move(mov.m_dptr)),
        m_size(std::move(mov.m_size)),
        m_pos(std::move(mov.m_pos))
{
    mov.m_dptr = nullptr;
    mov.m_size = nullptr;
    mov.m_pos = 0;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::~Element()
{
    m_dptr = nullptr;
    m_size = nullptr;
    m_pos = 0;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::IsEnd() const
{
    return !(*this && this->m_pos != *(this->m_size)); 
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType& 
    Element<const TChar, TCharTrait, TElemTrait>::operator++()
{
    if (!this->IsEnd())
        ElementTraitType::Increment(m_pos, *m_size);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType 
    Element<const TChar, TCharTrait, TElemTrait>::operator++(int)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return ++cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType& 
    Element<const TChar, TCharTrait, TElemTrait>::operator--()
{
    if (!this->IsEnd())
        ElementTraitType::Decrement(m_pos, *m_size);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType 
    Element<const TChar, TCharTrait, TElemTrait>::operator--(int)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return --cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType& 
    Element<const TChar, TCharTrait, TElemTrait>::
        operator+=(const DifferenceType& diff)
{
    if (!this->IsEnd())
        ElementTraitType::Increment(m_pos, diff, *m_size);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType& 
    Element<const TChar, TCharTrait, TElemTrait>::
        operator-=(const DifferenceType& diff)
{
    if (!this->IsEnd())
        ElementTraitType::Decrement(m_pos, diff, *m_size);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType 
    Element<const TChar, TCharTrait, TElemTrait>::
        operator+(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return cpy += diff;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType 
    Element<const TChar, TCharTrait, TElemTrait>::
        operator-(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return cpy -= diff;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::DifferenceType
    Element<const TChar, TCharTrait, TElemTrait>::
        operator-(const ConstElementType& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        if (*(this->m_dptr) == *(elem.m_dptr))
            return (DifferenceType)m_pos - elem.m_pos;
    if (this->IsEnd())
        return 0;
    return (DifferenceType)m_pos - *m_size;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::CharType& 
    Element<const TChar, TCharTrait, TElemTrait>::operator*() const
{
    if (!this->IsEnd())
        return (*m_dptr)[ElementTraitType::Position(m_pos, *m_size)];
    return std::move(CharType('\0'));
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::CharType*
    Element<const TChar, TCharTrait, TElemTrait>::Get() const
{
    if (!this->IsEnd())
        return &(*m_dptr)[ElementTraitType::Position(m_pos, *m_size)];
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator==(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::Equal((*m_dptr)[
            ElementTraitType::Position(m_pos, *m_size)], ch);
    return false;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator==(const ConstElementType& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (*(this->m_dptr) != *(elem.m_dptr))
            return operator==(*elem);
        return this->m_pos == elem.m_pos;
    }
    return this->IsEnd() && elem.IsEnd();
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator!=(const CharType& ch) const
{
    return !operator==(ch);
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator!=(const ConstElementType& elem) const
{
    return !operator==(elem);
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator<(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::LessThan(*(m_dptr)[
            ElementTraitType::Position(m_pos, *m_size)], ch);
    return false;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator<(const ConstElementType& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (*(this->m_dptr) != *(elem.m_dptr) || this->m_pos != elem.m_pos)
            return operator<(*elem);
        return false;
    }
    return !this->IsEnd();
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator>(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::LessThan(ch, (*m_dptr)[
            ElementTraitType::Position(m_pos)]);
    return false;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator>(const ConstElementType& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (*(this->m_dptr) != *(elem.m_dptr) || this->m_pos != elem.m_pos)
            return operator>(*elem);
        return false;
    }
    return !elem.IsEnd();
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator<=(const CharType& ch) const
{
    return operator<(ch) || operator==(ch);
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator<=(const ConstElementType& elem) const
{
    return operator<(elem) || operator==(elem);
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator>=(const CharType& ch) const
{
    return operator>(ch) || operator==(ch);
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator>=(const ConstElementType& elem) const
{
    return operator>(elem) || operator==(elem);
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::operator bool() const
{
    return m_dptr != nullptr && *m_dptr != nullptr;
}

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ELEMENT_H_

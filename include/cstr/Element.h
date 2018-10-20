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
    Element(CharType*& cstr, SizeType& size, 
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
    CharType** m_cstrPtr;
    SizeType* m_sizePtr;
    SizeType m_pos;
public:
    Element();
    Element(const CharType*& cstr, const SizeType& size,
        const SizeType& pos = 0);
protected:
    Element(CharType** cstr_ptr, SizeType* size_ptr, 
        const SizeType& pos);
public:
    Element(const ConstElementType& cpy);
    Element(ConstElementType&& mov);
    ~Element();
private:
    bool IsEnd() const;
    SizeType TraitPosition() const;
    const SizeType& Position() const;
    SizeType Size() const;
    CharType& Value();
    const CharType& Value() const;
    CharType* Pointer(const SizeType& off = 0);
    const CharType* Pointer(const SizeType& off = 0) const;
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
Element<TChar, TCharTrait, TElemTrait>::Element(CharType*& cstr, 
    SizeType& size, const SizeType& pos) :
        ConstElementType(&cstr, &size, pos)
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
        ch::Trait<TCharTrait>::Assign(this->Value(), ch);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator=(const ElementType& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Copy(this->Pointer(this->TraitPosition()),
            elem.Pointer(elem.TraitPosition()), 1);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<TChar, TCharTrait, TElemTrait>::ElementType& 
    Element<TChar, TCharTrait, TElemTrait>::operator=(ElementType&& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Move(this->Pointer(this->TraitPosition()),
            elem.Pointer(elem.TraitPosition()), 1);
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
        return this->Pointer(this->TraitPosition());
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<TChar, TCharTrait, TElemTrait>::CharType* 
    Element<TChar, TCharTrait, TElemTrait>::Get() const
{
    if (!this->IsEnd())
        return this->Pointer(this->TraitPosition());
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::Element() :
    m_cstrPtr(nullptr),
    m_sizePtr(nullptr),
    m_pos(0)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(const CharType*& cstr, const SizeType& size, const SizeType& pos) :
        m_cstrPtr(const_cast<CharType**>(&cstr)),
        m_sizePtr(const_cast<SizeType*>(&size)),
        m_pos((pos <= size ? pos : size))
{}
    
template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(CharType** cstr_ptr, SizeType* size_ptr, const SizeType& pos) :
        m_cstrPtr(cstr_ptr),
        m_sizePtr(size_ptr),
        m_pos((size_ptr == nullptr ? 0 : 
            (pos <= *size_ptr ? pos : *size_ptr)))
{}
    
template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(const ConstElementType& cpy) :
        m_cstrPtr(cpy.m_cstrPtr),
        m_sizePtr(cpy.m_sizePtr),
        m_pos(cpy.m_pos)
{}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::
    Element(ConstElementType&& mov) :
        m_cstrPtr(std::move(mov.m_cstrPtr)),
        m_sizePtr(std::move(mov.m_sizePtr)),
        m_pos(std::move(mov.m_pos))
{
    mov.m_cstrPtr = nullptr;
    mov.m_sizePtr = nullptr;
    mov.m_pos = 0;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
Element<const TChar, TCharTrait, TElemTrait>::~Element()
{
    m_cstrPtr = nullptr;
    m_sizePtr = nullptr;
    m_pos = 0;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::IsEnd() const
{
    return !(*this && this->Position() != this->Size()); 
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::SizeType 
    Element<const TChar, TCharTrait, TElemTrait>::TraitPosition() const
{
    return ElementTraitType::Position(this->Position(), this->Size());
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::SizeType& 
    Element<const TChar, TCharTrait, TElemTrait>::Position() const
{
    return m_pos;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::SizeType 
    Element<const TChar, TCharTrait, TElemTrait>::Size() const
{
    return *m_sizePtr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::CharType&
    Element<const TChar, TCharTrait, TElemTrait>::Value()
{
    return (*m_cstrPtr)[TraitPosition()];
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::CharType&
    Element<const TChar, TCharTrait, TElemTrait>::Value() const
{
    return (*m_cstrPtr)[TraitPosition()];
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::CharType* 
    Element<const TChar, TCharTrait, TElemTrait>::
        Pointer(const SizeType& off)
{
    return (*m_cstrPtr) + off;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::CharType* 
    Element<const TChar, TCharTrait, TElemTrait>::
        Pointer(const SizeType& off) const
{
    return (*m_cstrPtr) + off;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType& 
    Element<const TChar, TCharTrait, TElemTrait>::operator++()
{
    if (!this->IsEnd())
        m_pos = ElementTraitType::Increment(this->Position(), 
            this->Size());
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
        m_pos = ElementTraitType::Decrement(this->Position(), 
            this->Size());
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
        m_pos = ElementTraitType::Increment(this->Position(), diff, 
            this->Size());
    return *this;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
typename Element<const TChar, TCharTrait, TElemTrait>::ConstElementType& 
    Element<const TChar, TCharTrait, TElemTrait>::
        operator-=(const DifferenceType& diff)
{
    if (!this->IsEnd())
        m_pos = ElementTraitType::Decrement(this->Position(), diff, 
            this->Size());
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
        if (this->Pointer() == elem.Pointer())
            return (DifferenceType)this->Position() - elem.Position();
    if (this->IsEnd())
        return 0;
    return (DifferenceType)this->Position() - this->Size();
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::CharType& 
    Element<const TChar, TCharTrait, TElemTrait>::operator*() const
{
    if (!this->IsEnd())
        return this->Value();
    return std::move(CharType('\0'));
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TElemTrait>::CharType*
    Element<const TChar, TCharTrait, TElemTrait>::Get() const
{
    if (!this->IsEnd())
        return &(this->Value());
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator==(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::Equal(this->Value(), ch);
    return false;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator==(const ConstElementType& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (this->Pointer() != elem.Pointer())
            return operator==(*elem);
        return this->Position() == elem.Position();
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
        return ch::Trait<TCharTrait>::LessThan(this->Value(), ch);
    return false;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator<(const ConstElementType& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (this->Pointer() != elem.Pointer() || 
            this->Position() != elem.Position())
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
        return ch::Trait<TCharTrait>::LessThan(ch, this->Value());
    return false;
}

template<typename TChar, typename TCharTrait, typename TElemTrait>
bool Element<const TChar, TCharTrait, TElemTrait>::
    operator>(const ConstElementType& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (this->Pointer() != elem.Pointer() || 
            this->Position() != elem.Position())
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
    return m_cstrPtr != nullptr && this->Pointer() != nullptr;
}

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ELEMENT_H_

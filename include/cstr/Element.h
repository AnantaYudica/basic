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
    typename TSize = std::size_t, typename TDifference = std::ptrdiff_t,
    typename TElemTrait = cstr::elem::Forward<TSize, TDifference>>
class Element : public Element<const TChar, TCharTrait, TSize,
    TDifference, TElemTrait>
{
public:
    typedef Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait> ConstElementType;
    typedef Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait> ElementType;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    typedef TElemTrait ElementTraitType;
public:
    typedef TDifference DifferenceType;
    typedef TSize SizeType;
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
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    ElementType& operator=(const Element<TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem);
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    ElementType& operator=(Element<TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>&& elem);
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
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    DifferenceType operator-(const Element<TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem);
public:
    CharType* Get();
    const CharType* Get() const;
};

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
class Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>
{
    friend class Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>;
public:
    typedef Element<const TChar, TCharTrait, TSize, TDifference, 
        TElemTrait> ConstElementType;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    typedef TElemTrait ElementTraitType;
public:
    typedef TDifference DifferenceType;
    typedef TSize SizeType;
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
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    ConstElementType& operator=(const Element<const TChar, TCharTrait,
        TSize_, TDifference_, TElemTrait_>& cpy) = delete;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    ConstElementType& operator=(Element<const TChar, TCharTrait,
        TSize_, TDifference_, TElemTrait_>&& mov) = delete;
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
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    DifferenceType operator-(const Element<const TChar, TCharTrait,
        TSize_, TDifference_, TElemTrait_>& elem);
public:
    const CharType& operator*() const;
public:
    const CharType* Get() const;
public:
    bool operator==(const CharType& ch) const;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    bool operator==(const Element<const TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem) const;
    bool operator!=(const CharType& ch) const;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    bool operator!=(const Element<const TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem) const;
    bool operator<(const CharType& ch) const;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    bool operator<(const Element<const TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem) const;
    bool operator>(const CharType& ch) const;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    bool operator>(const Element<const TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem) const;
    bool operator<=(const CharType& ch) const;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    bool operator<=(const Element<const TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem) const;
    bool operator>=(const CharType& ch) const;
    template<typename TElemTrait_ = TElemTrait, typename TSize_ = TSize, 
        typename TDifference_ = TDifference>
    bool operator>=(const Element<const TChar, TCharTrait, TSize_,
        TDifference_, TElemTrait_>& elem) const;
public:
    operator bool() const;
};

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::Element() :
    ConstElementType(nullptr, nullptr, 0)
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(CharType*& cstr, SizeType& size, const SizeType& pos) :
        ConstElementType(&cstr, &size, pos)
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(const ElementType& cpy) :
        ConstElementType(cpy)
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(ElementType&& mov) :
        ConstElementType(std::move(mov))
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::~Element()
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& 
        Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::
            operator=(const CharType& ch)
{
    if (!this->IsEnd())
        ch::Trait<TCharTrait>::Assign(this->Value(), ch);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& Element<TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator=(const Element<TChar, TCharTrait, 
            TSize_, TDifference_, TElemTrait_>& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Copy(this->Pointer(this->TraitPosition()),
            elem.Pointer(elem.TraitPosition()), 1);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator=(Element<TChar, TCharTrait, TSize_,
            TDifference_, TElemTrait_>&& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        ch::Trait<TCharTrait>::Move(this->Pointer(this->TraitPosition()),
            elem.Pointer(elem.TraitPosition()), 1);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator++()
{
    ConstElementType::operator++();
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator++(int)
{
    if (!this->IsEnd())
    {
        ElementType cpy(*this);
        ConstElementType::operator++();
        return cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator--()
{
    ConstElementType::operator--();
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator--(int)
{
    if (!this->IsEnd())
    {
        ElementType cpy(*this);
        ConstElementType::operator--();
        return cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator+=(const DifferenceType& diff)
{
    ConstElementType::operator+=(diff);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType& Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator-=(const DifferenceType& diff)
{
    ConstElementType::operator-=(diff);
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator+(const DifferenceType& diff)
{
    ElementType cpy(*this);
    cpy += diff;
    return cpy;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ElementType Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator-(const DifferenceType& diff)
{
    ElementType cpy(*this);
    cpy -= diff;
    return cpy;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::DifferenceType Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::operator-(const Element<TChar, TCharTrait, TSize_,
            TDifference_, TElemTrait_>& elem)
{
    return std::move(ConstElementType::operator-(elem));
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::CharType* 
    Element<TChar, TCharTrait, TSize, TDifference, TElemTrait>::Get()
{
    if (!this->IsEnd())
        return this->Pointer(this->TraitPosition());
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
const typename Element<TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::CharType* Element<TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::Get() const
{
    if (!this->IsEnd())
        return this->Pointer(this->TraitPosition());
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::Element() :
    m_cstrPtr(nullptr),
    m_sizePtr(nullptr),
    m_pos(0)
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(const CharType*& cstr, const SizeType& size, const SizeType& pos) :
        m_cstrPtr(const_cast<CharType**>(&cstr)),
        m_sizePtr(const_cast<SizeType*>(&size)),
        m_pos((pos <= size ? pos : size))
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(CharType** cstr_ptr, SizeType* size_ptr, const SizeType& pos) :
        m_cstrPtr(cstr_ptr),
        m_sizePtr(size_ptr),
        m_pos((size_ptr == nullptr ? 0 : 
            (pos <= *size_ptr ? pos : *size_ptr)))
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(const ConstElementType& cpy) :
        m_cstrPtr(cpy.m_cstrPtr),
        m_sizePtr(cpy.m_sizePtr),
        m_pos(cpy.m_pos)
{}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    Element(ConstElementType&& mov) :
        m_cstrPtr(std::move(mov.m_cstrPtr)),
        m_sizePtr(std::move(mov.m_sizePtr)),
        m_pos(std::move(mov.m_pos))
{
    mov.m_cstrPtr = nullptr;
    mov.m_sizePtr = nullptr;
    mov.m_pos = 0;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::~Element()
{
    m_cstrPtr = nullptr;
    m_sizePtr = nullptr;
    m_pos = 0;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::IsEnd() const
{
    return !(*this && this->Position() != this->Size()); 
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::SizeType Element<const TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::TraitPosition() const
{
    return ElementTraitType::Position(this->Position(), this->Size());
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::SizeType& Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::Position() const
{
    return m_pos;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::SizeType Element<const TChar, TCharTrait, TSize, TDifference, 
        TElemTrait>::Size() const
{
    return *m_sizePtr;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference,
    TElemTrait>::CharType& Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::Value()
{
    return (*m_cstrPtr)[TraitPosition()];
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::CharType& Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::Value() const
{
    return (*m_cstrPtr)[TraitPosition()];
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::CharType* Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::Pointer(const SizeType& off)
{
    return (*m_cstrPtr) + off;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::CharType* Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::Pointer(const SizeType& off) const
{
    return (*m_cstrPtr) + off;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType& Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator++()
{
    if (!this->IsEnd())
        m_pos = ElementTraitType::Increment(this->Position(), 
            this->Size());
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator++(int)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return ++cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType& Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator--()
{
    if (!this->IsEnd())
        m_pos = ElementTraitType::Decrement(this->Position(), 
            this->Size());
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator--(int)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return --cpy;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType& Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator+=(const DifferenceType& diff)
{
    if (!this->IsEnd())
        m_pos = ElementTraitType::Increment(this->Position(), diff, 
            this->Size());
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType& Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator-=(const DifferenceType& diff)
{
    if (!this->IsEnd())
        m_pos = ElementTraitType::Decrement(this->Position(), diff, 
            this->Size());
    return *this;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator+(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return cpy += diff;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::ConstElementType Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator-(const DifferenceType& diff)
{
    if (!this->IsEnd())
    {
        ConstElementType cpy(*this);
        return cpy -= diff;
    }
    return {};
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::DifferenceType Element<const TChar, TCharTrait, TSize, 
        TDifference, TElemTrait>::operator-(const Element<const TChar,
            TCharTrait, TSize_, TDifference_, TElemTrait_>& elem)
{
    if (!this->IsEnd() && !elem.IsEnd())
        if (this->Pointer() == elem.Pointer())
            return (DifferenceType)this->Position() - elem.Position();
    if (this->IsEnd())
        return 0;
    return (DifferenceType)this->Position() - this->Size();
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::CharType& Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::operator*() const
{
    if (!this->IsEnd())
        return this->Value();
    return std::move(CharType('\0'));
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
const typename Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::CharType* Element<const TChar, TCharTrait, TSize, TDifference,
        TElemTrait>::Get() const
{
    if (!this->IsEnd())
        return &(this->Value());
    return nullptr;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator==(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::Equal(this->Value(), ch);
    return false;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator==(const Element<const TChar, TCharTrait, TSize_, TDifference_, 
        TElemTrait_>& elem) const
{
    if (!this->IsEnd() && !elem.IsEnd())
    {
        if (this->Pointer() != elem.Pointer())
            return operator==(*elem);
        return this->Position() == elem.Position();
    }
    return this->IsEnd() && elem.IsEnd();
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator!=(const CharType& ch) const
{
    return !operator==(ch);
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator!=(const Element<const TChar, TCharTrait, TSize_, TDifference_, 
        TElemTrait_>& elem) const
{
    return !operator==(elem);
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator<(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::LessThan(this->Value(), ch);
    return false;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator<(const Element<const TChar, TCharTrait, TSize_, TDifference_, 
        TElemTrait_>& elem) const
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

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator>(const CharType& ch) const
{
    if (!this->IsEnd())
        return ch::Trait<TCharTrait>::LessThan(ch, this->Value());
    return false;
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator>(const Element<const TChar, TCharTrait, TSize_, TDifference_, 
        TElemTrait_>& elem) const
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

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator<=(const CharType& ch) const
{
    return operator<(ch) || operator==(ch);
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator<=(const Element<const TChar, TCharTrait, TSize_, TDifference_, 
        TElemTrait_>& elem) const
{
    return operator<(elem) || operator==(elem);
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator>=(const CharType& ch) const
{
    return operator>(ch) || operator==(ch);
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
template<typename TElemTrait_, typename TSize_, typename TDifference_>
bool Element<const TChar, TCharTrait, TSize, TDifference, TElemTrait>::
    operator>=(const Element<const TChar, TCharTrait, TSize_, TDifference_, 
        TElemTrait_>& elem) const
{
    return operator>(elem) || operator==(elem);
}

template<typename TChar, typename TCharTrait, typename TSize,
    typename TDifference, typename TElemTrait>
Element<const TChar, TCharTrait, TSize, TDifference, 
    TElemTrait>::operator bool() const
{
    return m_cstrPtr != nullptr && this->Pointer() != nullptr;
}

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ELEMENT_H_

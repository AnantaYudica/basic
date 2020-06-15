#ifndef BASIC_CSTRING_H_
#define BASIC_CSTRING_H_

#include <cstddef>
#include <memory>
#include <string>
#include <istream>
#include <ostream>
#include <utility>
#include <limits>
#include <initializer_list>

#include "cstr/ch/Trait.h"
#include "cstr/Element.h"
#include "cstr/elem/Forward.h"
#include "cstr/elem/Backward.h"

#include "cstr/find/First.h"
#include "cstr/find/FirstNotOf.h"
#include "cstr/find/FirstOf.h"
#include "cstr/find/Last.h"
#include "cstr/find/LastNotOf.h"
#include "cstr/find/LastOf.h"

namespace basic
{

template<typename TChar, 
    typename TCharTrait = std::char_traits<typename basic::type::trait::
        Simple<TChar>::Type>,
    typename TAllocator = std::allocator<typename basic::type::trait::
        Simple<TChar>::Type>>
class Cstring : public Cstring<const TChar, TCharTrait, TAllocator>
{
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    typedef TAllocator AllocatorType;
    typedef std::size_t SizeType;
    typedef std::ptrdiff_t DifferenceType;
public:
    template<typename TCharTrait_ = TCharTrait, 
        typename TAllocator_ = TAllocator>
    using CStringType = Cstring<TChar, TCharTrait_, TAllocator_>;
    template<typename TCharTrait_ = TCharTrait, 
        typename TAllocator_ = TAllocator>
    using ConstCStringType = Cstring<const TChar, TCharTrait_, TAllocator_>;
public:
    typedef typename cstr::ch::Trait<TCharTrait>::CharType CharType;
    typedef typename cstr::ch::Trait<TCharTrait>::IntType IntType;
public:
    template<DifferenceType Diff = 1>
    using ForwardElementTraitType = cstr::elem::Forward<SizeType, 
        DifferenceType, Diff>;
    template<DifferenceType Diff = 1>
    using BackwardElementTraitType = cstr::elem::Backward<SizeType, 
        DifferenceType, Diff>;
public:
    template<typename TElemenTrait_, typename TCharTrait_ = TCharTrait,
        typename TSize_ = SizeType, typename TDifference_ = DifferenceType>
    using ElementType = basic::cstr::Element<ValueType, TCharTrait_, TSize_, 
        TDifference_, TElemenTrait_> ;
    template<typename TElemenTrait_, typename TCharTrait_ = TCharTrait,
        typename TSize_ = SizeType, typename TDifference_ = DifferenceType>
    using ConstElementType = basic::cstr::Element<const ValueType, TCharTrait_,
        TSize_, TDifference_, TElemenTrait_> ;
private:
    SizeType m_allocSize;
    SizeType m_reserveSize;
    AllocatorType m_allocator;
public:
    Cstring();
    explicit Cstring(const AllocatorType& alloc);
    Cstring(const SizeType& Size, 
        const AllocatorType& alloc = AllocatorType());
    Cstring(const SizeType& Size, const TChar * cstr,
        const AllocatorType& alloc = AllocatorType());
    template<std::size_t N>
    Cstring(const TChar(&cstr)[N],
        const AllocatorType& alloc = AllocatorType());
    Cstring(std::initializer_list<ValueType> il,
        const AllocatorType& alloc = AllocatorType());
public:
    template<typename TElemenTrait_>
    Cstring(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end, 
        const AllocatorType& alloc = AllocatorType());
    template<typename TElemenTrait_, typename TCharTrait_,
        typename TSize_, typename TDifference_>
    Cstring(const ConstElementType<TElemenTrait_, TCharTrait_, 
        TSize_, TDifference_>& begin, const ConstElementType<TElemenTrait_, 
        TCharTrait_, TSize_, TDifference_>& end, 
        const AllocatorType& alloc = AllocatorType());
public:
    Cstring(const CStringType& cpy);
    Cstring(CStringType&& mov);
    ~Cstring();
public:
    CStringType& operator=(const CStringType& cpy);
    CStringType& operator=(CStringType&& mov);
public:
    CStringType& operator=(const ValueType* cstr);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& operator=(const CStringType<TCharTrait_, TAllocator_>& cstr);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& operator=(const ConstCStringType<TCharTrait_, 
        TAllocator_>& cstr);
protected:
    static TChar* Allocate(AllocatorType& alloc, 
        const SizeType& size);
    static void Deallocate(AllocatorType& alloc, TChar* cstr, 
        const SizeType& size);
    static void Clear(const SizeType& size, TChar* cstr);
public: 
    ValueType* Get();
    const ValueType* Get() const;
public:
    void Resize(const SizeType& size);
    void Resize(const SizeType& size, const ValueType& ch);
    const SizeType& MaximumSize() const
    const SizeType& Capacity() const;
    void Reserve(const SizeType& size = 0);
    void ShrinkToFit();
public:
    ValueType& At(const SizeType& index);
    const ValueType& At(const SizeType& index) const;
    ValueType& Front();
    const ValueType& Front() const;
    ValueType& Back();
    const ValueType& Back() const;
public:
    template<typename TElemenTrait_>
    ElementType<TElemenTrait_> Element(const SizeType& pos = 0);
    template<typename TElemenTrait_>
    ConstElementType<TElemenTrait_> Element(const SizeType& pos = 0) const;
public:
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ElementType<TElemenTrait_> Begin();
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ConstElementType<TElemenTrait_> Begin() const;
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ConstElementType<TElemenTrait_> ConstBegin() const;
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ElementType<TElemenTrait_> End();
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ConstElementType<TElemenTrait_> End() const;
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ConstElementType<TElemenTrait_> ConstEnd() const;
public:
    void Clear();
    CStringType& Erase(const SizeType& index = 0, 
        const SizeType& size = SizeTypeMaximum);
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ElementType<TElemenTrait_> Erase(const ConstElementType<
        TElemenTrait_>& begin);
    template<typename TElemenTrait_ = ForwardElementTraitType>
    ElementType<TElemenTrait_> Erase(const ConstElementType<
        TElemenTrait_>& begin, const ConstElementType<TElemenTrait_>& end);
public:
    void PushBack(const ValueType& ch);
    template<typename TElemenTrait_ = ForwardElementTraitType>
    void PushBack(const ConstElementType<TElemenTrait_>& elem);
    template<typename TElemenTrait_, typename TCharTrait_,
        typename TSize_, typename TDifference_>
    void PushBack(const ConstElementType<TElemenTrait_, TCharTrait_,
        TSize_, TDifference_>& elem);
    void PopBack();
public:
    CStringType& Append(const ConstCStringType& cstr);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Append(const ConstCStringType<TCharTrait_,
        TAllocator_>& cstr);

    CStringType& Append(const ConstCStringType& cstr, 
        const SizeType& sub_pos, const SizeType& sub_size = SizeTypeMaximum);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Append(const ConstCStringType<TCharTrait_, TAllocator_>& cstr,
        const SizeType& sub_pos, const SizeType& sub_size = SizeTypeMaximum);

    template<typename TElemenTrait_>
    CStringType& Append(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end);
    template<typename TElemenTrait_, typename TCharTrait_,
        typename TSize_, typename TDifference_>
    CStringType& Append(const ConstElementType<TElemenTrait_, TCharTrait_,
        TSize_, TDifference_>& begin, const ConstElementType<TElemenTrait_,
        TCharTrait_, TSize_, TDifference_>& end);

    CStringType& Append(const ValueType* cstr);
    CStringType& Append(const ValueType* cstr, const SizeType& size);
    CStringType& Append(const SizeType& size, const ValueType& ch);
    CStringType& Append(std::initializer_list<ValueType> il);
    
public:
    CStringType& Assign(const ConstCStringType& cstr);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Assign(const ConstCStringType<TCharTrait_, 
        TAllocator_>& cstr);
    
    CStringType& Assign(const ConstCStringType& cstr, const SizeType& sub_pos,
        const SizeType& sublen = SizeTypeMaximum);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Assign(const ConstCStringType<TCharTrait_, TAllocator_>& cstr,
        const SizeType& sub_pos, const SizeType& sublen = SizeTypeMaximum);
    
    template<typename TElemenTrait_>
    CStringType& Assign(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end);
    template<typename TElemenTrait_, typename TCharTrait_,
        typename TSize_, typename TDifference_>
    CStringType& Assign(const ConstElementType<TElemenTrait_, TCharTrait_, 
        TSize_, TDifference_>& begin, const ConstElementType<TElemenTrait_,
        TCharTrait_, TSize_, TDifference_>& end);

    CStringType& Assign(CStringType&& str)

    CStringType& Assign(const ValueType* cstr);
    CStringType& Assign(const ValueType* cstr, const SizeType& size);
    CStringType& Assign(const SizeType& size, const ValueType& ch);
    CStringType& Assign(std::initializer_list<ValueType> il);
public:
    CStringType& Replace(const SizeType& pos, const SizeType& size, 
        const ConstCStringType& cstr);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Replace(const SizeType& pos, const SizeType& size, 
        const ConstCStringType<TCharTrait_, TAllocator_>& cstr);

    template<typename TElemenTrait_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end, 
        const ConstCStringType& cstr);
    template<typename TElemenTrait_,typename TCharTrait_, typename TAllocator_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end, const ConstCStringType<
        TCharTrait_, TAllocator_>& cstr);

    CStringType& Replace(const SizeType& pos, const SizeType& size,
        const ConstCStringType& cstr, const SizeType& sub_pos, 
        const SizeType& sub_size = SizeTypeMaximum);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Replace(const SizeType& pos, const SizeType& size,
        const ConstCStringType<TCharTrait_, TAllocator_>& cstr, 
        const SizeType& sub_pos, const SizeType& sub_size = SizeTypeMaximum);

    CStringType& Replace(const SizeType& pos, const SizeType& size, 
        const ValueType* cstr);
    template<typename TElemenTrait_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end, const ValueType* cstr);	
    CStringType& Replace(const SizeType& pos, const SizeType& size, 
        const ValueType* cstr, const SizeType& size);
    
    template<typename TElemenTrait_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end, const ValueType* cstr, 
        const SizeType& size);	
    CStringType& Replace(const SizeType& pos, const SizeType& size, 
        const SizeType& count, const ValueType& ch);
    template<typename TElemenTrait_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end, const SizeType& count, 
        const ValueType& ch);	
    template<typename TElemenTrait_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin,
        const ConstElementType<TElemenTrait_>& end, 
        std::initializer_list<ValueType> il);
    
    template<typename TElemenTrait_, typename TInputElemenTrait_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end,
        const ConstElementType<TInputElemenTrait_>& begin_input, 
        const ConstElementType<TInputElemenTrait_>& begin_end);
    template<typename TElemenTrait_, typename TInputElemenTrait_, 
        typename TInputCharTrait_, typename TInputSize_, 
        typename TInputDifference_>
    CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end,
        const ConstElementType<TInputElemenTrait_, TInputCharTrait_,
            TInputSize_, TInputDifference_>& begin_input, 
        const ConstElementType<TInputElemenTrait_, TInputCharTrait_,
            TInputSize_, TInputDifference_>& begin_end);

public:
    CStringType& Insert(const SizeType& pos, const ConstCStringType& cstr);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Insert(const SizeType& pos, const ConstCStringType<
        TCharTrait_, TAllocator_>& cstr);

    CStringType& Insert(const SizeType& pos, const ConstCStringType& cstr, 
        const SizeType& sub_pos, const SizeType& sub_size = 
        SizeTypeMaximum);
    template<typename TCharTrait_, typename TAllocator_>
    CStringType& Insert(const SizeType& pos, const ConstCStringType<
        TCharTrait_, TAllocator_>& cstr, const SizeType& sub_pos, 
        const SizeType& sub_size = SizeTypeMaximum);

    CStringType& Insert(const SizeType& pos, const ValueType* s);
    CStringType& Insert(const SizeType& pos, const ValueType* cstr, 
        const SizeType& sub_size);
    CStringType& Insert(const SizeType& pos, const SizeType& count, 
        const ValueType& ch);

    template<typename TElemenTrait_>
    CStringType& Insert(const ConstElementType<TElemenTrait_>& elem,
        std::initializer_list<ValueType> il);

    template<typename TElemenTrait_>
    ElementType<TElemenTrait_> Insert(const ConstElementTyp<
        TElemenTrait_>& elem, const SizeType& count, 
        const ValueType& ch);
    
    template<typename TElemenTrait_>
    ElementType<TElemenTrait_> Insert(const ConstElementType<
        TElemenTrait_>& elem, const ValueType& ch);

    template<typename TElemenTrait_, typename TInputElemenTrait_>
    ElementType<TElemenTrait_> Insert(const ConstElementType<
        TElemenTrait_>& elem, const ConstElementType<
        TInputElemenTrait_>& begin_input, const ConstElementType<
        TInputElemenTrait_>& end_input);
public:
    void Swap(CStringType& other);
public:
    operator bool() const;
    ValueType& operator[](SizeType index);
    const ValueType& operator[](SizeType index) const;
    CStringType& operator+=(const ValueType& ch);
};

template<typename TChar, typename TCharTrait, typename TAllocator>
class Cstring<const TChar, TCharTrait, TAllocator>
{
private:
    friend class Cstring<TChar, TAllocator, TCharTrait>;
public:
    typedef Cstring<const TChar, TCharTrait, TAllocator> ConstCstring;
public:
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    typedef TAllocator AllocatorType;
public:
    typedef std::size_t SizeType;
    typedef std::ptrdiff_t DifferenceType;
public:
    typedef typename cstr::ch::Trait<TCharTrait>::CharType CharType;
    typedef typename cstr::ch::Trait<TCharTrait>::IntType IntType;
public:
    template<DifferenceType Diff = 1>
    using ForwardElementTraitType = cstr::elem::Forward<SizeType, 
        DifferenceType, Diff> ;
    template<DifferenceType Diff = 1>
    using BackwardElementTraitType = cstr::elem::Backward<SizeType, 
        DifferenceType, Diff> ;
public:
    template<typename TElemenTrait_, typename TSize_ = SizeType, 
        typename TDifference_ = DifferenceType>
    using ElementType = basic::cstr::Element<ValueType, TCharTrait, TSize_, 
        TDifference_, TElemenTrait_> ;
    template<typename TElemenTrait_, typename TSize_ = SizeType, 
        typename TDifference_ = DifferenceType>
    using ConstElementType = basic::cstr::Element<const ValueType, TCharTrait,
        TSize_, TDifference_, TElemenTrait_>;
public:
    using FirstFindTraitType = cstr::find::First<TChar, TCharTrait>;
    using FirstNotOfFindTraitType = cstr::find::FirstNotOf<TChar, TCharTrait>;
    using FirstOfFindTraitType = cstr::find::FirstNotOf<TChar, TCharTrait>;
    using LastFindTraitType = cstr::find::Last<TChar, TCharTrait>;
    using LastNotOfFindTraitType = cstr::find::LastNotOf<TChar, TCharTrait>;
    using LastOfFindTraitType = cstr::find::LastNotOf<TChar, TCharTrait>;
public:
    static constexpr SizeType SizeTypeMaximum = 
        std::numeric_limits<SizeType>::max();
private:
    bool m_isAssigned;
    ValueType * m_cstr;
    SizeType m_size;
public:
    Cstring();
    Cstring(const SizeType& size, const ValueType * cstr);
    template<std::size_t N>
    Cstring(const ValueType(&cstr)[N]);
public:
    Cstring(const ConstCstring& cpy);
    Cstring(ConstCstring&& mov);
    ~Cstring();
protected:
    Cstring(const SizeType& size, ValueType * cstr);
public:
    ConstCstring& operator=(const ConstCstring& cpy);
    ConstCstring& operator=(ConstCstring&& mov);
public:
    const ValueType* Get() const;
public:
    SizeType Size() const;
    SizeType Length() const;
    SizeType Capacity() const;
    SizeType MaximumSize() const;
    bool Empty() const;
public:
    const ValueType& At(const SizeType& index) const;
    const ValueType& Front() const;
    const ValueType& Back() const;
public:
    template<typename TElemenTrait_, typename TSize_ = SizeType,
        typename TDifference_ = DifferenceType>
    ConstElementType<TElemenTrait_, SizeType, TDifference_> 
        Element(const SizeType& pos = 0) const;
public:
    template<typename TElemenTrait_ = cstr::elem::Forward<SizeType, 
        DifferenceType>, typename TSize_ = SizeType, 
        typename TDifference_ = DifferenceType>
    ConstElementType<TElemenTrait_, TSize_, TDifference_> Begin() const;
    template<typename TElemenTrait_ = cstr::elem::Forward<SizeType, 
        DifferenceType>, typename TSize_ = SizeType, 
        typename TDifference_ = DifferenceType>
    ConstElementType<TElemenTrait_, TSize_, TDifference_> 
        ConstBegin() const;
    template<typename TElemenTrait_ = cstr::elem::Forward<SizeType, 
        DifferenceType>, typename TSize_ = SizeType, 
        typename TDifference_ = DifferenceType>
    ConstElementType<TElemenTrait_, TSize_, TDifference_> End() const;
    template<typename TElemenTrait_ = cstr::elem::Forward<SizeType, 
        DifferenceType>, typename TSize_ = SizeType, 
        typename TDifference_ = DifferenceType>
    ConstElementType<TElemenTrait_, TSize_, TDifference_> ConstEnd() const;
public:
    void Swap(ConstCstring& cstr);
public:
    SizeType Copy(ValueType* cstr, const SizeType& size, 
        const SizeType& pos = 0) const;
public:
    template<typename FindTrait = cstr::find::First<TChar, TCharTrait>, 
        typename TCharTrait_ = TCharTrait, typename TAllocator_ = TAllocator>
    SizeType Find(const ConstCstring& cstr, const SizeType& pos = 0, 
        const SizeType& size = SizeTypeMaximum) const;
    template<typename FindTrait = cstr::find::First<TChar, TCharTrait>>
    SizeType Find(const TChar* cstr, const SizeType& pos = 0, 
        const SizeType& size = SizeTypeMaximum) const;
    template<typename FindTrait = cstr::find::First<TChar, TCharTrait>>
    SizeType Find(const TChar& ch, const SizeType& pos = 0) const;
public:
    Cstring<TChar, TCharTrait, TAllocator> SubString(const SizeType& pos = 0, 
        const SizeType& size = SizeTypeMaximum) const;
public:
    template<typename TCharTrait_, typename TAllocator_>
    int Compare(const Cstring<TChar, TCharTrait_, TAllocator_>& cstr) const;
    template<typename TCharTrait_, typename TAllocator_>
    int Compare(const SizeType& pos, const SizeType& size, 
        const Cstring<TChar, TCharTrait_, TAllocator_>& cstr) const;
    template<typename TCharTrait_, typename TAllocator_>
    int Compare(const SizeType& pos, const SizeType& size, 
        const Cstring<TChar, TCharTrait_, TAllocator_>& cstr,
        const SizeType& sub_pos, const SizeType& sub_size = 
        SizeTypeMaximum) const;
    int Compare(const ValueType* cstr) const;
    int Compare(const SizeType& pos, const SizeType& size, 
        const ValueType* cstr) const;
    int Compare(const SizeType& pos, const SizeType& len, const ValueType* cstr, 
        const ValueType* sub_len) const;
public:
    operator bool() const;
    ValueType operator[](const SizeType& index) const;
public:
    bool operator==(const ValueType * cstr) const;
    template<typename TCharTrait_, typename TAllocator_>
    bool operator==(const ConstCstring& cstr) const;
    bool operator!=(const ValueType * cstr) const;
    template<typename TCharTrait_, typename TAllocator_>
    bool operator!=(const ConstCstring& cstr) const;
};

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::Cstring() :
    ConstCstring(),
    m_allocSize(0),
    m_reserveSize(0),
    m_allocator()
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::Cstring(const AllocatorType& alloc) :
    ConstCstring(),
    m_allocator(alloc),
    m_allocSize(0),
    m_reserveSize(0)
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::
    Cstring(const SizeType& size, const AllocatorType& alloc) :
        m_allocator(alloc),
        m_allocSize(size),
        m_reserveSize(0),
        ConstCstring(size, Allocate(m_allocator, size + 1))
{
    Clear(this->m_allocSize + 1, this->m_cstr);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::Cstring(const SizeType& Size, 
    const TChar * cstr, const AllocatorType& alloc) :
        m_allocator(alloc),
        m_allocSize(size),
        m_reserveSize(0),
        ConstCstring(size, Allocate(m_allocator, size + 1))
{
    Clear(this->m_allocSize + 1, this->m_cstr);
    //Copy(m_size, m_cstr, cstr);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<std::size_t N>
Cstring<TChar, TCharTrait, TAllocator>::Cstring(const TChar(&cstr)[N], 
    const AllocatorType& alloc) :
        m_allocator(alloc),
        m_allocSize(N),
        m_reserveSize(0),
        ConstCstring(N, Allocate(m_allocator, N + 1))
{
    Clear(this->m_allocSize + 1, this->m_cstr);
    //Copy(m_size, m_cstr, cstr);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::
    Cstring(std::initializer_list<ValueType> il, const AllocatorType& alloc) :
        m_allocator(alloc),
        m_allocSize(il.size()),
        m_reserveSize(0),
        ConstCstring(il.size(), Allocate(m_allocator, il.size() + 1))
{
    Clear(this->m_allocSize + 1, this->m_cstr);
    //Copy(m_size, m_cstr, cstr);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_>
Cstring<TChar, TCharTrait, TAllocator>::
    Cstring(const ConstElementType<TElemenTrait_>& begin, 
        const ConstElementType<TElemenTrait_>& end,
        const AllocatorType& alloc) :
            m_allocator(alloc),
            m_allocSize((end - begin) + 1),
            m_reserveSize(0),
            ConstCstring(m_allocSize, Allocate(m_allocator, m_allocSize + 1))
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_, typename TCharTrait_,
    typename TSize_, typename TDifference_>
Cstring<TChar, TCharTrait, TAllocator>::
    Cstring(const ConstElementType<TElemenTrait_, TCharTrait_, 
        TSize_, TDifference_>& begin, const ConstElementType<TElemenTrait_, 
        TCharTrait_, TSize_, TDifference_>& end) :
            m_allocator(alloc),
            m_allocSize((end - begin) + 1),
            m_reserveSize(0),
            ConstCstring(m_allocSize, Allocate(m_allocator, m_allocSize + 1))
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::
    Cstring(const CStringType& cpy) :
        m_allocator(cpy.m_allocator),
        m_allocSize(cpy.m_allocSize),
        m_reserveSize(cpy.m_reserveSize),
        ConstCstring(m_allocSize, Allocate(m_allocator, m_allocSize + 1))
{
    Clear(this->m_allocSize + 1, this->m_cstr);
    //Copy(m_size, m_cstr, cstr);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::
    Cstring(CStringType&& mov) :
        m_allocator(std::move(mov.m_allocator)),
        m_allocSize(std::move(mov.m_allocSize)),
        m_reserveSize(std::move(mov.m_reserveSize)),
        ConstCstring(std::move(mov))
{
    mov.m_allocSize = 0;
    mov.m_reserveSize = 0;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator>::~Cstring()
{
    if (this->m_cstr != nullptr)
    {
        Clear(this->m_allocSize + 1, this->m_cstr);
        Deallocate(this->m_allocator, this->m_cstr, this->m_allocSize + 1);
        this->m_cstr = nullptr;
        this->m_size = 0;
        this->m_allocSize = 0;
        this->m_reserveSize = 0;
    }
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<TChar, TCharTrait, TAllocator>::CStringType& 
    Cstring<TChar, TCharTrait, TAllocator>::
        operator=(const CStringType& cpy)
{
    if (this->m_cstr != nullptr)
    {
        Clear(this->m_allocSize + 1, this->m_cstr);
        Deallocate(this->m_allocator, this->m_cstr, this->m_allocSize + 1);
    }
    
    this->m_allocator = cpy.m_allocator;

    if (cpy.m_cstr != nullptr)
    {
        this->m_allocator = cpy.m_allocator;
        this->m_allocSize = cpy.m_allocSize;
        this->m_reserveSize = cpy.m_reserveSize;
        this->m_cstr = Allocate(this->m_allocator, this->m_allocSize + 1);
        this->m_size = cpy.m_size;
        //copy
    }
    else
    {
        this->m_allocSize = 0;
        this->m_reserveSize = 0;
        this->m_cstr = nullptr;
        this->m_size = 0;
    }
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<TChar, TCharTrait, TAllocator>::CStringType& 
    Cstring<TChar, TCharTrait, TAllocator>::operator=(CStringType&& mov)
{
    if (this->m_cstr != nullptr)
    {
        Clear(this->m_allocSize + 1, this->m_cstr);
        Deallocate(this->m_allocator, this->m_cstr, this->m_allocSize + 1);
    }

    this->m_allocator = std::move(mov.m_allocator);

    if (mov.m_cstr != nullptr)
    {
        this->m_allocSize = std::move(mov.m_allocSize);
        this->m_reserveSize = std::move(mov.m_reserveSize);
        ConstCStringType::operator=(std::move(mov));
    }
    else
    {
        this->m_allocSize = 0;
        this->m_reserveSize = 0;
        this->m_cstr = nullptr;
        this->m_size = 0;
    }
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<TChar, TCharTrait, TAllocator>::CStringType& 
    Cstring<TChar, TCharTrait, TAllocator>::operator=(const ValueType* cstr)
{
    if (this->m_cstr != nullptr)
    {
        Clear(this->m_allocSize + 1, this->m_cstr);
        Deallocate(this->m_allocator, this->m_cstr, this->m_allocSize + 1);
    }
    
    if (cstr != nullptr)
    {
        this->m_allocSize = cstr::ch::Trait<TCharTrait>::Length(cstr);
        this->m_cstr = Allocate(this->m_alloc, this->m_allocSize + 1);
    }
    else
    {

    }
}

template<typename TCharTrait_, typename TAllocator_>
CStringType& operator=(const CStringType<TCharTrait_, TAllocator_>& cstr);

template<typename TCharTrait_, typename TAllocator_>
CStringType& operator=(const ConstCStringType<TCharTrait_, 
    TAllocator_>& cstr);

static TChar* Allocate(AllocatorType& alloc, 
    const SizeType& size);
static void Deallocate(AllocatorType& alloc, TChar* cstr, 
    const SizeType& size);
static void Clear(const SizeType& size, TChar* cstr);

ValueType* Get();
const ValueType* Get() const;

void Resize(const SizeType& size);
void Resize(const SizeType& size, const ValueType& ch);
const SizeType& MaximumSize() const
const SizeType& Capacity() const;
void Reserve(const SizeType& size = 0);
void ShrinkToFit();

ValueType& At(const SizeType& index);
const ValueType& At(const SizeType& index) const;
ValueType& Front();
const ValueType& Front() const;
ValueType& Back();
const ValueType& Back() const;

template<typename TElemenTrait_>
ElementType<TElemenTrait_> Element(const SizeType& pos = 0);
template<typename TElemenTrait_>
ConstElementType<TElemenTrait_> Element(const SizeType& pos = 0) const;

template<typename TElemenTrait_ = ForwardElementTraitType>
ElementType<TElemenTrait_> Begin();
template<typename TElemenTrait_ = ForwardElementTraitType>
ConstElementType<TElemenTrait_> Begin() const;
template<typename TElemenTrait_ = ForwardElementTraitType>
ConstElementType<TElemenTrait_> ConstBegin() const;
template<typename TElemenTrait_ = ForwardElementTraitType>
ElementType<TElemenTrait_> End();
template<typename TElemenTrait_ = ForwardElementTraitType>
ConstElementType<TElemenTrait_> End() const;
template<typename TElemenTrait_ = ForwardElementTraitType>
ConstElementType<TElemenTrait_> ConstEnd() const;

void Clear();
CStringType& Erase(const SizeType& index = 0, 
    const SizeType& size = SizeTypeMaximum);
template<typename TElemenTrait_ = ForwardElementTraitType>
ElementType<TElemenTrait_> Erase(const ConstElementType<
    TElemenTrait_>& begin);
template<typename TElemenTrait_ = ForwardElementTraitType>
ElementType<TElemenTrait_> Erase(const ConstElementType<
    TElemenTrait_>& begin, const ConstElementType<TElemenTrait_>& end);

void PushBack(const ValueType& ch);
template<typename TElemenTrait_ = ForwardElementTraitType>
void PushBack(const ConstElementType<TElemenTrait_>& elem);
template<typename TElemenTrait_, typename TCharTrait_,
    typename TSize_, typename TDifference_>
void PushBack(const ConstElementType<TElemenTrait_, TCharTrait_,
    TSize_, TDifference_>& elem);
void PopBack();

CStringType& Append(const ConstCStringType& cstr);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Append(const ConstCStringType<TCharTrait_,
    TAllocator_>& cstr);

CStringType& Append(const ConstCStringType& cstr, 
    const SizeType& sub_pos, const SizeType& sub_size = SizeTypeMaximum);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Append(const ConstCStringType<TCharTrait_, TAllocator_>& cstr,
    const SizeType& sub_pos, const SizeType& sub_size = SizeTypeMaximum);

template<typename TElemenTrait_>
CStringType& Append(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end);
template<typename TElemenTrait_, typename TCharTrait_,
    typename TSize_, typename TDifference_>
CStringType& Append(const ConstElementType<TElemenTrait_, TCharTrait_,
    TSize_, TDifference_>& begin, const ConstElementType<TElemenTrait_,
    TCharTrait_, TSize_, TDifference_>& end);

CStringType& Append(const ValueType* cstr);
CStringType& Append(const ValueType* cstr, const SizeType& size);
CStringType& Append(const SizeType& size, const ValueType& ch);
CStringType& Append(std::initializer_list<ValueType> il);

CStringType& Assign(const ConstCStringType& cstr);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Assign(const ConstCStringType<TCharTrait_, 
    TAllocator_>& cstr);

CStringType& Assign(const ConstCStringType& cstr, const SizeType& sub_pos,
    const SizeType& sublen = SizeTypeMaximum);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Assign(const ConstCStringType<TCharTrait_, TAllocator_>& cstr,
    const SizeType& sub_pos, const SizeType& sublen = SizeTypeMaximum);

template<typename TElemenTrait_>
CStringType& Assign(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end);
template<typename TElemenTrait_, typename TCharTrait_,
    typename TSize_, typename TDifference_>
CStringType& Assign(const ConstElementType<TElemenTrait_, TCharTrait_, 
    TSize_, TDifference_>& begin, const ConstElementType<TElemenTrait_,
    TCharTrait_, TSize_, TDifference_>& end);

CStringType& Assign(CStringType&& str)

CStringType& Assign(const ValueType* cstr);
CStringType& Assign(const ValueType* cstr, const SizeType& size);
CStringType& Assign(const SizeType& size, const ValueType& ch);
CStringType& Assign(std::initializer_list<ValueType> il);

CStringType& Replace(const SizeType& pos, const SizeType& size, 
    const ConstCStringType& cstr);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Replace(const SizeType& pos, const SizeType& size, 
    const ConstCStringType<TCharTrait_, TAllocator_>& cstr);

template<typename TElemenTrait_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end, 
    const ConstCStringType& cstr);
template<typename TElemenTrait_,typename TCharTrait_, typename TAllocator_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end, const ConstCStringType<
    TCharTrait_, TAllocator_>& cstr);

CStringType& Replace(const SizeType& pos, const SizeType& size,
    const ConstCStringType& cstr, const SizeType& sub_pos, 
    const SizeType& sub_size = SizeTypeMaximum);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Replace(const SizeType& pos, const SizeType& size,
    const ConstCStringType<TCharTrait_, TAllocator_>& cstr, 
    const SizeType& sub_pos, const SizeType& sub_size = SizeTypeMaximum);

CStringType& Replace(const SizeType& pos, const SizeType& size, 
    const ValueType* cstr);
template<typename TElemenTrait_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end, const ValueType* cstr);	
CStringType& Replace(const SizeType& pos, const SizeType& size, 
    const ValueType* cstr, const SizeType& size);

template<typename TElemenTrait_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end, const ValueType* cstr, 
    const SizeType& size);	
CStringType& Replace(const SizeType& pos, const SizeType& size, 
    const SizeType& count, const ValueType& ch);
template<typename TElemenTrait_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end, const SizeType& count, 
    const ValueType& ch);	
template<typename TElemenTrait_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin,
    const ConstElementType<TElemenTrait_>& end, 
    std::initializer_list<ValueType> il);

template<typename TElemenTrait_, typename TInputElemenTrait_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end,
    const ConstElementType<TInputElemenTrait_>& begin_input, 
    const ConstElementType<TInputElemenTrait_>& begin_end);
template<typename TElemenTrait_, typename TInputElemenTrait_, 
    typename TInputCharTrait_, typename TInputSize_, 
    typename TInputDifference_>
CStringType& Replace(const ConstElementType<TElemenTrait_>& begin, 
    const ConstElementType<TElemenTrait_>& end,
    const ConstElementType<TInputElemenTrait_, TInputCharTrait_,
        TInputSize_, TInputDifference_>& begin_input, 
    const ConstElementType<TInputElemenTrait_, TInputCharTrait_,
        TInputSize_, TInputDifference_>& begin_end);

CStringType& Insert(const SizeType& pos, const ConstCStringType& cstr);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Insert(const SizeType& pos, const ConstCStringType<
    TCharTrait_, TAllocator_>& cstr);

CStringType& Insert(const SizeType& pos, const ConstCStringType& cstr, 
    const SizeType& sub_pos, const SizeType& sub_size = 
    SizeTypeMaximum);
template<typename TCharTrait_, typename TAllocator_>
CStringType& Insert(const SizeType& pos, const ConstCStringType<
    TCharTrait_, TAllocator_>& cstr, const SizeType& sub_pos, 
    const SizeType& sub_size = SizeTypeMaximum);

CStringType& Insert(const SizeType& pos, const ValueType* s);
CStringType& Insert(const SizeType& pos, const ValueType* cstr, 
    const SizeType& sub_size);
CStringType& Insert(const SizeType& pos, const SizeType& count, 
    const ValueType& ch);

template<typename TElemenTrait_>
CStringType& Insert(const ConstElementType<TElemenTrait_>& elem,
    std::initializer_list<ValueType> il);

template<typename TElemenTrait_>
ElementType<TElemenTrait_> Insert(const ConstElementTyp<
    TElemenTrait_>& elem, const SizeType& count, 
    const ValueType& ch);

template<typename TElemenTrait_>
ElementType<TElemenTrait_> Insert(const ConstElementType<
    TElemenTrait_>& elem, const ValueType& ch);

template<typename TElemenTrait_, typename TInputElemenTrait_>
ElementType<TElemenTrait_> Insert(const ConstElementType<
    TElemenTrait_>& elem, const ConstElementType<
    TInputElemenTrait_>& begin_input, const ConstElementType<
    TInputElemenTrait_>& end_input);

void Swap(CStringType& other);

operator bool() const;
ValueType& operator[](SizeType index);
const ValueType& operator[](SizeType index) const;
CStringType& operator+=(const ValueType& ch);

template<typename TChar, typename TCharTrait, typename TAllocator>
TChar* Cstring<TChar, TCharTrait, TAllocator>::
    Allocate(AllocatorType& alloc, const SizeType& size)
{
    return std::allocator_trait<AllocatorType>::allocate(alloc, size);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
void Cstring<TChar, TCharTrait, TAllocator>::
    Deallocate(AllocatorType& alloc, TChar* cstr, const SizeType& size)
{
    if (m_cstr != nullptr)
        std::allocator_trait<AllocatorType>::deallocate(alloc, 
            cstr, size);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
void Cstring<TChar, TCharTrait, TAllocator>::
    Clear(const SizeType& size, TChar* cstr)
{
    std::memset(cstr, 0, size);
}

//const

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::Cstring() :
    m_isAssigned(false),
    m_cstr(nullptr),
    m_size(0)
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::
    Cstring(const SizeType& size, const ValueType * cstr) :
        m_isAssigned(false),
        m_cstr(cstr),
        m_size(size)
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<std::size_t N>
Cstring<const TChar, TCharTrait, TAllocator>::
    Cstring(const ValueType(&cstr)[N]) :
        m_isAssigned(false),
        m_cstr(cstr),
        m_size(N)
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::
    Cstring(const Cstring<const TChar, TCharTrait, TAllocator>& cpy) :
        m_isAssigned(cpy.m_isAssigned),
        m_cstr(cpy.m_cstr),
        m_size(cpy.m_size)
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::
    Cstring(Cstring<const TChar, TCharTrait, TAllocator>&& mov) :
        m_isAssigned(std::move(mov.m_isAssigned)),
        m_cstr(std::move(mov.m_cstr)),
        m_size(std::move(mov.m_size)
{
    mov.m_isAssigned = false;
    mov.m_cstr = nullptr;
    mov.m_size = 0;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::~Cstring()
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::
    Cstring(const SizeType& size, ValueType * cstr) :
        m_isAssigned(true),
        m_cstr(cstr),
        m_size(size)
{}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>& 
    Cstring<const TChar, TCharTrait, TAllocator>::
        operator=(const Cstring<const TChar, TCharTrait, TAllocator>& cpy)
{
    m_isAssigned = cpy.m_isAssigned;
    m_cstr = cpy.m_cstr;
    m_size = cpy.m_size;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>& 
    Cstring<const TChar, TCharTrait, TAllocator>::
        operator=(Cstring<const TChar, TCharTrait, TAllocator>&& mov)
{
    m_isAssigned = std::move(mov.m_isAssigned);
    m_cstr = std::move(mov.m_cstr);
    m_size = std::move(mov.m_size);
    mov.m_isAssigned = false;
    mov.m_cstr = nullptr;
    mov.m_size = 0;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
const typename Cstring<const TChar, TCharTrait, TAllocator>::ValueType* 
    Cstring<const TChar, TCharTrait, TAllocator>::Get() const
{
    return m_cstr;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::Size() const
{
    return m_size;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::Length() const
{
    return std::move(cstr::ch::Trait<TCharTrait>::Length(m_cstr));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::Capacity() const
{
    return m_size;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::MaximumSize() const
{
    return m_size;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
bool Cstring<const TChar, TCharTrait, TAllocator>::Empty() const
{
    return m_cstr == nullptr || 
        cstr::ch::Trait<TCharTrait>::Equal(m_cstr[0], '\0'); 
}

template<typename TChar, typename TCharTrait, typename TAllocator>
const typename Cstring<const TChar, TCharTrait, TAllocator>::ValueType& 
    Cstring<const TChar, TCharTrait, TAllocator>::
        At(const SizeType& index) const
{
    if (m_cstr != nullptr && index < m_size)
        return m_cstr[index];
    return std::move(ValueType(0));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
const typename Cstring<const TChar, TCharTrait, TAllocator>::ValueType& 
    Cstring<const TChar, TCharTrait, TAllocator>::Front() const
{
    if (m_cstr != nullptr && m_size > 0)
        return m_cstr[0];
    return std::move(ValueType(0));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
const typename Cstring<const TChar, TCharTrait, TAllocator>::ValueType& 
    Cstring<const TChar, TCharTrait, TAllocator>::Back() const
{
    if (m_cstr != nullptr)
    {
        const SizeType len = this->Length();
        if (len < m_size)
            return m_cstr[len];
    }
    return std::move(ValueType(0));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_, typename TSize_, typename TDifference_>
typename Cstring<const TChar, TCharTrait, TAllocator>::
    template ConstElementType<TElemenTrait_, SizeType, TDifference_> 
        Cstring<const TChar, TCharTrait, TAllocator>::
            Element(const SizeType& pos) const
{
    return ConstElementType<TElemenTrait_, SizeType, TDifference_>(m_cstr, 
        m_size, pos);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_, typename TSize_, typename TDifference_>
typename Cstring<const TChar, TCharTrait, TAllocator>::
    template ConstElementType<TElemenTrait_, TSize_, TDifference_> 
        Cstring<const TChar, TCharTrait, TAllocator>::Begin() const
{
    return std::move(this->ConstBegin());
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_, typename TSize_, typename TDifference_>
typename Cstring<const TChar, TCharTrait, TAllocator>::
    template ConstElementType<TElemenTrait_, TSize_, TDifference_> 
        Cstring<const TChar, TCharTrait, TAllocator>::ConstBegin() const
{
    return ConstElementType<TElemenTrait_, TSize_, TDifference_>(m_cstr, 
        m_size, TElemenTrait_::BeginPosition(m_cstr, m_size));
}
    
template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_, typename TSize_, typename TDifference_>
typename Cstring<const TChar, TCharTrait, TAllocator>::
    template ConstElementType<TElemenTrait_, TSize_, TDifference_> 
        Cstring<const TChar, TCharTrait, TAllocator>::End() const
{
    return std::move(this->ConstEnd());
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TElemenTrait_, typename TSize_, typename TDifference_>
typename Cstring<const TChar, TCharTrait, TAllocator>::
    template ConstElementType<TElemenTrait_, TSize_, TDifference_> 
        Cstring<const TChar, TCharTrait, TAllocator>::ConstEnd() const
{
    return ConstElementType<TElemenTrait_, TSize_, TDifference_>(m_cstr, 
        m_size, TElemenTrait_::EndPosition(m_cstr, m_size));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
void Cstring<const TChar, TCharTrait, TAllocator>::
    Swap(Cstring<const TChar, TCharTrait, TAllocator>& cstr)
{
    std::swap(*this, cstr);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::Copy(ValueType* cstr, 
        const SizeType& size, const SizeType& pos) const
{
    if (this->m_cstr != nullptr && pos < m_size && cstr != nullptr)
    {
        ConstElementType<ForwardElementTraitType, SizeType, 
            DifferenceType> it(m_cstr, m_size, pos);
        ConstElementType<ForwardElementTraitType, SizeType, 
            DifferenceType> end;
        SizeType sub_pos = 0;
        while(it != '\0' && it != end && sub_pos < size)
            cstr[sub_pos++] = *(it++);
        return sub_pos;
    }
    return 0;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename FindTrait, typename TCharTrait_, typename TAllocator_>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::
        Find(const Cstring<const TChar, TCharTrait_, TAllocator_>& cstr,
            const SizeType& pos, const SizeType& size) const
{
    ConstElementType<ForwardElementTraitType, SizeType, 
        DifferenceType> begin(m_cstr, m_size, pos);
    ConstElementType<ForwardElementTraitType, SizeType, 
        DifferenceType> end;
    return FindTrait::Position<Cstring<const TChar, TCharTrait_, 
        TAllocator_>>(begin, end, cstr, size);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename FindTrait>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::
        Find(const TChar* cstr, const SizeType& pos, 
            const SizeType& size) const
{
    ConstElementType<ForwardElementTraitType, SizeType, 
        DifferenceType> begin(m_cstr, m_size, pos);
    ConstElementType<ForwardElementTraitType, SizeType, 
        DifferenceType> end;
    return FindTrait::Position<const TChar*>(begin, end, cstr, size);
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename FindTrait>
typename Cstring<const TChar, TCharTrait, TAllocator>::SizeType 
    Cstring<const TChar, TCharTrait, TAllocator>::Find(const TChar& ch, 
        const SizeType& pos) const
{
    return std::move(Find<FindTrait>(&ch, pos, 1));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<TChar, TCharTrait, TAllocator> 
    Cstring<const TChar, TCharTrait, TAllocator>::
        SubString(const SizeType& pos, const SizeType& size) const
{
    return std::move(Cstring<TChar, TCharTrait, TAllocator> cstr(
        this->template Element<ForwardElementTraitType>(pos),
        this->template Element<ForwardElementTraitType>(pos + size)));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TCharTrait_, typename TAllocator_>
int Cstring<const TChar, TCharTrait, TAllocator>::
    Compare(const Cstring<TChar, TCharTrait_, TAllocator_>& cstr) const
{
    return std::move(ch::Trait<TCharTrait>::Compare(m_cstr,
        cstr.Get(), SizeTypeMaximum));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TCharTrait_, typename TAllocator_>
int Cstring<const TChar, TCharTrait, TAllocator>::
    Compare(const SizeType& pos, const SizeType& size, 
        const Cstring<TChar, TCharTrait_, TAllocator_>& cstr) const
{
    return std::move(ch::Trait<TCharTrait>::Compare(m_cstr + pos,
        cstr.Get(), size));
}
    
template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TCharTrait_, typename TAllocator_>
int Cstring<const TChar, TCharTrait, TAllocator>::
    Compare(const SizeType& pos, const SizeType& size, 
        const Cstring<TChar, TCharTrait_, TAllocator_>& cstr,
        const SizeType& sub_pos, const SizeType& sub_size) const
{
    return std::move(ch::Trait<TCharTrait>::Compare(m_cstr + pos,
        cstr.Get() + sub_pos, (size > sub_size ? size : sub_size)));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
int Cstring<const TChar, TCharTrait, TAllocator>::
    Compare(const ValueType* cstr) const
{
    return std::move(ch::Trait<TCharTrait>::Compare(m_cstr,
        cstr, SizeTypeMaximum));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
int Cstring<const TChar, TCharTrait, TAllocator>::
    Compare(const SizeType& pos, const SizeType& size, 
        const ValueType* cstr) const
{
    return std::move(ch::Trait<TCharTrait>::Compare(m_cstr + pos,
        cstr, size));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
int Cstring<const TChar, TCharTrait, TAllocator>::
    Compare(const SizeType& pos, const SizeType& size, const ValueType* cstr, 
        const ValueType* sub_size) const
{
    return std::move(ch::Trait<TCharTrait>::Compare(m_cstr + pos,
        cstr.Get(), (size > sub_size ? size : sub_size)));
}

template<typename TChar, typename TCharTrait, typename TAllocator>
Cstring<const TChar, TCharTrait, TAllocator>::operator bool() const
{
    return m_cstr != nullptr;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
typename Cstring<const TChar, TCharTrait, TAllocator>::ValueType
    Cstring<const TChar, TCharTrait, TAllocator>::
        operator[](const SizeType& index) const
{
    return (m_cstr == nullptr || index >= m_size) ? ValueType('\0') : 
        m_cstr[index];
}

template<typename TChar, typename TCharTrait, typename TAllocator>

bool Cstring<const TChar, TCharTrait, TAllocator>::
    operator==(const ValueType * cstr) const
{
    return this->Compare(cstr) == 0;
}
template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TCharTrait_, typename TAllocator_>
bool Cstring<const TChar, TCharTrait, TAllocator>::
    operator==(const Cstring<const TChar, TCharTrait_, 
        TAllocator_>& cstr) const
{
    return this->Compare(cstr) == 0;
}
    
template<typename TChar, typename TCharTrait, typename TAllocator>
bool Cstring<const TChar, TCharTrait, TAllocator>::
    operator!=(const ValueType * cstr) const
{
    return this->Compare(cstr) != 0;
}

template<typename TChar, typename TCharTrait, typename TAllocator>
template<typename TCharTrait_, typename TAllocator_>
bool Cstring<const TChar, TCharTrait, TAllocator>::
    operator!=(const Cstring<const TChar, TCharTrait_, 
        TAllocator_>& cstr) const
{
    return this->Compare(cstr) != 0;
}

} //!basic

#endif //!BASIC_CSTRING_H_

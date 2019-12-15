#ifndef BASIC_CSTR_ALLOCATOR_H_
#define BASIC_CSTR_ALLOCATOR_H_

#include <memory>

#include <exception>

#include "../Error.h"
#include "../err/exc/Overflow.h"
#include "../err/exc/Allocation.h"

namespace basic
{
namespace cstr
{

template<typename TAllocator, typename TChar, typename TSize, 
    TSize MaxSize>
struct Allocator
{
    typedef TAllocator AllocatorType;
    typedef TChar ValueType;
    typedef TSize SizeType;

    static constexpr TSize MaximumSize = MaxSize;

    static TChar* Allocate(AllocatorType& alloc, const SizeType& len);
    static TChar* Deallocate(AllocatorType& alloc, TChar* cstr, 
        const SizeType& len);
    static TChar* Reallocate(AllocatorType& alloc, TChar* cstr,
        const SizeType& len);
};

template<typename TAllocator, typename TChar, typename TSize, TSize MaxSize>
TChar* Allocator<TAllocator, TChar, TSize, MaxSize>::
    Allocate(AllocatorType& alloc, const SizeType& len) TRY
{
    THROW_IF(len >= MaximumSize, basic::err::exc::
        Overflow<TSize, MaxSize>);
    TChar* ptr = std::allocator_traits<TAllocator>::allocate(alloc, len);
    THROW_IF(ptr == nullptr, basic::err::exc::Allocation);
    return ptr;
} 
#ifdef ENABLE_EXCEPTION
catch(const ERR_EXCEPTION_BASE& e)
{
    THROW_AGAIN(e);
    return nullptr;
}
catch(const std::exception& e)
{
    THROW_AGAIN(e);
    return nullptr;
}
#endif

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ALLOCATOR_H_

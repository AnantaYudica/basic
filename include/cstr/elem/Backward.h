#ifndef BASIC_CSTR_ELEM_BACKWARD_H_
#define BASIC_CSTR_ELEM_BACKWARD_H_

#include <cstddef>
#include "Forward.h"
#include "../ch/Trait.h"

namespace basic
{
namespace cstr
{
namespace elem
{

template<typename TSize, typename TDiff, TDiff SizeDiff = 1>
class Backward : public elem::Forward<TSize, TDiff, SizeDiff>
{
public:
    typedef TSize SizeType;
    typedef TDiff DifferenceType;
public:
    static constexpr SizeType Position(const SizeType& pos,
        const SizeType& size);
    template<typename TChar, typename TCharTrait>
    static SizeType BeginPosition(const TChar* cstr, const TSize& size);
    template<typename TChar, typename TCharTrait>
    static SizeType EndPosition(const TChar* cstr, const TSize& size);
};

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Backward<TSize, TDiff, SizeDiff>::SizeType 
    Backward<TSize, TDiff, SizeDiff>::
        Position(const SizeType& pos, const SizeType& size)
{
    return (pos >= size ? size : size - (pos + 1));
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
template<typename TChar, typename TCharTrait>
typename Backward<TSize, TDiff, SizeDiff>::SizeType 
    Backward<TSize, TDiff, SizeDiff>::BeginPosition(const TChar* cstr, 
        const TSize& size)
{
    const TSize len = ch::Trait<TCharTrait>::Length(cstr);
    return (cstr == nullptr ? 0 : (size > len ? size - len : size));
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
template<typename TChar, typename TCharTrait>
typename Backward<TSize, TDiff, SizeDiff>::SizeType 
    Backward<TSize, TDiff, SizeDiff>::EndPosition(const TChar* cstr,
        const TSize& size)
{
    return size;
}

} //!elem

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ELEM_BACKWARD_H_

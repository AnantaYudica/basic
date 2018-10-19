#ifndef BASIC_CSTR_ELEM_FORWARD_H_
#define BASIC_CSTR_ELEM_FORWARD_H_

#include <cstddef>

namespace basic
{
namespace cstr
{
namespace elem
{

template<typename TSize, typename TDiff, TDiff SizeDiff = 1>
class Forward
{
public:
    typedef TSize SizeType;
    typedef TDiff DifferenceType;
private:
    static constexpr DifferenceType _Difference(const DifferenceType& diff);
    static constexpr SizeType _Increment(const SizeType& pos, 
        const DifferenceType& diff);
    static constexpr SizeType _Decrement(const SizeType& pos, 
        const DifferenceType& diff);
public:
    static constexpr SizeType SizeDifference = SizeDiff;
    static constexpr SizeType Position(const SizeType& pos,
        const SizeType& size);
    static constexpr SizeType Increment(const SizeType& pos, 
        const DifferenceType& diff, const SizeType& size);
    static constexpr SizeType Increment(const SizeType& pos, 
        const SizeType& size);
    static constexpr SizeType Decrement(const SizeType& pos, 
        const DifferenceType& diff, const SizeType& size);
    static constexpr SizeType Decrement(const SizeType& pos, 
        const SizeType& size);
};

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::DifferenceType 
    Forward<TSize, TDiff, SizeDiff>::_Difference(const DifferenceType& diff)
{
    return SizeDifference * diff;
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType 
    Forward<TSize, TDiff, SizeDiff>::_Increment(const SizeType& pos, 
        const DifferenceType& diff)
{
    return (diff > 0 ? pos + _Difference(diff) : 
        _Decrement(pos, -diff));
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType 
    Forward<TSize, TDiff, SizeDiff>::_Decrement(const SizeType& pos, 
        const DifferenceType& diff)
{
    return (diff > 0 ? (pos > _Difference(diff) ? pos - _Difference(diff) : 
        0) : _Increment(pos, -diff));
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType 
    Forward<TSize, TDiff, SizeDiff>::Position(const SizeType& pos,
        const SizeType& size)
{
    return pos < size ? pos : size;
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType 
    Forward<TSize, TDiff, SizeDiff>::Increment(const SizeType& pos, 
        const DifferenceType& diff, const SizeType& size)
{
    return _Increment(pos, diff) < size ? _Increment(pos, diff) : size;
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType
    Forward<TSize, TDiff, SizeDiff>::Increment(const SizeType& pos,
        const SizeType& size)
{
    return Increment(pos, 1, size);
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType
    Forward<TSize, TDiff, SizeDiff>::Decrement(const SizeType& pos, 
        const DifferenceType& diff, const SizeType& size)
{
    return _Decrement(pos, diff) < size ? _Decrement(pos, diff) : size;
}

template<typename TSize, typename TDiff, TDiff SizeDiff>
constexpr typename Forward<TSize, TDiff, SizeDiff>::SizeType
    Forward<TSize, TDiff, SizeDiff>::Decrement(const SizeType& pos,
        const SizeType& size)
{
    return Decrement(pos, 1, size);
}

} //!elem

} //!cstr

} //!basic

#endif //!BASIC_CSTR_ELEM_FORWARD_H_

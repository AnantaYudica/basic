#ifndef BASIC_CSTR_FIND_LAST_H_
#define BASIC_CSTR_FIND_LAST_H_

#include <cstddef>
#include <limits>

#include "../ch/Trait.h"
#include "../Element.h"

namespace basic
{
namespace cstr
{
namespace find
{

template<typename TChar, typename TCharTrait>
struct Last
{
    typedef TChar ValueType;
    typedef TCharTrait CharTraitType;
    
    typedef typename ch::Trait<TCharTrait>::CharType CharType;
    typedef typename ch::Trait<TCharTrait>::IntType IntType;

    template<typename TSubCstr, typename TElementTrait, typename TSize =
        std::size_t, typename TDifference = std::ptrdiff_t>
    static TSize Position(const cstr::Element<const TChar, TCharTrait, TSize,
        TDifference, TElementTrait>& const_begin_elem, 
        const cstr::Element<const TChar, TCharTrait, TSize, TDifference, 
        TElementTrait>& const_end_elem, const TSubCstr& sub_cstr, 
        const TSize& sub_size = std::numeric_limits<TSize>::max());
};

template<typename TChar, typename TCharTrait>
template<typename TSubCstr, typename TElementTrait, typename TSize, 
    typename TDifference>
TSize Last<TChar, TCharTrait>::Position(const cstr::Element<const TChar, TCharTrait,
    TSize, TDifference, TElementTrait>& const_begin_elem, 
    const cstr::Element<const TChar, TCharTrait, TSize, TDifference, 
    TElementTrait>& const_end_elem, const TSubCstr& sub_cstr, 
    const TSize& sub_size)
{
    if (!const_begin_elem || const_begin_elem >= const_end_elem) return 0;
    if (!sub_cstr || !const_begin_elem) return const_begin_elem.Size();
    if (ch::Trait<TCharTrait>::Equal(sub_cstr[0], '\0')) return 0;
    TSize sub_pos = 0;
    auto begin_elem = const_begin_elem;
    auto it_elem = const_begin_elem;
    while(it_elem != '\0' && it_elem != const_end_elem)
    {
        if (it_elem == sub_cstr[sub_pos])
        {
            if (ch::Trait<TCharTrait>::Equal(sub_cstr[++sub_pos], '\0') ||
                sub_pos >=  sub_size) return begin_elem.Position();
            --it_elem;
        }
        else
        {
            sub_pos = 0; 
            it_elem = ++begin_elem;
        }
    }
    return const_begin_elem.Size();
}

} //!find

} //!cstr

} //!basic

#endif //!BASIC_CSTR_FIND_LAST_H_

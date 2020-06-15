#ifndef BASIC_CSTR_FIND_LASTNOTOF_H_
#define BASIC_CSTR_FIND_LASTNOTOF_H_

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
struct LastNotOf
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
TSize LastNotOf<TChar, TCharTrait>::Position(const cstr::Element<const TChar, 
    TCharTrait, TSize, TDifference, TElementTrait>& const_begin_elem, 
    const cstr::Element<const TChar, TCharTrait, TSize, TDifference, 
    TElementTrait>& const_end_elem, const TSubCstr& sub_cstr, 
    const TSize& sub_size)
{
    if (!const_begin_elem || const_begin_elem >= const_end_elem) return 0;
    if (!sub_cstr || !const_begin_elem) return const_begin_elem.Size();
    if (ch::Trait<TCharTrait>::Equal(sub_cstr[0], '\0')) return 0;
    TSize sub_pos = 0;
    auto it_elem = const_begin_elem;
    while(it_elem != '\0' && it_elem != const_end_elem)
    {
        while(!ch::Trait<TCharTrait>::Equal(sub_cstr[sub_pos], '\0') &&
            sub_pos < sub_size)
        {
            if (it_elem != sub_cstr[sub_pos++])
                return it_elem.Position();
        }
        sub_pos = 0;
        ++it_elem;
    }
    return const_begin_elem.Size();
}

} //!find

} //!cstr

} //!basic

#endif //!BASIC_CSTR_FIND_LASTNOTOF_H_

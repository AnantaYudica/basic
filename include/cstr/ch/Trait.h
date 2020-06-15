#ifndef BASIC_CSTR_CH_TRAIT_H_
#define BASIC_CSTR_CH_TRAIT_H_

#include <type_traits>
#include <utility>

#include "../../macro/HasMemberDefinition.h"
#include "../../macro/HasStaticMemberFunction.h"
#include "../../type/condl/Switch.h"

namespace _helper
{
namespace _basic
{
namespace _cstr
{
namespace _ch
{
namespace _trait
{

__DEFINE_HAS_MMBR_DEFN_(_HasStdCharType, __HasStdCharType, TCharTrait,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, char_type);
__DEFINE_HAS_MMBR_DEFN_(_HasCharType, __HasCharType, TCharTrait,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, CharType);

__DEFINE_HAS_MMBR_DEFN_(_HasStdIntType, __HasStdIntType, TCharTrait,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, int_type);
__DEFINE_HAS_MMBR_DEFN_(_HasIntType, __HasIntType, TCharTrait,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, IntType);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdAssign, __HasStdAssign, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    assign);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasAssign, __HasAssign, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Assign);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdMove, __HasStdMove, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    move);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasMove, __HasMove, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Move);
    
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdCopy, __HasStdCopy, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    copy);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasCopy, __HasCopy, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Copy);
    
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdEqual, __HasStdEqual, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    eq);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasEqual, __HasEqual, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Equal);
    
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdLessThan, __HasStdLessThan, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    lt);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasLessThan, __HasLessThan, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    LessThan);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdCompare, __HasStdCompare, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    compare);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasCompare, __HasCompare, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Compare);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdLength, __HasStdLength, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    length);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasLength, __HasLength, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Length);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdFind, __HasStdFind, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    find);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasFind, __HasFind, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Find);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdToCharType, __HasStdToCharType, 
    TCharTrait, TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, to_char_type);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasToCharType, __HasToCharType, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    ToCharType);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdToIntType, __HasStdToIntType, 
    TCharTrait, TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, to_int_type);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasToIntType, __HasToIntType, TCharTrait, 
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    ToIntType);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdEqualIntType, __HasStdEqualIntType, 
    TCharTrait, TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, equal_int_type);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasEqualIntType, __HasEqualIntType, TCharTrait,
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    EqualIntType);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdEndOfFile, __HasStdEndOfFile, 
    TCharTrait, TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, eof);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasEndOfFile, __HasEndOfFile, TCharTrait,
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    EndOfFile);

__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasStdNotEndOfFile, __HasStdNotEndOfFile, 
    TCharTrait, TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, not_eof);
__DEFINE_HAS_STATIC_MMBR_FUNC_(_HasNotEndOfFile, __HasNotEndOfFile, TCharTrait,
    TRet, TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    NotEndOfFile);

template<typename TCharTrait>
using _SwDefnChar = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdCharType<TCharTrait>::Value>,
    std::integral_constant<bool, _HasCharType<TCharTrait>::Value>>;

template<typename TCharTrait>
using _SWDefnInt = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdIntType<TCharTrait>::Value>,
    std::integral_constant<bool, _HasIntType<TCharTrait>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncAssign = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdAssign<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasAssign<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncMove = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdMove<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasMove<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncCopy = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdCopy<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasCopy<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncEqual = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdEqual<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasEqual<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncLessThan = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdLessThan<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasLessThan<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncCompare = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdCompare<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasCompare<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncLength = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdLength<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasLength<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncFind = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdFind<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasFind<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncToCharType = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdToCharType<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasToCharType<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncToIntType = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdToIntType<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasToIntType<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncEqualIntType = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdEqualIntType<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasEqualIntType<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncEndOfFile = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdEndOfFile<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasEndOfFile<TCharTrait, 
        TRet, TArgs...>::Value>>;

template<typename TCharTrait, typename TRet, typename... TArgs>
using _SwFuncNotEndOfFile = basic::type::condl::Switch<std::false_type, 
    std::integral_constant<bool, _HasStdNotEndOfFile<TCharTrait, 
        TRet, TArgs...>::Value>,
    std::integral_constant<bool, _HasNotEndOfFile<TCharTrait, 
        TRet, TArgs...>::Value>>;
namespace _defn
{

template<typename TCharTrait, std::size_t = _SwDefnChar<TCharTrait>::Index>
struct _Char
{};

template<typename TCharTrait>
struct _Char<TCharTrait, 0>
{
    typedef typename TCharTrait::char_type Type;
};

template<typename TCharTrait>
struct _Char<TCharTrait, 1>
{
    typedef typename TCharTrait::CharType Type;
};

template<typename TCharTrait, std::size_t = _SWDefnInt<TCharTrait>::Index>
struct _Int
{};

template<typename TCharTrait>
struct _Int<TCharTrait, 0>
{
    typedef typename TCharTrait::int_type Type;
};

template<typename TCharTrait>
struct _Int<TCharTrait, 1>
{
    typedef typename TCharTrait::IntType Type;
};

} //!_defn

namespace _func
{

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncAssign<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Assign(TArgs&&... args)
{
    return TCharTrait::assign(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncAssign<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Assign(TArgs&&... args)
{
    return TCharTrait::Assign(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncMove<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Move(TArgs&&... args)
{
    return TCharTrait::move(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncMove<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Move(TArgs&&... args)
{
    return TCharTrait::Move(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncCopy<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Copy(TArgs&&... args)
{
    return TCharTrait::copy(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncCopy<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Copy(TArgs&&... args)
{
    return TCharTrait::Copy(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncEqual<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Equal(TArgs&&... args)
{
    return TCharTrait::eq(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncEqual<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Equal(TArgs&&... args)
{
    return TCharTrait::Equal(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncLessThan<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _LessThan(TArgs&&... args)
{
    return TCharTrait::lt(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncLessThan<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _LessThan(TArgs&&... args)
{
    return TCharTrait::LessThan(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncCompare<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Compare(TArgs&&... args)
{
    return TCharTrait::compare(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncCompare<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Compare(TArgs&&... args)
{
    return TCharTrait::Compare(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncLength<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Length(TArgs&&... args)
{
    return TCharTrait::length(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncLength<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Length(TArgs&&... args)
{
    return TCharTrait::Length(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncFind<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _Find(TArgs&&... args)
{
    return TCharTrait::find(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncFind<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _Find(TArgs&&... args)
{
    return TCharTrait::Find(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncToCharType<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _ToCharType(TArgs&&... args)
{
    return TCharTrait::to_char_type(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncToCharType<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _ToCharType(TArgs&&... args)
{
    return TCharTrait::ToCharType(std::forward<TArgs>(args)...);
}

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncToIntType<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _ToIntType(TArgs&&... args)
{
    return TCharTrait::to_int_type(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncToIntType<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _ToIntType(TArgs&&... args)
{
    return TCharTrait::ToIntType(std::forward<TArgs>(args)...);
}

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncEqualIntType<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _EqualIntType(TArgs&&... args)
{
    return TCharTrait::equal_int_type(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncEqualIntType<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _EqualIntType(TArgs&&... args)
{
    return TCharTrait::EqualIntType(std::forward<TArgs>(args)...);
}

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncEndOfFile<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _EndOfFile(TArgs&&... args)
{
    return TCharTrait::eof(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncEndOfFile<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _EndOfFile(TArgs&&... args)
{
    return TCharTrait::EndOfFile(std::forward<TArgs>(args)...);
}

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncNotEndOfFile<TCharTrait, TRet, 
    TArgs...>::Index == 0, TRet>::type _NotEndOfFile(TArgs&&... args)
{
    return TCharTrait::not_eof(std::forward<TArgs>(args)...);
} 

template<typename TCharTrait, typename TRet, typename... TArgs>
constexpr typename std::enable_if<_SwFuncNotEndOfFile<TCharTrait, TRet, 
    TArgs...>::Index == 1, TRet>::type _NotEndOfFile(TArgs&&... args)
{
    return TCharTrait::NotEndOfFile(std::forward<TArgs>(args)...);
}

} //!_func

} //!_trait

} //!_ch

} //!_cstr

} //!_basic

} //_helper

namespace basic
{
namespace cstr
{
namespace ch
{

template<typename TCharTrait>
struct Trait
{
    typedef typename _helper::_basic::_cstr::_ch::_trait::
        _defn::_Char<TCharTrait>::Type CharType;
    typedef typename _helper::_basic::_cstr::_ch::_trait::
        _defn::_Int<TCharTrait>::Type IntType;

    static constexpr void Assign(CharType& ch_cstr, const CharType& ch);
    static CharType* Assign(CharType* cstr, const std::size_t& count, 
        const CharType& ch);
    static CharType* Move(CharType* dest, const CharType* src, 
        const std::size_t& count);
    static CharType* Copy(CharType* dest, const CharType* src, 
        const std::size_t& count);
    static constexpr bool Equal(const CharType& a, const CharType& b);
    static constexpr bool LessThan(const CharType& a, const CharType& b);
    static constexpr int Compare(const CharType* cstr1, const CharType* cstr2, 
        const std::size_t& count);
    static constexpr std::size_t Length(const CharType* cstr);
    static constexpr const CharType* Find(const CharType* cstr, 
        const std::size_t& count, const CharType& ch);
    static constexpr CharType ToCharType(const IntType& val);
    static constexpr IntType ToIntType(const CharType& ch);
    static constexpr bool EqualIntType(const IntType& val1, 
        const IntType& val2);
    static constexpr IntType EndOfFile();
    static constexpr IntType NotEndOfFile(const IntType& val);
    
};

template<typename TCharTrait>
constexpr void Trait<TCharTrait>::Assign(CharType& ch_cstr, 
    const CharType& ch)
{
    return _helper::_basic::_cstr::_ch::_trait::_func::_Assign<TCharTrait, 
        void, CharType&, const CharType&>(
            std::forward<CharType&>(ch_cstr), 
            std::forward<const CharType&>(ch));
}

template<typename TCharTrait>
typename Trait<TCharTrait>::CharType* Trait<TCharTrait>::Assign(CharType* cstr,
    const std::size_t& count, const CharType& ch)
{
    return _helper::_basic::_cstr::_ch::_trait::_func::_Assign<TCharTrait, 
        CharType*, CharType*, const std::size_t&, const CharType&>(
            std::forward<CharType*>(cstr), 
            std::forward<const std::size_t&>(count),
            std::forward<const CharType&>(ch));
}

template<typename TCharTrait>
typename Trait<TCharTrait>::CharType* Trait<TCharTrait>::Move(CharType* dest, 
    const CharType* src, const std::size_t& count)
{
    return _helper::_basic::_cstr::_ch::_trait::_func::_Move<TCharTrait,
        CharType*, CharType*, const CharType*, const std::size_t&>(
            std::forward<CharType*>(dest), 
            std::forward<const CharType*>(src), 
            std::forward<const std::size_t&>(count));
}

template<typename TCharTrait>
typename Trait<TCharTrait>::CharType* Trait<TCharTrait>::Copy(CharType* dest, 
    const CharType* src, const std::size_t& count)
{
    return _helper::_basic::_cstr::_ch::_trait::_func::_Copy<TCharTrait,
        CharType*, CharType*, const CharType*, const std::size_t&>(
            std::forward<CharType*>(dest), 
            std::forward<const CharType*>(src), 
            std::forward<const std::size_t&>(count));
}

template<typename TCharTrait>
constexpr bool Trait<TCharTrait>::Equal(const CharType& a, const CharType& b)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _Equal<TCharTrait, bool, const CharType&, const CharType&>(
            std::forward<const CharType&>(a), 
            std::forward<const CharType&>(b)));
}

template<typename TCharTrait>
constexpr bool Trait<TCharTrait>::LessThan(const CharType& a, const CharType& b)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _LessThan<TCharTrait, bool, const CharType&, const CharType&>(
            std::forward<const CharType&>(a), 
            std::forward<const CharType&>(b)));
}

template<typename TCharTrait>
constexpr int Trait<TCharTrait>::Compare(const CharType* cstr1, 
    const CharType* cstr2, const std::size_t& count)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _Compare<TCharTrait, int, const CharType*, const CharType*, 
        const std::size_t&>(
            std::forward<const CharType*>(cstr1), 
            std::forward<const CharType*>(cstr2), 
            std::forward<const std::size_t&>(count)));
}

template<typename TCharTrait>
constexpr std::size_t Trait<TCharTrait>::Length(const CharType* cstr)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _Length<TCharTrait, std::size_t, const CharType*>(
            std::forward<const CharType*>(cstr)));
}

template<typename TCharTrait>
constexpr const typename Trait<TCharTrait>::CharType* 
    Trait<TCharTrait>::Find(const CharType* cstr, const std::size_t& count, 
        const CharType& ch)
{
    return _helper::_basic::_cstr::_ch::_trait::_func::_Find<TCharTrait,
        const CharType*, const CharType*, const std::size_t&, 
        const CharType&>(
            std::forward<const CharType*>(cstr),
            std::forward<const std::size_t&>(count), 
            std::forward<const CharType&>(ch));
}

template<typename TCharTrait>
constexpr typename Trait<TCharTrait>::CharType 
    Trait<TCharTrait>::ToCharType(const IntType& val)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _ToCharType<TCharTrait, CharType, const IntType&>(
            std::forward<const IntType&>(val)));
}

template<typename TCharTrait>
constexpr typename Trait<TCharTrait>::IntType 
    Trait<TCharTrait>::ToIntType(const CharType& ch)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _ToIntType<TCharTrait, IntType, const CharType&>(
            std::forward<const CharType&>(ch)));
}

template<typename TCharTrait>
constexpr bool Trait<TCharTrait>::EqualIntType(const IntType& val1, 
    const IntType& val2)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _EqualIntType<TCharTrait, bool, const IntType&, 
        const IntType&>(
            std::forward<const IntType&>(val1),
            std::forward<const IntType&>(val2)));
}

template<typename TCharTrait>
constexpr typename Trait<TCharTrait>::IntType 
    Trait<TCharTrait>::EndOfFile()
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _EndOfFile<TCharTrait, IntType>());
}

template<typename TCharTrait>
constexpr typename Trait<TCharTrait>::IntType 
    Trait<TCharTrait>::NotEndOfFile(const IntType& val)
{
    return std::move(_helper::_basic::_cstr::_ch::_trait::_func::
        _NotEndOfFile<TCharTrait, IntType, const IntType&>(
            std::forward<const IntType&>(val)));
}

} //!ch

} //!cstr

} //!basic

#endif //!BASIC_CSTR_CH_TRAIT_H_

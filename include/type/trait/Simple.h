#ifndef BASIC_TYPE_TRAIT_SIMPLE_H_
#define BASIC_TYPE_TRAIT_SIMPLE_H_

#include <cstddef>

namespace basic
{
namespace type
{
namespace trait
{

template<typename T>
struct Simple
{
    typedef T Type;
    typedef typename Simple<T>::Type type;
};

template<typename T>
struct Simple<const T>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<volatile T>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<const volatile T>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T*>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T*const>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T*volatile>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T*const volatile>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename Tc>
struct Simple<T Tc::*>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename Tc>
struct Simple<T Tc::*const>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename Tc>
struct Simple<T Tc::*volatile>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename Tc>
struct Simple<T Tc::*const volatile>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T&>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T&&>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<T[]>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T>
struct Simple<const T[]>
{
    typedef typename Simple<const T>::Type Type;
    typedef typename Simple<const T>::type type;
};

template<typename T>
struct Simple<volatile T[]>
{
    typedef typename Simple<volatile T>::Type Type;
    typedef typename Simple<volatile T>::type type;
};


template<typename T>
struct Simple<const volatile T[]>
{
    typedef typename Simple<const volatile T>::Type Type;
    typedef typename Simple<const volatile T>::type type;
};

template<typename T, std::size_t N>
struct Simple<T[N]>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, std::size_t N>
struct Simple<const T[N]>
{
    typedef typename Simple<const T>::Type Type;
    typedef typename Simple<const T>::type type;
};

template<typename T, std::size_t N>
struct Simple<volatile T[N]>
{
    typedef typename Simple<volatile T>::Type Type;
    typedef typename Simple<volatile T>::type type;
};

template<typename T, std::size_t N>
struct Simple<const volatile T[N]>
{
    typedef typename Simple<const volatile T>::Type Type;
    typedef typename Simple<const volatile T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...)>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) &>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) &&>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) const>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) const &>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) const &&>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) volatile>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) volatile &>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) volatile &&>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) const volatile>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) const volatile &>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

template<typename T, typename... Targs>
struct Simple<T(Targs...) const volatile &&>
{
    typedef typename Simple<T>::Type Type;
    typedef typename Simple<T>::type type;
};

} //!trait

} //!type

} //!basic

#endif //!BASIC_TYPE_TRAIT_SIMPLE_H_

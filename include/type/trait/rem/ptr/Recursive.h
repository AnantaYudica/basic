#ifndef BASIC_TYPE_TRAIT_REM_PTR_RECURSIVE_H_
#define BASIC_TYPE_TRAIT_REM_PTR_RECURSIVE_H_

namespace basic
{
namespace type
{
namespace trait
{
namespace rem
{
namespace ptr
{

template<typename T>
struct Recursive
{
    typedef T type;
    typedef typename Recursive<T>::type Type;
};

template<typename T>
struct Recursive<T*>
{
    typedef typename Recursive<T>::type type;
    typedef typename Recursive<T*>::type Type;
};

template<typename T>
struct Recursive<T*const>
{
    typedef typename Recursive<T>::type type;
    typedef typename Recursive<T*const>::type Type;
};

template<typename T>
struct Recursive<T*volatile>
{
    typedef typename Recursive<T>::type type;
    typedef typename Recursive<T*volatile>::type Type;
};

template<typename T>
struct Recursive<T*const volatile>
{
    typedef typename Recursive<T>::type type;
    typedef typename Recursive<T*const volatile>::type Type;
};

} //!ptr

} //!rem

} //!trait

} //!type

} //!basic

#endif //!BASIC_TYPE_TRAIT_REM_PTR_RECURSIVE_H_

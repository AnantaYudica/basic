#ifndef TYPE_TRAIT_REM_POINTER_H_
#define TYPE_TRAIT_REM_POINTER_H_

namespace basic
{
namespace type
{
namespace trait
{
namespace rem
{

template<typename T>
struct Pointer
{
    typedef T type;
    typedef typename Pointer<T>::type Type;
};

template<typename T>
struct Pointer<T*>
{
    typedef T type;
    typedef typename Pointer<T*>::type Type;
};

template<typename T>
struct Pointer<T*const>
{
    typedef T type;
    typedef typename Pointer<T*const>::type Type;
};

template<typename T>
struct Pointer<T*volatile>
{
    typedef T type;
    typedef typename Pointer<T*volatile>::type Type;
};

template<typename T>
struct Pointer<T*const volatile>
{
    typedef T type;
    typedef typename Pointer<T*const volatile>::type Type;
};

} //!rem

} //!trait

} //!type

} //!basic

#endif //!TYPE_TRAIT_REM_POINTER_H_

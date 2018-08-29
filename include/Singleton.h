#ifndef BASIC_SINGLETON_H_
#define BASIC_SINGLETON_H_

#include <type_traits>
#include <cstdlib>
#include <memory>
#include <utility>

#include "macro/Conditional.h"
#include "macro/HasMemberDefinition.h"
#include "macro/EnableIf.h"
#include "macro/MemberDefinition.h"
#include "type/Access.h"
#include "type/trait/Simple.h"

namespace _helper
{
namespace _basic
{
namespace _singleton
{
namespace _has_member
{
namespace _defn
{

__DEFINE_HAS_MMBR_DEFN_DEFAULT_(_AccessConstructInstance,
    __AccessConstructInstance, T, AccessConstructInstanceType);

__DEFINE_HAS_MMBR_DEFN_DEFAULT_(_AccessDestroyInstance,
    __AccessDestroyInstance, T, AccessDestroyInstanceType);

__DEFINE_HAS_MMBR_DEFN_DEFAULT_(_AccessHasInstance,
    __AccessHasInstance, T, AccessHasInstanceType);

__DEFINE_HAS_MMBR_DEFN_DEFAULT_(_AccessGetInstance,
    __AccessGetInstance, T, AccessGetInstanceType);

} //!_defn

} //!_has_member

namespace _member
{
namespace _defn
{

__DEFINE_MMBR_DEFN_DEFAULT_(__AccessConstructInstance, T, 
    AccessConstructInstanceType);

__DEFINE_MMBR_DEFN_DEFAULT_(__AccessDestroyInstance, T, 
    AccessDestroyInstanceType);

__DEFINE_MMBR_DEFN_DEFAULT_(__AccessHasInstance, T, 
    AccessHasInstanceType);

__DEFINE_MMBR_DEFN_DEFAULT_(__AccessGetInstance, T, 
    AccessGetInstanceType);
    
#define __DEFINE_CONDITIONAL_T_TRUE_DEFN_TYPE_MMBR_NAME_TYPE_()\
type

__DEFINE_CONDITIONAL_DEFAULT_TRUE_TYPE_MMBR_DEFN_FALSE_TYPE_DEFN_(
    _DefaultConditional, BoolTest, Ttrue, Tfalse, TYPE_);

#undef __DEFINE_CONDITIONAL_T_TRUE_DEFN_TYPE_MMBR_NAME_TYPE_

template<typename T, typename Td>
using _AccessConstructInstance = _DefaultConditional<_has_member::
    _defn::_AccessConstructInstance<Td>::value && std::is_same<T, Td>::value,
        __AccessConstructInstance<Td>, void>;

template<typename T, typename Td>
using _AccessDestroyInstance = _DefaultConditional<_has_member::
    _defn::_AccessDestroyInstance<Td>::value && std::is_same<T, Td>::value,
        __AccessDestroyInstance<Td>, void>;

template<typename T, typename Td>
using _AccessHasInstance = _DefaultConditional<_has_member::_defn::
    _AccessHasInstance<Td>::value && std::is_same<T, Td>::value,
        __AccessHasInstance<Td>, void>;

template<typename T, typename Td>
using _AccessGetInstance = _DefaultConditional<_has_member::_defn::
    _AccessGetInstance<Td>::value && std::is_same<T, Td>::value,
        __AccessGetInstance<Td>, void>;

} //!_defn

} //!_member

}// !_singleton

template<typename T>
class _Singleton
{
public:
    typedef basic::type::access::Public AccessConstructInstanceType;
    typedef basic::type::access::Public AccessDestroyInstanceType;
    typedef basic::type::access::Public AccessHasInstanceType;
    typedef basic::type::access::Public AccessGetInstanceType;
public:
    typedef T ValueType;
    typedef T* PointerType;
    typedef T& ReferenceType;
private:
    typedef typename basic::type::trait::Simple<T>::Type SimpleType;
private:
    template<typename Td>
    static constexpr auto _HasAllocate(Td d) ->
        decltype(Td::Allocate(), std::true_type());
    static constexpr std::false_type _HasAllocate(...);
    template<typename Td>
    static constexpr auto _HasDeallocate(Td d) ->
        decltype(Td::Deallocate(std::declval<PointerType>()), std::true_type());
    static constexpr std::false_type _HasDeallocate(...);
    template<typename Td, typename... Targs>
    static constexpr auto _HasConstruct(Td d, Targs... args) ->
        decltype(Td::Construct(std::declval<PointerType>(), args...), 
            std::true_type());
    static constexpr std::false_type _HasConstruct(...);
    template<typename Td>
    static constexpr auto _HasDestroy(Td d) ->
        decltype(Td::Destroy(std::declval<PointerType>()), std::true_type());
    static constexpr std::false_type _HasDestroy(...);
    template<typename Td, typename... Targs>
    static constexpr auto _HasConstructor(Td td, Targs... args) ->
        decltype(Td(args...),std::true_type());
    static constexpr std::false_type _HasConstructor(...);
private:
    template<typename Td>
    using HasAllocate = std::integral_constant<bool,
        decltype(_HasAllocate(std::declval<Td>()))::value>;
    template<typename Td>
    using HasDeallocate = std::integral_constant<bool,
        decltype(_HasDeallocate(std::declval<Td>()))::value>;
    template<typename Td, typename... Targs>
    using HasConstruct = std::integral_constant<bool, 
        decltype(_HasConstruct(std::declval<Td>(), 
            std::declval<Targs>()...))::value>;
    template<typename Td>
    using HasDestroy = std::integral_constant<bool,
        decltype(_HasDestroy(std::declval<Td>()))::value>;
    template<typename Td, typename... Targs>
    using HasConstructor = std::integral_constant<bool,
        decltype(_HasConstructor(std::declval<Td>(), 
            std::declval<Targs>()...))::value>;
private:
    static std::shared_ptr<T> ms_instance;
protected:
    _Singleton();
protected:
    virtual ~_Singleton();
private:
    static void Deleter(PointerType pointer);
private:
    template<typename Td>
    static typename std::enable_if<HasDestroy<Td>::value>::type 
        AssignInstance(PointerType pointer);
    template<typename Td>
    static typename std::enable_if<!HasDestroy<Td>::value>::type 
        AssignInstance(PointerType pointer);
private:
    template<typename Td>
    static typename std::enable_if<HasAllocate<Td>::value, PointerType>::type
        Allocate();
    template<typename Td>
    static typename std::enable_if<!HasAllocate<Td>::value, PointerType>::type
        Allocate();
private:
    template<typename Td>
    static typename std::enable_if<HasDeallocate<Td>::value>::type
        Deallocate(PointerType pointer);
    template<typename Td>
    static typename std::enable_if<!HasDeallocate<Td>::value>::type
        Deallocate(PointerType pointer);
private:
    template<typename... Targs>
    static typename std::enable_if<HasConstruct<SimpleType,
        Targs...>::value, PointerType>::type 
            Constructor(PointerType pointer, Targs&&... args);
    template<typename... Targs>
    static typename std::enable_if<!HasConstruct<SimpleType,
        Targs...>::value, PointerType>::type 
            Constructor(PointerType pointer, Targs&&... args);
protected:
    template<typename... Targs>
    static typename std::enable_if<HasConstructor<SimpleType, 
        Targs...>::value>::type
            Construct(PointerType pointer, Targs&&... args);
    template<typename... Targs>
    static typename std::enable_if<!HasConstructor<SimpleType, 
        Targs...>::value>::type
            Construct(PointerType pointer, Targs&&... args);
private:
    template<typename... Targs>
    static T& _ConstructInstance(Targs&&... args);
    static void _DestroyInstance();
    static bool _HasInstance();
    static T& _GetInstance();
public:
    template<typename Td = T, typename... Targs>
    static typename basic::type::access::enable_if::Public<typename
        _singleton::_member::_defn::_AccessConstructInstance<T, Td>::type, 
        T&>::type ConstructInstance(Targs&&... args);
    template<typename Td = T>
    static typename basic::type::access::enable_if::Public<typename
        _singleton::_member::_defn::_AccessDestroyInstance<T, Td>::type,
        void>::type DestroyInstance();
    template<typename Td = T>
    static typename basic::type::access::enable_if::Public<typename
        _singleton::_member::_defn::_AccessHasInstance<T, Td>::type,
        bool>::type HasInstance();
    template<typename Td = T>
    static typename basic::type::access::enable_if::Public<typename
        _singleton::_member::_defn::_AccessGetInstance<T, Td>::type,
        T&>::type GetInstance();
protected:
    template<typename Td = T, typename... Targs>
    static typename basic::type::access::enable_if::Protected<typename
        _singleton::_member::_defn::_AccessConstructInstance<T, Td>::type,
        T&>::type ConstructInstance(Targs&&... args);
    template<typename Td = T>
    static typename basic::type::access::enable_if::Protected<typename
        _singleton::_member::_defn::_AccessDestroyInstance<T, Td>::type,
        void>::type DestroyInstance();
    template<typename Td = T>
    static typename basic::type::access::enable_if::Protected<typename
        _singleton::_member::_defn::_AccessHasInstance<T, Td>::type,
        bool>::type HasInstance();
    template<typename Td = T>
    static typename basic::type::access::enable_if::Protected<typename
        _singleton::_member::_defn::_AccessGetInstance<T, Td>::type,
        T&>::type GetInstance();
private:
    template<typename Td = T, typename... Targs>
    static typename basic::type::access::enable_if::Private<typename
        _singleton::_member::_defn::_AccessConstructInstance<T, Td>::type,
        T&>::type ConstructInstance(Targs&&... args);
    template<typename Td = T>
    static typename basic::type::access::enable_if::Private<typename
        _singleton::_member::_defn::_AccessDestroyInstance<T, Td>::type,
        void>::type DestroyInstance();
    template<typename Td = T>
    static typename basic::type::access::enable_if::Private<typename
        _singleton::_member::_defn::_AccessHasInstance<T, Td>::type,
        bool>::type HasInstance();
    template<typename Td = T>
    static typename basic::type::access::enable_if::Private<typename
        _singleton::_member::_defn::_AccessGetInstance<T, Td>::type,
        T&>::type GetInstance();
};

template<typename T>
std::shared_ptr<T> _Singleton<T>::ms_instance = nullptr;

template<typename T>
_Singleton<T>::_Singleton()
{}

template<typename T>
_Singleton<T>::~_Singleton()
{}

template<typename T>
void _Singleton<T>::Deleter(PointerType pointer)
{
    SimpleType::Destroy(pointer);
    Deallocate<SimpleType>(pointer);
}

template<typename T>
template<typename Td>
typename std::enable_if<_Singleton<T>::template HasDestroy<Td>::value>::type 
    _Singleton<T>::AssignInstance(PointerType pointer)
{
    ms_instance = std::shared_ptr<T>(pointer, &Deleter);
}

template<typename T>
template<typename Td>
typename std::enable_if<!_Singleton<T>::template HasDestroy<Td>::value>::type
    _Singleton<T>::AssignInstance(PointerType pointer)
{
    ms_instance = std::shared_ptr<T>(pointer);
}

template<typename T>
template<typename Td>
typename std::enable_if<_Singleton<T>::template HasAllocate<Td>::value, 
    typename _Singleton<T>::PointerType>::type
        _Singleton<T>::Allocate()
{
    return Td::Allocate();
}

template<typename T>
template<typename Td>
typename std::enable_if<!_Singleton<T>::template HasAllocate<Td>::value, 
    typename _Singleton<T>::PointerType>::type
        _Singleton<T>::Allocate()
{
    return (PointerType)::operator new(sizeof(T));
}

template<typename T>
template<typename Td>
typename std::enable_if<_Singleton<T>::template HasDeallocate<Td>::value>::type
    _Singleton<T>::Deallocate(PointerType pointer)
{
    Td::Deallocate(pointer);
}

template<typename T>
template<typename Td>
typename std::enable_if<!_Singleton<T>::template HasDeallocate<Td>::value>::type
    _Singleton<T>::Deallocate(PointerType pointer)
{
    delete pointer;
}

template<typename T>
template<typename... Targs>
typename std::enable_if<_Singleton<T>::template HasConstruct<
    typename _Singleton<T>::SimpleType, Targs...>::value, 
        typename _Singleton<T>::PointerType>::type 
            _Singleton<T>::Constructor(PointerType pointer, Targs&&... args)
{
    SimpleType::Construct(pointer, args...);
    return pointer;
}

template<typename T>
template<typename... Targs>
typename std::enable_if<!_Singleton<T>::template HasConstruct<
    typename _Singleton<T>::SimpleType, Targs...>::value, 
        typename _Singleton<T>::PointerType>::type 
            _Singleton<T>::Constructor(PointerType pointer, Targs&&... args)
{
    _Singleton<T>::Construct(pointer, args...);
    return pointer;
}

template<typename T>
template<typename... Targs>
typename std::enable_if<_Singleton<T>::template HasConstructor<
    typename _Singleton<T>::SimpleType, Targs...>::value>::type
        _Singleton<T>::Construct(PointerType pointer, Targs&&... args)
{
    new ((void*)pointer) T(args...);
}

template<typename T>
template<typename... Targs>
typename std::enable_if<!_Singleton<T>::template HasConstructor<
    typename _Singleton<T>::SimpleType, Targs...>::value>::type
        _Singleton<T>::Construct(PointerType pointer, Targs&&... args)
{
    static_assert(_Singleton<T>::HasConstructor<
        SimpleType, Targs...>::value, "class T has no constructor");
}

template<typename T>
template<typename... Targs>
T& _Singleton<T>::_ConstructInstance(Targs&&... args)
{
    DestroyInstance();
    PointerType pointer = Allocate<SimpleType>();
    Constructor(pointer, args...);
    AssignInstance<SimpleType>(pointer);
    return (T&)(*ms_instance);
}

template<typename T>
void _Singleton<T>::_DestroyInstance()
{
    if (ms_instance != nullptr)
    {
        ms_instance = nullptr;
    }
}

template<typename T>
bool _Singleton<T>::_HasInstance()
{
    return ms_instance != nullptr;
}

template<typename T>
T& _Singleton<T>::_GetInstance()
{
    if (ms_instance == nullptr)
    {
        return ConstructInstance();
    }
    return dynamic_cast<T&>(*ms_instance);
}

template<typename T>
template<typename Td, typename... Targs>
typename basic::type::access::enable_if::Public<typename _singleton::
    _member::_defn::_AccessConstructInstance<T, Td>::type, T&>::type 
        _Singleton<T>::ConstructInstance(Targs&&... args)
{
    return _ConstructInstance(std::forward<Targs>(args)...);
}

template<typename T>
template<typename Td>
typename basic::type::access::enable_if::Public<typename _singleton::
    _member::_defn::_AccessDestroyInstance<T, Td>::type, void>::type 
        _Singleton<T>::DestroyInstance()
{
    return _DestroyInstance();
}

template<typename T>
template<typename Td>
typename basic::type::access::enable_if::Public<typename _singleton::
    _member::_defn::_AccessHasInstance<T, Td>::type, bool>::type 
        _Singleton<T>::HasInstance()
{
    return _HasInstance();
}

template<typename T>
template<typename Td >
typename basic::type::access::enable_if::Public<typename _singleton::
    _member::_defn::_AccessGetInstance<T, Td>::type, T&>::type 
        _Singleton<T>::GetInstance()
{
    return _GetInstance();
}

template<typename T>
template<typename Td, typename... Targs>
typename basic::type::access::enable_if::Protected<typename _singleton::
    _member::_defn::_AccessConstructInstance<T, Td>::type, T&>::type 
        _Singleton<T>::ConstructInstance(Targs&&... args)
{
    return _ConstructInstance(std::forward<Targs>(args)...);
}

template<typename T>
template<typename Td>
typename basic::type::access::enable_if::Protected<typename _singleton::
    _member::_defn::_AccessDestroyInstance<T, Td>::type, void>::type 
        _Singleton<T>::DestroyInstance()
{
    return _DestroyInstance();
}

template<typename T>
template<typename Td>
typename basic::type::access::enable_if::Protected<typename _singleton::
    _member::_defn::_AccessHasInstance<T, Td>::type, bool>::type 
        _Singleton<T>::HasInstance()
{
    return _HasInstance();
}

template<typename T>
template<typename Td >
typename basic::type::access::enable_if::Protected<typename _singleton::
    _member::_defn::_AccessGetInstance<T, Td>::type, T&>::type 
        _Singleton<T>::GetInstance()
{
    return _GetInstance();
}

template<typename T>
template<typename Td, typename... Targs>
typename basic::type::access::enable_if::Private<typename _singleton::
    _member::_defn::_AccessConstructInstance<T, Td>::type, T&>::type 
        _Singleton<T>::ConstructInstance(Targs&&... args)
{
    return _ConstructInstance(std::forward<Targs>(args)...);
}

template<typename T>
template<typename Td>
typename basic::type::access::enable_if::Private<typename _singleton::
    _member::_defn::_AccessDestroyInstance<T, Td>::type, void>::type 
        _Singleton<T>::DestroyInstance()
{
    return _DestroyInstance();
}

template<typename T>
template<typename Td>
typename basic::type::access::enable_if::Private<typename _singleton::
    _member::_defn::_AccessHasInstance<T, Td>::type, bool>::type 
        _Singleton<T>::HasInstance()
{
    return _HasInstance();
}

template<typename T>
template<typename Td >
typename basic::type::access::enable_if::Private<typename _singleton::
    _member::_defn::_AccessGetInstance<T, Td>::type, T&>::type 
        _Singleton<T>::GetInstance()
{
    return _GetInstance();
}

} //!_basic

} //!_helper

namespace basic
{

template<typename T>
using Singleton = _helper::_basic::_Singleton<T>;

} //!basic

#endif //!BASIC_SINGLETON_H_

#ifndef BASIC_TYPE_NAME_DECLARATOR_POINTER_H_
#define BASIC_TYPE_NAME_DECLARATOR_POINTER_H_

#include <string>
#include <ostream>

#include "../Declarator.h"
#include "../Specifier.h"

namespace basic
{
namespace type
{
namespace name
{
namespace decltor
{

static const char Pointer[] = "*";

namespace ptr
{
namespace mmbr
{

static const char Scope[] = "::";
static const char Prefix[] = " ";

} //!mmbr

static const char OpenBracket[] = "(";
static const char CloseBracket[] = ")";

} //!ptr

} //!decltor

template<typename T>
class Declarator<T*> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T>
class Declarator<T*const> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T>
class Declarator<T*volatile> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T>
class Declarator<T*const volatile> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T, typename To>
class Declarator<T To::*> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T, typename To>
class Declarator<T To::*const> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T, typename To>
class Declarator<T To::*volatile> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T, typename To>
class Declarator<T To::*const volatile> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T>
constexpr Declarator<T*>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T>
constexpr Declarator<T*>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T*>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    o << decltor::Pointer;
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T*>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T>
constexpr Declarator<T*const>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T>
constexpr Declarator<T*const>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T*const>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    o << decltor::Pointer;
    o << name::specifier::Const;
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T* const>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T>
constexpr Declarator<T*volatile>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T>
constexpr Declarator<T*volatile>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T*volatile>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    o << decltor::Pointer;
    o << name::specifier::Volatile;
    return o;
}
    
template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T*volatile>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T>
constexpr Declarator<T*const volatile>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T>
constexpr Declarator<T*const volatile>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T*const volatile>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    o << decltor::Pointer;
    o << name::specifier::ConstVolatile;
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T*const volatile>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename To>
constexpr Declarator<T To::*>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T, typename To>
constexpr Declarator<T To::*>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T To::*>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (!d.HasFlag(decltor::Type::function_flag) &&
        !d.HasFlag(decltor::Type::array_flag))
            o << decltor::ptr::mmbr::Prefix;
    o << Name<To>();
    o << decltor::ptr::mmbr::Scope;
    o << decltor::Pointer;
    return o;
}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T To::*>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename To>
constexpr Declarator<T To::*const>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T, typename To>
constexpr Declarator<T To::*const>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T To::*const>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (!d.HasFlag(decltor::Type::function_flag) &&
        !d.HasFlag(decltor::Type::array_flag))
            o << decltor::ptr::mmbr::Prefix;
    o << Name<To>();
    o << decltor::ptr::mmbr::Scope;
    o << decltor::Pointer;
    o << name::specifier::Const;
    return o;
}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T To::*const>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename To>
constexpr Declarator<T To::*volatile>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T, typename To>
constexpr Declarator<T To::*volatile>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T To::*volatile>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (!d.HasFlag(decltor::Type::function_flag) &&
        !d.HasFlag(decltor::Type::array_flag))
            o << decltor::ptr::mmbr::Prefix;
    o << Name<To>();
    o << decltor::ptr::mmbr::Scope;
    o << decltor::Pointer;
    o << name::specifier::Volatile;
    return o;
}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T To::*volatile>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename To>
constexpr Declarator<T To::*const volatile>::Declarator() :
    Declarator<T>(decltor::Type::pointer_flag, decltor::Type::pointer_flag)
{}

template<typename T, typename To>
constexpr Declarator<T To::*const volatile>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::pointer_flag)
{}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T To::*const volatile>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (!d.HasFlag(decltor::Type::function_flag) &&
        !d.HasFlag(decltor::Type::array_flag))
            o << decltor::ptr::mmbr::Prefix;
    o << Name<To>();
    o << decltor::ptr::mmbr::Scope;
    o << decltor::Pointer;
    o << name::specifier::ConstVolatile;
    return o;
}

template<typename T, typename To>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T To::*const volatile>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_POINTER_H_

#ifndef BASIC_TYPE_NAME_DECLTOR_FUNCTION_H_
#define BASIC_TYPE_NAME_DECLTOR_FUNCTION_H_

#include <string>
#include <ostream>

#include "../Declarator.h"
#include "../Parameter.h"
#include "Pointer.h"

namespace basic
{
namespace type
{
namespace name
{
namespace decltor
{
namespace func
{
namespace param
{

static const char OpenBracket[] = "(";
static const char CloseBracket[] = ")";

} //!param

static const char Conjunction[] = " ";

} //!func

} //!decltor

template<typename T, typename... Targs>
class Declarator<T(Targs...)> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) &> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) &&> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) const> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) const &> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) const &&> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) volatile> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) volatile &> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) volatile &&> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) const volatile> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) const volatile &> :
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

template<typename T, typename... Targs>
class Declarator<T(Targs...) const volatile &&> :
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

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...)>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...)>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...)>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...)>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) &>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) &>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) &>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) &>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << decltor::ref::LValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) &&>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) &&>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) &&>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) &&>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << decltor::ref::RValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const >::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::Const;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const &>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const &>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const &>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const &>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::Const;
    o << decltor::func::Conjunction;
    o << decltor::ref::LValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const &&>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const &&>::
    Declarator(const decltor::Type& first, const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const &&>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const &&>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::Const;
    o << decltor::func::Conjunction;
    o << decltor::ref::RValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) volatile>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) volatile>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) volatile>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) volatile>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::Volatile;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) volatile &>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) volatile &>::
    Declarator(const decltor::Type& first, const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) volatile &>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) volatile &>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::Volatile;
    o << decltor::func::Conjunction;
    o << decltor::ref::LValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) volatile &&>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) volatile &&>::
    Declarator(const decltor::Type& first, const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) volatile &&>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) volatile &&>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::Volatile;
    o << decltor::func::Conjunction;
    o << decltor::ref::RValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const volatile>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const volatile>::
    Declarator(const decltor::Type& first, const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const volatile>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const volatile>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::ConstVolatile;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const volatile &>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const volatile &>::
    Declarator(const decltor::Type& first, const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const volatile &>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const volatile &>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::ConstVolatile;
    o << decltor::func::Conjunction;
    o << decltor::ref::LValue;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const volatile &&>::Declarator() :
    Declarator<T>(decltor::Type::function_flag, decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
constexpr Declarator<T(Targs...) const volatile &&>::
    Declarator(const decltor::Type& first, const char& flags) :
        Declarator<T>(first, first | decltor::Type::function_flag)
{}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const volatile &&>::
    Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, typename... Targs>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& Declarator<T(Targs...) const volatile &&>::
    Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::func::param::OpenBracket;
    o << Parameter<Targs...>();
    o << decltor::func::param::CloseBracket;
    o << decltor::func::Conjunction;
    o << specifier::ConstVolatile;
    o << decltor::func::Conjunction;
    o << decltor::ref::RValue;
    Declarator<T>::Forward(o, d);
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLTOR_FUNCTION_H_

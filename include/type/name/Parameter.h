#ifndef BASIC_TYPE_NAME_PARAMETER_H_
#define BASIC_TYPE_NAME_PARAMETER_H_

#include <string>
#include <ostream>
#include <type_traits>

namespace basic
{
namespace type
{
namespace name
{
namespace param
{

static const char Conjunction[] = ",";
static const char NoConjunction[] = "";
static const char FirstPrefix[] = "";
static const char Prefix[] = " ";
static const char NoPrefix[] = "";
static const char LastPostfix[] = "";
static const char Postfix[] = "";
static const char NoPostfix[] = "";

} //!param

template<typename... Targs>
class Parameter
{
protected:
    typedef Parameter<Targs...> BaseType;
public:
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<I == 0, char>::type* Prefix();
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<I != 0 && I != S, char>::type* 
        Prefix();
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<I == S && I != 0, char>::type* 
        Prefix();
public:
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<(I + 1) == S, char>::type* Postfix();
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<(I + 1) != S && I != S, char>::type* 
        Postfix();
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<I == S, char>::type* Postfix();
public:
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<(I + 1) == S, char>::type*
        Conjunction();
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<(I + 1) != S && I != S, char>::type* 
        Conjunction();
    template<std::size_t I, std::size_t S>
    static const typename std::enable_if<I == S, char>::type* Conjunction();
public:
    template<std::size_t I, std::size_t S, typename CharT, typename Traits>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o);
};

template<typename Targ, typename... Targs>
class Parameter<Targ, Targs...> :
    public Parameter<Targs...>
{
protected:
    typedef typename Parameter<Targs...>::BaseType BaseType;
public:
    template<std::size_t I, std::size_t S, typename CharT, typename Traits>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o);
};

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<I == 0, char>::type* Parameter<Targs...>::
    Prefix()
{
     return param::FirstPrefix; 
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<I != 0 && I != S, char>::type* 
    Parameter<Targs...>::Prefix()
{
    return param::Prefix;
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<I == S && I != 0, char>::type* 
    Parameter<Targs...>::Prefix()
{
     return param::NoPrefix; 
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<(I + 1) == S, char>::type* Parameter<Targs...>::
    Postfix()
{
     return param::NoPostfix; 
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<(I + 1) != S && I != S, char>::type* 
    Parameter<Targs...>::Postfix()
{
    return param::Postfix;
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<I == S, char>::type* Parameter<Targs...>::
    Postfix()
{
     return param::LastPostfix; 
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<(I + 1) == S, char>::type* Parameter<Targs...>::
    Conjunction()
{
     return param::NoConjunction; 
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<(I + 1) != S && I != S, char>::type* 
    Parameter<Targs...>::Conjunction()
{
    return param::Conjunction;
}

template<typename... Targs>
template<std::size_t I, std::size_t S>
const typename std::enable_if<I == S, char>::type* Parameter<Targs...>::
    Conjunction()
{
    return param::NoConjunction; 
}

template<typename... Targs>
template<std::size_t I, std::size_t S, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    Parameter<Targs...>::Forward(std::basic_ostream<CharT, Traits>& o)
{
    o << BaseType::template Prefix<I, S>();
    o << BaseType::template Postfix<I, S>();
    return o;
}

template<typename... Targs>
std::ostream& operator<<(std::ostream& o, Parameter<Targs...>&&)
{
    Parameter<Targs...>::template Forward<0, sizeof...(Targs)>(o);
    return o;
}

template<typename Targ, typename... Targs>
template<std::size_t I, std::size_t S, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    Parameter<Targ, Targs...>::Forward(std::basic_ostream<CharT, Traits>& o)
{
    o << BaseType::template Prefix<I, S>();
    o << Name<Targ>();
    o << BaseType::template Postfix<I, S>();
    o << BaseType::template Conjunction<I, S>();
    Parameter<Targs...>::template Forward<I+1, S>(o);
    return o;
}

template<typename Targ, typename... Targs>
std::ostream& operator<<(std::ostream& o, Parameter<Targ, Targs...>&& p)
{
    Parameter<Targ, Targs...>::template Forward<0, sizeof...(Targs) + 1>(o);
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_PARAMETER_H_

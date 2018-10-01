#ifndef BASIC_TEST_VAL_FUNCTION_H_
#define BASIC_TEST_VAL_FUNCTION_H_

#include <utility>

namespace basic
{
namespace test
{
namespace val
{

template<typename TFunction>
class Function
{};

template<typename TRet, typename... TArgs>
class Function<TRet(TArgs...)>
{
public:
    typedef TRet ReturnType;
    typedef TRet(*PointerType)(TArgs...);
public:
    typedef PointerType& GetType;
    typedef const PointerType& ConstGetType;
private:
    PointerType m_func;
public:
    Function();
    Function(PointerType func);
    Function(const Function<TRet(TArgs...)>& cpy);
    Function(Function<TRet(TArgs...)>&& mov);
public:
    Function<TRet(TArgs...)>& operator=(const Function<TRet(TArgs...)>& cpy);
    Function<TRet(TArgs...)>& operator=(Function<TRet(TArgs...)>&& mov);
public:
    TRet Call(TArgs&&... args) const;
public:
    GetType Get();
    ConstGetType Get() const;
public:
    operator bool() const;
};

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>::Function() :
    m_func(nullptr)
{}

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>::Function(PointerType func) :
    m_func(func)
{}

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>::Function(const Function<TRet(TArgs...)>& cpy) :
    m_func(cpy.m_func)
{}

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>::Function(Function<TRet(TArgs...)>&& mov) :
    m_func(std::move(mov.m_func))
{}

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>& Function<TRet(TArgs...)>::
    operator=(const Function<TRet(TArgs...)>& cpy)
{
    m_func = cpy.m_func;
    return *this;
}

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>& Function<TRet(TArgs...)>::
    operator=(Function<TRet(TArgs...)>&& mov)
{
    m_func = std::move(mov.m_func);
    return *this;
}

template<typename TRet, typename... TArgs>
TRet Function<TRet(TArgs...)>::Call(TArgs&&... args) const
{
    return m_func(std::forward<TArgs>(args)...);
}

template<typename TRet, typename... TArgs>
typename Function<TRet(TArgs...)>::GetType 
    Function<TRet(TArgs...)>::Get()
{
    return m_func;
}

template<typename TRet, typename... TArgs>
typename Function<TRet(TArgs...)>::ConstGetType 
    Function<TRet(TArgs...)>::Get() const
{
    return m_func;
}

template<typename TRet, typename... TArgs>
Function<TRet(TArgs...)>::operator bool() const
{
    return m_func != nullptr;
}

} //!val

} //!test

} //!basic

#endif //!BASIC_TEST_VAL_FUNCTION_H_

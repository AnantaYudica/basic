#ifndef BASIC_TEST_TYPE_FUNCTION_H_
#define BASIC_TEST_TYPE_FUNCTION_H_

#include <utility>

namespace basic
{
namespace test
{
namespace type
{

template<typename TFunction, TFunction* FunctionPointer>
class Function
{};

template<typename TRet, typename... TArgs, TRet(*Func)(TArgs...)>
class Function<TRet(TArgs...), Func>
{
public:
    typedef TRet ReturnType;
    typedef TRet(*PointerType)(TArgs...);
public:
    static constexpr PointerType Pointer = Func;
public:
    constexpr TRet Call(TArgs&&... args) const;
};

template<typename TRet, typename... TArgs, TRet(*Func)(TArgs...)>
constexpr TRet Function<TRet(TArgs...), Func>::Call(TArgs&&... args) const
{
    return Func(std::forward<TArgs>(args)...);
}

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_FUNCTION_H_


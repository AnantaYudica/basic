#ifndef BASIC_TEST_VAR_HAS_H_
#define BASIC_TEST_VAR_HAS_H_

#include "../Variable.h"
#include "Definition.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace var
{
namespace has
{

template<typename TVar>
constexpr auto LValue(int) -> decltype(
    static_cast<typename TVar::GetType(TVar::*)()>(&TVar::Get), 
        std::true_type());
template<typename TVar>
constexpr std::false_type LValue(...);

template<typename TVar>
constexpr auto RValue(int) -> decltype(
    static_cast<typename TVar::ConstGetType(TVar::*)() const>(&TVar::Get), 
        std::true_type());
template<typename TVar>
constexpr std::false_type RValue(...);

} //!has

template<std::size_t I, typename TVar>
class Has
{};

template<std::size_t I, typename... TArgs>
class Has<I, test::Variable<TArgs...>>
{
private:
    typedef typename var::Definition<I, 
        test::Variable<TArgs...>>::Type VariableType;
public:
    static constexpr bool LValue = decltype(var::has::
        LValue<VariableType>(0))::value;
    static constexpr bool RValue = decltype(var::has::
        RValue<VariableType>(0))::value;
    static constexpr bool Value = LValue || RValue;
};


} //!var

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_HAS_H_
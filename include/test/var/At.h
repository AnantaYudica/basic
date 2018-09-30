#ifndef BASIC_TEST_VAR_AT_H_
#define BASIC_TEST_VAR_AT_H_

#include "../Variable.h"
#include "Definition.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace var
{

template<std::size_t I, typename TArg, typename... TArgs>
typename var::Definition<I, test::Variable<TArg, TArgs...>>::Type&
    At(test::Variable<TArg, TArgs...>& var)
{
    return dynamic_cast<typename var::Definition<I, test::Variable<TArg, 
        TArgs...>>::Type&>(var);
}

template<std::size_t I, typename TArg, typename... TArgs>
const typename var::Definition<I, test::Variable<TArg, TArgs...>>::Type&
    At(const test::Variable<TArg, TArgs...>& var)
{
    return dynamic_cast<typename var::Definition<I, test::Variable<TArg, 
        TArgs...>>::Type&>(var);
}

} //!var

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_AT_H_

#ifndef BASIC_TEST_VAR_VAL_DEFINITION_H_
#define BASIC_TEST_VAR_VAL_DEFINITION_H_

#include "../Value.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace var
{
namespace val
{

template<std::size_t I, typename... TArgs>
struct Definition
{
    typedef void type;
    typedef void Type;
    typedef bool has_value_type;
    typedef bool HasValueType;
    static constexpr has_value_type has_value = false;
    static constexpr HasValueType HasValue = false;
}; 

template<std::size_t I, typename TArg, typename... TArgs>
struct Definition<I, TArg, TArgs...> : Definition<I - 1, TArgs...>
{
    typedef typename Definition<I - 1, TArgs...>::type type;
    typedef typename Definition<I - 1, TArgs...>::Type Type;
    typedef typename Definition<I - 1, TArgs...>::has_value_type 
        has_value_type;
    typedef typename Definition<I - 1, TArgs...>::HasValueType HasValueType;
    static constexpr has_value_type has_value = 
        Definition<I - 1, TArgs...>::has_value;
    static constexpr HasValueType HasValue = 
        Definition<I - 1, TArgs...>::HasValue;
};

template<typename TArg, typename... TArgs>
struct Definition<0, TArg, TArgs...>
{
    typedef void type;
    typedef void Type;
    typedef bool has_value_type;
    typedef bool HasValueType;
    static constexpr has_value_type has_value = false;
    static constexpr HasValueType HasValue = false;
};

template<typename TArg, typename... TArgs>
struct Definition<0, var::Value<TArg>, TArgs...>
{
    typedef TArg type;
    typedef TArg Type;
    typedef bool has_value_type;
    typedef bool HasValueType;
    static constexpr has_value_type has_value = true;
    static constexpr HasValueType HasValue = true;
};

} //!val

} //!var

} //!test

}//!basic

#endif //!BASIC_TEST_VAR_VAL_DEFINITION_H_

#ifndef BASIC_TEST_TYPE_VAL_SEQ_MAKE_H_
#define BASIC_TEST_TYPE_VAL_SEQ_MAKE_H_

#include <utility>
#include "../Sequence.h"

namespace basic
{
namespace test
{
namespace type
{
namespace val
{
namespace seq
{

template<typename TValue, TValue FirstValue, std::size_t SizeTerm,
    typename TFormula, std::size_t Term = 0, TValue... Values>
struct Make
{
    using Type = typename Make<TValue, FirstValue, SizeTerm - 1,
        TFormula, Term + 1, Values..., 
        TFormula::Formula(FirstValue, Term)>::Type;
};

template<typename TValue, TValue FirstValue, typename TFormula, 
    std::size_t Term, TValue... Values>
struct Make<TValue, FirstValue, 0, TFormula, Term, Values...>
{
    using Type = val::Sequence<TValue, Values...>;
};

} //!seq

} //!val

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_VAL_SEQUENCE_MAKE_H_

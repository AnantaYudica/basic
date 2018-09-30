#ifndef BASIC_TEST_TYPE_INDEX_H_
#define BASIC_TEST_TYPE_INDEX_H_

#include <cstddef>

namespace basic
{
namespace test
{
namespace type
{

template<typename T, std::size_t I>
struct Index
{
    typedef T Type;
    static constexpr std::size_t Value = I;
};

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_INDEX_H_

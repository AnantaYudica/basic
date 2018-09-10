#ifndef BASIC_TEST_CSTR_FORMAT_H_
#define BASIC_TEST_CSTR_FORMAT_H_

#include "../CString.h"

#include <cstring>
#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace cstr
{

template<typename TChar = char, typename... TArgs>
test::CString<typename std::remove_reference<TChar>::type> 
    Format(const std::size_t& size, const char* format, TArgs&&... args)
{
    if (size != 0)
    {
        auto* cstr = new typename std::remove_reference<TChar>::type[size];
        int res = snprintf(cstr, size, format, std::forward<TArgs>(args)...);
        if (res >= size || res < 0)
            cstr[size - 1] = '\0';
        return {std::move(cstr), size};
    }
    return {""};
}

} //!cstr

} //!test

} //!basic

#endif //!BASIC_TEST_CSTR_FORMAT_H_


#ifndef BASIC_TEST_TYPE_PARAM_NAME_H_
#define BASIC_TEST_TYPE_PARAM_NAME_H_

#include "../Name.h"
#include "../../CString.h"

#include <cstddef>
#include <type_traits>

namespace basic
{
namespace test
{
namespace type
{
namespace param
{

template<typename... TArgs>
class Name 
{
protected:
    template<typename TChar>
    static TChar* Forward(std::size_t& size);
public:
    template<typename TChar = char>
    static test::CString<TChar> CStr();
};

template<typename TArg, typename... TArgs>
class Name<TArg, TArgs...> : public Name<TArgs...>
{
protected:
    template<typename TChar>
    static TChar* Forward(std::size_t& size);
public:
    template<typename TChar = char>
    static test::CString<TChar> CStr();
};

template<typename... TArgs>
template<typename TChar>
TChar* Name<TArgs...>::Forward(std::size_t& size)
{
    TChar * cstr = new TChar[size + 1];
    cstr[size] = '\0';
    size += 1;
    return cstr;
}

template<typename... TArgs>
template<typename TChar>
test::CString<TChar> Name<TArgs...>::CStr()
{
    std::size_t size = 0;
    return {std::move(Forward<TChar>(size)), size};
}

template<typename TArg, typename... TArgs>
template<typename TChar>
TChar* Name<TArg, TArgs...>::Forward(std::size_t& size)
{
    TChar * cstr;
    std::size_t begin = size;
    test::CString<typename std::remove_const<TChar>::type> arg_cstr =
        std::move(type::Name<TArg>::CStr());
    size += arg_cstr.Size();
    if (arg_cstr.Size() != 0)
    {
        size += 1;
        cstr = Name<TArgs...>::template Forward<TChar>(size);
        memcpy(cstr + (begin + 2), *arg_cstr, (arg_cstr.Size() - 1) * 
            sizeof(TChar));
    }
    else
    {
        size += 2;
        cstr = Name<TArgs...>::template Forward<TChar>(size);
    }
    cstr[begin] = ',';
    cstr[begin + 1] = ' ';
    return cstr;
}

template<typename TArg, typename... TArgs>
template<typename TChar>
test::CString<TChar> Name<TArg, TArgs...>::CStr()
{
    std::size_t size = 0;
    TChar * cstr;
    test::CString<typename std::remove_const<TChar>::type> arg_cstr =
        std::move(type::Name<TArg>::CStr());
    size += arg_cstr.Size();
    if (arg_cstr.Size() != 0)
    {
        size -= 1;
        cstr = Name<TArgs...>::template Forward<TChar>(size);
        memcpy(cstr, *arg_cstr, (arg_cstr.Size() - 1) * 
            sizeof(TChar));
    }
    return {std::move(cstr), size};
}

} //!param

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_PARAM_NAME_H_

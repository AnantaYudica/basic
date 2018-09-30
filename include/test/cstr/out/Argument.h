#ifndef BASIC_TEST_CSTR_OUT_ARGUMENT_H_
#define BASIC_TEST_CSTR_OUT_ARGUMENT_H_

#include "../../out/Argument.h"
#include "../../CString.h"

namespace basic
{
namespace test
{
namespace out
{

template<typename TChar>
struct Argument<test::CString<TChar>>
{
    static const char* Value(test::CString<TChar> & cstr);
    static const char* Value(const test::CString<TChar> & cstr);
    static const char* Value(test::CString<TChar> && cstr);
};

template<typename TChar>
const char* Argument<test::CString<TChar>>::
    Value(test::CString<TChar> & cstr)
{
    return *cstr;
}

template<typename TChar>
const char* Argument<test::CString<TChar>>::
    Value(const test::CString<TChar> & cstr)
{
    return *cstr;
}

template<typename TChar>
const char* Argument<test::CString<TChar>>::
    Value(test::CString<TChar> && cstr)
{
    return *cstr;
}

} //!out

} //!test

} //!basic

#endif //!BASIC_TEST_CSTR_OUT_ARGUMENT_H_

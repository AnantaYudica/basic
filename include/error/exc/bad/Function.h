#ifndef BASIC_ERROR_EXC_BAD_FUNCTION_H_
#define BASIC_ERROR_EXC_BAD_FUNCTION_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <utility>

namespace basic
{
namespace error
{
namespace exc
{
namespace bad
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Function : public error::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Function() noexcept;
public:
    inline Function(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Function() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Function(const Function & cpy) noexcept;
    inline Function(Function && mov) noexcept;
public:
    inline Function & operator=(const Function &) = delete;
    inline Function & operator=(Function &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Function::Function() noexcept :
    TriggerType(constant::error::bad_function_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Function::Function(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_function_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Function::Function(const Function & cpy) noexcept :
    TriggerType(cpy)
{}

inline Function::Function(Function && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Function::CharType * 
Function::Message() const noexcept
{
    return "Bad Function Exception";
}

inline const error::intf::Output & Function::
    operator>>(OutputType & out) const noexcept
{
    error::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Function : public error::exc::Bad
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const error::exc::bad::Function & e) noexcept
{
    return Standard(constant::error::bad_function_id);
}

#endif //!USING_STANDARD_EXCEPTION

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_BAD_FUNCTION_H_

#ifndef BASIC_ERR_EXC_BAD_FUNCTION_H_
#define BASIC_ERR_EXC_BAD_FUNCTION_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <utility>

namespace basic
{
namespace err
{
namespace exc
{
namespace bad
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Function : public err::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Function() noexcept;
public:
    inline Function(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Function() noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Function(const Function & cpy) noexcept;
    inline Function(Function && mov) noexcept;
public:
    inline Function & operator=(const Function &) = delete;
    inline Function & operator=(Function &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Function::Function() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::bad_function_id,
        "unknown", static_cast<std::size_t>(-1))
#else
    TriggerType(basic::defn::err::bad_function_id)
#endif //!USING_BASIC_ERR_FILE_AND_LINE
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Function::Function(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::bad_function_id, file, line)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

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

inline const err::intf::Output & Function::
    operator>>(OutputType & out) const noexcept
{
    err::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Function : public err::exc::Bad
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const err::exc::bad::Function & e) noexcept
{
    return Standard(basic::defn::err::bad_function_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_BAD_FUNCTION_H_

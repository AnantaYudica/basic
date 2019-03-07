#ifndef BASIC_ERR_EXC_RUNTIME_UNDERFLOW_H_
#define BASIC_ERR_EXC_RUNTIME_UNDERFLOW_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{
namespace runtime
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Underflow : public exc::Runtime
{
public:
    typedef typename err::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Underflow() noexcept;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Underflow(const CharType * message) noexcept;
public:
    inline Underflow(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Underflow(const CharType * message) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Underflow(const Underflow & cpy) noexcept;
    inline Underflow(Underflow && mov) noexcept;
public:
    inline Underflow & operator=(const Underflow &) = delete;
    inline Underflow & operator=(Underflow &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Underflow::Underflow() noexcept :
    TriggerType(basic::defn::err::runtime_underflow_id),
    exc::Runtime("Underflow Runtime Exception")
{}

inline Underflow::Underflow(const CharType * message) noexcept :
    TriggerType(basic::defn::err::runtime_underflow_id),
    exc::Runtime(message)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Underflow::Underflow(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::runtime_underflow_id, file, line),
        exc::Runtime(message)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Underflow::Underflow(const Underflow & cpy) noexcept :
    TriggerType(cpy),
    exc::Runtime(cpy)
{}

inline Underflow::Underflow(Underflow && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Runtime(std::move(mov))
{}

inline const typename Underflow::CharType * Underflow::Message() const noexcept
{
    return exc::Runtime::Message();
}

inline const err::intf::Output & 
Underflow::operator>>(OutputType & out) const noexcept
{
    exc::Runtime::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::underflow_error Underflow;

#endif //!USING_STANDARD_EXCEPTION

} //!runtime

} //!exc

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::underflow_error & e)
{
    return Standard(basic::defn::err::runtime_underflow_id);
}

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_RUNTIME_UNDERFLOW_H_

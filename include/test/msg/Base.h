#ifndef BASIC_TEST_MSG_BASE_H_
#define BASIC_TEST_MSG_BASE_H_

#include "Format.h"
#include "Argument.h"
#include "arg/Value.h"
#include "arg/type/Function.h"
#include "arg/type/Index.h"
#include "arg/type/Name.h"
#include "arg/type/Value.h"
#include "arg/type/param/Name.h"
#include "arg/type/param/name/At.h"
#include "arg/type/val/Sequence.h"
#include "arg/type/val/seq/At.h"
#include "arg/val/Function.h"
#include "arg/val/Parameter.h"
#include "arg/val/Sequence.h"
#include "arg/val/param/At.h"
#include "arg/val/seq/At.h"

// todo : Remove when next release
#ifndef REMOVED_DEPRECATED
#define REMOVED_DEPRECATED
#endif //!REMOVED_DEPRECATED

#include "arg/var/Value.h"

// end todo


namespace basic
{
namespace test
{
namespace msg
{

namespace base
{

struct Info {};
struct Debug {};
struct Error {};

}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
class Base
{
private:
    msg::Format<TChar> m_infoFormat;
    msg::Format<TChar> m_debugFormat;
    msg::Format<TChar> m_errorFormat;
protected:
    Base();
public:
    ~Base();
protected:
    void SetFormat(const base::Info&, const TCaseId&, 
        const msg::Format<TChar>& format);
    void SetFormat(const base::Debug&, const TCaseId&, 
        const msg::Format<TChar>& format);
    void SetFormat(const base::Error&, const TCaseId&, 
        const msg::Format<TChar>& format);
    void SetFormat(const base::Info&, const TCaseId&, 
        msg::Format<TChar>&& format);
    void SetFormat(const base::Debug&, const TCaseId&, 
        msg::Format<TChar>&& format);
    void SetFormat(const base::Error&, const TCaseId&, 
        msg::Format<TChar>&& format);
public:
    const msg::Format<TChar>& Format(const base::Info&, const TCaseId&) const;
    const msg::Format<TChar>& Format(const base::Debug&, const TCaseId&) const;
    const msg::Format<TChar>& Format(const base::Error&, const TCaseId&) const;
    TArgInfo Argument(const base::Info&, const TCaseId&) const;
    TArgDebug Argument(const base::Debug&, const TCaseId&) const;
    TArgError Argument(const base::Error&, const TCaseId&) const;
};

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::Base()
{}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::~Base()
{}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
void Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    SetFormat(const base::Info&, const TCaseId&, 
        const msg::Format<TChar>& format)
{
    m_infoFormat = format;
}

template<typename TCaseId, typename TChar, typename TArgInfo,
    typename TArgDebug, typename TArgError>
void Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    SetFormat(const base::Debug&, const TCaseId&, 
        const msg::Format<TChar>& format)
{
    m_debugFormat = format;
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
void Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    SetFormat(const base::Error&, const TCaseId&, 
        const msg::Format<TChar>& format)
{
    m_errorFormat = format;
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
void Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    SetFormat(const base::Info&, const TCaseId&, msg::Format<TChar>&& format)
{
    m_infoFormat = std::move(format);
}

template<typename TCaseId, typename TChar, typename TArgInfo,
    typename TArgDebug, typename TArgError>
void Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    SetFormat(const base::Debug&, const TCaseId&, msg::Format<TChar>&& format)
{
    m_debugFormat = std::move(format);
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
void Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    SetFormat(const base::Error&, const TCaseId&, msg::Format<TChar>&& format)
{
    m_errorFormat = std::move(format);
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
const msg::Format<TChar>& Base<TCaseId, TChar, TArgInfo, TArgDebug, 
    TArgError>::Format(const base::Info&, const TCaseId&) const
{
    return m_infoFormat;
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
const msg::Format<TChar>& Base<TCaseId, TChar, TArgInfo, TArgDebug, 
    TArgError>::Format(const base::Debug&, const TCaseId&) const
{
    return m_debugFormat;
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
const msg::Format<TChar>& Base<TCaseId, TChar, TArgInfo, TArgDebug, 
    TArgError>::Format(const base::Error&, const TCaseId&) const
{
    return m_errorFormat;
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
TArgInfo Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    Argument(const base::Info&, const TCaseId&) const
{
    return {};
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
TArgDebug Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    Argument(const base::Debug&, const TCaseId&) const
{
    return {};
}

template<typename TCaseId, typename TChar, typename TArgInfo, 
    typename TArgDebug, typename TArgError>
TArgError Base<TCaseId, TChar, TArgInfo, TArgDebug, TArgError>::
    Argument(const base::Error&, const TCaseId&) const
{
    return {};
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_BASE_H_
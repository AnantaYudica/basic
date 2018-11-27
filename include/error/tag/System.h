#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_SYSTEM_H_
#define BASIC_ERROR_TAG_SYSTEM_H_

#include "Trigger.h"
#include "../id/System.h"
#include "../system/Category.h"
#include "../defn/type/Output.h"
#include "../defn/type/system/category/Value.h"
#include "../defn/type/system/code/Value.h"

namespace basic
{
namespace error
{
namespace tag
{

struct System {};

} //!tag

} //!error

template<>
class Error<error::tag::System> :
    public Error<error::tag::Trigger>
{
public:
    typedef Error<error::tag::Trigger> TriggerType;
public:
    typedef error::defn::type::Output OutputValueType;
public:
    typedef error::defn::type::system::category::Value 
        CategoryValueType;
    typedef error::defn::type::system::code::Value 
        CodeValueType;
public:
    Error() noexcept;
    Error(const error::id::System& id, const char* file, 
        const std::size_t& line) noexcept;
public:
    Error(const Error<error::tag::System>& cpy) noexcept;
    Error(Error<error::tag::System>&& mov) noexcept;
public:
    Error<error::tag::System>& 
        operator=(const Error<error::tag::System>&) = delete;
    Error<error::tag::System>& 
        operator=(Error<error::tag::System>&&) = delete;
public:
    virtual const char * Message() const noexcept;
public:
    CategoryValueType Category() const noexcept;
    CodeValueType Code() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

Error<error::tag::System>::Error() noexcept :
    TriggerType()
{}

Error<error::tag::System>::Error(const error::id::System& id, 
    const char* file, const std::size_t& line) noexcept :
        TriggerType(id, file, line)
{}

Error<error::tag::System>::Error(const Error<error::tag::System>& cpy) 
    noexcept :
        TriggerType(cpy)
{}

Error<error::tag::System>::Error(Error<error::tag::System>&& mov) noexcept :
    TriggerType(std::move(mov))
{}

const char * Error<error::tag::System>::Message() const noexcept 
{
    return "";
}

typename Error<error::tag::System>::CategoryValueType 
    Error<error::tag::System>::Category() const noexcept
{
    return this->Identification().ErrorSystem().Category();
}

typename Error<error::tag::System>::CodeValueType 
    Error<error::tag::System>::Code() const noexcept
{
    return this->Identification().ErrorSystem().Code();
}

typename Error<error::tag::System>::OutputValueType& 
Error<error::tag::System>::Output(OutputValueType& out) const noexcept
{
    TriggerType::Output(out);
    return out;
}

} //!basic

#endif //!BASIC_ERROR_TAG_SYSTEM_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_

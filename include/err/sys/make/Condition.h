#ifndef BASIC_ERR_SYS_MAKE_CONDITION_H_
#define BASIC_ERR_SYS_MAKE_CONDITION_H_

#include "../../defn/type/sys/cond/Value.h"

namespace basic
{
namespace err
{
namespace sys
{
namespace make
{

template<typename T>
struct Condition
{
    Condition() = delete;
    static err::defn::type::sys::cond::Value Value(const T & cond) noexcept
    {
        return static_cast<const err::defn::type::sys::cond::Value &>(cond);
    }
};

} //!make

} //!sys

} //!err

} //!basic

#endif //BASIC_ERR_SYS_MAKE_CONDITION_H_

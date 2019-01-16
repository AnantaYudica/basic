#ifndef BASIC_CONSTANT_ERROR_IDENTIFICATION_H_
#define BASIC_CONSTANT_ERROR_IDENTIFICATION_H_

#include "../../error/defn/type/code/Value.h"
#include "../../error/Identification.h"

namespace basic
{
namespace constant
{
namespace error
{

enum : basic::error::defn::type::code::Value
{
    undefined_id = static_cast<basic::error::defn::type::code::Value>(-1),
    exception_id = 1,
    logic_id = 11,
    logic_invalid_id = 111,
    logic_invalid_argument_id = 1111,
    logic_domain_id = 113,
    logic_length_id = 114,
    logic_outofrange_id = 115,
    logic_future_id = 116,
    runtime_id = 12,
    runtime_range_id = 121,
    runtime_overflow_id = 122,
    runtime_underflow_id = 123,
    runtime_regex_id = 124,
    runtime_system = 125,
    runtime_system_ios_failure = 1251,
    bad_id = 13,
    bad_typeid_id = 131,
    bad_cast_id = 132,
    bad_weakptr_id = 133,
    bad_function_id = 134,
    bad_function_call_id = 1341,
    bad_allocation_id = 135,
    bad_allocation_array_id = 1351,
    bad_allocation_array_length_id = 13511
};

} //!error

} //!constant

} //!basic

#endif //!BASIC_CONSTANT_ERROR_IDENTIFICATION_H_

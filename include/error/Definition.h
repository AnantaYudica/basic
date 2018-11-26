#ifndef BASIC_ERROR_DEFINITION_H_
#define BASIC_ERROR_DEFINITION_H_

#include <ostream>
#include <iostream>
#include <string>
#include <cstdint>

#ifndef BASIC_ERROR_CODE_VALUE_TYPE
#define BASIC_ERROR_CODE_VALUE_TYPE std::uint16_t
#endif //!BASIC_ERROR_CODE_VALUE_TYPE

#ifndef BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE
#define BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE std::uint16_t
#endif //!BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE

#ifndef BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE
#define BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE std::uint16_t
#endif //!BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE

#ifndef BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE
#define BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE std::uint8_t
#endif //!BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE

#ifndef BASIC_ERROR_OUTPUT_CHAR_TYPE
#define BASIC_ERROR_OUTPUT_CHAR_TYPE char
#endif //!BASIC_ERROR_OUTPUT_CHAR_TYPE

#ifndef BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE
#define BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE\
    std::char_traits<BASIC_ERROR_OUTPUT_CHAR_TYPE>
#endif //!BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE

#ifndef BASIC_ERROR_OUTPUT_TYPE
#define BASIC_ERROR_OUTPUT_TYPE\
    std::basic_ostream<BASIC_ERROR_OUTPUT_CHAR_TYPE,\
        BASIC_ERROR_OUTPUT_CHARTRAIT_TYPE>
#endif //!BASIC_ERROR_OUTPUT_TYPE

#ifndef BASIC_ERROR_IDENTIFICATION_RECORD_TYPE
#include "id/Record.h"
#define BASIC_ERROR_IDENTIFICATION_RECORD_TYPE \
    basic::error::id::Record<BASIC_ERROR_CODE_VALUE_TYPE,\
        BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE,\
        BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE>
#endif //!BASIC_ERROR_IDENTIFICATION_RECORD_TYPE

#ifndef BASIC_ERROR_OUTPUT
#define BASIC_ERROR_OUTPUT std::cerr
#endif //!BASIC_ERROR_OUTPUT

#ifndef BASIC_ERROR_OUTPUT_OPERATOR
#define BASIC_ERROR_OUTPUT_OPERATOR(OUTPUT_NAME, ARG,...)\
    OUTPUT_NAME << ARG,##__VA_ARGS__
#endif //!BASIC_ERROR_OUTPUT_OPERATOR

#endif //!BASIC_ERROR_DEFINITION_H_
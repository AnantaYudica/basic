#ifndef BASIC_ERROR_H_
#define BASIC_ERROR_H_

#include "Error.defn.h"

#include <cstddef>
#include <ostream>
#include <string>
#include <cstdint>

#include "error/tag/Trigger.h"
#include "error/tag/Catch.h"
#include "error/tag/System.h"

#ifdef USING_ABORT
#ifdef USING_EXCEPTION
#error "USING_EXCEPTION is defined"
#endif //!USING_EXCEPTION
#endif //!USING_ABORT

//#define USING_EXCEPTION
//#define USING_BASIC_ERROR_EXCEPTION
//#define USING_STANDARD_EXCEPTION
//#define USING_BASIC_ERROR_CATCH_OPERATOR_THROW_AGAIN
//#define USING_BASIC_ERROR_CATCH_OPERATOR_OUTPUT
//#define USING_BASIC_ERROR_ALLOCATE_MESSAGE_DYNAMIC
//#define USING_BASIC_ERROR_ALLOCATE_MESSAGE_AUTOMATIC
//#define USING_BASIC_ERROR_FILE_AND_LINE
//#define BASIC_ERROR_ALLOCATE_MESSAGE_AUTOMATIC_SIZE

#ifdef USING_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION
#ifdef USING_BASIC_ERROR_EXCEPTION
#error "USING_BASIC_ERROR_EXCEPTION is defined"
#endif //!USING_BASIC_ERROR_EXCEPTION 

#else //else USING_STANDARD_EXCEPTION

#ifndef USING_BASIC_ERROR_EXCEPTION
#define USING_BASIC_ERROR_EXCEPTION
#endif //!USING_BASIC_ERROR_EXCEPTION

#endif //!USING_STANDARD_EXCEPTION

#ifdef USING_BASIC_ERROR_CATCH_OPERATOR_THROW_AGAIN

#endif //!USING_BASIC_ERROR_CATCH_OPERATOR_THROW_AGAIN

#ifdef USING_BASIC_ERROR_CATCH_OPERATOR_OUTPUT

#endif //!USING_BASIC_ERROR_CATCH_OPERATOR_OUTPUT

#endif //!USING_EXCEPTION

#ifndef TRY
#ifdef USING_EXCEPTION
#define TRY try

#else //else USING_EXCEPTION
#define TRY

#endif //!USING_EXCEPTION
#endif //!TRY

#ifndef CATCH
#ifdef USING_EXCEPTION
#define CATCH catch
#else
#define CATCH if (false)
#endif
#endif

#ifndef THROW
#ifdef USING_EXCEPTION
#define THROW(TYPE, ...) throw TYPE,##__VA_ARGS__(__FILE__, __LINE__)
#else
#define THROW(TYPE, ...) 

#endif
#endif
#ifndef THROW_IF
#ifdef USING_EXCEPTION
#define THROW_IF(CONDITIONAL, TYPE, ...)\
    if (CONDITIONAL) throw TYPE,##__VA_ARGS__(__FILE__, __LINE__)
#else
#define THROW_IF(...)
#endif
#endif

#ifndef BASIC_ERROR_CATCH_OPERATOR
#ifdef USING_EXCEPTION

#if !defined(USING_BASIC_ERROR_CATCH_OPERATOR_THROW_AGAIN)
#define BASIC_ERROR_CATCH_OPERATOR(...)\
throw

#elif defined(USING_BASIC_ERROR_CATCH_OPERATOR_OUTPUT)
#define BASIC_ERROR_CATCH_OPERATOR(...)\
basic::Error<basic::error::tag::Output>(__VA_ARGS__)

#else
#define BASIC_ERROR_CATCH_OPERATOR(...)
#endif

#else //else USING_EXCEPTION
#define BASIC_ERROR_CATCH_OPERATOR(...)

#endif //!USING_EXCEPTION

#endif //!BASIC_ERROR_CATCH_OPERATOR

#endif //!BASIC_ERROR_H_

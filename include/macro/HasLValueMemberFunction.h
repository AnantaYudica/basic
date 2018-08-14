#ifndef BASIC_MACRO_HASMEMBERFUNCTION_H_INITIALIZATION_
#include "HasMemberFunction.h"
#else //ELSE BASIC_HASMEMBERFUNCTION_H_INITIALIZATION_

#ifndef BASIC_MACRO_HASLVALUEMEMBERFUNCTION_H_
#define BASIC_MACRO_HASLVALUEMEMBERFUNCTION_H_

#include <type_traits>

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TRAILING_LVAL_(\
    __VAR_T_NAME__,\
    __VAR_T_ARGS_NAME__,\
    __T_RET_NAME__,\
    __MACRO_DEFINE_NAME_PREFIX__,\
    __PROTO_FUNC_T_RET_NAME_OR_PROTO_FUNC_T_RET_NAME_TMPL__,\
    __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
decltype(__DEFINE_HAS_MMBR_FUNC_\
    ##__PROTO_FUNC_T_RET_NAME_OR_PROTO_FUNC_T_RET_NAME_TMPL__(\
        __T_RET_NAME__, __MACRO_DEFINE_NAME_PREFIX__,\
        __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)(\
            __VAR_T_NAME__.__MMBR_FUNC_NAME__\
            ##__VA_ARGS__(__VAR_T_ARGS_NAME__...)), std::true_type())

#define __DEFINE_HAS_LVAL_MMBR_FUNC_VAL_(\
    __VAL_NAME__,\
    __ALIAS_VAL_TYPE_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__)\
static constexpr __ALIAS_VAL_TYPE_NAME__ __VAL_NAME__ =\
    __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_DECLTYPE_(__T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
        __DEFINE_HAS_LVAL_MMBR_FUNC_, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
        __PROTO_FUNC_TMPL_ARG_LIST__)::value

#define __DEFINE_HAS_LVAL_MMBR_FUNC_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
__DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_(__T_NAME__, __T_RET_NAME__,\
    __T_ARGS_NAME__)

#define __DEFINE_HAS_LVAL_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_()\
__DEFINE_HAS_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_()

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
__DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_(__T_NAME__,\
    __T_RET_NAME__, __T_ARGS_NAME__)

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
__DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_(__T_NAME__,\
    __T_RET_NAME__, __T_ARGS_NAME__)

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_(__T_NAME__, __T_RET_NAME__,\
    __T_ARGS_NAME__, __T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__)

#define __DEFINE_HAS_LVAL_MMBR_FUNC_STRUCT_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__)\
template<__DEFINE_HAS_LVAL_MMBR_FUNC_TMPL_PARAM_LIST_\
    ##__TMPL_PARAM_LIST_POSTFIX__(__T_NAME__, __T_RET_NAME__,\
        __T_ARGS_NAME__)>\
struct __STRUCT_NAME__\
{\
    __DEFINE_HAS_MMBR_FUNC_ALIAS_VAL_TYPE_(value_type);\
    __DEFINE_HAS_MMBR_FUNC_ALIAS_VAL_TYPE_(ValueType);\
    __DEFINE_HAS_LVAL_MMBR_FUNC_VAL_(value, value_type, __T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
        __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
        __PROTO_FUNC_TMPL_ARG_LIST__);\
    __DEFINE_HAS_LVAL_MMBR_FUNC_VAL_(Value, ValueType, __T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
        __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
        __PROTO_FUNC_TMPL_ARG_LIST__);\
}

#define __DEFINE_HAS_LVAL_MMBR_FUNC_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_T_RET_NAME_OR_PROTO_FUNC_T_RET_NAME_TMPL__,\
    __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
__DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_(__PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__,\
    __DEFINE_HAS_LVAL_MMBR_FUNC_,\
    __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_T_RET_NAME_OR_PROTO_FUNC_T_RET_NAME_TMPL__,\
    __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    LVAL_, __MMBR_FUNC_NAME__,##__VA_ARGS__);\
__DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_(__PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__, __DEFINE_HAS_LVAL_MMBR_FUNC_,\
    __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__);\
__DEFINE_HAS_LVAL_MMBR_FUNC_STRUCT_(__STRUCT_NAME__, __PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__, __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__)

#define __DEFINE_HAS_LVAL_MMBR_FUNC_DEFAULT_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __MMBR_FUNC_NAME__, ...)\
__DEFINE_HAS_LVAL_MMBR_FUNC_(__STRUCT_NAME__, __PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__,, T_NAME_,,,,,\
    PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,,\
    __MMBR_FUNC_NAME__,##__VA_ARGS__)

#endif //!BASIC_MACRO_HASLVALUEMEMBERFUNCTION_H_

#include "HasMemberFunction.h"

#endif //!BASIC_MACRO_HASMEMBERFUNCTION_H_INITIALIZATION_

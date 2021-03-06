#ifndef BASIC_MACRO_HASSTATICMEMBERFUNCTION_H_
#define BASIC_MACRO_HASSTATICMEMBERFUNCTION_H_

#include <type_traits>
#include "../type/trait/Simple.h"

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_NAME_(\
    __T_NAME__, ...)\
__T_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_(\
    __T_NAME__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_NAME__<__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_\
    ##__PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_(\
    __T_RET_NAME__, ...)\
__T_RET_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_(\
    __T_RET_NAME__,\
    __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_RET_NAME__<\
    __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_\
        ##__PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TRAILING_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_T_GET_NAME_OR_PROTO_FUNC_T_GET_NAME_TMPL__,\
    __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
decltype(__DEFINE_HAS_STATIC_MMBR_FUNC_\
    ##__PROTO_FUNC_T_GET_NAME_OR_PROTO_FUNC_T_GET_NAME_TMPL__(\
        __T_RET_NAME__, __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)(\
            __DEFINE_HAS_STATIC_MMBR_FUNC_\
                ##__PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__(\
                    __T_NAME__, __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__)::\
                        __MMBR_FUNC_NAME__,##__VA_ARGS__(args...)),\
                            std::true_type())

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_(\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_T_GET_NAME_OR_PROTO_FUNC_T_GET_NAME_TMPL__,\
    __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
template<__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_\
    ##__PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__(__T_NAME__, __T_RET_NAME__,\
        __T_ARGS_NAME__)>\
constexpr auto __PROTO_FUNC_NAME__(int, __T_ARGS_NAME__... args) ->\
__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TRAILING_(__T_NAME__,\
    __T_RET_NAME__, __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__,\
        __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
            __PROTO_FUNC_T_GET_NAME_OR_PROTO_FUNC_T_GET_NAME_TMPL__,\
                __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
                    __MMBR_FUNC_NAME__,##__VA_ARGS__)

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_(\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__)\
template<__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_\
    ##__PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__(__T_NAME__, __T_RET_NAME__,\
        __T_ARGS_NAME__)>\
constexpr std::false_type __PROTO_FUNC_NAME__ (...)

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_ALIAS_VAL_TYPE_(\
    __ALIAS_VAL_TYPE_NAME__)\
typedef bool __ALIAS_VAL_TYPE_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_(\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__,\
        __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME_SIMPLE_TYPE__,##__VA_ARGS__, __T_RET_NAME__, __T_ARGS_NAME__...

#define __DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_(\
    __T_NAME__, ...)\
__T_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_TMPL_(\
    __T_NAME__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_NAME__<__DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_\
    ##__T_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_SIMPLE_TYPE_(\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
typename basic::type::trait::Simple<__DEFINE_HAS_STATIC_MMBR_FUNC_\
    ##__T_NAME_OR_T_NAME_TMPL__(__T_NAME__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__)>::type

#define __DEFINE_HAS_STATIC_MMBR_FUNC_T_ARGS_NAME_DECLVAL_(\
    __T_ARGS_NAME__)\
std::declval<typename std::remove_cv<__T_ARGS_NAME__>::type>()

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__)\
__PROTO_FUNC_NAME__<__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_\
    ##__PROTO_FUNC_TMPL_ARG_LIST__(__T_NAME__, __T_RET_NAME__,\
        __T_ARGS_NAME__, __DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_SIMPLE_TYPE_(\
            __T_NAME__, __T_NAME_OR_T_NAME_TMPL__, \
                __T_NAME_TMPL_ARG_LIST_POSTFIX__))>

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARGS_(\
    __T_ARGS_NAME__)\
0, __DEFINE_HAS_STATIC_MMBR_FUNC_T_ARGS_NAME_DECLVAL_(__T_ARGS_NAME__)...

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_DECLTYPE_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__)\
decltype(__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_(__T_NAME__,\
    __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
        __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
            __PROTO_FUNC_TMPL_ARG_LIST__)(\
                __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARGS_(\
                    __T_ARGS_NAME__)))

#define __DEFINE_HAS_STATIC_MMBR_FUNC_VAL_(\
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
    __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_DECLTYPE_(__T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
            __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                __PROTO_FUNC_TMPL_ARG_LIST__)::value

#define __DEFINE_HAS_STATIC_MMBR_FUNC_STRUCT_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST__)\
template<__DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_\
    ##__TMPL_PARAM_LIST_POSTFIX__(__T_NAME__, __T_RET_NAME__,\
        __T_ARGS_NAME__)>\
struct __STRUCT_NAME__\
{\
    __DEFINE_HAS_STATIC_MMBR_FUNC_ALIAS_VAL_TYPE_(value_type);\
    __DEFINE_HAS_STATIC_MMBR_FUNC_ALIAS_VAL_TYPE_(ValueType);\
    __DEFINE_HAS_STATIC_MMBR_FUNC_VAL_(value, value_type, __T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
            __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                __PROTO_FUNC_TMPL_ARG_LIST__);\
    __DEFINE_HAS_STATIC_MMBR_FUNC_VAL_(Value, ValueType, __T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __PROTO_FUNC_NAME__,\
            __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                __PROTO_FUNC_TMPL_ARG_LIST__);\
}

#define __DEFINE_HAS_STATIC_MMBR_FUNC_(\
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
__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_(__PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__,\
        __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
            __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL__,\
                __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                    __PROTO_FUNC_T_RET_NAME_OR_PROTO_FUNC_T_RET_NAME_TMPL__,\
                        __PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
                            __MMBR_FUNC_NAME__,##__VA_ARGS__);\
__DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_(__PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__,\
        __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__);\
__DEFINE_HAS_STATIC_MMBR_FUNC_STRUCT_(__STRUCT_NAME__, __PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__, __TMPL_PARAM_LIST_POSTFIX__,\
        __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
            __PROTO_FUNC_TMPL_ARG_LIST__)

#define __DEFINE_HAS_STATIC_MMBR_FUNC_DEFAULT_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __MMBR_FUNC_NAME__, ...)\
__DEFINE_HAS_STATIC_MMBR_FUNC_(__STRUCT_NAME__, __PROTO_FUNC_NAME__,\
    __T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__,, T_NAME_,,,,,\
        PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,,\
            __MMBR_FUNC_NAME__,##__VA_ARGS__)

#endif //!BASIC_MACRO_HASSTATICMEMBERFUNCTION_H_

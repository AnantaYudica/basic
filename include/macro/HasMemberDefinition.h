#ifndef BASIC_MACRO_HASMEMBERDEFINITION_H_
#define BASIC_MACRO_HASMEMBERDEFINITION_H_

#include <type_traits>
#include "../type/trait/Simple.h"

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_(\
    __T_NAME__)\
typename __T_NAME__

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_(\
    __T_NAME__)\
typename __T_NAME__

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_T_NAME_(\
    __T_NAME__, ...)\
__T_NAME__

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_T_NAME_TMPL_(\
    __T_NAME__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_NAME__<__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_\
    ##__PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_(\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL_,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __TYPE_MMBR_NAME__, ...)\
template<__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_\
    ##__PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__(__T_NAME__)>\
constexpr auto __PROTO_FUNC_NAME__(int) ->\
    decltype(std::declval<typename __DEFINE_HAS_MMBR_DEFN_\
        ##__PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL_(__T_NAME__,\
            __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__)::\
                __TYPE_MMBR_NAME__,##__VA_ARGS__>(), std::true_type())

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_FALSE_(\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__)\
template<__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_\
    ##__PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__(__T_NAME__)>\
constexpr std::false_type __PROTO_FUNC_NAME__ (...)

#define __DEFINE_HAS_MMBR_DEFN_TMPL_PARAM_LIST_(__T_NAME__)\
typename __T_NAME__

#define __DEFINE_HAS_MMBR_DEFN_T_NAME_(\
    __T_NAME__, ...)\
__T_NAME__

#define __DEFINE_HAS_MMBR_DEFN_T_NAME_TMPL_(\
    __T_NAME__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_NAME__<__DEFINE_HAS_MMBR_DEFN_T_NAME_TMPL_ARG_LIST_\
    ##__T_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_HAS_MMBR_DEFN_ALIAS_VAL_TYPE_(\
    __ALIAS_VAL_TYPE_NAME)\
typedef bool __ALIAS_VAL_TYPE_NAME

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_LIST_(\
    __T_NAME__, __SIMPLE_T_TYPE__, ...)\
__SIMPLE_T_TYPE__,##__VA_ARGS__

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_(\
    __T_NAME__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL_,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)\
__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_LIST_\
    ##__PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__(__T_NAME__,\
        typename basic::type::trait::Simple<__DEFINE_HAS_MMBR_DEFN_\
            ##__PROTO_FUNC_T_NAME_OR_PROTO_FUNC_T_NAME_TMPL_(__T_NAME__,\
                __T_NAME_TMPL_ARG_LIST_POSTFIX__)>::type)

#define __DEFINE_HAS_MMBR_DEFN_DECLTYPE_VAL_(\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL_,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)\
decltype(__PROTO_FUNC_NAME__<__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_(\
    __T_NAME__, __T_NAME_OR_T_NAME_TMPL_, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
        __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)>(0))::value

#define __DEFINE_HAS_MMBR_DEFN_VAL_(\
    __VAL_NAME__,\
    __ALIAS_VAL_TYPE_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL_,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)\
static constexpr __ALIAS_VAL_TYPE_NAME__ __VAL_NAME__ =\
    __DEFINE_HAS_MMBR_DEFN_DECLTYPE_VAL_(__PROTO_FUNC_NAME__, __T_NAME__,\
        __T_NAME_OR_T_NAME_TMPL_, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
            __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)

#define __DEFINE_HAS_MMBR_DEFN_STRUCT_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL_,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)\
template<__DEFINE_HAS_MMBR_DEFN_TMPL_PARAM_LIST_\
    ##__TMPL_PARAM_LIST_POSTFIX__(__T_NAME__)>\
struct __STRUCT_NAME__\
{\
    __DEFINE_HAS_MMBR_DEFN_ALIAS_VAL_TYPE_(value_type);\
    __DEFINE_HAS_MMBR_DEFN_ALIAS_VAL_TYPE_(ValueType);\
    __DEFINE_HAS_MMBR_DEFN_VAL_(value, value_type, __PROTO_FUNC_NAME__,\
        __T_NAME__, __T_NAME_OR_T_NAME_TMPL_,\
            __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__);\
    __DEFINE_HAS_MMBR_DEFN_VAL_(Value, ValueType, __PROTO_FUNC_NAME__,\
        __T_NAME__, __T_NAME_OR_T_NAME_TMPL_,\
            __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__);\
}

#define __DEFINE_HAS_MMBR_DEFN_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL_,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__,\
    __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__,\
    __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_TMPL_T_NAME__,\
    __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __TYPE_MMBR_NAME__, ...)\
__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_(__PROTO_FUNC_NAME__, __T_NAME__,\
    __PROTO_FUNC_TRUE_TMPL_PARAM_LIST_POSTFIX__,\
        __PROTO_FUNC_T_NAME_OR_PROTO_FUNC_TMPL_T_NAME__,\
            __PROTO_FUNC_T_NAME_TMPL_ARG_LIST_POSTFIX__,\
                __TYPE_MMBR_NAME__,##__VA_ARGS__);\
__DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_FALSE_(__PROTO_FUNC_NAME__, __T_NAME__,\
    __PROTO_FUNC_FALSE_TMPL_PARAM_LIST_POSTFIX__);\
__DEFINE_HAS_MMBR_DEFN_STRUCT_(__STRUCT_NAME__, __PROTO_FUNC_NAME__,\
    __T_NAME__, __TMPL_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL_,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __PROTO_FUNC_TMPL_ARG_LIST_POSTFIX__)

#define __DEFINE_HAS_MMBR_DEFN_DEFAULT_(\
    __STRUCT_NAME__,\
    __PROTO_FUNC_NAME__,\
    __T_NAME__,\
    __TYPE_MMBR_NAME__, ...)\
__DEFINE_HAS_MMBR_DEFN_(__STRUCT_NAME__, __PROTO_FUNC_NAME__, __T_NAME__,,\
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, __TYPE_MMBR_NAME__,##__VA_ARGS__)

#endif //!BASIC_MACRO_HASMEMBERDEFINITION_H_

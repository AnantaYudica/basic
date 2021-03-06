#ifndef BASIC_MACRO_MEMBERFUNCTION_H_
#define BASIC_MACRO_MEMBERFUNCTION_H_

#include <type_traits>
#include "../type/trait/Simple.h"

#define __DEFINE_MMBR_FUNC_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__\
)\
typename __T_NAME__, typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_MMBR_FUNC_T_NAME_(\
    __T_NAME__, ...)\
__T_NAME__

#define __DEFINE_MMBR_FUNC_T_NAME_TMPL_(\
    __T_NAME__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_NAME__<__DEFINE_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_\
    ##__T_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_MMBR_FUNC_T_NAME_SIMPLE_TYPE_(\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
typename basic::type::trait::Simple<\
    __DEFINE_MMBR_FUNC_##__T_NAME_OR_T_NAME_TMPL__(\
        __T_NAME__, __T_NAME_TMPL_ARG_LIST_POSTFIX__)>::type

#define __DEFINE_MMBR_FUNC_T_NAME_IS_SIMPLE_TYPE_(\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
std::is_same<\
    __DEFINE_MMBR_FUNC_##__T_NAME_OR_T_NAME_TMPL__(__T_NAME__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__),\
    __DEFINE_MMBR_FUNC_T_NAME_SIMPLE_TYPE_(__T_NAME__,\
        __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__)>::value

#define __DEFINE_MMBR_FUNC_T_RET_NAME_(\
    __T_RET_NAME__, ...)\
__T_RET_NAME__

#define __DEFINE_MMBR_FUNC_T_RET_NAME_TMPL_(\
    __T_RET_NAME__,\
    __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_RET_NAME__<__DEFINE_MMBR_FUNC_T_RET_NAME_TMPL_ARG_LIST_\
    ##__T_RET_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_MMBR_FUNC_STATIC_ASSERT_(\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
static_assert(\
    __DEFINE_MMBR_FUNC_T_NAME_IS_SIMPLE_TYPE_(__T_NAME__,\
        __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__),\
    #__T_NAME__ " is not simple type");

#define __DEFINE_MMBR_FUNC_ALIAS_TYPE_(\
    __ALIAS_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __CV_REF_DEFN__,\
    __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
    __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)\
using __ALIAS_NAME__ =\
    __DEFINE_MMBR_FUNC_##__T_RET_NAME_OR_T_RET_NAME_TMPL__(__T_RET_NAME__,\
        __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)(\
    __DEFINE_MMBR_FUNC_##__T_NAME_OR_T_NAME_TMPL__(__T_NAME__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__)::*)(__T_ARGS_NAME__...)\
        __CV_REF_DEFN__

#define __DEFINE_MMBR_FUNC_ALIAS_TYPE_TMPL_(\
    __ALIAS_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __CV_REF_DEFN__,\
    __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
    __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)\
template<__DEFINE_MMBR_FUNC_ALIAS_TYPE_TMPL_PARAM_LIST_\
    ##__ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__()>\
__DEFINE_MMBR_FUNC_ALIAS_TYPE_(__ALIAS_NAME__, __T_NAME__,\
    __T_RET_NAME__, __T_ARGS_NAME__, __CV_REF_DEFN__,\
    __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
        __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__)

#define __DEFINE_MMBR_FUNC_PTR_RET_(__ALIAS_TYPE_NAME__, ...)\
__ALIAS_TYPE_NAME__

#define __DEFINE_MMBR_FUNC_PTR_RET_TMPL_(\
    __ALIAS_TYPE_NAME__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__)\
__ALIAS_TYPE_NAME__<__DEFINE_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_\
    ##__PTR_RET_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_MMBR_FUNC_PTR_(\
    __FUNC_NAME__,\
    __ALIAS_TYPE_NAME__,\
    __T_NAME__,\
    __PTR_TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
static constexpr __DEFINE_MMBR_FUNC_##__PTR_RET_OR_PTR_RET_TMPL__(\
    __ALIAS_TYPE_NAME__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__) __FUNC_NAME__()\
{\
    return &__DEFINE_MMBR_FUNC_##__T_NAME_OR_T_NAME_TMPL__(\
        __T_NAME__, __T_NAME_TMPL_ARG_LIST_POSTFIX__)::__MMBR_FUNC_NAME__,\
            ##__VA_ARGS__;\
}

#define __DEFINE_MMBR_FUNC_PTR_TMPL_(\
    __FUNC_NAME__,\
    __ALIAS_TYPE_NAME__,\
    __T_NAME__,\
    __PTR_TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
template<__DEFINE_MMBR_FUNC_PTR_TMPL_PARAM_LIST_\
    ##__PTR_TMPL_PARAM_LIST_POSTFIX__()>\
__DEFINE_MMBR_FUNC_PTR_(__FUNC_NAME__, __ALIAS_TYPE_NAME__, __T_NAME__,,\
    __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__,##__VA_ARGS__)

#define __DEFINE_MMBR_FUNC_STRUCT_(\
    __STRUCT_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __CV_REF_DEFN__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
    __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__,\
    __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__,\
    __PTR_OR_PTR_TMPL__,\
    __PTR_TMPL_PARAM_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
template<__DEFINE_MMBR_FUNC_TMPL_PARAM_LIST_\
    ##__TMPL_PARAM_LIST_POSTFIX__(__T_NAME__, __T_RET_NAME__,\
        __T_ARGS_NAME__)>\
struct __STRUCT_NAME__\
{\
    __DEFINE_MMBR_FUNC_STATIC_ASSERT_(\
        __T_NAME__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
    __DEFINE_MMBR_FUNC_##__ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__(Type, __T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __CV_REF_DEFN__,\
        __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
        __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__);\
    __DEFINE_MMBR_FUNC_##__ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__(type, __T_NAME__,\
        __T_RET_NAME__, __T_ARGS_NAME__, __CV_REF_DEFN__,\
        __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
        __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__);\
    __DEFINE_MMBR_FUNC_##__PTR_OR_PTR_TMPL__(Pointer, Type, __T_NAME__,\
        __PTR_TMPL_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __PTR_RET_OR_PTR_RET_TMPL__,\
        __PTR_RET_TMPL_ARG_LIST_POSTFIX__, __MMBR_FUNC_NAME__,##__VA_ARGS__)\
    __DEFINE_MMBR_FUNC_##__PTR_OR_PTR_TMPL__(pointer, type, __T_NAME__,\
        __PTR_TMPL_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __PTR_RET_OR_PTR_RET_TMPL__,\
        __PTR_RET_TMPL_ARG_LIST_POSTFIX__, __MMBR_FUNC_NAME__,##__VA_ARGS__)\
}

#define __DEFINE_MMBR_FUNC_(\
    __STRUCT_NAME__,\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __CV_REF_DEFN__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_RET_NAME_OR_T_RET_NAME_TMPL__,\
    __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__,\
    __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__,\
    __PTR_OR_PTR_TMPL__,\
    __PTR_TMPL_PARAM_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__, ...)\
__DEFINE_MMBR_FUNC_STRUCT_(__STRUCT_NAME__, __T_NAME__, __T_RET_NAME__,\
    __T_ARGS_NAME__, __CV_REF_DEFN__, __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_RET_NAME_OR_T_RET_NAME_TMPL__, __T_RET_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__, __ALIAS_TMPL_TYPE_PARAM_LIST_POSTFIX__,\
    __PTR_OR_PTR_TMPL__, __PTR_TMPL_PARAM_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __MMBR_FUNC_NAME__,##__VA_ARGS__)

#define __DEFINE_MMBR_FUNC_DEFAULT_(__STRUCT_NAME__, __T_NAME__,\
    __T_RET_NAME__, __T_ARGS_NAME__, __CV_REF_DEFN__, __MMBR_FUNC_NAME__, ...)\
__DEFINE_MMBR_FUNC_(__STRUCT_NAME__, __T_NAME__, __T_RET_NAME__,\
    __T_ARGS_NAME__, __CV_REF_DEFN__,, T_NAME_,, T_RET_NAME_,, ALIAS_TYPE_,,\
    PTR_,, PTR_RET_,, __MMBR_FUNC_NAME__,##__VA_ARGS__)

#endif //!BASIC_MACRO_MEMBERFUNCTION_H_

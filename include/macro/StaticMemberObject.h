#ifndef BASIC_MACRO_STATICMEMBEROBJECT_H_
#define BASIC_MACRO_STATICMEMBEROBJECT_H_

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_NAME_(\
    __T_NAME__, ...)\
__T_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_NAME_TMPL_(\
    __T_NAME_,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_NAME__<__DEFINE_STATIC_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_\
    ##__T_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_(\
    __T_OBJ_NAME__, ...)\
__T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_TMPL_(\
    __T_OBJ_NAME_,\
    __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__)\
__T_OBJ_NAME_<__DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_\
    ##__T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__()>

#define __DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_(\
    __ALIAS_TYPE_NAME__,\
    __T_OBJ_NAME__,\
    __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
    __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
    __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__)\
using __ALIAS_TYPE_NAME__ =\
    __DEFINE_STATIC_MMBR_OBJ_##__T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__(\
        __T_OBJ_NAME__, __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__);

#define __DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_TMPL_(\
    __ALIAS_TYPE_NAME__,\
    __T_OBJ_NAME__,\
    __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
    __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
    __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__)\
template<__DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_\
    ##__ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__()>\
__DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_(__ALIAS_TYPE_NAME__,\
    __T_OBJ_NAME__, __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
    __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__, __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__)

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_(__ALIAS_TYPE_NAME__, ...)\
__ALIAS_TYPE_NAME__*

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_(\
    __ALIAS_TYPE_NAME__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__)\
__ALIAS_TYPE_NAME__<__DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_\
    ##__PTR_RET_TMPL_ARG_LIST_POSTFIX__()>*

#define __DEFINE_STATIC_MMBR_OBJ_PTR_(\
    __FUNC_NAME__,\
    __ALIAS_TYPE_NAME__,\
    __T_NAME__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __PTR_TMPL_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __STATIC_MMBR_OBJ_NAME__, ...)\
static constexpr __DEFINE_STATIC_MMBR_OBJ_##__PTR_RET_OR_PTR_RET_TMPL__(\
    __ALIAS_TYPE_NAME__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__) __FUNC_NAME__()\
{\
    return &__DEFINE_STATIC_MMBR_OBJ_##__T_NAME_OR_T_NAME_TMPL__(__T_NAME__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__)::__STATIC_MMBR_OBJ_NAME__,\
        ##__VA_ARGS__;\
}

#define __DEFINE_STATIC_MMBR_OBJ_PTR_TMPL_(\
    __FUNC_NAME__,\
    __ALIAS_TYPE_NAME__,\
    __T_NAME__,\
    __PTR_TMPL_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __STATIC_MMBR_OBJ_NAME__, ...)\
template<__DEFINE_STATIC_MMBR_OBJ_PTR_TMPL_LIST_\
    ##__PTR_TMPL_LIST_POSTFIX__()>\
__DEFINE_STATIC_MMBR_OBJ_PTR_(__FUNC_NAME__, __ALIAS_TYPE_NAME__,\
    __T_NAME__, __T_NAME_OR_T_NAME_TMPL__, __T_NAME_TMPL_ARG_LIST_POSTFIX__,,\
    __PTR_RET_OR_PTR_RET_TMPL__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __STATIC_MMBR_OBJ_NAME__, ##__VA_ARGS__)

#define __DEFINE_STATIC_MMBR_OBJ_STRUCT_(\
    __STRUCT_NAME__,\
    __T_NAME__,\
    __T_OBJ_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
    __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__,\
    __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
    __PTR_OR_PTR_TMPL__,\
    __PTR_TMPL_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __STATIC_MMBR_OBJ_NAME__, ...)\
template<__DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_\
    ##__TMPL_PARAM_LIST_POSTFIX__(__T_NAME__, __T_OBJ_NAME__)>\
struct __STRUCT_NAME__\
{\
    __DEFINE_STATIC_MMBR_OBJ_##__ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__(\
        Type, __T_OBJ_NAME__, __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
        __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
        __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__);\
    __DEFINE_STATIC_MMBR_OBJ_##__ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__(\
        type, __T_OBJ_NAME__, __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
        __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
        __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__);\
    __DEFINE_STATIC_MMBR_OBJ_##__PTR_OR_PTR_TMPL__(Pointer, Type,\
        __T_NAME__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __PTR_TMPL_LIST_POSTFIX__,\
        __PTR_RET_OR_PTR_RET_TMPL__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
        __STATIC_MMBR_OBJ_NAME__,##__VA_ARGS__)\
    __DEFINE_STATIC_MMBR_OBJ_##__PTR_OR_PTR_TMPL__(pointer, type,\
        __T_NAME__, __T_NAME_OR_T_NAME_TMPL__,\
        __T_NAME_TMPL_ARG_LIST_POSTFIX__, __PTR_TMPL_LIST_POSTFIX__,\
        __PTR_RET_OR_PTR_RET_TMPL__, __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
        __STATIC_MMBR_OBJ_NAME__,##__VA_ARGS__)\
}

#define __DEFINE_STATIC_MMBR_OBJ_(\
    __STRUCT_NAME__,\
    __T_NAME__,\
    __T_OBJ_NAME__,\
    __TMPL_PARAM_LIST_POSTFIX__,\
    __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
    __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__,\
    __ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__,\
    __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__,\
    __PTR_OR_PTR_TMPL__,\
    __PTR_TMPL_LIST_POSTFIX__,\
    __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __STATIC_MMBR_OBJ_NAME__, ...)\
__DEFINE_STATIC_MMBR_OBJ_STRUCT_(__STRUCT_NAME__, __T_NAME__,\
    __T_OBJ_NAME__, __TMPL_PARAM_LIST_POSTFIX__, __T_NAME_OR_T_NAME_TMPL__,\
    __T_NAME_TMPL_ARG_LIST_POSTFIX__, __T_OBJ_NAME_OR_T_OBJ_NAME_TMPL__,\
    __T_OBJ_NAME_TMPL_ARG_LIST_POSTFIX__, __ALIAS_TYPE_OR_ALIAS_TYPE_TMPL__,\
    __ALIAS_TYPE_TMPL_PARAM_LIST_POSTFIX__, __PTR_OR_PTR_TMPL__,\
    __PTR_TMPL_LIST_POSTFIX__, __PTR_RET_OR_PTR_RET_TMPL__,\
    __PTR_RET_TMPL_ARG_LIST_POSTFIX__,\
    __STATIC_MMBR_OBJ_NAME__,##__VA_ARGS__)

#define __DEFINE_STATIC_MMBR_OBJ_DEFAULT_(\
    __STRUCT_NAME__,\
    __T_NAME__,\
    __T_OBJ_NAME__,\
    __STATIC_MMBR_OBJ_NAME__, ...)\
__DEFINE_STATIC_MMBR_OBJ_(__STRUCT_NAME__, __T_NAME__, __T_OBJ_NAME__,,\
    T_NAME_,, T_OBJ_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,,\
    __STATIC_MMBR_OBJ_NAME__,##__VA_ARGS__)

#endif //!BASIC_MACRO_STATICMEMBEROBJECT_H_

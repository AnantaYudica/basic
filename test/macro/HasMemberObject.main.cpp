#include "macro/HasMemberObject.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <typeinfo>

struct A
{
    int Obj1;
};

struct B
{};

template<typename>
struct C
{
    int Obj2;
};

template<>
struct C<std::false_type>
{};

template<typename T, T TVal>
struct ValueName
{
    static constexpr const char * Value = "undefined"; 
};

#define __DEFINE_VALUE_NAME_(NAME, ...)\
template<>\
struct ValueName<__VA_ARGS__>\
{\
    static constexpr const char * Value = NAME;\
}

template<typename T>
struct Name
{
    static const char * Value;
};

template<typename T>
const char* Name<T>::Value = "undefined"; 

template<typename T, T TVal>
struct Name<ValueName<T, TVal>>
{
    static constexpr const char * Value = ValueName<T, TVal>::Value;
};

#define __DEFINE_NAME_(...)\
template<>\
struct Name<__VA_ARGS__>\
{\
    static constexpr const char * Value = #__VA_ARGS__;\
}

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);

__DEFINE_NAME_(std::true_type);
__DEFINE_NAME_(std::false_type);
__DEFINE_NAME_(void);
__DEFINE_NAME_(bool);
__DEFINE_NAME_(A);
__DEFINE_NAME_(B);

struct BaseTest
{
    virtual ~BaseTest() {};
    virtual void Test() = 0;
};

struct TestRegister
{
    static std::vector<BaseTest*> List;
    BaseTest* m_ptr;
    TestRegister(BaseTest* ptr)
    {
        List.push_back(ptr);
    }
    ~TestRegister()
    {
        delete m_ptr;
    }
};

std::vector<BaseTest*> TestRegister::List;

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Thmo, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thmo<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmo<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thmo<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thmo, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thmo<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thmo<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmo<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thmo<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thmo<T>::value_type).hash_code() ==
            typeid(typename Thmo<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thmo, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thmo<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmo<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thmo<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thmo, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thmo<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thmo<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmo<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thmo<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thmo<T>::value, Thmo<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thmo, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasMmbrObj : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thmo, T, Ttavt>();
        TestAliasType<Thmo, T>();
        TestValueAndTargetValue<Thmo, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thmo, T, Ttavt, Compare>();
    };
};

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrObj1(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj1(...);
 *  template<typename T>
 *  struct HasMmbrObj1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj1, _HasMmbrObj1, T,, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasMmbrObj1_t = HasMmbrObj1<T>;

__DEFINE_NAME_(HasMmbrObj1<A>);
__DEFINE_NAME_(HasMmbrObj1<B>);

TestRegister t1(new TestHasMmbrObj<HasMmbrObj1_t, A, bool, true, 
    &BoolCompare>());
TestRegister t2(new TestHasMmbrObj<HasMmbrObj1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrObj2(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj2(...);
 *  template<typename T, typename T1>
 *  struct HasMmbrObj2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj2, _HasMmbrObj2, T, TPL1, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasMmbrObj2_t = HasMmbrObj2<T, void>;

__DEFINE_NAME_(HasMmbrObj2<A, void>);
__DEFINE_NAME_(HasMmbrObj2<B, void>);

TestRegister t3(new TestHasMmbrObj<HasMmbrObj2_t, A, bool, true, 
    &BoolCompare>());
TestRegister t4(new TestHasMmbrObj<HasMmbrObj2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrObj3(T t) -> 
 *      decltype(t.Obj2, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj3(...);
 *  template<template<typename> class T, typename T1>
 *  struct HasMmbrObj3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj3, _HasMmbrObj3, T, TPL2, T_NAME_TMPL_, 
    TNTAL1,,,, PROTO_FUNC_T_NAME_,, Obj2);

template<typename T>
using HasMmbrObj3_t = HasMmbrObj3<C, T>;

__DEFINE_NAME_(HasMmbrObj3<C, std::true_type>);
__DEFINE_NAME_(HasMmbrObj3<C, std::false_type>);

TestRegister t5(new TestHasMmbrObj<HasMmbrObj3_t, std::true_type, bool,
    true, &BoolCompare>());
TestRegister t6(new TestHasMmbrObj<HasMmbrObj3_t, std::false_type , bool,
    false, &BoolCompare>());

/**
 *  template<typename T, typename T1 = void>
 *  constexpr auto _HasMmbrObj4(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj4(...);
 *  template<typename T>
 *  struct HasMmbrObj4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1 = void

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj4, _HasMmbrObj4, T,, T_NAME_,,
    PFTTPL1,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasMmbrObj4_t = HasMmbrObj4<T>;

__DEFINE_NAME_(HasMmbrObj4<A>);
__DEFINE_NAME_(HasMmbrObj4<B>);

TestRegister t7(new TestHasMmbrObj<HasMmbrObj4_t, A, bool, true, 
    &BoolCompare>());
TestRegister t8(new TestHasMmbrObj<HasMmbrObj4_t, B , bool, false, 
    &BoolCompare>());

/**
 *  template<typename T, typename T1>
 *  constexpr auto _HasMmbrObj5(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T, typename T1>
 *  constexpr std::false _HasMmbrObj5(...);
 *  template<typename T, typename T1>
 *  struct HasMmbrObj5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type, T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type, T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__,...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj5, _HasMmbrObj5, T, TPL1, T_NAME_,,
    PFTTPL2, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasMmbrObj5_t = HasMmbrObj5<T, void>;

__DEFINE_NAME_(HasMmbrObj5<A, void>);
__DEFINE_NAME_(HasMmbrObj5<B, void>);

TestRegister t9(new TestHasMmbrObj<HasMmbrObj5_t, A, bool, true, 
    &BoolCompare>());
TestRegister t10(new TestHasMmbrObj<HasMmbrObj5_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<template<typename> class T, typename T1>
 *  constexpr auto _HasMmbrObj6(T<T1> t) -> 
 *      decltype(t.Obj2, std::true_type());
 *  template<template<typename> class T>
 *  constexpr std::false _HasMmbrObj6(...);
 *  template<typename T, template<typename> class T1>
 *  struct HasMmbrObj6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj6<T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj6<T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__)\
typename __T_NAME__, template<typename> class T1 

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__,...)\
T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj6, _HasMmbrObj6, T, TPL3, T_NAME_,,
    PFTTPL3, PFFTPL2, PFTAL2, PROTO_FUNC_T_NAME_TMPL_, PFTNTAL1, Obj2);

template<typename T>
using HasMmbrObj6_t = HasMmbrObj6<C<T>, C>;

__DEFINE_NAME_(HasMmbrObj6<C<std::true_type>, C>);
__DEFINE_NAME_(HasMmbrObj6<C<std::false_type>, C>);

TestRegister t11(new TestHasMmbrObj<HasMmbrObj6_t, std::true_type, bool, true, 
    &BoolCompare>());
TestRegister t12(new TestHasMmbrObj<HasMmbrObj6_t, std::false_type, bool, false,
    &BoolCompare>());

int main()
{
    Info("BeginTest:\n");
    
    for (auto t : TestRegister::List)
    {
        t->Test();
    }
    Info("EndTest:");
    return  ResultStatus;
}

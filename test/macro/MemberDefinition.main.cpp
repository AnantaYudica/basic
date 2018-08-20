#include "macro/MemberDefinition.h"
#include "Test.h"

#include <vector>
#include <type_traits>

struct A
{
    typedef void Type1;
};

template<typename>
struct B
{
    typedef void Type2;
};

template<>
struct B<std::false_type>
{};

struct C
{
    template<typename T>
    using Type3 = B<T>;
};

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

template<typename T, typename... Targs>
typename std::enable_if<sizeof...(Targs) != 0>::type 
    NameParameterTmpl(std::string& str, bool first = true)
{
    if (!first)
        str += ", ";
    str += Name<T>::Value;
    NameParameterTmpl<Targs...>(str, false);
}

template<typename T, typename... Targs>
typename std::enable_if<sizeof...(Targs) == 0>::type 
    NameParameterTmpl(std::string& str, bool first = true)
{
     if (!first)
        str += ", ";
    str += Name<T>::Value;
}

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);

__DEFINE_NAME_(std::true_type);
__DEFINE_NAME_(std::false_type);
__DEFINE_NAME_(void);
__DEFINE_NAME_(bool);
__DEFINE_NAME_(A);
__DEFINE_NAME_(B<void>);

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

struct AliasType;
struct AliasTypeTmpl;

template<template<typename> class Tmd, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Tmd<T>>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmd<T>>::Value;
    info_msg += "::type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmd<T>::type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmd, typename T,
    typename Tta, typename... Targs>
void TestAliasTypeTmplAndTarget()
{
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmd<T>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Tmd<T>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Tta>::Value;
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmd<T>::template type<Targs...>).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmd, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Tmd<T>>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Tmd<T>>::Value;
    error_msg += "::Type";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmd<T>>::Value;
    info_msg += "::type and ";
    info_msg += Name<Tmd<T>>::Value;
    info_msg += "::Type : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmd<T>::type).hash_code() ==
            typeid(typename Tmd<T>::Type).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmd, typename T,
    typename... Targs>
void TestAliasTypeTmpl()
{
    std::string error_msg = Name<Tmd<T>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Tmd<T>>::Value;
    error_msg += "::template Type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmd<T>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tmd<T>>::Value;
    info_msg += "::template Type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmd<T>::template type<Targs...>).hash_code() ==
            typeid( typename Tmd<T>:: template Type<Targs...>).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmd, typename T, typename Ttavt,
    typename = AliasType, typename... Targs>
struct TestMmbrDefn : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tmd, T, Ttavt>();
        TestAliasType<Tmd, T>();
    };
};

template<template<typename> class Tmd, typename T, typename Ttavt,
    typename... Targs>
struct TestMmbrDefn<Tmd, T, Ttavt, AliasTypeTmpl, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeTmplAndTarget<Tmd, T, Ttavt, Targs...>();
        TestAliasTypeTmpl<Tmd, T, Targs...>();
    };
};

/**
 *  template<typename T>
 *  struct MemberDefn1
 *  {
 *      using type = typename T::Type1;
 *      using Type = typename T::Type1;
 *  }
 * */

__DEFINE_MMBR_DEFN_(MmbrDefn1, T,, T_NAME_,, ALIAS_TYPE_,, Type1);

template<typename T>
using MmbrDefn1_t = MmbrDefn1<T>;

__DEFINE_NAME_(MmbrDefn1<A>);

TestRegister t1(new TestMmbrDefn<MmbrDefn1_t, A, typename A::Type1>());

/**
 *  template<typename T, typename T1>
 *  struct MemberDefn2
 *  {
 *      using type = typename T::Type1;
 *      using Type = typename T::Type1;
 *  }
 * */

#define __DEFINE_MMBR_DEFN_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_MMBR_DEFN_(MmbrDefn2, T, TPL1, T_NAME_,, ALIAS_TYPE_,, Type1);

template<typename T>
using MmbrDefn2_t = MmbrDefn2<T, void>;

__DEFINE_NAME_(MmbrDefn2<A, void>);

TestRegister t2(new TestMmbrDefn<MmbrDefn2_t, A, typename A::Type1>());

/**
 *  template<template<typename> class T, typename T1>
 *  struct MemberDefn3
 *  {
 *      using type = typename T<T1>::Type2;
 *      using Type = typename T<T1>::Type2;
 *  }
 * */

#define __DEFINE_MMBR_DEFN_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_MMBR_DEFN_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_MMBR_DEFN_(MmbrDefn3, T, TPL2, T_NAME_TMPL_, 
    TNTAL1, ALIAS_TYPE_,, Type2);

template<typename T>
using MmbrDefn3_t = MmbrDefn3<B, T>;

__DEFINE_NAME_(MmbrDefn3<B, void>);

TestRegister t3(new TestMmbrDefn<MmbrDefn3_t, void, typename B<void>::Type2>());

/**
 *  template<typename T>
 *  struct MemberDefn3
 *  {
 *      template<typename T1>
 *      using type = typename T::template Type3<T1>;
 *      template<typename T1>
 *      using Type = typename T::template Type1<T1>;
 *  }
 * */

#define __DEFINE_MMBR_DEFN_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1

__DEFINE_MMBR_DEFN_(MmbrDefn4, T,, T_NAME_,, ALIAS_TYPE_TMPL_, ATTPL1, 
    template Type3<T1>);

template<typename T>
using MmbrDefn4_t = MmbrDefn4<T>;

__DEFINE_NAME_(MmbrDefn4<C>);

TestRegister t4(new TestMmbrDefn<MmbrDefn4_t, C, 
    typename C::template Type3<void>, AliasTypeTmpl, void>());


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

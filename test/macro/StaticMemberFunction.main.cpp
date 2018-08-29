#include "macro/StaticMemberFunction.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <sstream>

struct A
{
    static void Foo1() {}
};

template<typename T>
struct B
{
    static void Foo2() {}
};

struct C
{
    template<typename T>
    static B<T> Foo3() {}
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

template<typename... Targs>
struct NameParameterTmpl 
{
    static void String(std::string& str, bool first = true)
    {}
};

template<typename T, typename... Targs>
struct NameParameterTmpl<T, Targs...> 
{
    static void String(std::string& str, bool first = true)
    {
        if (!first)
            str += ", ";
        str += Name<T>::Value;
        NameParameterTmpl<Targs...>::String(str, false);
    }
};

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);

__DEFINE_NAME_(std::true_type);
__DEFINE_NAME_(std::false_type);
__DEFINE_NAME_(void);
__DEFINE_NAME_(bool);
__DEFINE_NAME_(A);
__DEFINE_NAME_(B<void>);
__DEFINE_NAME_(void(*)());
__DEFINE_NAME_(B<void> (*)());


struct BaseTest
{
    virtual ~BaseTest() {};
    virtual void Test() = 0;
};

struct TestRegister
{
    static std::vector<BaseTest*> List;
    BaseTest* m_ptr;
    TestRegister(BaseTest* ptr) :
        m_ptr(ptr)
    {
        List.push_back(m_ptr);
    }
    ~TestRegister()
    {
        delete m_ptr;
    }
};

std::vector<BaseTest*> TestRegister::List;

struct AliasType;
struct AliasTypeTmpl;
struct Pointer;
struct PointerTmpl;

template<typename Tptr>
void* ToVoidPtr(Tptr t)
{
    Tptr * tp = &t;
    void ** vp = reinterpret_cast<void**>(tp);
    return *vp;
}

template<typename Tptr>
void ToString(Tptr t, std::string& str)
{
    std::ostringstream ostr;
    ostr << std::hex << ToVoidPtr(t); 
    str += ostr.str();
}

template<template<typename> class Tmf, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmf<T>::type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmf, typename T,
    typename Tta, typename... Targs>
void TestAliasTypeTmplAndTarget()
{
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Tta>::Value;
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmf<T>::template type<Targs...>).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmf, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::Type";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::type and ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::Type : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmf<T>::type).hash_code() ==
            typeid(typename Tmf<T>::Type).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmf, typename T,
    typename... Targs>
void TestAliasTypeTmpl()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::template Type<";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += ">";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template Type<";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += "> : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmf<T>::template type<Targs...>).hash_code() ==
            typeid( typename Tmf<T>:: template Type<Targs...>).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tmf, typename T, typename Ttp,
    Ttp TtpValue>
void TestPointerAndTarget()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::pointer() is not same with ";
    ToString(TtpValue, error_msg);
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::pointer() and ";
    ToString(TtpValue, info_msg);
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(Tmf<T>::pointer()) == ToVoidPtr(TtpValue)))
            Info("Pass\n");
}

template<template<typename> class Tmf, typename T, typename Ttp,
    Ttp TtpValue, typename... Targs>
void TestPointerTmplAndTarget()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::template pointer<";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += ">() is not same with ";
    ToString(TtpValue, error_msg);
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template pointer<";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += ">() and ";
    ToString(TtpValue, info_msg);
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(Tmf<T>::template pointer<Targs...>()) == ToVoidPtr(TtpValue)))
            Info("Pass\n");
}

template<template<typename> class Tmf, typename T>
void TestPointer()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::pointer() is not same with ";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::Pointer()";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::pointer() and ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::Pointer() : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(Tmf<T>::pointer()) == ToVoidPtr(Tmf<T>::Pointer())))
            Info("Pass\n");
}

template<template<typename> class Tmf, typename T,
    typename... Targs>
void TestPointerTmpl()
{
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::template pointer<";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += ">() is not same with ";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::template Pointer<";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += ">()";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template pointer<";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += ">() and ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template Pointer<";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += ">() : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(Tmf<T>::template pointer<Targs...>()) == 
        ToVoidPtr(Tmf<T>::template Pointer<Targs...>())))
            Info("Pass\n");
}


template<template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename = AliasType, typename = Pointer,
    typename... Targs>
struct TestStaticMmbrFunc : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tmf, T, Tta>();
        TestAliasType<Tmf, T>();
        TestPointerAndTarget<Tmf, T, Ttp, TtpValue>();
        TestPointer<Tmf, T>();
    };
};

template<template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename... Targs>
struct TestStaticMmbrFunc<Tmf, T, Tta, Ttp, TtpValue, 
    AliasType, PointerTmpl, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tmf, T, Tta>();
        TestAliasType<Tmf, T>();
        TestPointerTmplAndTarget<Tmf, T, Ttp, TtpValue, Targs...>();
        TestPointerTmpl<Tmf, T, Targs...>();
    };
};

template<template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename... Targs>
struct TestStaticMmbrFunc<Tmf, T, Tta, Ttp, TtpValue, 
    AliasTypeTmpl, Pointer, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeTmplAndTarget<Tmf, T, Tta, Targs...>();
        TestAliasTypeTmpl<Tmf, T, Targs...>();
        TestPointerAndTarget<Tmf, T, Ttp, TtpValue>();
        TestPointer<Tmf, T>();
    };
};

template<template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename... Targs>
struct TestStaticMmbrFunc<Tmf, T, Tta, Ttp, TtpValue, 
    AliasTypeTmpl, PointerTmpl, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeTmplAndTarget<Tmf, T, Tta, Targs...>();
        TestAliasTypeTmpl<Tmf, T, Targs...>();
        TestPointerTmplAndTarget<Tmf, T, Ttp, TtpValue, Targs...>();
        TestPointerTmpl<Tmf, T, Targs...>();
    };
};

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc1
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc1, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using StaticMmbrFunc1_t = StaticMmbrFunc1<T, void>;

__DEFINE_NAME_(StaticMmbrFunc1<A, void>);

TestRegister t1_1(new TestStaticMmbrFunc<StaticMmbrFunc1_t, A, 
    void (*)(), void (*)(), &A::Foo1>());

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc2
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc2, T, Tr, Targs, TPL1, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using StaticMmbrFunc2_t = StaticMmbrFunc2<T, void, void>;

__DEFINE_NAME_(StaticMmbrFunc2<A, void, void>);

TestRegister t2_1(new TestStaticMmbrFunc<StaticMmbrFunc2_t, A, 
    void (*)(), void (*)(), &A::Foo1>());

/**
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	struct StaticMmbrFunc3
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T<T1>::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T<T1>::Foo2;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename>class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_STATIC_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc3, T, Tr, Targs, TPL2, 
    T_NAME_TMPL_, TNTAL1, T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using StaticMmbrFunc3_t = StaticMmbrFunc3<B, T, void>;

__DEFINE_NAME_(StaticMmbrFunc3<B, void, void>);

TestRegister t3_1(new TestStaticMmbrFunc<StaticMmbrFunc3_t, void, 
    void (*)(), void (*)(), &B<void>::Foo2>());

/**
 * 	template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 * 	struct StaticMmbrFunc4
 * 	{
 * 	    using Type = Tr<T1> (*)(Targs...);
 * 	    using type = Tr<T1> (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo3;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo3;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_STATIC_MMBR_FUNC_T_RET_NAME_TMPL_ARG_LIST_TRNTAL1()\
T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc4, T, Tr, Targs, TPL3, T_NAME_,,
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo3);

template<typename T>
using StaticMmbrFunc4_t = StaticMmbrFunc4<T, void, B>;

__DEFINE_NAME_(StaticMmbrFunc4<C, void, B>);

TestRegister t4_1(new TestStaticMmbrFunc<StaticMmbrFunc4_t, C, 
    B<void> (*)(),  B<void> (*)(), &C::Foo3>());

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc5
 * 	{
 *      template<typename T1 = void>
 * 	    using Type = Tr (*)(Targs...);
 *      template<typename T1 = void>
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type<> Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type<> pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1 = void

#define __DEFINE_STATIC_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL1()

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc5, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, PTR_RET_TMPL_, PRTAL1, Foo1);

template<typename T>
using StaticMmbrFunc5_t = StaticMmbrFunc5<T, void>;

__DEFINE_NAME_(StaticMmbrFunc5<A, void>);

TestRegister t5_1(new TestStaticMmbrFunc<StaticMmbrFunc5_t, A, 
    void (*)(), void (*)(), &A::Foo1, AliasTypeTmpl, Pointer>());

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc6
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_PTR_TMPL_PARAM_LIST_PTPL1()\
typename T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc6, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_TMPL_, PTPL1, PTR_RET_,, Foo1);

template<typename T>
using StaticMmbrFunc6_t = StaticMmbrFunc6<T, void>;

__DEFINE_NAME_(StaticMmbrFunc6<A, void>);

TestRegister t6_1(new TestStaticMmbrFunc<StaticMmbrFunc6_t, A, 
    void (*)(), void (*)(), &A::Foo1, AliasType, PointerTmpl, void>());

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc7
 * 	{
 *      template<typename T1>
 * 	    using Type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type<void> Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type<void> pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL2()\
typename T1

#define __DEFINE_STATIC_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL2()\
void

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc7, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_TMPL_, ATTPL2, PTR_,, PTR_RET_TMPL_, PRTAL2, Foo1);

template<typename T>
using StaticMmbrFunc7_t = StaticMmbrFunc7<T, void>;

__DEFINE_NAME_(StaticMmbrFunc7<A, void>);

TestRegister t7_1(new TestStaticMmbrFunc<StaticMmbrFunc7_t, A, 
    void (*)(), void (*)(), &A::Foo1, AliasTypeTmpl, Pointer, void>());

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc8
 * 	{
 *      template<typename T1>
 * 	    using Type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    using type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    static constexpr Type<T1> Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type<T1> pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_STATIC_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL3()\
T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc8, T, Tr, Targs, TPL4, T_NAME_,,
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_TMPL_, ATTPL2, PTR_TMPL_, PTPL1, 
    PTR_RET_TMPL_, PRTAL3, Foo3);

template<typename T>
using StaticMmbrFunc8_t = StaticMmbrFunc8<T, B>;

__DEFINE_NAME_(StaticMmbrFunc8<C, B>);

TestRegister t8_1(new TestStaticMmbrFunc<StaticMmbrFunc8_t, C, 
    B<void> (*)(), B<void> (*)(), &C::Foo3, AliasTypeTmpl, PointerTmpl, void>());

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

#include "macro/StaticMemberObject.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <sstream>

struct A
{
    static int Obj1;
};

int A::Obj1;

template<typename T>
struct B
{
    static int Obj2;
};

template<typename T>
int B<T>::Obj2;

struct C
{
    static B<void> Obj3;
};

B<void> C::Obj3;

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
__DEFINE_NAME_(int);
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
struct TestStaticMmbrObj : BaseTest
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
struct TestStaticMmbrObj<Tmf, T, Tta, Ttp, TtpValue, 
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
struct TestStaticMmbrObj<Tmf, T, Tta, Ttp, TtpValue, 
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
struct TestStaticMmbrObj<Tmf, T, Tta, Ttp, TtpValue, 
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
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj1
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj1, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using StaticMmbrObj1_t = StaticMmbrObj1<T, int>;

__DEFINE_NAME_(StaticMmbrObj1<A, int>);

TestRegister t1_1(new TestStaticMmbrObj<StaticMmbrObj1_t, A, 
    int, int*, &A::Obj1>());

/**
 * 	template<typename T, typename T1, typename To>
 * 	struct StaticMmbrObj2
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename T1, typename __T_OBJ_NAME__

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj2, T, To, TPL1, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using StaticMmbrObj2_t = StaticMmbrObj2<T, void, int>;

__DEFINE_NAME_(StaticMmbrObj2<A, void, int>);

TestRegister t2_1(new TestStaticMmbrObj<StaticMmbrObj2_t, A, 
    int, int*, &A::Obj1>());

/**
 * 	template<template<typename> class T, typename T1, typename To>
 * 	struct StaticMmbrObj3
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL()\
T1

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj3, T, To, TPL2, T_NAME_TMPL_, TNTAL, 
    T_OBJ_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj2);

template<typename T>
using StaticMmbrObj3_t = StaticMmbrObj3<B, T, int>;

__DEFINE_NAME_(StaticMmbrObj3<B, void, int>);

TestRegister t3_1(new TestStaticMmbrObj<StaticMmbrObj3_t, void, 
    int, int*, &B<void>::Obj2>());

/**
 * 	template<typename T, typename T1, template<typename> class To>
 * 	struct StaticMmbrObj4
 * 	{
 * 	    using Type = To<T1>;
 * 	    using type = To<T1>;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_TONTAL1()\
T1

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj4, T, To, TPL3, T_NAME_,, 
    T_OBJ_NAME_TMPL_, TONTAL1, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj3);

template<typename T>
using StaticMmbrObj4_t = StaticMmbrObj4<T, void, B>;

__DEFINE_NAME_(StaticMmbrObj4<C, void, B>);

TestRegister t4_1(new TestStaticMmbrObj<StaticMmbrObj4_t, C, 
    B<void>, B<void>*, &C::Obj3>());

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj5
 * 	{
 *      template<typename = void>
 * 	    using Type = To;
 *      template<typename = void>
 * 	    using type = To;
 * 	    static constexpr Type<>* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type<>* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename = void

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL1()

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj5, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, PTR_RET_TMPL_, PRTAL1, Obj1);

template<typename T>
using StaticMmbrObj5_t = StaticMmbrObj5<T, int>;

__DEFINE_NAME_(StaticMmbrObj5<A, int>);

TestRegister t5_1(new TestStaticMmbrObj<StaticMmbrObj5_t, A, 
    int, int*, &A::Obj1, AliasTypeTmpl, Pointer>());

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj6
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 *      template<typename = void>
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 *      template<typename = void>
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_PTR_TMPL_PARAM_LIST_PTPL1()\
typename = void

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj6, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_TMPL_, PTPL1, PTR_RET_,, Obj1);

template<typename T>
using StaticMmbrObj6_t = StaticMmbrObj6<T, int>;

__DEFINE_NAME_(StaticMmbrObj6<A, int>);

TestRegister t6_1(new TestStaticMmbrObj<StaticMmbrObj6_t, A, 
    int, int*, &A::Obj1, AliasType, PointerTmpl>());

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj7
 * 	{
 *      template<typename T1>
 * 	    using Type = To;
 *      template<typename T1>
 * 	    using type = To;
 * 	    static constexpr Type<void>* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type<void>* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL2()\
typename T1

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL2()\
void

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj7, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_TMPL_, ATTPL2, PTR_,, PTR_RET_TMPL_, PRTAL2, Obj1);

template<typename T>
using StaticMmbrObj7_t = StaticMmbrObj7<T, int>;

__DEFINE_NAME_(StaticMmbrObj7<A, int>);

TestRegister t7_1(new TestStaticMmbrObj<StaticMmbrObj7_t, A, 
    int, int*, &A::Obj1, AliasTypeTmpl, Pointer, void>());

/**
 * 	template<typename T, template<typename> class To>
 * 	struct StaticMmbrObj8
 * 	{
 *      template<typename T1>
 * 	    using Type = To<T1>;
 *      template<typename T1>
 * 	    using type = To<T1>;
 *      template<typename T1>
 * 	    static constexpr Type<T1>* Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type<T1>* pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, template<typename> class __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_TONTAL1()\
T1

#define __DEFINE_STATIC_MMBR_OBJ_PTR_TMPL_PARAM_LIST_PTPL2()\
typename T1

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL3()\
void

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj8, T, To, TPL4, T_NAME_,, 
    T_OBJ_NAME_TMPL_, TONTAL1, ALIAS_TYPE_TMPL_, ATTPL2, 
    PTR_TMPL_, PTPL2, PTR_RET_TMPL_, PRTAL3, Obj3);

template<typename T>
using StaticMmbrObj8_t = StaticMmbrObj8<T, B>;

__DEFINE_NAME_(StaticMmbrObj8<C, B>);

TestRegister t8_1(new TestStaticMmbrObj<StaticMmbrObj8_t, C, 
    B<void>, B<void>*, &C::Obj3, AliasTypeTmpl, PointerTmpl, void>());


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

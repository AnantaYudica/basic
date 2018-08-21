#include "macro/MemberObject.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <sstream>

struct A
{
    int Obj1;
};

template<typename>
struct B
{
    int Obj2;
};

struct C
{
    B<void> Obj3;
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
__DEFINE_NAME_(int A::*);
__DEFINE_NAME_(B<void>);
__DEFINE_NAME_(int B<void>::*);
__DEFINE_NAME_(C);
__DEFINE_NAME_(B<void> C::*);

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

template<typename T>
struct InputObject
{
    static T Obj;
    static T& Get() {return Obj;}
};

template<typename T>
T InputObject<T>::Obj;

__DEFINE_NAME_(InputObject<A>);
__DEFINE_NAME_(InputObject<B<void>>);
__DEFINE_NAME_(InputObject<C>);

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
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Tmf<T>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
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
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::template Type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template Type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tmf<T>::template type<Targs...>).hash_code() ==
            typeid( typename Tmf<T>:: template Type<Targs...>).hash_code()))
                Info("Pass\n");
}

template<typename Tio, template<typename> class Tmf, typename T, typename Ttp,
    Ttp TtpValue>
void TestPointerAndTarget()
{
    std::string error_msg = Name<Tio>::Value;
    error_msg += "::Get().*";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::pointer() is not same with ";
    ToString(&(Tio::Get().*TtpValue), error_msg);
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tio>::Value;
    info_msg += "::Get().*";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::pointer() and ";
    ToString(&(Tio::Get().*TtpValue), info_msg);
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(&(Tio::Get().*Tmf<T>::pointer())) == 
        ToVoidPtr(&(Tio::Get().*TtpValue))))
            Info("Pass\n");
}

template<typename Tio, template<typename> class Tmf, typename T, typename Ttp,
    Ttp TtpValue, typename... Targs>
void TestPointerTmplAndTarget()
{
    std::string error_msg = Name<Tio>::Value;
    error_msg += "::Get().*";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::template pointer<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">() is not same with ";
    ToString(&(Tio::Get().*TtpValue), error_msg);
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tio>::Value;
    info_msg += "::Get().*";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template pointer<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += ">() and ";
    ToString(&(Tio::Get().*TtpValue), error_msg);
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(&(Tio::Get().*Tmf<T>::template pointer<Targs...>())) == 
        ToVoidPtr(&(Tio::Get().*TtpValue))))
            Info("Pass\n");
}

template<typename Tio, template<typename> class Tmf, typename T>
void TestPointer()
{
    std::string error_msg = Name<Tio>::Value;
    error_msg += "::Get().*";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::pointer() is not same with ";
    error_msg += Name<Tio>::Value;
    error_msg += "::Get().*";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::Pointer()";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tio>::Value;
    info_msg += "::Get().*";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::pointer() and ";
    info_msg += Name<Tio>::Value;
    info_msg += "::Get().*";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::Pointer() : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(&(Tio::Get().*Tmf<T>::pointer())) == 
        ToVoidPtr(&(Tio::Get().*Tmf<T>::Pointer()))))
            Info("Pass\n");
}

template<typename Tio, template<typename> class Tmf, typename T,
    typename... Targs>
void TestPointerTmpl()
{
    std::string error_msg = Name<Tio>::Value;
    error_msg += "::Get().*";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::template pointer<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">() is not same with ";
    error_msg += Name<Tio>::Value;
    error_msg += "::Get().*";
    error_msg += Name<Tmf<T>>::Value;
    error_msg += "::template Pointer<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">()";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tio>::Value;
    info_msg += "::Get().*";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template pointer<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += ">() and ";
    info_msg += Name<Tio>::Value;
    info_msg += "::Get().*";
    info_msg += Name<Tmf<T>>::Value;
    info_msg += "::template Pointer<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += ">() : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        ToVoidPtr(&(Tio::Get().*Tmf<T>::template pointer<Targs...>())) == 
        ToVoidPtr(&(Tio::Get().*Tmf<T>::template Pointer<Targs...>()))))
            Info("Pass\n");
}


template<typename Tio, template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename = AliasType, typename = Pointer,
    typename... Targs>
struct TestMmbrObj : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tmf, T, Tta>();
        TestAliasType<Tmf, T>();
        TestPointerAndTarget<Tio, Tmf, T, Ttp, TtpValue>();
        TestPointer<Tio, Tmf, T>();
    };
};

template<typename Tio, template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename... Targs>
struct TestMmbrObj<Tio, Tmf, T, Tta, Ttp, TtpValue, 
    AliasType, PointerTmpl, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tmf, T, Tta>();
        TestAliasType<Tmf, T>();
        TestPointerTmplAndTarget<Tio, Tmf, T, Ttp, TtpValue, Targs...>();
        TestPointerTmpl<Tio, Tmf, T, Targs...>();
    };
};

template<typename Tio, template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename... Targs>
struct TestMmbrObj<Tio, Tmf, T, Tta, Ttp, TtpValue, 
    AliasTypeTmpl, Pointer, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeTmplAndTarget<Tmf, T, Tta, Targs...>();
        TestAliasTypeTmpl<Tmf, T, Targs...>();
        TestPointerAndTarget<Tio, Tmf, T, Ttp, TtpValue>();
        TestPointer<Tio, Tmf, T>();
    };
};

template<typename Tio, template<typename> class Tmf, typename T, typename Tta,
    typename Ttp, Ttp TtpValue, typename... Targs>
struct TestMmbrObj<Tio, Tmf, T, Tta, Ttp, TtpValue, 
    AliasTypeTmpl, PointerTmpl, Targs...> : BaseTest
{
    void Test() 
    {
        TestAliasTypeTmplAndTarget<Tmf, T, Tta, Targs...>();
        TestAliasTypeTmpl<Tmf, T, Targs...>();
        TestPointerTmplAndTarget<Tio, Tmf, T, Ttp, TtpValue, Targs...>();
        TestPointerTmpl<Tio, Tmf, T, Targs...>();
    };
};

/**
 * 	template<typename T, typename To>
 * 	struct MmbrObj1
 * 	{
 * 	    using type = To T::*;
 * 	    using Type = To T::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_OBJ_(MmbrObj1, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using MmbrObj1_t = MmbrObj1<T, int>;

__DEFINE_NAME_(MmbrObj1<A, int>);

TestRegister t1_1(new TestMmbrObj<InputObject<A>, MmbrObj1_t, A, 
    int A::*, int A::*, &A::Obj1>());

/**
 * 	template<typename T, typename To, typename T1>
 * 	struct MmbrObj2
 * 	{
 * 	    using type = To T::*;
 * 	    using Type = To T::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename __T_OBJ_NAME__, typename T1

__DEFINE_MMBR_OBJ_(MmbrObj2, T, To, TPL1, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using MmbrObj2_t = MmbrObj2<T, int, void>;

__DEFINE_NAME_(MmbrObj2<A, int, void>);

TestRegister t2_1(new TestMmbrObj<InputObject<A>, MmbrObj2_t, A, 
    int A::*, int A::*, &A::Obj1>());

/**
 * 	template<template<typename> class T, typename To, typename T1>
 * 	struct MmbrObj3
 * 	{
 * 	    using type = To T<T1>::*;
 * 	    using Type = To T<T1>::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
template<typename>class __T_NAME__, typename __T_OBJ_NAME__, typename T1

#define __DEFINE_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_MMBR_OBJ_(MmbrObj3, T, To, TPL2, T_NAME_TMPL_, TNTAL1, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj2);

template<typename T>
using MmbrObj3_t = MmbrObj3<B, int, T>;

__DEFINE_NAME_(MmbrObj3<B, int, void>);

TestRegister t3_1(new TestMmbrObj<InputObject<B<void>>, MmbrObj3_t, void, 
    int B<void>::*, int B<void>::*, &B<void>::Obj2>());

/**
 * 	template<typename T, template<typename> class To, typename T1>
 * 	struct MmbrObj4
 * 	{
 * 	    using type = To<T1> T::*;
 * 	    using Type = To<T1> T::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, template<typename>class __T_OBJ_NAME__, typename T1

#define __DEFINE_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_TONTAL1()\
T1

__DEFINE_MMBR_OBJ_(MmbrObj4, T, To, TPL3, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj3);

template<typename T>
using MmbrObj4_t = MmbrObj4<T, B, void>;

__DEFINE_NAME_(MmbrObj4<C, B, void>);

TestRegister t4_1(new TestMmbrObj<InputObject<C>, MmbrObj4_t, C, 
    B<void> C::*, B<void> C::*, &C::Obj3>());

/**
 * 	template<typename T, template<typename> class To>
 * 	struct MmbrObj5
 * 	{
 *      template<typenane T1 = void>
 * 	    using type = To<T1> T::*;
 *      template<typenane T1 = void>
 * 	    using Type = To<T1> T::*;
 * 	    static constexpr type<> pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr Type<> Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, template<typename>class __T_OBJ_NAME__

#define __DEFINE_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1 = void

#define __DEFINE_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL1()

__DEFINE_MMBR_OBJ_(MmbrObj5, T, To, TPL4, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, PTR_RET_TMPL_, PRTAL1, Obj3);

template<typename T>
using MmbrObj5_t = MmbrObj5<T, B>;

__DEFINE_NAME_(MmbrObj5<C, B>);

TestRegister t5_1(new TestMmbrObj<InputObject<C>, MmbrObj5_t, C, 
    B<void> C::*, B<void> C::*, &C::Obj3, AliasTypeTmpl, Pointer, void>());

/**
 * 	template<typename T, typename To>
 * 	struct MmbrObj6
 * 	{
 * 	    using type = To T::*;
 * 	    using Type = To T::*;
 *      template<typename T1>
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_PTR_TMPL_PARAM_LIST_PTPL1()\
typename T1

__DEFINE_MMBR_OBJ_(MmbrObj6, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_TMPL_, PTPL1, PTR_RET_,, Obj1);

template<typename T>
using MmbrObj6_t = MmbrObj6<T, int>;

__DEFINE_NAME_(MmbrObj6<A, int>);

TestRegister t6_1(new TestMmbrObj<InputObject<A>, MmbrObj6_t, A, 
    int A::*, int A::*, &A::Obj1, AliasType, PointerTmpl, void>());

/**
 * 	template<typename T, template<typename> class To>
 * 	struct MmbrObj7
 * 	{
 *      template<typenane T1>
 * 	    using type = To<T1> T::*;
 *      template<typenane T1>
 * 	    using Type = To<T1> T::*;
 * 	    static constexpr type<void> pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr Type<void> Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL2()\
typename T1

#define __DEFINE_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL2()\
void

__DEFINE_MMBR_OBJ_(MmbrObj7, T, To, TPL4, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_TMPL_, ATTPL2, PTR_,, PTR_RET_TMPL_, PRTAL2, Obj3);

template<typename T>
using MmbrObj7_t = MmbrObj7<T, B>;

__DEFINE_NAME_(MmbrObj7<C, B>);

TestRegister t7_1(new TestMmbrObj<InputObject<C>, MmbrObj7_t, C, 
    B<void> C::*, B<void> C::*, &C::Obj3, AliasTypeTmpl, Pointer, void>());

/**
 * 	template<typename T, template<typename> class To>
 * 	struct MmbrObj8
 * 	{
 *      template<typenane T1>
 * 	    using type = To<T1> T::*;
 *      template<typenane T1>
 * 	    using Type = To<T1> T::*;
 *      template<typename T1>
 * 	    static constexpr type<T1> pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr Type<T1> Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL3()\
T1

__DEFINE_MMBR_OBJ_(MmbrObj8, T, To, TPL4, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_TMPL_, ATTPL2, PTR_TMPL_, PTPL1, PTR_RET_TMPL_, PRTAL3, Obj3);

template<typename T>
using MmbrObj8_t = MmbrObj8<T, B>;

__DEFINE_NAME_(MmbrObj8<C, B>);

TestRegister t8_1(new TestMmbrObj<InputObject<C>, MmbrObj8_t, C, 
    B<void> C::*, B<void> C::*, &C::Obj3, AliasTypeTmpl, PointerTmpl, void>());

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

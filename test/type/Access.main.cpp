#include "type/Access.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <sstream>

template<typename T, T TVal>
struct ValueName
{
    static constexpr const char* Value = "undefined"; 
};

#define __DEFINE_VALUE_NAME_(NAME, ...)\
template<>\
struct ValueName<__VA_ARGS__>\
{\
    static constexpr const char* Value = NAME;\
}

template<typename T>
struct Name
{
    static constexpr const char* Value = "undefined";
};

template<typename T, T TVal>
struct Name<ValueName<T, TVal>>
{
    static constexpr const char* Value = ValueName<T, TVal>::Value;
};

#define __DEFINE_NAME_(...)\
template<>\
struct Name<__VA_ARGS__>\
{\
    static constexpr const char* Value = #__VA_ARGS__;\
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

template<typename Tid, typename Tb>
struct Derived : Tb
{
    template<typename T>
    static constexpr auto 
        HasMemberFunctionFoo1(int) ->
            decltype(std::declval<T>().Foo1(), std::true_type());
    template<typename T>
    static constexpr std::false_type HasMemberFunctionFoo1(...);
    template<typename T>
    static constexpr auto 
        HasStaticMemberFunctionFoo2(int) -> 
            decltype(T::Foo2(), std::true_type());
    template<typename T>
    static constexpr std::false_type HasStaticMemberFunctionFoo2(...);
};

template<template<typename> class Td, template<typename> class Tb,
    typename Tda, typename Tt, Tt TtValue>
void TestHasMemberFunctionFoo1()
{
    std::string error_msg = "decltype(";
    error_msg += Name<Td<Tda>>::Value;
    error_msg += "<";
    error_msg += Name<Tda>::Value;
    error_msg += ">";
    error_msg += "::template HasMemberFunctionFoo1<";
    error_msg += Name<Tb<Tda>>::Value;
    error_msg += "<";
    error_msg += Name<Tda>::Value;
    error_msg += ">";
    error_msg += ">(0)::";
    error_msg += "value is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between decltype(";
    
    info_msg += Name<Td<Tda>>::Value;
    info_msg += "<";
    info_msg += Name<Tda>::Value;
    info_msg += ">";
    info_msg += "::template HasMemberFunctionFoo1<";
    info_msg += Name<Tb<Tda>>::Value;
    info_msg += "<";
    info_msg += Name<Tda>::Value;
    info_msg += ">";
    info_msg += ">(0)::";
    info_msg += "value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        decltype(Td<Tda>::template HasMemberFunctionFoo1<Tb<Tda>>(0))::value ==
            TtValue))
                Info("Pass\n");
}

template<template<typename> class Td, template<typename> class Tb,
    typename Tda, typename Tt, Tt TtValue>
void TestHasStaticMemberFunctionFoo2()
{
    std::string error_msg = "decltype(";
    error_msg += Name<Td<Tda>>::Value;
    error_msg += "<";
    error_msg += Name<Tda>::Value;
    error_msg += ">";
    error_msg += "::template HasStaticMemberFunctionFoo2<";
    error_msg += Name<Tb<Tda>>::Value;
    error_msg += "<";
    error_msg += Name<Tda>::Value;
    error_msg += ">";
    error_msg += ">(0))::value is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between decltype(";
    info_msg += Name<Td<Tda>>::Value;
    info_msg += "<";
    info_msg += Name<Tda>::Value;
    info_msg += ">";
    info_msg += "::template HasStaticMemberFunctionFoo2<";
    info_msg += Name<Tb<Tda>>::Value;
    info_msg += "<";
    info_msg += Name<Tda>::Value;
    info_msg += ">";
    info_msg += ">(0))::value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        decltype(Td<Tda>::template HasStaticMemberFunctionFoo2<Tb<Tda>>(0))::value
            == TtValue))
                Info("Pass\n");
}

template<template<typename> class Td, template<typename> class Tb,
    typename Tda, typename Tt, Tt TtValueFoo1, Tt TtValueFoo2>
struct TestAccess : BaseTest
{
    void Test() 
    {
        TestHasMemberFunctionFoo1<Td, Tb, Tda, Tt, TtValueFoo1>();
        TestHasStaticMemberFunctionFoo2<Td, Tb, Tda, Tt, TtValueFoo2>();
    };
};

struct AccessPublic
{
    typedef basic::type::access::Public Foo1Access;
    typedef basic::type::access::Public Foo2Access;
};

struct AccessProtected
{
    typedef basic::type::access::Protected Foo1Access;
    typedef basic::type::access::Protected Foo2Access;
};

struct AccessPrivate
{
    typedef basic::type::access::Private Foo1Access;
    typedef basic::type::access::Private Foo2Access;
};

__DEFINE_NAME_(AccessPublic);
__DEFINE_NAME_(AccessProtected);
__DEFINE_NAME_(AccessPrivate);

template<typename Tda>
struct DerivedA;

template<typename Tda, typename TTFriend>
struct DerivedFriendA;

template<typename Tda>
struct DerivedBTrue;

template<typename Tda>
struct DerivedBFalse;

template<typename Tda, typename Tid>
struct DerivedFriendBTrue;

template<typename Tda, typename Tid>
struct DerivedFriendBFalse;

template<typename Tda>
struct ImaginaryFriend {};

template<typename Tda, typename TFriend = ImaginaryFriend<Tda>>
class A
{
    friend TFriend;
public:
    template<typename T = Tda>
    typename basic::type::access::enable_if::
        Public<typename T::Foo1Access>::type Foo1() {}
    template<typename T = Tda>
    static typename basic::type::access::enable_if::
        Public<typename T::Foo2Access>::type Foo2() {}
protected:
    template<typename T = Tda>
    typename basic::type::access::enable_if::
        Protected<typename T::Foo1Access>::type Foo1() {}
    template<typename T = Tda>
    static typename basic::type::access::enable_if::
        Protected<typename T::Foo2Access>::type Foo2() {};
private:
    template<typename T = Tda>
    typename basic::type::access::enable_if::
        Private<typename T::Foo1Access>::type Foo1() {}
    template<typename T = Tda>
    static typename basic::type::access::enable_if::
        Private<typename T::Foo2Access>::type Foo2() {};
};

template<typename Tda>
using A1 = A<Tda>;

template<typename Tda>
struct Name<A1<Tda>>
{
    static constexpr const char * Value = "A1";
};

template<typename Tda, bool BoolOtherTest, 
    typename TFriend = ImaginaryFriend<Tda>>
class B
{
    friend TFriend;
public:
    template<typename T = Tda>
    typename basic::type::access::enable_if::
        Public<typename T::Foo1Access, void, BoolOtherTest>::type Foo1() {}
    template<typename T = Tda>
    static typename basic::type::access::enable_if::
        Public<typename T::Foo2Access, void, BoolOtherTest>::type Foo2() {};
protected:
    template<typename T = Tda>
    typename basic::type::access::enable_if::
        Protected<typename T::Foo1Access, void, BoolOtherTest>::type Foo1() {}
    template<typename T = Tda>
    static typename basic::type::access::enable_if::
        Protected<typename T::Foo2Access, void, BoolOtherTest>::type Foo2() {};

private:
    template<typename T = Tda>
    typename basic::type::access::enable_if::
        Private<typename T::Foo1Access, void, BoolOtherTest>::type Foo1() {}
    template<typename T = Tda>
    static typename basic::type::access::enable_if::
        Private<typename T::Foo2Access, void, BoolOtherTest>::type Foo2() {};
};

template<typename Tda>
using B1True = B<Tda, true>;

template<typename Tda>
struct Name<B1True<Tda>>
{
    static constexpr const char * Value = "B1True";
};

template<typename Tda>
using B1False = B<Tda, false>;

template<typename Tda>
struct Name<B1False<Tda>>
{
    static constexpr const char * Value = "B1False";
};

template<typename Tda>
struct Void
{};

template<typename Tda>
struct DerivedA : A<Tda>
{};

template<typename Tda, typename Tid>
struct DerivedFriendA : A<Tda, Derived<Tid, DerivedFriendA<Tda, Tid>>>
{};

template<typename Tda>
struct DerivedBTrue : B<Tda, true>
{};

template<typename Tda>
struct DerivedBFalse : B<Tda, false>
{};

template<typename Tda, typename Tid>
struct DerivedFriendBTrue : B<Tda, true,
    Derived<Tid, DerivedFriendBTrue<Tda, Tid>>>
{};

template<typename Tda, typename Tid>
struct DerivedFriendBFalse : B<Tda, false,
    Derived<Tid, DerivedFriendBFalse<Tda, Tid>>>
{};

struct Void1;

template<typename Tda>
using Void1_t = Derived<Void1, Void<Tda>>;

template<typename Tda>
struct Name<Void1_t<Tda>>
{
    static constexpr const char * Value = "Void1_t";
};

TestRegister t1_1(new TestAccess<Void1_t, A1, 
    AccessPublic, bool, true, true>());
TestRegister t1_2(new TestAccess<Void1_t, A1, 
    AccessProtected, bool, false, false>());
TestRegister t1_3(new TestAccess<Void1_t, A1, 
    AccessPrivate, bool, false, false>());
    
TestRegister t1_4(new TestAccess<Void1_t, B1True, 
    AccessPublic, bool, true, true>());
TestRegister t1_5(new TestAccess<Void1_t, B1True, 
    AccessProtected, bool, false, false>());
TestRegister t1_6(new TestAccess<Void1_t, B1True, 
    AccessPrivate, bool, false, false>());

TestRegister t1_7(new TestAccess<Void1_t, B1False, 
    AccessPublic, bool, false, false>());
TestRegister t1_8(new TestAccess<Void1_t, B1False, 
    AccessProtected, bool, false, false>());
TestRegister t1_9(new TestAccess<Void1_t, B1False, 
    AccessPrivate, bool, false, false>());

struct DerivedA1;

template<typename Tda>
using DerivedA1_t = Derived<DerivedA1, DerivedA<Tda>>;

template<typename Tda>
struct Name<DerivedA1_t<Tda>>
{
    static constexpr const char * Value = "DerivedA1_t";
};

TestRegister t2_1(new TestAccess<DerivedA1_t, DerivedA1_t, 
    AccessPublic, bool, true, true>());
TestRegister t2_2(new TestAccess<DerivedA1_t, DerivedA1_t, 
    AccessProtected, bool, true, true>());
TestRegister t2_3(new TestAccess<DerivedA1_t, DerivedA1_t, 
    AccessPrivate, bool, false, false>());

struct DerivedB1True;

template<typename Tda>
using DerivedB1True_t = Derived<DerivedB1True, DerivedBTrue<Tda>>;

template<typename Tda>
struct Name<DerivedB1True_t<Tda>>
{
    static constexpr const char * Value = "DerivedB1True_t";
};

TestRegister t3_1(new TestAccess<DerivedB1True_t, DerivedB1True_t, 
    AccessPublic, bool, true, true>());
TestRegister t3_2(new TestAccess<DerivedB1True_t, DerivedB1True_t, 
    AccessProtected, bool, true, true>());
TestRegister t3_3(new TestAccess<DerivedB1True_t, DerivedB1True_t, 
    AccessPrivate, bool, false, false>());

struct DerivedB1False;

template<typename Tda>
using DerivedB1False_t = Derived<DerivedB1False, DerivedBFalse<Tda>>;

template<typename Tda>
struct Name<DerivedB1False_t<Tda>>
{
    static constexpr const char * Value = "DerivedB1False_t";
};

TestRegister t4_1(new TestAccess<DerivedB1False_t, DerivedB1False_t, 
    AccessPublic, bool, false, false>());
TestRegister t4_2(new TestAccess<DerivedB1False_t, DerivedB1False_t, 
    AccessProtected, bool, false, false>());
TestRegister t4_3(new TestAccess<DerivedB1False_t, DerivedB1False_t, 
    AccessPrivate, bool, false, false>());

struct DerivedFriendA1;

template<typename Tda>
using DerivedFriendA1_t = Derived<DerivedFriendA1, DerivedFriendA<Tda, 
    DerivedFriendA1>>;

template<typename Tda>
struct Name<DerivedFriendA1_t<Tda>>
{
    static constexpr const char * Value = "DerivedFriendA1_t";
};

TestRegister t5_1(new TestAccess<DerivedFriendA1_t, DerivedFriendA1_t, 
    AccessPublic, bool, true, true>());
TestRegister t5_2(new TestAccess<DerivedFriendA1_t, DerivedFriendA1_t, 
    AccessProtected, bool, true, true>());
TestRegister t5_3(new TestAccess<DerivedFriendA1_t, DerivedFriendA1_t, 
    AccessPrivate, bool, true, true>());

struct DerivedFriendB1True;

template<typename Tda>
using DerivedFriendB1True_t = Derived<DerivedFriendB1True, 
    DerivedFriendBTrue<Tda, DerivedFriendB1True>>;

template<typename Tda>
struct Name<DerivedFriendB1True_t<Tda>>
{
    static constexpr const char * Value = "DerivedFriendB1True_t";
};

TestRegister t6_1(new TestAccess<DerivedFriendB1True_t, DerivedFriendB1True_t, 
    AccessPublic, bool, true, true>());
TestRegister t6_2(new TestAccess<DerivedFriendB1True_t, DerivedFriendB1True_t, 
    AccessProtected, bool, true, true>());
TestRegister t6_3(new TestAccess<DerivedFriendB1True_t, DerivedFriendB1True_t, 
    AccessPrivate, bool, true, true>());

struct DerivedFriendB1False;

template<typename Tda>
using DerivedFriendB1False_t = Derived<DerivedFriendB1False, 
    DerivedFriendBFalse<Tda, DerivedFriendB1False>>;

template<typename Tda>
struct Name<DerivedFriendB1False_t<Tda>>
{
    static constexpr const char * Value = "DerivedFriendB1False_t";
};

TestRegister t7_1(new TestAccess<DerivedFriendB1False_t, 
    DerivedFriendB1False_t, AccessPublic, bool, false, false>());
TestRegister t7_2(new TestAccess<DerivedFriendB1False_t, 
    DerivedFriendB1False_t, AccessProtected, bool, false, false>());
TestRegister t7_3(new TestAccess<DerivedFriendB1False_t, 
    DerivedFriendB1False_t, AccessPrivate, bool, false, false>());

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

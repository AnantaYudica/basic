#include "type/Access.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <type_traits>

struct CaseHMFFoo1 {}; // case has member function Foo1
struct CaseHSMFFoo2 {}; // case has static member function Foo2

template<typename TDerivedAccess, typename TBaseAccess, bool HasMmbrFuncFoo1, 
    bool HasStaticMmbrFuncFoo2>
using VariableTestAccess = basic::test::Variable<
    TDerivedAccess, 
    TBaseAccess,
    basic::test::type::Value<bool, HasMmbrFuncFoo1>,
    basic::test::type::Value<bool, HasStaticMmbrFuncFoo2>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IDerivedAccess = 0;
constexpr std::size_t IBaseAccess = 1;
constexpr std::size_t ITypeValHasMmbrFuncFoo1 = 2;
constexpr std::size_t ITypeHasStaticMmbrFuncFoo2 = 3;
constexpr std::size_t IValFuncBoolToCString = 4;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeValue = basic::test::msg::arg::type::Value<I>;

template<std::size_t I, typename... TArgArgs>
using ArgValFunction = basic::test::msg::arg::val::Function<I, TArgArgs...>;

typedef basic::test::msg::Argument<CaseHMFFoo1, 
    ArgTypeName<IDerivedAccess>,
    ArgTypeName<IBaseAccess>, 
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValHasMmbrFuncFoo1>>> ArgCaseHMFFoo1;

typedef basic::test::msg::Base<CaseHMFFoo1, char, ArgCaseHMFFoo1, 
    ArgCaseHMFFoo1, ArgCaseHMFFoo1> MsgBaseCaseHMFFoo1;

typedef basic::test::msg::Argument<CaseHSMFFoo2, 
    ArgTypeName<IDerivedAccess>,
    ArgTypeName<IDerivedAccess>, 
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeHasStaticMmbrFuncFoo2>>> ArgCaseHSMFFoo2;

typedef basic::test::msg::Base<CaseHSMFFoo2, char, ArgCaseHSMFFoo2, 
    ArgCaseHSMFFoo2, ArgCaseHSMFFoo2> MsgBaseCaseHSMFFoo2;


template<typename TID, typename TBase>
struct Derived : TBase
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


template<typename TCases, typename... TVars>
class TestAccess :
    public MsgBaseCaseHMFFoo1,
    public MsgBaseCaseHSMFFoo2,
    public basic::test::Message<BASIC_TEST, TestAccess<TCases, TVars...>>,
    public basic::test::Case<TestAccess<TCases, TVars...>, TCases>,
    public basic::test::Base<TestAccess<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestAccess<TCases, TVars...>, TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestAccess<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestAccess<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseHMFFoo1::SetFormat;
    using MsgBaseCaseHSMFFoo2::SetFormat;
public:
    using MsgBaseCaseHMFFoo1::Format;
    using MsgBaseCaseHSMFFoo2::Format;
    using MsgBaseCaseHMFFoo1::Argument;
    using MsgBaseCaseHSMFFoo2::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestAccess(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseHMFFoo1 case_has_member_function_Foo1;
        SetFormat(info, case_has_member_function_Foo1, 
            "test compare between delctype(%s::template "
            "HasMemberFunctionFoo1<%s>(0))::value and %s\n");
        SetFormat(debug, case_has_member_function_Foo1, 
            "test compare between delctype(%s::template "
            "HasMemberFunctionFoo1<%s>(0))::value and %s\n");
        SetFormat(error, case_has_member_function_Foo1,
            "error delctype(%s::template HasMemberFunctionFoo1<%s>(0))::value "
            "is not same with %s\n");

        CaseHSMFFoo2 case_has_static_member_function_Foo2;
        SetFormat(info, case_has_static_member_function_Foo2, 
            "test compare between delctype(%s::template "
            "HasStaticMemberFunctionFoo2<%s>(0))::value and %s\n");
        SetFormat(debug, case_has_static_member_function_Foo2,
            "test compare between delctype(%s::template "
            "HasStaticMemberFunctionFoo2<%s>(0))::value and %s\n");
        SetFormat(error, case_has_static_member_function_Foo2,
            "error delctype(%s::template HasStaticMemberFunctionFoo2<%s>(0))::"
            "value is not same with %s\n");
    }

    template<typename TDerivedAccess, typename TBaseAccess, 
        bool HasMmbrFuncFoo1, bool HasStaticMmbrFuncFoo2>
    bool Result(const CaseHMFFoo1&, VariableTestAccess<TDerivedAccess, 
        TBaseAccess, HasMmbrFuncFoo1, HasStaticMmbrFuncFoo2>& var)
    {
        return decltype(TDerivedAccess::template HasMemberFunctionFoo1<
            TBaseAccess>(0))::value == HasMmbrFuncFoo1; 
    }

    template<typename TDerivedAccess, typename TBaseAccess, 
        bool HasMmbrFuncFoo1, bool HasStaticMmbrFuncFoo2>
    bool Result(const CaseHSMFFoo2&, VariableTestAccess<TDerivedAccess, 
        TBaseAccess, HasMmbrFuncFoo1, HasStaticMmbrFuncFoo2>& var)
    {
        return decltype(TDerivedAccess::template HasStaticMemberFunctionFoo2<
            TBaseAccess>(0))::value == HasStaticMmbrFuncFoo2; 
    }
};

using Cases = basic::test::type::Parameter<CaseHMFFoo1, CaseHSMFFoo2>;

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);

const char * true_cstr = "true";
const char * false_cstr = "false";

const char* BoolToString(bool&& b)
{
    return b ? true_cstr : false_cstr;
}

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

BASIC_TEST_TYPE_NAME("AccessPublic", AccessPublic);
BASIC_TEST_TYPE_NAME("AccessProtected", AccessProtected);
BASIC_TEST_TYPE_NAME("AccessPrivate", AccessPrivate);

template<typename TID, typename TBase>
struct basic::test::type::Name<Derived<TID, TBase>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "Derived<%s, %s>";
        const auto& arg1_cstr = basic::test::type::Name<TID>::CStr();
        const auto& arg2_cstr = basic::test::type::Name<TBase>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size() + arg2_cstr.Size(), _format_cstr, *arg1_cstr,
            *arg2_cstr);
    }
};

template<typename TDA>
struct DerivedA;

template<typename TDA, typename TTFriend>
struct DerivedFriendA;

template<typename TDA>
struct DerivedBTrue;

template<typename TDA>
struct DerivedBFalse;

template<typename TDA, typename TID>
struct DerivedFriendBTrue;

template<typename TDA, typename TID>
struct DerivedFriendBFalse;

template<typename TDA>
struct ImaginaryFriend {};

template<typename TDA>
struct basic::test::type::Name<ImaginaryFriend<TDA>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "ImaginaryFriend<%s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size(), _format_cstr, *arg1_cstr);
    }
};

template<typename TDA, typename TFriend = ImaginaryFriend<TDA>>
class A
{
    friend TFriend;
public:
    template<typename T = TDA>
    typename basic::type::access::enable_if::
        Public<typename T::Foo1Access>::type Foo1() {}
    template<typename T = TDA>
    static typename basic::type::access::enable_if::
        Public<typename T::Foo2Access>::type Foo2() {}
protected:
    template<typename T = TDA>
    typename basic::type::access::enable_if::
        Protected<typename T::Foo1Access>::type Foo1() {}
    template<typename T = TDA>
    static typename basic::type::access::enable_if::
        Protected<typename T::Foo2Access>::type Foo2() {};
private:
    template<typename T = TDA>
    typename basic::type::access::enable_if::
        Private<typename T::Foo1Access>::type Foo1() {}
    template<typename T = TDA>
    static typename basic::type::access::enable_if::
        Private<typename T::Foo2Access>::type Foo2() {};
};

template<typename TDA, typename TFriend>
struct basic::test::type::Name<A<TDA, TFriend>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "A<%s, %s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        const auto& arg2_cstr = basic::test::type::Name<TFriend>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size() + arg2_cstr.Size(), _format_cstr, *arg1_cstr,
            *arg2_cstr);
    }
};

template<typename TDA>
using A1 = A<TDA>;

template<typename TDA, bool BoolOtherTest, 
    typename TFriend = ImaginaryFriend<TDA>>
class B
{
    friend TFriend;
public:
    template<typename T = TDA>
    typename basic::type::access::enable_if::
        Public<typename T::Foo1Access, void, BoolOtherTest>::type Foo1() {}
    template<typename T = TDA>
    static typename basic::type::access::enable_if::
        Public<typename T::Foo2Access, void, BoolOtherTest>::type Foo2() {};
protected:
    template<typename T = TDA>
    typename basic::type::access::enable_if::
        Protected<typename T::Foo1Access, void, BoolOtherTest>::type Foo1() {}
    template<typename T = TDA>
    static typename basic::type::access::enable_if::
        Protected<typename T::Foo2Access, void, BoolOtherTest>::type Foo2() {};

private:
    template<typename T = TDA>
    typename basic::type::access::enable_if::
        Private<typename T::Foo1Access, void, BoolOtherTest>::type Foo1() {}
    template<typename T = TDA>
    static typename basic::type::access::enable_if::
        Private<typename T::Foo2Access, void, BoolOtherTest>::type Foo2() {};
};

template<typename TDA, bool BoolOtherTest, typename TFriend>
struct basic::test::type::Name<B<TDA, BoolOtherTest, TFriend>>
{
    static basic::test::CString<char> CStr()
    {
        static std::size_t boolSize = sizeof(true_cstr) > sizeof(false_cstr) ?
            sizeof(true_cstr) : sizeof(false_cstr);
        static char _format_cstr[] = "B<%s, %s, %s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        const auto& arg2_cstr = basic::test::type::Name<TFriend>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size() + arg2_cstr.Size() + boolSize, _format_cstr, 
            *arg1_cstr, (BoolOtherTest? true_cstr : false_cstr), *arg2_cstr);
    }
};

template<typename TDA>
using B1True = B<TDA, true>;

template<typename TDA>
using B1False = B<TDA, false>;

template<typename TDA>
struct Void
{};

template<typename TDA>
struct DerivedA : A<TDA>
{};

template<typename TDA>
struct basic::test::type::Name<DerivedA<TDA>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "DerivedA<%s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size(), _format_cstr, *arg1_cstr);
    }
};

template<typename TDA, typename TID>
struct DerivedFriendA : A<TDA, Derived<TID, DerivedFriendA<TDA, TID>>>
{};

template<typename TDA, typename TID>
struct basic::test::type::Name<DerivedFriendA<TDA, TID>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "DerivedFriendA<%s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        const auto& arg2_cstr = basic::test::type::Name<TID>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size() + arg2_cstr.Size(), _format_cstr, *arg1_cstr,
            *arg2_cstr);
    }
};

template<typename TDA>
struct DerivedBTrue : B<TDA, true>
{};

template<typename TDA>
struct basic::test::type::Name<DerivedBTrue<TDA>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "DerivedBTrue<%s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size(), _format_cstr, *arg1_cstr);
    }
};

template<typename TDA>
struct DerivedBFalse : B<TDA, false>
{};

template<typename TDA>
struct basic::test::type::Name<DerivedBFalse<TDA>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "DerivedBFalse<%s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size(), _format_cstr, *arg1_cstr);
    }
};

template<typename TDA, typename TID>
struct DerivedFriendBTrue : B<TDA, true,
    Derived<TID, DerivedFriendBTrue<TDA, TID>>>
{};

template<typename TDA, typename TID>
struct basic::test::type::Name<DerivedFriendBTrue<TDA, TID>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "DerivedFriendBTrue<%s, %s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        const auto& arg2_cstr = basic::test::type::Name<TID>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size() + arg2_cstr.Size(), _format_cstr, *arg1_cstr,
            *arg2_cstr);
    }
};

template<typename TDA, typename TID>
struct DerivedFriendBFalse : B<TDA, false,
    Derived<TID, DerivedFriendBFalse<TDA, TID>>>
{};

template<typename TDA, typename TID>
struct basic::test::type::Name<DerivedFriendBFalse<TDA, TID>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "DerivedFriendBFalse<%s, %s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        const auto& arg2_cstr = basic::test::type::Name<TID>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size() + arg2_cstr.Size(), _format_cstr, *arg1_cstr,
            *arg2_cstr);
    }
};

struct Void1;

BASIC_TEST_TYPE_NAME("Void1", Void1);

template<typename TDA>
using TVoid1 = Derived<Void1, Void<TDA>>;

template<typename TDA>
struct basic::test::type::Name<TVoid1<TDA>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "TVoid1<%s>";
        const auto& arg1_cstr = basic::test::type::Name<TDA>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size(), _format_cstr, *arg1_cstr);
    }
};

typedef VariableTestAccess<TVoid1<AccessPublic>, 
    A1<AccessPublic>, true, true> T1Var1;
typedef VariableTestAccess<TVoid1<AccessProtected>, 
    A1<AccessProtected>, false, false> T1Var2;
typedef VariableTestAccess<TVoid1<AccessPrivate>, 
    A1<AccessPrivate>, false, false> T1Var3;
typedef VariableTestAccess<TVoid1<AccessPublic>, 
    B1True<AccessPublic>, true, true> T1Var4;
typedef VariableTestAccess<TVoid1<AccessProtected>, 
    B1True<AccessProtected>, false, false> T1Var5;
typedef VariableTestAccess<TVoid1<AccessPrivate>, 
    B1True<AccessPrivate>, false, false> T1Var6;
typedef VariableTestAccess<TVoid1<AccessPublic>, 
    B1False<AccessPublic>, false, false> T1Var7;
typedef VariableTestAccess<TVoid1<AccessProtected>, 
    B1False<AccessProtected>, false, false> T1Var8;
typedef VariableTestAccess<TVoid1<AccessPrivate>, 
    B1False<AccessPrivate>, false, false> T1Var9;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);
T1Var3 t1_var3(&BoolToString);
T1Var4 t1_var4(&BoolToString);
T1Var5 t1_var5(&BoolToString);
T1Var6 t1_var6(&BoolToString);
T1Var7 t1_var7(&BoolToString);
T1Var8 t1_var8(&BoolToString);
T1Var9 t1_var9(&BoolToString);

REGISTER_TEST(t1, new TestAccess<Cases, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9>(t1_var1, t1_var2, t1_var3,
        t1_var4, t1_var5, t1_var6, t1_var7, t1_var8, t1_var9));

struct DerivedA1;

BASIC_TEST_TYPE_NAME("DerivedA1", DerivedA1);

template<typename Tda>
using TDerivedA1 = Derived<DerivedA1, DerivedA<Tda>>;

typedef VariableTestAccess<TDerivedA1<AccessPublic>, 
    TDerivedA1<AccessPublic>, true, true> T2Var1;
typedef VariableTestAccess<TDerivedA1<AccessProtected>, 
    TDerivedA1<AccessProtected>, true, true> T2Var2;
typedef VariableTestAccess<TDerivedA1<AccessPrivate>, 
    TDerivedA1<AccessPrivate>, false, false> T2Var3;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);
T2Var3 t2_var3(&BoolToString);

REGISTER_TEST(t2, new TestAccess<Cases, T2Var1, T2Var2, T2Var3>(t2_var1, 
    t2_var2, t2_var3));

struct DerivedB1True;

BASIC_TEST_TYPE_NAME("DerivedB1True", DerivedB1True);

template<typename TDA>
using DerivedB1True_t = Derived<DerivedB1True, DerivedBTrue<TDA>>;

typedef VariableTestAccess<DerivedB1True_t<AccessPublic>, 
    DerivedB1True_t<AccessPublic>, true, true> T3Var1;
typedef VariableTestAccess<DerivedB1True_t<AccessProtected>, 
    DerivedB1True_t<AccessProtected>, true, true> T3Var2;
typedef VariableTestAccess<DerivedB1True_t<AccessPrivate>, 
    DerivedB1True_t<AccessPrivate>, false, false> T3Var3;

T3Var1 t3_var1(&BoolToString);
T3Var2 t3_var2(&BoolToString);
T3Var3 t3_var3(&BoolToString);

REGISTER_TEST(t3, new TestAccess<Cases, T3Var1, T3Var2, T3Var3>(t3_var1, 
    t3_var2, t3_var3));

struct DerivedB1False;

BASIC_TEST_TYPE_NAME("DerivedB1False", DerivedB1False);

template<typename TDA>
using DerivedB1False_t = Derived<DerivedB1False, DerivedBFalse<TDA>>;

typedef VariableTestAccess<DerivedB1False_t<AccessPublic>, 
    DerivedB1False_t<AccessPublic>, false, false> T4Var1;
typedef VariableTestAccess<DerivedB1False_t<AccessProtected>, 
    DerivedB1False_t<AccessProtected>, false, false> T4Var2;
typedef VariableTestAccess<DerivedB1False_t<AccessPrivate>, 
    DerivedB1False_t<AccessPrivate>, false, false> T4Var3;

T4Var1 t4_var1(&BoolToString);
T4Var2 t4_var2(&BoolToString);
T4Var3 t4_var3(&BoolToString);

REGISTER_TEST(t4, new TestAccess<Cases, T4Var1, T4Var2, T4Var3>(t4_var1, 
    t4_var2, t4_var3));

struct DerivedFriendA1;

BASIC_TEST_TYPE_NAME("DerivedFriendA1", DerivedFriendA1);

template<typename TDA>
using TDerivedFriendA1 = Derived<DerivedFriendA1, DerivedFriendA<TDA, 
    DerivedFriendA1>>;

typedef VariableTestAccess<TDerivedFriendA1<AccessPublic>, 
    TDerivedFriendA1<AccessPublic>, true, true> T5Var1;
typedef VariableTestAccess<TDerivedFriendA1<AccessProtected>, 
    TDerivedFriendA1<AccessProtected>, true, true> T5Var2;
typedef VariableTestAccess<TDerivedFriendA1<AccessPrivate>, 
    TDerivedFriendA1<AccessPrivate>, true, true> T5Var3;

T5Var1 t5_var1(&BoolToString);
T5Var2 t5_var2(&BoolToString);
T5Var3 t5_var3(&BoolToString);

REGISTER_TEST(t5, new TestAccess<Cases, T5Var1, T5Var2, T5Var3>(t5_var1, 
    t5_var2, t5_var3));

struct DerivedFriendB1True;

BASIC_TEST_TYPE_NAME("DerivedFriendB1True", DerivedFriendB1True);

template<typename TDA>
using DerivedFriendB1True_t = Derived<DerivedFriendB1True, 
    DerivedFriendBTrue<TDA, DerivedFriendB1True>>;

typedef VariableTestAccess<DerivedFriendB1True_t<AccessPublic>, 
    DerivedFriendB1True_t<AccessPublic>, true, true> T6Var1;
typedef VariableTestAccess<DerivedFriendB1True_t<AccessProtected>, 
    DerivedFriendB1True_t<AccessProtected>, true, true> T6Var2;
typedef VariableTestAccess<DerivedFriendB1True_t<AccessPrivate>, 
    DerivedFriendB1True_t<AccessPrivate>, true, true> T6Var3;

T6Var1 t6_var1(&BoolToString);
T6Var2 t6_var2(&BoolToString);
T6Var3 t6_var3(&BoolToString);

REGISTER_TEST(t6, new TestAccess<Cases, T6Var1, T6Var2, T6Var3>(t6_var1, 
    t6_var2, t6_var3));

struct DerivedFriendB1False;

BASIC_TEST_TYPE_NAME("DerivedFriendB1False", DerivedFriendB1False);

template<typename TDA>
using DerivedFriendB1False_t = Derived<DerivedFriendB1False, 
    DerivedFriendBFalse<TDA, DerivedFriendB1False>>;

typedef VariableTestAccess<DerivedFriendB1False_t<AccessPublic>, 
    DerivedFriendB1False_t<AccessPublic>, false, false> T7Var1;
typedef VariableTestAccess<DerivedFriendB1False_t<AccessProtected>, 
    DerivedFriendB1False_t<AccessProtected>, false, false> T7Var2;
typedef VariableTestAccess<DerivedFriendB1False_t<AccessPrivate>, 
    DerivedFriendB1False_t<AccessPrivate>, false, false> T7Var3;

T7Var1 t7_var1(&BoolToString);
T7Var2 t7_var2(&BoolToString);
T7Var3 t7_var3(&BoolToString);

REGISTER_TEST(t7, new TestAccess<Cases, T7Var1, T7Var2, T7Var3>(t7_var1, 
    t7_var2, t7_var3));

int main()
{
    return RUN_TEST();
}

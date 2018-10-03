#include "macro/HasMemberFunction.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <type_traits>
#include <typeinfo>

struct CaseAVTTa {}; // case alias value_type and target
struct CaseAVT {}; // case alias value_type
struct CaseVTa {}; // case value and target
struct CaseV {}; // case value

template<typename THasMmbrFunc, typename TAliasVal, TAliasVal AliasValue>
using VariableTestHasMmbrFunc = basic::test::Variable<
    THasMmbrFunc,
    TAliasVal,  
    basic::test::type::Value<TAliasVal, AliasValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IHasMmbrFunc = 0;
constexpr std::size_t IAliasVal = 1;
constexpr std::size_t ITypeValAliasValue = 2;
constexpr std::size_t IValFuncBoolToCString = 3;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeValue = basic::test::msg::arg::type::Value<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

template<std::size_t I, typename... TArgArgs>
using ArgValFunction = basic::test::msg::arg::val::Function<I, TArgArgs...>;

typedef basic::test::msg::Argument<CaseAVTTa, 
    ArgTypeName<IHasMmbrFunc>,
    ArgTypeName<IAliasVal>> ArgCaseAVTTa;

typedef basic::test::msg::Base<CaseAVTTa, char, ArgCaseAVTTa, 
    ArgCaseAVTTa, ArgCaseAVTTa> MsgBaseCaseAVTTa;

typedef basic::test::msg::Argument<CaseAVT, 
    ArgTypeName<IHasMmbrFunc>,
    ArgTypeName<IHasMmbrFunc>> ArgCaseAVT;

typedef basic::test::msg::Base<CaseAVT, char, ArgCaseAVT, 
    ArgCaseAVT, ArgCaseAVT> MsgBaseCaseAVT;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IHasMmbrFunc>,
    ArgValFunction<IValFuncBoolToCString, 
        ArgTypeValue<ITypeValAliasValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, 
    ArgTypeName<IHasMmbrFunc>,
    ArgTypeName<IHasMmbrFunc>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
class TestHasMmbrFunc : 
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestHasMmbrFunc<TCases, TVars...>>,
    public basic::test::Case<TestHasMmbrFunc<TCases, TVars...>, TCases>,
    public basic::test::Base<TestHasMmbrFunc<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestHasMmbrFunc<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestHasMmbrFunc<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestHasMmbrFunc<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseAVTTa::SetFormat;
    using MsgBaseCaseAVT::SetFormat;
    using MsgBaseCaseVTa::SetFormat;
    using MsgBaseCaseV::SetFormat;
public:
    using MsgBaseCaseAVTTa::Format;
    using MsgBaseCaseAVT::Format;
    using MsgBaseCaseVTa::Format;
    using MsgBaseCaseV::Format;
    using MsgBaseCaseAVTTa::Argument;
    using MsgBaseCaseAVT::Argument;
    using MsgBaseCaseVTa::Argument;
    using MsgBaseCaseV::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestHasMmbrFunc(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseAVTTa case_alias_value_type_and_target;
        SetFormat(info, case_alias_value_type_and_target,
            "Test compare between %s::value_type and %s\n");
        SetFormat(debug, case_alias_value_type_and_target,
            "Test compare between %s::value_type and %s\n");
        SetFormat(error, case_alias_value_type_and_target,
            "error %s::value_type is not same with %s\n");
            
        CaseAVT case_alias_value_type;
        SetFormat(info, case_alias_value_type,
            "Test compare between %s::value_type and "
            "%s::ValueType\n");
        SetFormat(debug, case_alias_value_type,
            "Test compare between %s::value_type and "
            "%s::ValueType\n");
        SetFormat(error, case_alias_value_type,
            "error %s::value_type is not same with "
            "%s::ValueType\n");

        CaseVTa case_value_and_target;
        SetFormat(info, case_value_and_target,
            "Test compare between %s::value and %s\n");
        SetFormat(debug, case_value_and_target,
            "Test compare between %s::value and %s\n");
        SetFormat(error, case_value_and_target,
            "error %s::value is not same with %s\n");

        CaseV case_value;
        SetFormat(info, case_value,
            "Test compare between %s::value and "
            "%s::Value\n");
        SetFormat(debug, case_value,
            "Test compare between %s::value and "
            "%s::Value\n");
        SetFormat(error, case_value,
            "error %s::value is not same with "
            "%s::Value\n");
    }

    template<typename THasMmbrFunc, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVTTa&, VariableTestHasMmbrFunc<THasMmbrFunc, 
        TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasMmbrFunc::value_type).hash_code() ==
            typeid(TAliasVal).hash_code();
    }
    
    template<typename THasMmbrFunc, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVT&, VariableTestHasMmbrFunc<THasMmbrFunc, 
        TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasMmbrFunc::value_type).hash_code() ==
            typeid(typename THasMmbrFunc::ValueType).hash_code();
    }
    
    template<typename THasMmbrFunc, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseVTa&, VariableTestHasMmbrFunc<THasMmbrFunc, 
        TAliasVal, AliasValue>& var)
    {
        return AliasValue == THasMmbrFunc::value;
    }
    
    template<typename THasMmbrFunc, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseV&, VariableTestHasMmbrFunc<THasMmbrFunc, 
        TAliasVal, AliasValue>& var)
    {
        return THasMmbrFunc::value == THasMmbrFunc::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A1
{
    void Foo1() {}
    template<typename>
    void Foo2() {}
};

struct A2
{
    void Foo1() const {}
    template<typename>
    void Foo2() const {}
};

struct A3
{
    void Foo1() volatile {}
    template<typename>
    void Foo2() volatile {}
};

struct A4
{
    void Foo1() const volatile {}
    template<typename>
    void Foo2() const volatile {}
};

struct A5
{
    void Foo1() & {}
    template<typename>
    void Foo2() & {}
};

struct A6
{
    void Foo1() const & {}
    template<typename>
    void Foo2() const & {}
};

struct A7
{
    void Foo1() volatile & {}
    template<typename>
    void Foo2() volatile & {}
};

struct A8
{
    void Foo1() const volatile & {}
    template<typename>
    void Foo2() const volatile & {}
};

struct A9
{
    void Foo1() && {}
    template<typename>
    void Foo2() && {}
};

struct A10
{
    void Foo1() const && {}
    template<typename>
    void Foo2() const && {}
};

struct A11
{
    void Foo1() volatile && {}
    template<typename>
    void Foo2() volatile && {}
};

struct A12
{
    void Foo1() const volatile && {}
    template<typename>
    void Foo2() const volatile && {}
};

struct B
{};

template<typename T>
struct C1
{
    void Foo1() {}
    template<typename>
    void Foo2() {}
};

template<>
struct C1<std::false_type>
{};

struct D1
{
    template<typename T>
    C1<T> Foo3() {return C1<T>();}
};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A1", A1);
BASIC_TEST_TYPE_NAME("A2", A2);
BASIC_TEST_TYPE_NAME("B", B);

const char* true_cstr = "true";
const char* false_cstr = "false";

const char* BoolToString(bool&& b)
{
    return b ? true_cstr : false_cstr;
}

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc1(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc1 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc1
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc1<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc1<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
    
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc1, _HasMmbrFunc1, T, Tr, Targs,,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc1 = HasMmbrFunc1<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A1, void>", HasMmbrFunc1<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A2, void>", HasMmbrFunc1<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A3, void>", HasMmbrFunc1<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A4, void>", HasMmbrFunc1<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A5, void>", HasMmbrFunc1<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A6, void>", HasMmbrFunc1<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A7, void>", HasMmbrFunc1<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A8, void>", HasMmbrFunc1<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A9, void>", HasMmbrFunc1<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A10, void>", HasMmbrFunc1<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A11, void>", HasMmbrFunc1<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<A12, void>", HasMmbrFunc1<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc1<B, void>", HasMmbrFunc1<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A1>, bool, true> T1Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A2>, bool, false> T1Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A3>, bool, false> T1Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A4>, bool, false> T1Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A5>, bool, false> T1Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A6>, bool, false> T1Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A7>, bool, false> T1Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A8>, bool, false> T1Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A9>, bool, false> T1Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A10>, bool, false> T1Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A11>, bool, false> T1Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<A12>, bool, false> T1Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc1<B>, bool, false> T1Var13;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);
T1Var3 t1_var3(&BoolToString);
T1Var4 t1_var4(&BoolToString);
T1Var5 t1_var5(&BoolToString);
T1Var6 t1_var6(&BoolToString);
T1Var7 t1_var7(&BoolToString);
T1Var8 t1_var8(&BoolToString);
T1Var9 t1_var9(&BoolToString);
T1Var10 t1_var10(&BoolToString);
T1Var11 t1_var11(&BoolToString);
T1Var12 t1_var12(&BoolToString);
T1Var13 t1_var13(&BoolToString);

REGISTER_TEST(t1, new TestHasMmbrFunc<Cases, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12, 
    T1Var13>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5, t1_var6, t1_var7,
        t1_var8, t1_var9, t1_var10, t1_var11, t1_var12, t1_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc2(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc2 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc2
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc2<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc2<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
 
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc2, _HasMmbrFunc2, T, Tr, Targs, const,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc2 = HasMmbrFunc2<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A1, void>", HasMmbrFunc2<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A2, void>", HasMmbrFunc2<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A3, void>", HasMmbrFunc2<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A4, void>", HasMmbrFunc2<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A5, void>", HasMmbrFunc2<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A6, void>", HasMmbrFunc2<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A7, void>", HasMmbrFunc2<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A8, void>", HasMmbrFunc2<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A9, void>", HasMmbrFunc2<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A10, void>", HasMmbrFunc2<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A11, void>", HasMmbrFunc2<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<A12, void>", HasMmbrFunc2<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc2<B, void>", HasMmbrFunc2<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A1>, bool, false> T2Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A2>, bool, true> T2Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A3>, bool, false> T2Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A4>, bool, false> T2Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A5>, bool, false> T2Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A6>, bool, false> T2Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A7>, bool, false> T2Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A8>, bool, false> T2Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A9>, bool, false> T2Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A10>, bool, false> T2Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A11>, bool, false> T2Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<A12>, bool, false> T2Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc2<B>, bool, false> T2Var13;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);
T2Var3 t2_var3(&BoolToString);
T2Var4 t2_var4(&BoolToString);
T2Var5 t2_var5(&BoolToString);
T2Var6 t2_var6(&BoolToString);
T2Var7 t2_var7(&BoolToString);
T2Var8 t2_var8(&BoolToString);
T2Var9 t2_var9(&BoolToString);
T2Var10 t2_var10(&BoolToString);
T2Var11 t2_var11(&BoolToString);
T2Var12 t2_var12(&BoolToString);
T2Var13 t2_var13(&BoolToString);

REGISTER_TEST(t2, new TestHasMmbrFunc<Cases, T2Var1, T2Var2, T2Var3, T2Var4,
    T2Var5, T2Var6, T2Var7, T2Var8, T2Var9, T2Var10, T2Var11, T2Var12, 
    T2Var13>(t2_var1, t2_var2, t2_var3, t2_var4, t2_var5, t2_var6, t2_var7,
        t2_var8, t2_var9, t2_var10, t2_var11, t2_var12, t2_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc3(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *          static_cast<Tr (T::*)(Targs...) volatile>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc3 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc3
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc3<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc3<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc3, _HasMmbrFunc3, T, Tr, Targs, volatile,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc3 = HasMmbrFunc3<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A1, void>", HasMmbrFunc3<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A2, void>", HasMmbrFunc3<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A3, void>", HasMmbrFunc3<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A4, void>", HasMmbrFunc3<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A5, void>", HasMmbrFunc3<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A6, void>", HasMmbrFunc3<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A7, void>", HasMmbrFunc3<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A8, void>", HasMmbrFunc3<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A9, void>", HasMmbrFunc3<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A10, void>", HasMmbrFunc3<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A11, void>", HasMmbrFunc3<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<A12, void>", HasMmbrFunc3<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc3<B, void>", HasMmbrFunc3<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A1>, bool, false> T3Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A2>, bool, false> T3Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A3>, bool, true> T3Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A4>, bool, false> T3Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A5>, bool, false> T3Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A6>, bool, false> T3Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A7>, bool, false> T3Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A8>, bool, false> T3Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A9>, bool, false> T3Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A10>, bool, false> T3Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A11>, bool, false> T3Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<A12>, bool, false> T3Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc3<B>, bool, false> T3Var13;

T3Var1 t3_var1(&BoolToString);
T3Var2 t3_var2(&BoolToString);
T3Var3 t3_var3(&BoolToString);
T3Var4 t3_var4(&BoolToString);
T3Var5 t3_var5(&BoolToString);
T3Var6 t3_var6(&BoolToString);
T3Var7 t3_var7(&BoolToString);
T3Var8 t3_var8(&BoolToString);
T3Var9 t3_var9(&BoolToString);
T3Var10 t3_var10(&BoolToString);
T3Var11 t3_var11(&BoolToString);
T3Var12 t3_var12(&BoolToString);
T3Var13 t3_var13(&BoolToString);

REGISTER_TEST(t3, new TestHasMmbrFunc<Cases, T3Var1, T3Var2, T3Var3, T3Var4,
    T3Var5, T3Var6, T3Var7, T3Var8, T3Var9, T3Var10, T3Var11, T3Var12, 
    T3Var13>(t3_var1, t3_var2, t3_var3, t3_var4, t3_var5, t3_var6, t3_var7,
        t3_var8, t3_var9, t3_var10, t3_var11, t3_var12, t3_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc4(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const volatile>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc4 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc4
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc4<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc4<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc4, _HasMmbrFunc4, T, Tr, Targs, const volatile,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc4 = HasMmbrFunc4<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A1, void>", HasMmbrFunc4<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A2, void>", HasMmbrFunc4<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A3, void>", HasMmbrFunc4<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A4, void>", HasMmbrFunc4<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A5, void>", HasMmbrFunc4<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A6, void>", HasMmbrFunc4<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A7, void>", HasMmbrFunc4<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A8, void>", HasMmbrFunc4<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A9, void>", HasMmbrFunc4<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A10, void>", HasMmbrFunc4<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A11, void>", HasMmbrFunc4<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<A12, void>", HasMmbrFunc4<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc4<B, void>", HasMmbrFunc4<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A1>, bool, false> T4Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A2>, bool, false> T4Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A3>, bool, false> T4Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A4>, bool, true> T4Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A5>, bool, false> T4Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A6>, bool, false> T4Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A7>, bool, false> T4Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A8>, bool, false> T4Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A9>, bool, false> T4Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A10>, bool, false> T4Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A11>, bool, false> T4Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<A12>, bool, false> T4Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc4<B>, bool, false> T4Var13;

T4Var1 t4_var1(&BoolToString);
T4Var2 t4_var2(&BoolToString);
T4Var3 t4_var3(&BoolToString);
T4Var4 t4_var4(&BoolToString);
T4Var5 t4_var5(&BoolToString);
T4Var6 t4_var6(&BoolToString);
T4Var7 t4_var7(&BoolToString);
T4Var8 t4_var8(&BoolToString);
T4Var9 t4_var9(&BoolToString);
T4Var10 t4_var10(&BoolToString);
T4Var11 t4_var11(&BoolToString);
T4Var12 t4_var12(&BoolToString);
T4Var13 t4_var13(&BoolToString);

REGISTER_TEST(t4, new TestHasMmbrFunc<Cases, T4Var1, T4Var2, T4Var3, T4Var4,
    T4Var5, T4Var6, T4Var7, T4Var8, T4Var9, T4Var10, T4Var11, T4Var12, 
    T4Var13>(t4_var1, t4_var2, t4_var3, t4_var4, t4_var5, t4_var6, t4_var7,
        t4_var8, t4_var9, t4_var10, t4_var11, t4_var12, t4_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc5(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) &>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc5 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc5
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc5<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc5<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
    
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc5, _HasMmbrFunc5, T, Tr, Targs,, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc5 = HasMmbrFunc5<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A1, void>", HasMmbrFunc5<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A2, void>", HasMmbrFunc5<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A3, void>", HasMmbrFunc5<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A4, void>", HasMmbrFunc5<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A5, void>", HasMmbrFunc5<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A6, void>", HasMmbrFunc5<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A7, void>", HasMmbrFunc5<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A8, void>", HasMmbrFunc5<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A9, void>", HasMmbrFunc5<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A10, void>", HasMmbrFunc5<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A11, void>", HasMmbrFunc5<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<A12, void>", HasMmbrFunc5<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc5<B, void>", HasMmbrFunc5<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A1>, bool, false> T5Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A2>, bool, false> T5Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A3>, bool, false> T5Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A4>, bool, false> T5Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A5>, bool, true> T5Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A6>, bool, false> T5Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A7>, bool, false> T5Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A8>, bool, false> T5Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A9>, bool, false> T5Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A10>, bool, false> T5Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A11>, bool, false> T5Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<A12>, bool, false> T5Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc5<B>, bool, false> T5Var13;

T5Var1 t5_var1(&BoolToString);
T5Var2 t5_var2(&BoolToString);
T5Var3 t5_var3(&BoolToString);
T5Var4 t5_var4(&BoolToString);
T5Var5 t5_var5(&BoolToString);
T5Var6 t5_var6(&BoolToString);
T5Var7 t5_var7(&BoolToString);
T5Var8 t5_var8(&BoolToString);
T5Var9 t5_var9(&BoolToString);
T5Var10 t5_var10(&BoolToString);
T5Var11 t5_var11(&BoolToString);
T5Var12 t5_var12(&BoolToString);
T5Var13 t5_var13(&BoolToString);

REGISTER_TEST(t5, new TestHasMmbrFunc<Cases, T5Var1, T5Var2, T5Var3, T5Var4,
    T5Var5, T5Var6, T5Var7, T5Var8, T5Var9, T5Var10, T5Var11, T5Var12, 
    T5Var13>(t5_var1, t5_var2, t5_var3, t5_var4, t5_var5, t5_var6, t5_var7,
        t5_var8, t5_var9, t5_var10, t5_var11, t5_var12, t5_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc6(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const &>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc6 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc6
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc6<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc6<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
 
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc6, _HasMmbrFunc6, T, Tr, Targs, const, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc6 = HasMmbrFunc6<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A1, void>", HasMmbrFunc6<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A2, void>", HasMmbrFunc6<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A3, void>", HasMmbrFunc6<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A4, void>", HasMmbrFunc6<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A5, void>", HasMmbrFunc6<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A6, void>", HasMmbrFunc6<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A7, void>", HasMmbrFunc6<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A8, void>", HasMmbrFunc6<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A9, void>", HasMmbrFunc6<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A10, void>", HasMmbrFunc6<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A11, void>", HasMmbrFunc6<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<A12, void>", HasMmbrFunc6<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc6<B, void>", HasMmbrFunc6<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A1>, bool, false> T6Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A2>, bool, false> T6Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A3>, bool, false> T6Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A4>, bool, false> T6Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A5>, bool, false> T6Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A6>, bool, true> T6Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A7>, bool, false> T6Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A8>, bool, false> T6Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A9>, bool, false> T6Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A10>, bool, false> T6Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A11>, bool, false> T6Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<A12>, bool, false> T6Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc6<B>, bool, false> T6Var13;

T6Var1 t6_var1(&BoolToString);
T6Var2 t6_var2(&BoolToString);
T6Var3 t6_var3(&BoolToString);
T6Var4 t6_var4(&BoolToString);
T6Var5 t6_var5(&BoolToString);
T6Var6 t6_var6(&BoolToString);
T6Var7 t6_var7(&BoolToString);
T6Var8 t6_var8(&BoolToString);
T6Var9 t6_var9(&BoolToString);
T6Var10 t6_var10(&BoolToString);
T6Var11 t6_var11(&BoolToString);
T6Var12 t6_var12(&BoolToString);
T6Var13 t6_var13(&BoolToString);

REGISTER_TEST(t6, new TestHasMmbrFunc<Cases, T6Var1, T6Var2, T6Var3, T6Var4,
    T6Var5, T6Var6, T6Var7, T6Var8, T6Var9, T6Var10, T6Var11, T6Var12, 
    T6Var13>(t6_var1, t6_var2, t6_var3, t6_var4, t6_var5, t6_var6, t6_var7,
        t6_var8, t6_var9, t6_var10, t6_var11, t6_var12, t6_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc7(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) volatile &>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc7 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc7
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc7<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc7<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc7, _HasMmbrFunc7, T, Tr, Targs, volatile, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc7 = HasMmbrFunc7<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A1, void>", HasMmbrFunc7<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A2, void>", HasMmbrFunc7<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A3, void>", HasMmbrFunc7<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A4, void>", HasMmbrFunc7<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A5, void>", HasMmbrFunc7<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A6, void>", HasMmbrFunc7<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A7, void>", HasMmbrFunc7<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A8, void>", HasMmbrFunc7<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A9, void>", HasMmbrFunc7<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A10, void>", HasMmbrFunc7<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A11, void>", HasMmbrFunc7<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<A12, void>", HasMmbrFunc7<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc7<B, void>", HasMmbrFunc7<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A1>, bool, false> T7Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A2>, bool, false> T7Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A3>, bool, false> T7Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A4>, bool, false> T7Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A5>, bool, false> T7Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A6>, bool, false> T7Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A7>, bool, true> T7Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A8>, bool, false> T7Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A9>, bool, false> T7Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A10>, bool, false> T7Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A11>, bool, false> T7Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<A12>, bool, false> T7Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc7<B>, bool, false> T7Var13;

T7Var1 t7_var1(&BoolToString);
T7Var2 t7_var2(&BoolToString);
T7Var3 t7_var3(&BoolToString);
T7Var4 t7_var4(&BoolToString);
T7Var5 t7_var5(&BoolToString);
T7Var6 t7_var6(&BoolToString);
T7Var7 t7_var7(&BoolToString);
T7Var8 t7_var8(&BoolToString);
T7Var9 t7_var9(&BoolToString);
T7Var10 t7_var10(&BoolToString);
T7Var11 t7_var11(&BoolToString);
T7Var12 t7_var12(&BoolToString);
T7Var13 t7_var13(&BoolToString);

REGISTER_TEST(t7, new TestHasMmbrFunc<Cases, T7Var1, T7Var2, T7Var3, T7Var4,
    T7Var5, T7Var6, T7Var7, T7Var8, T7Var9, T7Var10, T7Var11, T7Var12, 
    T7Var13>(t7_var1, t7_var2, t7_var3, t7_var4, t7_var5, t7_var6, t7_var7,
        t7_var8, t7_var9, t7_var10, t7_var11, t7_var12, t7_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc8(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const volatile &>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc8 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc8
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc8<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc8<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc8, _HasMmbrFunc8, T, Tr, Targs, const volatile, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc8 = HasMmbrFunc8<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A1, void>", HasMmbrFunc8<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A2, void>", HasMmbrFunc8<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A3, void>", HasMmbrFunc8<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A4, void>", HasMmbrFunc8<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A5, void>", HasMmbrFunc8<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A6, void>", HasMmbrFunc8<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A7, void>", HasMmbrFunc8<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A8, void>", HasMmbrFunc8<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A9, void>", HasMmbrFunc8<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A10, void>", HasMmbrFunc8<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A11, void>", HasMmbrFunc8<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<A12, void>", HasMmbrFunc8<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc8<B, void>", HasMmbrFunc8<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A1>, bool, false> T8Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A2>, bool, false> T8Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A3>, bool, false> T8Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A4>, bool, false> T8Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A5>, bool, false> T8Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A6>, bool, false> T8Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A7>, bool, false> T8Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A8>, bool, true> T8Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A9>, bool, false> T8Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A10>, bool, false> T8Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A11>, bool, false> T8Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<A12>, bool, false> T8Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc8<B>, bool, false> T8Var13;

T8Var1 t8_var1(&BoolToString);
T8Var2 t8_var2(&BoolToString);
T8Var3 t8_var3(&BoolToString);
T8Var4 t8_var4(&BoolToString);
T8Var5 t8_var5(&BoolToString);
T8Var6 t8_var6(&BoolToString);
T8Var7 t8_var7(&BoolToString);
T8Var8 t8_var8(&BoolToString);
T8Var9 t8_var9(&BoolToString);
T8Var10 t8_var10(&BoolToString);
T8Var11 t8_var11(&BoolToString);
T8Var12 t8_var12(&BoolToString);
T8Var13 t8_var13(&BoolToString);

REGISTER_TEST(t8, new TestHasMmbrFunc<Cases, T8Var1, T8Var2, T8Var3, T8Var4,
    T8Var5, T8Var6, T8Var7, T8Var8, T8Var9, T8Var10, T8Var11, T8Var12, 
    T8Var13>(t8_var1, t8_var2, t8_var3, t8_var4, t8_var5, t8_var6, t8_var7,
        t8_var8, t8_var9, t8_var10, t8_var11, t8_var12, t8_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc9(T t, Targs... args) ->
 * 	    decltype((static_cast<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc9 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc9
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc9<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc9<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc9, _HasMmbrFunc9, T, Tr, Targs,, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);
    
template<typename T>
using THasMmbrFunc9 = HasMmbrFunc9<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A1, void>", HasMmbrFunc9<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A2, void>", HasMmbrFunc9<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A3, void>", HasMmbrFunc9<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A4, void>", HasMmbrFunc9<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A5, void>", HasMmbrFunc9<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A6, void>", HasMmbrFunc9<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A7, void>", HasMmbrFunc9<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A8, void>", HasMmbrFunc9<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A9, void>", HasMmbrFunc9<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A10, void>", HasMmbrFunc9<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A11, void>", HasMmbrFunc9<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<A12, void>", HasMmbrFunc9<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc9<B, void>", HasMmbrFunc9<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A1>, bool, false> T9Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A2>, bool, false> T9Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A3>, bool, false> T9Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A4>, bool, false> T9Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A5>, bool, false> T9Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A6>, bool, false> T9Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A7>, bool, false> T9Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A8>, bool, false> T9Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A9>, bool, true> T9Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A10>, bool, false> T9Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A11>, bool, false> T9Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<A12>, bool, false> T9Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc9<B>, bool, false> T9Var13;

T9Var1 t9_var1(&BoolToString);
T9Var2 t9_var2(&BoolToString);
T9Var3 t9_var3(&BoolToString);
T9Var4 t9_var4(&BoolToString);
T9Var5 t9_var5(&BoolToString);
T9Var6 t9_var6(&BoolToString);
T9Var7 t9_var7(&BoolToString);
T9Var8 t9_var8(&BoolToString);
T9Var9 t9_var9(&BoolToString);
T9Var10 t9_var10(&BoolToString);
T9Var11 t9_var11(&BoolToString);
T9Var12 t9_var12(&BoolToString);
T9Var13 t9_var13(&BoolToString);

REGISTER_TEST(t9, new TestHasMmbrFunc<Cases, T9Var1, T9Var2, T9Var3, T9Var4,
    T9Var5, T9Var6, T9Var7, T9Var8, T9Var9, T9Var10, T9Var11, T9Var12, 
    T9Var13>(t9_var1, t9_var2, t9_var3, t9_var4, t9_var5, t9_var6, t9_var7,
        t9_var8, t9_var9, t9_var10, t9_var11, t9_var12, t9_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc10(T t, Targs... args) ->
 * 	    decltype((static_cast<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc10 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc10
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc10<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc10<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
 
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc10, _HasMmbrFunc10, T, Tr, Targs, const, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc10 = HasMmbrFunc10<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A1, void>", HasMmbrFunc10<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A2, void>", HasMmbrFunc10<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A3, void>", HasMmbrFunc10<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A4, void>", HasMmbrFunc10<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A5, void>", HasMmbrFunc10<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A6, void>", HasMmbrFunc10<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A7, void>", HasMmbrFunc10<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A8, void>", HasMmbrFunc10<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A9, void>", HasMmbrFunc10<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A10, void>", HasMmbrFunc10<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A11, void>", HasMmbrFunc10<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<A12, void>", HasMmbrFunc10<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc10<B, void>", HasMmbrFunc10<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A1>, bool, false> T10Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A2>, bool, false> T10Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A3>, bool, false> T10Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A4>, bool, false> T10Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A5>, bool, false> T10Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A6>, bool, false> T10Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A7>, bool, false> T10Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A8>, bool, false> T10Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A9>, bool, false> T10Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A10>, bool, true> T10Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A11>, bool, false> T10Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<A12>, bool, false> T10Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc10<B>, bool, false> T10Var13;

T10Var1 t10_var1(&BoolToString);
T10Var2 t10_var2(&BoolToString);
T10Var3 t10_var3(&BoolToString);
T10Var4 t10_var4(&BoolToString);
T10Var5 t10_var5(&BoolToString);
T10Var6 t10_var6(&BoolToString);
T10Var7 t10_var7(&BoolToString);
T10Var8 t10_var8(&BoolToString);
T10Var9 t10_var9(&BoolToString);
T10Var10 t10_var10(&BoolToString);
T10Var11 t10_var11(&BoolToString);
T10Var12 t10_var12(&BoolToString);
T10Var13 t10_var13(&BoolToString);

REGISTER_TEST(t10, new TestHasMmbrFunc<Cases, T10Var1, T10Var2, T10Var3, T10Var4,
    T10Var5, T10Var6, T10Var7, T10Var8, T10Var9, T10Var10, T10Var11, T10Var12, 
    T10Var13>(t10_var1, t10_var2, t10_var3, t10_var4, t10_var5, t10_var6, t10_var7,
        t10_var8, t10_var9, t10_var10, t10_var11, t10_var12, t10_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc11(T t, Targs... args) ->
 * 	    decltype((static_cast<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) volatile &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc11 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc11
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc11<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc11<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc11, _HasMmbrFunc11, T, Tr, Targs, volatile, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc11 = HasMmbrFunc11<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A1, void>", HasMmbrFunc11<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A2, void>", HasMmbrFunc11<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A3, void>", HasMmbrFunc11<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A4, void>", HasMmbrFunc11<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A5, void>", HasMmbrFunc11<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A6, void>", HasMmbrFunc11<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A7, void>", HasMmbrFunc11<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A8, void>", HasMmbrFunc11<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A9, void>", HasMmbrFunc11<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A10, void>", HasMmbrFunc11<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A11, void>", HasMmbrFunc11<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<A12, void>", HasMmbrFunc11<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc11<B, void>", HasMmbrFunc11<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A1>, bool, false> T11Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A2>, bool, false> T11Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A3>, bool, false> T11Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A4>, bool, false> T11Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A5>, bool, false> T11Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A6>, bool, false> T11Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A7>, bool, false> T11Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A8>, bool, false> T11Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A9>, bool, false> T11Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A10>, bool, false> T11Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A11>, bool, true> T11Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<A12>, bool, false> T11Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc11<B>, bool, false> T11Var13;

T11Var1 t11_var1(&BoolToString);
T11Var2 t11_var2(&BoolToString);
T11Var3 t11_var3(&BoolToString);
T11Var4 t11_var4(&BoolToString);
T11Var5 t11_var5(&BoolToString);
T11Var6 t11_var6(&BoolToString);
T11Var7 t11_var7(&BoolToString);
T11Var8 t11_var8(&BoolToString);
T11Var9 t11_var9(&BoolToString);
T11Var10 t11_var10(&BoolToString);
T11Var11 t11_var11(&BoolToString);
T11Var12 t11_var12(&BoolToString);
T11Var13 t11_var13(&BoolToString);

REGISTER_TEST(t11, new TestHasMmbrFunc<Cases, T11Var1, T11Var2, T11Var3, T11Var4,
    T11Var5, T11Var6, T11Var7, T11Var8, T11Var9, T11Var10, T11Var11, T11Var12, 
    T11Var13>(t11_var1, t11_var2, t11_var3, t11_var4, t11_var5, t11_var6, t11_var7,
        t11_var8, t11_var9, t11_var10, t11_var11, t11_var12, t11_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc12(T t, Targs... args) ->
 * 	    decltype((static<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const volatile &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc12 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc12
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc12<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc12<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc12, _HasMmbrFunc12, T, Tr, Targs, const volatile, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc12 = HasMmbrFunc12<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A1, void>", HasMmbrFunc12<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A2, void>", HasMmbrFunc12<A2, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A3, void>", HasMmbrFunc12<A3, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A4, void>", HasMmbrFunc12<A4, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A5, void>", HasMmbrFunc12<A5, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A6, void>", HasMmbrFunc12<A6, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A7, void>", HasMmbrFunc12<A7, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A8, void>", HasMmbrFunc12<A8, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A9, void>", HasMmbrFunc12<A9, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A10, void>", HasMmbrFunc12<A10, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A11, void>", HasMmbrFunc12<A11, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<A12, void>", HasMmbrFunc12<A12, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc12<B, void>", HasMmbrFunc12<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A1>, bool, false> T12Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A2>, bool, false> T12Var2;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A3>, bool, false> T12Var3;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A4>, bool, false> T12Var4;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A5>, bool, false> T12Var5;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A6>, bool, false> T12Var6;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A7>, bool, false> T12Var7;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A8>, bool, false> T12Var8;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A9>, bool, false> T12Var9;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A10>, bool, false> T12Var10;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A11>, bool, false> T12Var11;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<A12>, bool, true> T12Var12;
typedef VariableTestHasMmbrFunc<THasMmbrFunc12<B>, bool, false> T12Var13;

T12Var1 t12_var1(&BoolToString);
T12Var2 t12_var2(&BoolToString);
T12Var3 t12_var3(&BoolToString);
T12Var4 t12_var4(&BoolToString);
T12Var5 t12_var5(&BoolToString);
T12Var6 t12_var6(&BoolToString);
T12Var7 t12_var7(&BoolToString);
T12Var8 t12_var8(&BoolToString);
T12Var9 t12_var9(&BoolToString);
T12Var10 t12_var10(&BoolToString);
T12Var11 t12_var11(&BoolToString);
T12Var12 t12_var12(&BoolToString);
T12Var13 t12_var13(&BoolToString);

REGISTER_TEST(t12, new TestHasMmbrFunc<Cases, T12Var1, T12Var2, T12Var3, T12Var4,
    T12Var5, T12Var6, T12Var7, T12Var8, T12Var9, T12Var10, T12Var11, T12Var12, 
    T12Var13>(t12_var1, t12_var2, t12_var3, t12_var4, t12_var5, t12_var6, t12_var7,
        t12_var8, t12_var9, t12_var10, t12_var11, t12_var12, t12_var13));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc13(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc13 (...);
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc13
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc13<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc13<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
    
#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc13, _HasMmbrFunc13, T, Tr, Targs,,, TPL1,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc13 = HasMmbrFunc13<T, void, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc13<A1, void, void>",
    HasMmbrFunc13<A1, void, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc13<B, void, void>",
    HasMmbrFunc13<B, void, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc13<A1>, bool, true> T13Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc13<B>, bool, false> T13Var2;

T13Var1 t13_var1(&BoolToString);
T13Var2 t13_var2(&BoolToString);

REGISTER_TEST(t13, new TestHasMmbrFunc<Cases, T13Var1, 
    T13Var2>(t13_var1, t13_var2));

/**
 * 	template<template T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc14(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc14 (...);
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	struct HasMmbrFunc14
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc14<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T<T1>>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc14<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T<T1>>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc14, _HasMmbrFunc14, T, Tr, Targs,,, TPL2,
    T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc14 = HasMmbrFunc14<C1, T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc14<C1, std::true_type, void>",
    HasMmbrFunc14<C1, std::true_type, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc14<C1, std::false_type, void>",
    HasMmbrFunc14<C1, std::false_type, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc14<std::true_type>, 
    bool, true> T14Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc14<std::false_type>, 
    bool, false> T14Var2;

T14Var1 t14_var1(&BoolToString);
T14Var2 t14_var2(&BoolToString);

REGISTER_TEST(t14, new TestHasMmbrFunc<Cases, T14Var1, 
    T14Var2>(t14_var1, t14_var2));

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc15(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc15 (...);
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc15
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc15<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc15<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTP1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS__NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS__NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTP1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS__NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS__NAME__
    
#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc15, _HasMmbrFunc15, T, Tr, Targs,,, TPL1,
    T_NAME_,, PFTTP1, PFFTP1, PFTAL1, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc15 = HasMmbrFunc15<T, void, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc15<A1, void, void>",
    HasMmbrFunc15<A1, void, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc15<B, void, void>",
    HasMmbrFunc15<B, void, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc15<A1>, bool, true> T15Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc15<B>, bool, false> T15Var2;

T15Var1 t15_var1(&BoolToString);
T15Var2 t15_var2(&BoolToString);

REGISTER_TEST(t15, new TestHasMmbrFunc<Cases, T15Var1,
    T15Var2>(t15_var1, t15_var2));

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc16(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc16 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc16
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc16<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, void, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc16<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, void, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc16, _HasMmbrFunc16, T, Tr, Targs,,,,
    T_NAME_,, PFTTP1, PFFTP1, PFTAL2, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc16 = HasMmbrFunc16<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc16<A1, void>", 
    HasMmbrFunc16<A1, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc16<B, void>",
    HasMmbrFunc16<B, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc16<A1>, bool, true> T16Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc16<B>, bool, false> T16Var2;

T16Var1 t16_var1(&BoolToString);
T16Var2 t16_var2(&BoolToString);

REGISTER_TEST(t16, new TestHasMmbrFunc<Cases, T16Var1, 
    T16Var2>(t16_var1, t16_var2));

/**
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	constexpr auto _HasMmbrFunc17(T<T1> t, Targs... args) ->
 * 	    decltype((static_cast<T<T1>>(t).*(
 *      static_cast<Tr (T<T1>::*)(Targs...)>(&T<T1>::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc17 (...);
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	struct HasMmbrFunc17
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc17<T, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc17<T, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
 template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
     typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
 template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
     typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc17, _HasMmbrFunc17, T, Tr, Targs,,, TPL2,
    T_NAME_TMPL_, TNTAL1, PFTTPL2, PFFTPL2, PFTAL3, PROTO_FUNC_T_NAME_TMPL_, 
    PFTNTAL1, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasMmbrFunc17 = HasMmbrFunc17<C1, T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc17<C1, std::true_type, void>",
    HasMmbrFunc17<C1, std::true_type, void>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc17<C1, std::false_type, void>",
    HasMmbrFunc17<C1, std::false_type, void>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc17<std::true_type>, 
    bool, true> T17Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc17<std::false_type>, 
    bool, false> T17Var2;

T17Var1 t17_var1(&BoolToString);
T17Var2 t17_var2(&BoolToString);

REGISTER_TEST(t17, new TestHasMmbrFunc<Cases, T17Var1,
    T17Var2>(t17_var1, t17_var2));


/**
 * 	template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 * 	constexpr auto _HasMmbrFunc18(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr<T1> (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc18 (...);
 * 	template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 * 	struct HasMmbrFunc18
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc18<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc18<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
     typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
     typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNTAL1()\
T1

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc18, _HasMmbrFunc18, T, Tr, Targs,,, TPL3,
    T_NAME_,, PFTTPL3, PFFTPL3, PFTAL1, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_TMPL_, PFTRNTAL1, template Foo3<T1>);

template<typename T>
using THasMmbrFunc18 = HasMmbrFunc18<T, void, C1>;

BASIC_TEST_TYPE_NAME("HasMmbrFunc18<D1, void, C1>",
    HasMmbrFunc18<D1, void, C1>);
BASIC_TEST_TYPE_NAME("HasMmbrFunc18<B, void, C1>",
    HasMmbrFunc18<B, void, C1>);

typedef VariableTestHasMmbrFunc<THasMmbrFunc18<D1>, bool, true> T18Var1;
typedef VariableTestHasMmbrFunc<THasMmbrFunc18<B>, bool, false> T18Var2;

T18Var1 t18_var1(&BoolToString);
T18Var2 t18_var2(&BoolToString);

REGISTER_TEST(t18, new TestHasMmbrFunc<Cases, T18Var1, 
    T18Var2>(t18_var1, t18_var2));


int main()
{
    return RUN_TEST();
}

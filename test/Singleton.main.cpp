#include "Singleton.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"

BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include "test/cstr/Format.h"

struct CaseHasCI {}; //case has ConstructInstance
struct CaseHasDI {}; //case has DestroyInstance
struct CaseHasHI {}; //case has HasInstance
struct CaseHasGI {}; //case has GetInstance
struct CaseHITa {}; //case HasInstance and target
struct CaseGITa {}; //case GetInstance and target
struct CaseCI {}; //case ConstructInstance
struct CaseDI {}; //case DestroyInstance

template<typename TSingleton,
    std::size_t SCaseHITa,
    typename TGetInstance, 
    typename... TArgs>
using VariableTestSingleton = basic::test::Variable<
    TSingleton,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::val::Sequence<bool, SCaseHITa>,
    basic::test::Value<bool>,
    basic::test::Value<void*>,
    TGetInstance,
    basic::test::Value<void*(*)(TGetInstance&)>,
    basic::test::val::Function<
        basic::test::CString<char>(basic::test::CString<char>&&, TArgs&&...)>,
    basic::test::val::Function<const char*(bool&&)>,
    basic::test::val::Parameter<TArgs...>>;

constexpr std::size_t ITSingleton = 0;
constexpr std::size_t IValBoolHasCI = 1;
constexpr std::size_t IValBoolHasDI = 2;
constexpr std::size_t IValBoolHasHI = 3;
constexpr std::size_t IValBoolHasGI = 4;
constexpr std::size_t IValSeqBoolHITa = 5;
constexpr std::size_t IValBoolGITa = 6;
constexpr std::size_t IValVoidPtrGITa = 7;
constexpr std::size_t ITGetInstance = 8;
constexpr std::size_t IValGIToVoidPTr = 9;
constexpr std::size_t IValFuncHasCIParam = 10;
constexpr std::size_t IValFuncBoolToCString = 11;
constexpr std::size_t IValParamCI = 12;

template<std::size_t I, typename... TArgArgs>
using ArgTypeFunction = basic::test::msg::arg::type::Function<I,
    TArgArgs...>;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I, template<std::size_t, std::size_t> class TArgAt>
using ArgTypeIndex = basic::test::msg::arg::type::Index<I, TArgAt>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

template<std::size_t I>
using ArgValParameter = basic::test::msg::arg::val::Parameter<I>;

template<std::size_t I, typename... TArgArgs>
using ArgValFunction = basic::test::msg::arg::val::Function<I,
    TArgArgs...>;

typedef basic::test::msg::Argument<CaseHasCI, 
    ArgValFunction<IValFuncHasCIParam, ArgTypeName<ITSingleton>, 
        ArgValParameter<IValParamCI>>,
    ArgTypeFunction<IValFuncBoolToCString, 
        ArgValue<IValBoolHasCI>>> ArgCaseHasCI;

typedef basic::test::msg::Base<CaseHasCI, char, ArgCaseHasCI, 
    ArgCaseHasCI, ArgCaseHasCI> MsgBaseCaseHasCI;

typedef basic::test::msg::Argument<CaseHasDI,
    ArgTypeName<ITSingleton>,
    ArgTypeFunction<IValFuncBoolToCString, 
        ArgValue<IValBoolHasDI>>> ArgCaseHasDI;

typedef basic::test::msg::Base<CaseHasDI, char, ArgCaseHasDI, 
    ArgCaseHasDI, ArgCaseHasDI> MsgBaseCaseHasDI;

typedef basic::test::msg::Argument<CaseHasHI,
    ArgTypeName<ITSingleton>,
    ArgTypeFunction<IValFuncBoolToCString, 
        ArgValue<IValBoolHasHI>>> ArgCaseHasHI;

typedef basic::test::msg::Base<CaseHasHI, char, ArgCaseHasHI, 
    ArgCaseHasHI, ArgCaseHasHI> MsgBaseCaseHasHI;

typedef basic::test::msg::Argument<CaseHasGI,
    ArgTypeName<ITSingleton>,
    ArgTypeFunction<IValFuncBoolToCString, 
        ArgValue<IValBoolHasGI>>> ArgCaseHasGI;

typedef basic::test::msg::Base<CaseHasGI, char, ArgCaseHasGI, 
    ArgCaseHasGI, ArgCaseHasGI> MsgBaseCaseHasGI;

typedef basic::test::msg::Argument<CaseHITa,
    ArgTypeName<ITSingleton>,
    ArgTypeFunction<IValFuncBoolToCString, 
        ArgTypeIndex<IValSeqBoolHITa, 
            basic::test::msg::arg::val::seq::At>>> ArgCaseHITa;

typedef basic::test::msg::Base<CaseHITa, char, ArgCaseHITa, 
    ArgCaseHITa, ArgCaseHITa> MsgBaseCaseHITa;
    
typedef basic::test::msg::Argument<CaseGITa,
    ArgTypeName<ITSingleton>,
    ArgValue<IValVoidPtrGITa>,
    ArgTypeFunction<IValFuncBoolToCString, 
        ArgValue<IValBoolGITa>>> ArgCaseGITa;

typedef basic::test::msg::Base<CaseGITa, char, ArgCaseGITa, 
    ArgCaseGITa, ArgCaseGITa> MsgBaseCaseGITa;

typedef basic::test::msg::Argument<CaseCI,
    ArgTypeName<ITSingleton>> ArgCaseCI;

typedef basic::test::msg::Base<CaseCI, char, ArgCaseCI, 
    ArgCaseCI, ArgCaseCI> MsgBaseCaseCI;

typedef basic::test::msg::Argument<CaseDI,
    ArgTypeName<ITSingleton>> ArgCaseDI;

typedef basic::test::msg::Base<CaseDI, char, ArgCaseDI, 
    ArgCaseDI, ArgCaseDI> MsgBaseCaseDI;
    
template<typename T, typename... Targs>
constexpr auto HasConstructInstance(int) ->
    decltype(T::ConstructInstance(std::declval<Targs>()...), 
        std::true_type());
template<typename T, typename... Targs>
constexpr std::false_type HasConstructInstance(...);

template<typename T>
constexpr auto HasDestroyInstance(int) ->
    decltype(T::DestroyInstance(), std::true_type());
template<typename T>
constexpr std::false_type HasDestroyInstance(...);

template<typename T>
constexpr auto HasHasInstance(int) ->
    decltype(T::HasInstance(), std::true_type());
template<typename T>
constexpr std::false_type HasHasInstance(...);

template<typename T>
constexpr auto HasGetInstance(int) ->
    decltype(T::GetInstance(), std::true_type());
template<typename T>
constexpr std::false_type HasGetInstance(...);

template<typename Tptr>
void* ToVoidPtr(Tptr t)
{
    Tptr * tp = &t;
    void ** vp = reinterpret_cast<void**>(tp);
    return *vp;
} 

template<typename TCases, typename... TVars>
class TestSingleton :
    public MsgBaseCaseHasCI,
    public MsgBaseCaseHasDI,
    public MsgBaseCaseHasHI,
    public MsgBaseCaseHasGI,
    public MsgBaseCaseHITa,
    public MsgBaseCaseGITa,
    public MsgBaseCaseCI,
    public MsgBaseCaseDI,
    public basic::test::Message<BASIC_TEST, TestSingleton<TCases, TVars...>>,
    public basic::test::Case<TestSingleton<TCases, TVars...>, TCases>,
    public basic::test::Base<TestSingleton<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestSingleton<TCases, TVars...>, TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestSingleton<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestSingleton<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseHasCI::SetFormat;
    using MsgBaseCaseHasDI::SetFormat;
    using MsgBaseCaseHasHI::SetFormat;
    using MsgBaseCaseHasGI::SetFormat;
    using MsgBaseCaseHITa::SetFormat;
    using MsgBaseCaseGITa::SetFormat;
    using MsgBaseCaseCI::SetFormat;
    using MsgBaseCaseDI::SetFormat;
public:
    using MsgBaseCaseHasCI::Format;
    using MsgBaseCaseHasDI::Format;
    using MsgBaseCaseHasHI::Format;
    using MsgBaseCaseHasGI::Format;
    using MsgBaseCaseHITa::Format;
    using MsgBaseCaseGITa::Format;
    using MsgBaseCaseCI::Format;
    using MsgBaseCaseDI::Format;
    using MsgBaseCaseHasCI::Argument;
    using MsgBaseCaseHasDI::Argument;
    using MsgBaseCaseHasHI::Argument;
    using MsgBaseCaseHasGI::Argument;
    using MsgBaseCaseHITa::Argument;
    using MsgBaseCaseGITa::Argument;
    using MsgBaseCaseCI::Argument;
    using MsgBaseCaseDI::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestSingleton(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseHasCI case_has_ConstructInstance;
        SetFormat(info, case_has_ConstructInstance, 
            "test compare between decltype("
            "HasConstructInstance<%s>(0))::value and %s\n");
        SetFormat(debug, case_has_ConstructInstance,
            "test compare between decltype("
            "HasConstructInstance<%s>(0))::value and %s\n");
        SetFormat(error, case_has_ConstructInstance,
            "error decltype(HasConstructInstance<%s>(0))::value "
            "is not same with %s\n");

        CaseHasDI case_has_DestroyInstance;
        SetFormat(info, case_has_DestroyInstance,
            "test compare between decltype("
            "HasDestroyInstance<%s>(0))::value and %s\n");
        SetFormat(debug, case_has_DestroyInstance,
            "test compare between decltype("
            "HasDestroyInstance<%s>(0))::value and %s\n");
        SetFormat(error, case_has_DestroyInstance,
            "error decltype(HasDestroyInstance<%s>(0))::value "
            "is not same with %s\n");

        CaseHasHI case_has_HasInstance;
        SetFormat(info, case_has_HasInstance, 
            "test compare between decltype("
            "HasHasInstance<%s>(0))::value and %s\n");
        SetFormat(debug, case_has_HasInstance,
            "test compare between decltype("
            "HasHasInstance<%s>(0))::value and %s\n");
        SetFormat(error, case_has_HasInstance,
            "error decltype(HasHasInstance<%s>(0))::value "
            "is not same with %s\n");

        CaseHasGI case_has_GetInstance;
        SetFormat(info, case_has_GetInstance, 
            "test compare between decltype("
            "HasGetInstance<%s>(0))::value and %s\n");
        SetFormat(debug, case_has_GetInstance,
            "test compare between decltype("
            "HasGetInstance<%s>(0))::value and %s\n");
        SetFormat(error, case_has_GetInstance,
            "error decltype(HasGetInstance<%s>(0))::value "
            "is not same with %s\n");

        CaseHITa case_HasInstance_and_target;
        SetFormat(info, case_HasInstance_and_target, 
            "test compare between %s::HasInstance() and %s\n");
        SetFormat(debug, case_HasInstance_and_target, 
            "test compare between %s::HasInstance() and %s\n");
        SetFormat(error, case_HasInstance_and_target,
            "error %s::HasInstance() is not same with %s\n");

        CaseGITa case_GetInstance_and_target;
        SetFormat(info, case_GetInstance_and_target, 
            "test compare between pointer of %s::GetInstance() "
            "== %p and %s\n");
        SetFormat(debug, case_GetInstance_and_target, 
            "test compare between pointer of %s::GetInstance() "
            "== %p and %s\n");
        SetFormat(error, case_GetInstance_and_target,
            "error pointer of %s::GetInstance() == %p is not same with %s\n");
            
        CaseCI case_ConstructInstance;
        SetFormat(info, case_ConstructInstance, 
            "Test ConstructInstance of %s\n");
        SetFormat(debug, case_ConstructInstance, 
            "Test ConstructInstance of %s\n");
        SetFormat(error, case_ConstructInstance,  
            "error ConstructInstance of %s\n");
        
        CaseDI case_DestroyInstance;
        SetFormat(info, case_DestroyInstance, 
            "Test DestroyInstance of %s\n");
        SetFormat(debug, case_DestroyInstance, 
            "Test DestroyInstance of %s\n");
        SetFormat(error, case_DestroyInstance, 
            "error ConstructInstance of %s\n");
    }

    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseHasCI&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        return decltype(HasConstructInstance<TSingleton, TArgs...>(0))
            ::value == basic::test::var::At<IValBoolHasCI>(var).Get().Get();
    }

    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseHasDI&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        return decltype(HasDestroyInstance<TSingleton>(0))::value == 
            basic::test::var::At<IValBoolHasDI>(var).Get().Get();
    }

    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseHasHI&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        return decltype(HasDestroyInstance<TSingleton>(0))::value == 
            basic::test::var::At<IValBoolHasHI>(var).Get().Get();
    }

    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseHasGI&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        return decltype(HasDestroyInstance<TSingleton>(0))::value == 
            basic::test::var::At<IValBoolHasGI>(var).Get().Get();
    }

    template<std::size_t I, typename TSingleton, std::size_t SCaseHIT, 
        typename TGetInstance, typename... TArgs>
    bool Result(const basic::test::type::Index<CaseHITa, I>&, 
        VariableTestSingleton<TSingleton, SCaseHIT, TGetInstance, 
            TArgs...>& var)
    {
        return TSingleton::HasInstance() == basic::test::var::
            At<IValSeqBoolHITa>(var).Get().template At<I>();
    }
    
    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseGITa&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        return ((basic::test::var::At<IValGIToVoidPTr>(var).
            Get().Get())(TSingleton::GetInstance()) == basic::test::var::
                At<IValVoidPtrGITa>(var).Get().Get()) == basic::test::var::
                    At<IValBoolGITa>(var).Get().Get();
    }
    
    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseCI&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        TGetInstance& instance = basic::test::var::
            At<IValParamCI>(var).Get().template Fill<TGetInstance&>(
                &TSingleton::template ConstructInstance<TGetInstance, 
                    TArgs...>);
        return true;
    }

    template<typename TSingleton, std::size_t SCaseHIT, typename TGetInstance, 
        typename... TArgs>
    bool Result(const CaseDI&, VariableTestSingleton<TSingleton, SCaseHIT,
        TGetInstance, TArgs...>& var)
    {
        TSingleton::DestroyInstance();
        return true;
    }
};

const char* true_cstr = "true";
const char* false_cstr = "false";

const char* BoolToString(bool&& b)
{
    return b ? true_cstr : false_cstr;
}

template<typename... TArgs>
basic::test::CString<char> ParamHasCIToCString(basic::test::
    CString<char>&& singleton_cstr, TArgs&&...)
{
    if (sizeof...(TArgs) > 0)
    {
        basic::test::CString<char> args_cstr = std::move(basic::test::type::
            param::Name<basic::test::type::Parameter<TArgs...>>::CStr());
        return std::move(basic::test::cstr::Format(singleton_cstr.Size() +
            args_cstr.Size() + 1, "%s, %s", *singleton_cstr, *args_cstr));
    }
    else
        return std::move(singleton_cstr);
}

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("int", int);

class Value
{
private:
    int m_value;
public:
    Value() : m_value(0) {}
    Value(const int& val) : m_value(val){}
public:
    int& GetValue() {return m_value;}
    const int& GetValue() const {return m_value;} 
};

class A : 
    public Value,
    public basic::Singleton<A>
{
    friend basic::Singleton<A>;
private:
    A() {}
};

void* AToPtr(A& a)
{
    return &a;
}

BASIC_TEST_TYPE_NAME("A", A);

typedef VariableTestSingleton<A, 3, A> T1Var;

typedef basic::test::type::Parameter<
    CaseHasCI,
    CaseHasDI,
    CaseHasGI,
    CaseHasHI,
    basic::test::type::Index<CaseHITa, 0>,
    CaseCI,
    basic::test::type::Index<CaseHITa, 1>,
    CaseGITa,
    CaseDI,
    basic::test::type::Index<CaseHITa, 2>> T1Cases;

T1Var t1_var1(true, true, true, true, false, true, false, false, 
    nullptr, &AToPtr, &ParamHasCIToCString<>, &BoolToString);

REGISTER_TEST(t1, new TestSingleton<T1Cases, T1Var>(t1_var1));

class B :
    public Value,
    public basic::Singleton<B>
{
    friend basic::Singleton<B>;
private:
    static void Construct(void * p)
    {
        new (p) B(4);
    }
private:
    B(int i) : Value(i) {}
};

BASIC_TEST_TYPE_NAME("B", B);

void* BToPtr(B& b)
{
    return &b;
}

typedef VariableTestSingleton<B, 3, B, int> T2Var;

typedef basic::test::type::Parameter<
    CaseHasCI,
    CaseHasDI,
    CaseHasGI,
    CaseHasHI,
    basic::test::type::Index<CaseHITa, 0>,
    CaseCI,
    basic::test::type::Index<CaseHITa, 1>,
    CaseGITa,
    CaseDI,
    basic::test::type::Index<CaseHITa, 2>> T2Cases;

T2Var t2_var1(true, true, true, true, false, true, false, false, 
    nullptr, &BToPtr, &ParamHasCIToCString<int>, &BoolToString, 4);

REGISTER_TEST(t2, new TestSingleton<T2Cases, T2Var>(t2_var1));

class C :
    public Value,
    public basic::Singleton<C*>
{
    friend basic::Singleton<C*>;
private:
    static void Construct(void * p)
    {
        new (p) C*(new C);
    }
    static void Destroy(C** p)
    {
        delete *p;
    }
    C() {}
};

BASIC_TEST_TYPE_NAME("C", C);

void* CToPtr(C*& c)
{
    return c;
}

typedef VariableTestSingleton<C, 3, C*> T3Var;

typedef basic::test::type::Parameter<
    CaseHasCI,
    CaseHasDI,
    CaseHasGI,
    CaseHasHI,
    basic::test::type::Index<CaseHITa, 0>,
    CaseCI,
    basic::test::type::Index<CaseHITa, 1>,
    CaseGITa,
    CaseDI,
    basic::test::type::Index<CaseHITa, 2>> T3Cases;

T3Var t3_var1(true, true, true, true, false, true, false, false, 
    nullptr, &CToPtr, &ParamHasCIToCString<>, &BoolToString);

REGISTER_TEST(t3, new TestSingleton<T3Cases, T3Var>(t3_var1));

class D:
    public Value,
    public basic::Singleton<const D>
{
    friend basic::Singleton<const D>;
private:
    D() : Value(14) {}
};

BASIC_TEST_TYPE_NAME("D", D);

void* DToPtr(const D& d)
{
    return const_cast<D*>(&d);
}

typedef VariableTestSingleton<D, 3, const D> T4Var;

typedef basic::test::type::Parameter<
    CaseHasCI,
    CaseHasDI,
    CaseHasGI,
    CaseHasHI,
    basic::test::type::Index<CaseHITa, 0>,
    CaseCI,
    basic::test::type::Index<CaseHITa, 1>,
    CaseGITa,
    CaseDI,
    basic::test::type::Index<CaseHITa, 2>> T4Cases;

T4Var t4_var1(true, true, true, true, false, true, false, false, 
    nullptr, &DToPtr, &ParamHasCIToCString<>, &BoolToString);

REGISTER_TEST(t4, new TestSingleton<T4Cases, T4Var>(t4_var1));

class E:
    public Value,
    public basic::Singleton<const E>
{
public:
    typedef basic::type::access::Protected AccessConstructInstanceType;
    typedef basic::type::access::Protected AccessDestroyInstanceType;
private:
    friend basic::Singleton<const E>;
private:
    E() : Value(4) {}
};

BASIC_TEST_TYPE_NAME("E", E);

void* EToPtr(const E& e)
{
    return const_cast<E*>(&e);
}

typedef VariableTestSingleton<E, 2, const E> T5Var;

typedef basic::test::type::Parameter<
    CaseHasCI,
    CaseHasDI,
    CaseHasGI,
    CaseHasHI,
    basic::test::type::Index<CaseHITa, 0>,
    CaseGITa,
    basic::test::type::Index<CaseHITa, 1>> T5Cases;

T5Var t5_var1(false, false, false, false, false, true, false, 
    nullptr, &EToPtr, &ParamHasCIToCString<>, &BoolToString);

REGISTER_TEST(t5, new TestSingleton<T5Cases, T5Var>(t5_var1));

class F:
    public Value,
    public basic::Singleton<const F>
{
public:
    typedef basic::type::access::Private AccessConstructInstanceType;
    typedef basic::type::access::Private AccessDestroyInstanceType;
    typedef basic::type::access::Protected AccessHasInstanceType;
    typedef basic::type::access::Protected AccessGetInstanceType;
private:
    friend basic::Singleton<const F>;
private:
    F() : Value(4) {}
};

BASIC_TEST_TYPE_NAME("F", F);

typedef VariableTestSingleton<F, 0, const F> T6Var;

typedef basic::test::type::Parameter<
    CaseHasCI,
    CaseHasDI,
    CaseHasGI,
    CaseHasHI> T6Cases;

T6Var t6_var1(false, false, false, false, false, 
    nullptr, nullptr, &ParamHasCIToCString<>, &BoolToString);

REGISTER_TEST(t6, new TestSingleton<T6Cases, T6Var>(t6_var1));

int main()
{
    return RUN_TEST();
}

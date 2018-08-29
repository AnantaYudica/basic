#include "Singleton.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"

BasicTest& bt = BasicTest::ms_instance;

#include <vector>
#include <type_traits>
#include <sstream>
#include <iostream>

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

struct BaseTest
{
    BaseTest() {}
    virtual ~BaseTest() {}
    virtual void Test() = 0;
};

struct TestRegister
{
    static std::vector<BaseTest*> List;
    BaseTest* m_ptr;
    TestRegister(BaseTest* ptr) :
        m_ptr(ptr)
    {
        List.push_back(ptr);
    }
    ~TestRegister()
    {
        delete m_ptr;
    }
};

std::vector<BaseTest*> TestRegister::List;

template<typename... Targs>
struct ParameterValue
{
    ParameterValue()
    {}
    template<typename Tr, typename... Targs0, typename... Targs1>
    Tr Filler(Tr(*foo)(Targs0...), Targs1&&... values)
    {
        return foo(std::forward<Targs1>(values)...);
    }

    template<typename Tr, typename... Targs0>
    Tr Fill(Tr(*foo)(Targs0...))
    {
        return Filler<Tr, Targs0...>(foo);
    }
};

template<typename Targ, typename... Targs>
struct ParameterValue<Targ, Targs...> :
    ParameterValue<Targs...>
{
    Targ m_value;
    ParameterValue(Targ arg, Targs... args) :
        ParameterValue<Targs...>(args...),
        m_value(arg)
    {}

    template<typename Tr, typename... Targs0, typename... Targs1>
    Tr Filler(Tr(*foo)(Targs0...), Targs1&&... values)
    {
        return ParameterValue<Targs...>::template
            Filler<Tr, Targs0...>(foo, std::forward<Targs1>(values)..., 
                std::forward<Targ>(m_value));
    }

    template<typename Tr, typename... Targs0>
    Tr Fill(Tr(*foo)(Targs0...))
    {
        return Filler<Tr, Targs0...>(foo);
    }
};

template<typename Targ>
struct ParameterValue<Targ>
{
    Targ m_value;
    ParameterValue(Targ arg) :
        m_value(arg)
    {}
    template<typename Tr, typename... Targs0, typename... Targs1>
    Tr Filler(Tr(*foo)(Targs0...), Targs1&&... values)
    {
        return foo(std::forward<Targs1>(values)..., 
            std::forward<Targ>(m_value));
    }

    template<typename Tr, typename... Targs0>
    Tr Fill(Tr(*foo)(Targs0...))
    {
        return Filler<Tr, Targs0...>(foo);
    }
};

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

template<typename T, typename Tt, Tt TtValue, typename... Targs>
void TestHasConstructInstance()
{
    std::string error_msg = "decltype(HasConstructInstance<";
    error_msg += Name<T>::Value;
    error_msg += ",";
    NameParameterTmpl<Targs...>::String(error_msg);
    error_msg += ">(0))::value is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += "decltype(HasConstructInstance<";
    info_msg += Name<T>::Value;
    info_msg += ",";
    NameParameterTmpl<Targs...>::String(info_msg);
    info_msg += ">(0)))::value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        decltype(HasConstructInstance<T, Targs...>(0))::value == TtValue))
            Info("Pass\n");
}

template<typename T, typename Tt, Tt TtValue>
void TestHasDestroyInstance()
{
    std::string error_msg = "decltype(HasDestroyInstance<";
    error_msg += Name<T>::Value;
    error_msg += ">(0))::value is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += "decltype(HasDestroyInstance<";
    info_msg += Name<T>::Value;
    info_msg += ">(0)))::value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        decltype(HasDestroyInstance<T>(0))::value == TtValue))
            Info("Pass\n");
}

template<typename T, typename Tt, Tt TtValue>
void TestHasHasInstance()
{
    std::string error_msg = "decltype(HasHasInstance<";
    error_msg += Name<T>::Value;
    error_msg += ">(0))::value is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += "decltype(HasHasInstance<";
    info_msg += Name<T>::Value;
    info_msg += ">(0)))::value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        decltype(HasHasInstance<T>(0))::value == TtValue))
            Info("Pass\n");
}

template<typename T, typename Tt, Tt TtValue>
void TestHasGetInstance()
{
    std::string error_msg = "decltype(HasGetInstance<";
    error_msg += Name<T>::Value;
    error_msg += ">(0))::value is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += "decltype(HasGetInstance<";
    info_msg += Name<T>::Value;
    info_msg += ">(0)))::value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        decltype(HasGetInstance<T>(0))::value == TtValue))
            Info("Pass\n");
}

template<typename T, typename Tt, Tt TtValue>
void TestCompareHasInstance()
{
    std::string error_msg = Name<T>::Value;
    error_msg += "::HasInstance() is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<T>::Value;
    info_msg += "::HasInstance() and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        T::HasInstance() == TtValue))
            Info("Pass\n");
}

template<typename T, typename Tr, T*(*ToPtr)(Tr&),
    typename Tt = bool, Tt TtValue = true>
void TestCompareGetInstance(T* Tptr)
{
    std::string error_msg = "&";
    error_msg += Name<T>::Value;
    error_msg += "::GetInstance() is not same with ";
    ToString(Tptr, error_msg);
    std::string info_msg = "Test compare between ";
    info_msg += Name<T>::Value;
    info_msg += "::GetInstance() and ";
    ToString(Tptr, info_msg);
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        (ToPtr(T::GetInstance()) == Tptr) == TtValue))
            Info("Pass\n");
}

template<typename Ts, typename Tt, Tt TtValueCI, Tt TtValueDI,
    Tt TtValueHI, Tt TtValueGI, typename... Targs>
struct TestSingletonHasMember : BaseTest
{
    void Test() 
    {
        TestHasConstructInstance<Ts, Tt, TtValueCI, Targs...>();
        TestHasDestroyInstance<Ts, Tt, TtValueDI>();
        TestHasHasInstance<Ts, Tt, TtValueHI>();
        TestHasGetInstance<Ts, Tt, TtValueGI>();
    };
};

template<typename Ts, typename Tt, Tt TtValue>
struct TestSingletonHasInstance : BaseTest
{
    void Test() 
    {
        TestCompareHasInstance<Ts, Tt, TtValue>();
    }
};

template<typename Ts, typename Tr, Ts*(*ToPtr)(Tr&),
     typename... Targs>
struct TestSingletonConstructInstance : BaseTest
{
    ParameterValue<Targs...> m_paramVal;
    TestSingletonConstructInstance(Targs... args) :
        m_paramVal(args...)
    {}
    void Test() 
    {
        Tr& instance = m_paramVal.template Fill<Tr&>(
            &Ts::template ConstructInstance<Tr, Targs...>);
        TestCompareGetInstance<Ts, Tr, ToPtr>(ToPtr(instance));
    };
};

template<typename Ts, typename Tt, Tt TtValue>
struct TestSingletonDestroyInstance : BaseTest
{
    void Test()
    {
        Ts::DestroyInstance();
        TestCompareHasInstance<Ts, Tt, TtValue>();
    }
};

template<typename Ts, typename Tr, Ts*(*ToPtr)(Tr&),
    typename Tt, Tt TtValue>
struct TestSingletonGetInstance : BaseTest
{
    Ts* m_ptr;
    TestSingletonGetInstance(Ts* ptr) :
        m_ptr(ptr)
    {}
    void Test() 
    {
        TestCompareGetInstance<Ts, Tr, ToPtr, Tt, TtValue>(m_ptr);
    };
};

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

A* AToPtr(A& a)
{
    return &a;
}

__DEFINE_NAME_(A);

TestRegister t1_1(new TestSingletonHasMember<A, bool, true, true, 
    true, true>());
TestRegister t1_2(new TestSingletonHasInstance<A, bool, false>());
TestRegister t1_3(new TestSingletonConstructInstance<A, A, &AToPtr>());
TestRegister t1_4(new TestSingletonHasInstance<A, bool, true>());
TestRegister t1_5(new TestSingletonDestroyInstance<A, bool, false>());

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

__DEFINE_NAME_(B);

B* BToPtr(B& b)
{
    return &b;
}

TestRegister t2_1(new TestSingletonHasMember<B, bool, true, true, 
    true, true>());
TestRegister t2_2(new TestSingletonHasInstance<B, bool, false>());
TestRegister t2_3(new TestSingletonConstructInstance<B, B, &BToPtr, int>(4));
TestRegister t2_4(new TestSingletonHasInstance<B, bool, true>());
TestRegister t2_5(new TestSingletonDestroyInstance<B, bool, false>());

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

__DEFINE_NAME_(C);

C* CToPtr(C*& c)
{
    return c;
}

TestRegister t3_1(new TestSingletonHasMember<C, bool, true, true, 
    true, true>());
TestRegister t3_2(new TestSingletonHasInstance<C, bool, false>());
TestRegister t3_3(new TestSingletonConstructInstance<C, C*, &CToPtr>());
TestRegister t3_4(new TestSingletonHasInstance<C, bool, true>());
TestRegister t3_5(new TestSingletonDestroyInstance<C, bool, false>());


class D:
    public Value,
    public basic::Singleton<const D>
{
    friend basic::Singleton<const D>;
private:
    D() : Value(14) {}
};

__DEFINE_NAME_(D);

D* DToPtr(const D& d)
{
    return const_cast<D*>(&d);
}

TestRegister t4_1(new TestSingletonHasMember<D, bool, true, true, 
    true, true>());
TestRegister t4_2(new TestSingletonHasInstance<D, bool, false>());
TestRegister t4_3(new TestSingletonConstructInstance<D, const D, &DToPtr>());
TestRegister t4_4(new TestSingletonHasInstance<D, bool, true>());
TestRegister t4_5(new TestSingletonDestroyInstance<D, bool, false>());

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

__DEFINE_NAME_(E);

E* EToPtr(const E& e)
{
    return const_cast<E*>(&e);
}

TestRegister t5_1(new TestSingletonHasMember<E, bool, false, false, 
    true, true>());
TestRegister t5_2(new TestSingletonHasInstance<E, bool, false>());
TestRegister t5_3(new TestSingletonGetInstance<E, const E,
    &EToPtr, bool, false>(nullptr));
TestRegister t5_4(new TestSingletonHasInstance<E, bool, true>());


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

__DEFINE_NAME_(F);

TestRegister t6_1(new TestSingletonHasMember<F, bool, false, false, 
    false, false>());

int main()
{
    Info("BeginTest:\n");
    for (auto t : TestRegister::List)
    {
        t->Test();
    }
    Info("EndTest:\n");
    return  ResultStatus;
}

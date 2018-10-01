#include "type/Name.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <type_traits>

struct CaseTSTa {}; // case ToString and target

template<template<typename> class TTName, typename T>
using VariableTestName = basic::test::Variable<
    TTName<T>, 
    T>;

constexpr std::size_t ITName = 0;
constexpr std::size_t IT = 1;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

typedef basic::test::msg::Argument<CaseTSTa, 
    ArgTypeName<ITName>,
    ArgTypeName<IT>> ArgCaseTSTa;

typedef basic::test::msg::Base<CaseTSTa, char, ArgCaseTSTa, 
    ArgCaseTSTa, ArgCaseTSTa> MsgBaseCaseTSTa;

template<typename TCases, typename... TVars>
class TestName :
    public MsgBaseCaseTSTa,
    public basic::test::Message<BASIC_TEST, TestName<TCases, TVars...>>,
    public basic::test::Case<TestName<TCases, TVars...>, TCases>,
    public basic::test::Base<TestName<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestName<TCases, TVars...>, TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestName<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestName<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseTSTa::SetFormat;
public:
    using MsgBaseCaseTSTa::Format;
    using MsgBaseCaseTSTa::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestName(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseTSTa case_ToString_and_target;
        SetFormat(info, case_ToString_and_target, 
            "test compare between %s::ToString() and \"%s\"\n");
        SetFormat(debug, case_ToString_and_target, 
            "test compare between %s::ToString() and \"%s\"\n");
        SetFormat(error, case_ToString_and_target,
            "error %s::ToString() is not same with \"%s\"\n");
    }

    template<template<typename> class TTName, typename T>
    bool Result(const CaseTSTa&, VariableTestName<TTName, T>& var)
    {
        return TTName<T>::ToString().compare(*basic::test::type::
            Name<T>::CStr()) == 0;
    }
};

using Cases = basic::test::type::Parameter<CaseTSTa>;

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);

template<typename T>
struct basic::test::type::Name<basic::type::Name<T>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "basic::type::Name<%s>";
        const auto& arg1_cstr = basic::test::type::Name<T>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            arg1_cstr.Size(), _format_cstr, *arg1_cstr);
    }
};

struct A
{};

std::ostream& operator<<(std::ostream& o, basic::type::name::Type<A>&&)
{
    o << "A";
    return o;
}


template<typename T>
using TName = basic::type::Name<T>;

BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("std::nullptr_t", std::nullptr_t);
BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("short", short);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("const int", const int);
BASIC_TEST_TYPE_NAME("volatile int", volatile int);
BASIC_TEST_TYPE_NAME("const volatile int", const volatile int);
BASIC_TEST_TYPE_NAME("long", long);
BASIC_TEST_TYPE_NAME("long long", long long);
BASIC_TEST_TYPE_NAME("unsigned char", unsigned char);
BASIC_TEST_TYPE_NAME("unsigned short", unsigned short);
BASIC_TEST_TYPE_NAME("unsigned int", unsigned int);
BASIC_TEST_TYPE_NAME("unsigned long", unsigned long);
BASIC_TEST_TYPE_NAME("unsigned long long", unsigned long long);
BASIC_TEST_TYPE_NAME("float", float);
BASIC_TEST_TYPE_NAME("double", double);
BASIC_TEST_TYPE_NAME("long double", long double);

typedef VariableTestName<TName, void> T1Var1;
typedef VariableTestName<TName, std::nullptr_t> T1Var2;
typedef VariableTestName<TName, char> T1Var3;
typedef VariableTestName<TName, short> T1Var4;
typedef VariableTestName<TName, int> T1Var5;
typedef VariableTestName<TName, const int> T1Var6;
typedef VariableTestName<TName, volatile int> T1Var7;
typedef VariableTestName<TName, const volatile int> T1Var8;
typedef VariableTestName<TName, long> T1Var9;
typedef VariableTestName<TName, long long> T1Var10;
typedef VariableTestName<TName, unsigned char> T1Var11;
typedef VariableTestName<TName, unsigned short> T1Var12;
typedef VariableTestName<TName, unsigned int> T1Var13;
typedef VariableTestName<TName, unsigned long> T1Var14;
typedef VariableTestName<TName, unsigned long long> T1Var15;
typedef VariableTestName<TName, float> T1Var16;
typedef VariableTestName<TName, double> T1Var17;
typedef VariableTestName<TName, long double> T1Var18;

T1Var1 t1_var1;
T1Var2 t1_var2;
T1Var3 t1_var3;
T1Var4 t1_var4;
T1Var5 t1_var5;
T1Var6 t1_var6;
T1Var7 t1_var7;
T1Var8 t1_var8;
T1Var9 t1_var9;
T1Var10 t1_var10;
T1Var11 t1_var11;
T1Var12 t1_var12;
T1Var13 t1_var13;
T1Var14 t1_var14;
T1Var15 t1_var15;
T1Var16 t1_var16;
T1Var17 t1_var17;
T1Var18 t1_var18;

REGISTER_TEST(t1, new TestName<Cases, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var9, T1Var10, T1Var11, T1Var12,
    T1Var13, T1Var14, T1Var15, T1Var16, T1Var17, T1Var18>(t1_var1, 
        t1_var2, t1_var3, t1_var4, t1_var5, t1_var6, t1_var7, t1_var8,
        t1_var9, t1_var10, t1_var11, t1_var12, t1_var13, t1_var14, 
        t1_var15, t1_var16, t1_var17, t1_var18));

BASIC_TEST_TYPE_NAME("int&", int&);
BASIC_TEST_TYPE_NAME("const int&", const int&);
BASIC_TEST_TYPE_NAME("volatile int&", volatile int&);
BASIC_TEST_TYPE_NAME("const volatile int&", const volatile int&);

typedef VariableTestName<TName, int&> T2Var1;
typedef VariableTestName<TName, const int&> T2Var2;
typedef VariableTestName<TName, volatile int&> T2Var3;
typedef VariableTestName<TName, const volatile int&> T2Var4;

T2Var1 t2_var1;
T2Var2 t2_var2;
T2Var3 t2_var3;
T2Var4 t2_var4;

REGISTER_TEST(t2, new TestName<Cases, T2Var1, T2Var2, T2Var3, 
    T2Var4>(t2_var1, t2_var2, t2_var3, t2_var4));

BASIC_TEST_TYPE_NAME("int&&", int&&);
BASIC_TEST_TYPE_NAME("const int&&", const int&&);
BASIC_TEST_TYPE_NAME("volatile int&&", volatile int&&);
BASIC_TEST_TYPE_NAME("const volatile int&&", const volatile int&&);

typedef VariableTestName<TName, int&&> T3Var1;
typedef VariableTestName<TName, const int&&> T3Var2;
typedef VariableTestName<TName, volatile int&&> T3Var3;
typedef VariableTestName<TName, const volatile int&&> T3Var4;

T3Var1 t3_var1;
T3Var2 t3_var2;
T3Var3 t3_var3;
T3Var4 t3_var4;

REGISTER_TEST(t3, new TestName<Cases, T3Var1, T3Var2, T3Var3, 
    T3Var4>(t3_var1, t3_var2, t3_var3, t3_var4));
    
BASIC_TEST_TYPE_NAME("int*", int*);
BASIC_TEST_TYPE_NAME("const int*", const int*);
BASIC_TEST_TYPE_NAME("volatile int*", volatile int*);
BASIC_TEST_TYPE_NAME("const volatile int*", const volatile int*);
BASIC_TEST_TYPE_NAME("int*const", int*const);
BASIC_TEST_TYPE_NAME("int*volatile", int*volatile);
BASIC_TEST_TYPE_NAME("int*const volatile", int*const volatile);

typedef VariableTestName<TName, int*> T4Var1;
typedef VariableTestName<TName, const int*> T4Var2;
typedef VariableTestName<TName, volatile int*> T4Var3;
typedef VariableTestName<TName, const volatile int*> T4Var4;
typedef VariableTestName<TName, int*const> T4Var5;
typedef VariableTestName<TName, int*volatile> T4Var6;
typedef VariableTestName<TName, int*const volatile> T4Var7;

T4Var1 t4_var1;
T4Var2 t4_var2;
T4Var3 t4_var3;
T4Var4 t4_var4;
T4Var5 t4_var5;
T4Var6 t4_var6;
T4Var7 t4_var7;

REGISTER_TEST(t4, new TestName<Cases, T4Var1, T4Var2,
    T4Var3, T4Var4, T4Var5, T4Var6, T4Var7>(t4_var1, t4_var2, t4_var3, 
        t4_var4, t4_var5, t4_var6, t4_var7));

BASIC_TEST_TYPE_NAME("int**", int**);
BASIC_TEST_TYPE_NAME("const int**", const int**);
BASIC_TEST_TYPE_NAME("volatile int**", volatile int**);
BASIC_TEST_TYPE_NAME("const volatile int**", const volatile int**);
BASIC_TEST_TYPE_NAME("int**const", int**const);
BASIC_TEST_TYPE_NAME("int**volatile", int**volatile);
BASIC_TEST_TYPE_NAME("int**const volatile", int**const volatile);
BASIC_TEST_TYPE_NAME("int*const*", int*const*);
BASIC_TEST_TYPE_NAME("int*const*const", int*const*const);
BASIC_TEST_TYPE_NAME("int*const*volatile", int*const*volatile);
BASIC_TEST_TYPE_NAME("int*const*const volatile", int*const*const volatile);
BASIC_TEST_TYPE_NAME("int*volatile*", int*volatile*);
BASIC_TEST_TYPE_NAME("int*volatile*const", int*volatile*const);
BASIC_TEST_TYPE_NAME("int*volatile*volatile", int*volatile*volatile);
BASIC_TEST_TYPE_NAME("int*volatile*const volatile", int*volatile*const volatile);
BASIC_TEST_TYPE_NAME("int*const volatile*", int*const volatile*);
BASIC_TEST_TYPE_NAME("int*const volatile*const", int*const volatile*const);
BASIC_TEST_TYPE_NAME("int*const volatile*volatile", int*const volatile*volatile);
BASIC_TEST_TYPE_NAME("int*const volatile*const volatile", int*const volatile*const volatile);

typedef VariableTestName<TName, int**> T5Var1;
typedef VariableTestName<TName, const int**> T5Var2;
typedef VariableTestName<TName, volatile int**> T5Var3;
typedef VariableTestName<TName, const volatile int**> T5Var4;
typedef VariableTestName<TName, int**const> T5Var5;
typedef VariableTestName<TName, int**volatile> T5Var6;
typedef VariableTestName<TName, int**const volatile> T5Var7;
typedef VariableTestName<TName, int*const*> T5Var8;
typedef VariableTestName<TName, int*const*const> T5Var9;
typedef VariableTestName<TName, int*const*volatile> T5Var10;
typedef VariableTestName<TName, int*const*const volatile> T5Var11;
typedef VariableTestName<TName, int*volatile*> T5Var12;
typedef VariableTestName<TName, int*volatile*const> T5Var13;
typedef VariableTestName<TName, int*volatile*volatile> T5Var14;
typedef VariableTestName<TName, int*volatile*const volatile> T5Var15;
typedef VariableTestName<TName, int*const volatile*> T5Var16;
typedef VariableTestName<TName, int*const volatile*const> T5Var17;
typedef VariableTestName<TName, int*const volatile*volatile> T5Var18;
typedef VariableTestName<TName, int*const volatile*const volatile> T5Var19;

T5Var1 t5_var1;
T5Var2 t5_var2;
T5Var3 t5_var3;
T5Var4 t5_var4;
T5Var5 t5_var5;
T5Var6 t5_var6;
T5Var7 t5_var7;
T5Var8 t5_var8;
T5Var9 t5_var9;
T5Var10 t5_var10;
T5Var11 t5_var11;
T5Var12 t5_var12;
T5Var13 t5_var13;
T5Var14 t5_var14;
T5Var15 t5_var15;
T5Var16 t5_var16;
T5Var17 t5_var17;
T5Var18 t5_var18;
T5Var19 t5_var19;

REGISTER_TEST(t5, new TestName<Cases, T5Var1, T5Var2,
    T5Var3, T5Var4, T5Var5, T5Var6, T5Var7, T5Var8, T5Var9, T5Var10, T5Var11,
    T5Var12, T5Var13, T5Var14, T5Var15, T5Var16, T5Var17 ,T5Var18, 
    T5Var19>(t5_var1, t5_var2, t5_var3, t5_var4, t5_var5, t5_var6, t5_var7,
        t5_var8, t5_var9, t5_var10, t5_var11, t5_var12, t5_var13, t5_var14, 
        t5_var15, t5_var16, t5_var17, t5_var18, t5_var19));

BASIC_TEST_TYPE_NAME("int[]", int[]);
BASIC_TEST_TYPE_NAME("const int[]", const int[]);
BASIC_TEST_TYPE_NAME("volatile int[]", volatile int[]);
BASIC_TEST_TYPE_NAME("const volatile int[]", const volatile int[]);

typedef VariableTestName<TName, int[]> T6Var1;
typedef VariableTestName<TName, const int[]> T6Var2;
typedef VariableTestName<TName, volatile int[]> T6Var3;
typedef VariableTestName<TName, const volatile int[]> T6Var4;

T6Var1 t6_var1;
T6Var2 t6_var2;
T6Var3 t6_var3;
T6Var4 t6_var4;

REGISTER_TEST(t6, new TestName<Cases, T6Var1, T6Var2,
    T6Var3, T6Var4>(t6_var1, t6_var2, t6_var3, t6_var4));

BASIC_TEST_TYPE_NAME("int(&)[]", int(&)[]);
BASIC_TEST_TYPE_NAME("const int(&)[]", const int(&)[]);
BASIC_TEST_TYPE_NAME("volatile int(&)[]", volatile int(&)[]);
BASIC_TEST_TYPE_NAME("const volatile int(&)[]", const volatile int(&)[]);

typedef VariableTestName<TName, int(&)[]> T7Var1;
typedef VariableTestName<TName, const int(&)[]> T7Var2;
typedef VariableTestName<TName, volatile int(&)[]> T7Var3;
typedef VariableTestName<TName, const volatile int(&)[]> T7Var4;

T7Var1 t7_var1;
T7Var2 t7_var2;
T7Var3 t7_var3;
T7Var4 t7_var4;

REGISTER_TEST(t7, new TestName<Cases, T7Var1, T7Var2,
    T7Var3, T7Var4>(t7_var1, t7_var2, t7_var3, t7_var4));

BASIC_TEST_TYPE_NAME("int(&&)[]", int(&&)[]);
BASIC_TEST_TYPE_NAME("const int(&&)[]", const int(&&)[]);
BASIC_TEST_TYPE_NAME("volatile int(&&)[]", volatile int(&&)[]);
BASIC_TEST_TYPE_NAME("const volatile int(&&)[]", const volatile int(&&)[]);

typedef VariableTestName<TName, int(&&)[]> T8Var1;
typedef VariableTestName<TName, const int(&&)[]> T8Var2;
typedef VariableTestName<TName, volatile int(&&)[]> T8Var3;
typedef VariableTestName<TName, const volatile int(&&)[]> T8Var4;

T8Var1 t8_var1;
T8Var2 t8_var2;
T8Var3 t8_var3;
T8Var4 t8_var4;

REGISTER_TEST(t8, new TestName<Cases, T8Var1, T8Var2,
    T8Var3, T8Var4>(t8_var1, t8_var2, t8_var3, t8_var4));

BASIC_TEST_TYPE_NAME("int(*)[]", int(*)[]);
BASIC_TEST_TYPE_NAME("const int(*)[]", const int(*)[]);
BASIC_TEST_TYPE_NAME("volatile int(*)[]", volatile int(*)[]);
BASIC_TEST_TYPE_NAME("const volatile int(*)[]", const volatile int(*)[]);
BASIC_TEST_TYPE_NAME("int(*const)[]", int(*const)[]);
BASIC_TEST_TYPE_NAME("int(*volatile)[]", int(*volatile)[]);
BASIC_TEST_TYPE_NAME("int(*const volatile)[]", int(*const volatile)[]);

typedef VariableTestName<TName, int(*)[]> T9Var1;
typedef VariableTestName<TName, const int(*)[]> T9Var2;
typedef VariableTestName<TName, volatile int(*)[]> T9Var3;
typedef VariableTestName<TName, const volatile int(*)[]> T9Var4;
typedef VariableTestName<TName, int(*const)[]> T9Var5;
typedef VariableTestName<TName, int(*volatile)[]> T9Var6;
typedef VariableTestName<TName, int(*const volatile)[]> T9Var7;

T9Var1 t9_var1;
T9Var2 t9_var2;
T9Var3 t9_var3;
T9Var4 t9_var4;
T9Var5 t9_var5;
T9Var6 t9_var6;
T9Var7 t9_var7;

REGISTER_TEST(t9, new TestName<Cases, T9Var1, T9Var2,
    T9Var3, T9Var4, T9Var5, T9Var6, T9Var7>(t9_var1, t9_var2, t9_var3, 
        t9_var4, t9_var5, t9_var6, t9_var7));

BASIC_TEST_TYPE_NAME("int(**)[]", int(**)[]);
BASIC_TEST_TYPE_NAME("const int(**)[]", const int(**)[]);
BASIC_TEST_TYPE_NAME("volatile int(**)[]", volatile int(**)[]);
BASIC_TEST_TYPE_NAME("const volatile int(**)[]", const volatile int(**)[]);
BASIC_TEST_TYPE_NAME("int(**const)[]", int(**const)[]);
BASIC_TEST_TYPE_NAME("int(**volatile)[]", int(**volatile)[]);
BASIC_TEST_TYPE_NAME("int(**const volatile)[]", int(**const volatile)[]);
BASIC_TEST_TYPE_NAME("int(*const*)[]", int(*const*)[]);
BASIC_TEST_TYPE_NAME("int(*const*const)[]", int(*const*const)[]);
BASIC_TEST_TYPE_NAME("int(*const*volatile)[]", int(*const*volatile)[]);
BASIC_TEST_TYPE_NAME("int(*const*const volatile)[]", int(*const*const volatile)[]);
BASIC_TEST_TYPE_NAME("int(*volatile*)[]", int(*volatile*)[]);
BASIC_TEST_TYPE_NAME("int(*volatile*const)[]", int(*volatile*const)[]);
BASIC_TEST_TYPE_NAME("int(*volatile*volatile)[]", int(*volatile*volatile)[]);
BASIC_TEST_TYPE_NAME("int(*volatile*const volatile)[]", int(*volatile*const volatile)[]);
BASIC_TEST_TYPE_NAME("int(*const volatile*)[]", int(*const volatile*)[]);
BASIC_TEST_TYPE_NAME("int(*const volatile*const)[]", int(*const volatile*const)[]);
BASIC_TEST_TYPE_NAME("int(*const volatile*volatile)[]", int(*const volatile*volatile)[]);
BASIC_TEST_TYPE_NAME("int(*const volatile*const volatile)[]", int(*const volatile*const volatile)[]);

typedef VariableTestName<TName, int(**)[]> T10Var1;
typedef VariableTestName<TName, const int(**)[]> T10Var2;
typedef VariableTestName<TName, volatile int(**)[]> T10Var3;
typedef VariableTestName<TName, const volatile int(**)[]> T10Var4;
typedef VariableTestName<TName, int(**const)[]> T10Var5;
typedef VariableTestName<TName, int(**volatile)[]> T10Var6;
typedef VariableTestName<TName, int(**const volatile)[]> T10Var7;
typedef VariableTestName<TName, int(*const*)[]> T10Var8;
typedef VariableTestName<TName, int(*const*const)[]> T10Var9;
typedef VariableTestName<TName, int(*const*volatile)[]> T10Var10;
typedef VariableTestName<TName, int(*const*const volatile)[]> T10Var11;
typedef VariableTestName<TName, int(*volatile*)[]> T10Var12;
typedef VariableTestName<TName, int(*volatile*const)[]> T10Var13;
typedef VariableTestName<TName, int(*volatile*volatile)[]> T10Var14;
typedef VariableTestName<TName, int(*volatile*const volatile)[]> T10Var15;
typedef VariableTestName<TName, int(*const volatile*)[]> T10Var16;
typedef VariableTestName<TName, int(*const volatile*const)[]> T10Var17;
typedef VariableTestName<TName, int(*const volatile*volatile)[]> T10Var18;
typedef VariableTestName<TName, int(*const volatile*const volatile)[]> T10Var19;

T10Var1 t10_var1;
T10Var2 t10_var2;
T10Var3 t10_var3;
T10Var4 t10_var4;
T10Var5 t10_var5;
T10Var6 t10_var6;
T10Var7 t10_var7;
T10Var8 t10_var8;
T10Var9 t10_var9;
T10Var10 t10_var10;
T10Var11 t10_var11;
T10Var12 t10_var12;
T10Var13 t10_var13;
T10Var14 t10_var14;
T10Var15 t10_var15;
T10Var16 t10_var16;
T10Var17 t10_var17;
T10Var18 t10_var18;
T10Var19 t10_var19;

REGISTER_TEST(t10, new TestName<Cases, T10Var1, T10Var2,
    T10Var3, T10Var4, T10Var5, T10Var6, T10Var7, T10Var8, T10Var9, T10Var10, 
    T10Var11, T10Var12, T10Var13, T10Var14, T10Var15, T10Var16, T10Var17, 
    T10Var18, T10Var19>(t10_var1, t10_var2, t10_var3, t10_var4, t10_var5, 
        t10_var6, t10_var7, t10_var8, t10_var9, t10_var10, t10_var11, 
        t10_var12, t10_var13, t10_var14, t10_var15, t10_var16, t10_var17, 
        t10_var18, t10_var19));

BASIC_TEST_TYPE_NAME("int[1]", int[1]);
BASIC_TEST_TYPE_NAME("const int[1]", const int[1]);
BASIC_TEST_TYPE_NAME("volatile int[1]", volatile int[1]);
BASIC_TEST_TYPE_NAME("const volatile int[1]", const volatile int[1]);

typedef VariableTestName<TName, int[1]> T11Var1;
typedef VariableTestName<TName, const int[1]> T11Var2;
typedef VariableTestName<TName, volatile int[1]> T11Var3;
typedef VariableTestName<TName, const volatile int[1]> T11Var4;

T11Var1 t11_var1;
T11Var2 t11_var2;
T11Var3 t11_var3;
T11Var4 t11_var4;

REGISTER_TEST(t11, new TestName<Cases, T11Var1, T11Var2,
    T11Var3, T11Var4>(t11_var1, t11_var2, t11_var3, t11_var4));

BASIC_TEST_TYPE_NAME("int(&)[1]", int(&)[1]);
BASIC_TEST_TYPE_NAME("const int(&)[1]", const int(&)[1]);
BASIC_TEST_TYPE_NAME("volatile int(&)[1]", volatile int(&)[1]);
BASIC_TEST_TYPE_NAME("const volatile int(&)[1]", const volatile int(&)[1]);

typedef VariableTestName<TName, int(&)[1]> T12Var1;
typedef VariableTestName<TName, const int(&)[1]> T12Var2;
typedef VariableTestName<TName, volatile int(&)[1]> T12Var3;
typedef VariableTestName<TName, const volatile int(&)[1]> T12Var4;

T12Var1 t12_var1;
T12Var2 t12_var2;
T12Var3 t12_var3;
T12Var4 t12_var4;

REGISTER_TEST(t12, new TestName<Cases, T12Var1, T12Var2,
    T12Var3, T12Var4>(t12_var1, t12_var2, t12_var3, t12_var4));

BASIC_TEST_TYPE_NAME("int(&&)[1]", int(&&)[1]);
BASIC_TEST_TYPE_NAME("const int(&&)[1]", const int(&&)[1]);
BASIC_TEST_TYPE_NAME("volatile int(&&)[1]", volatile int(&&)[1]);
BASIC_TEST_TYPE_NAME("const volatile int(&&)[1]", const volatile int(&&)[1]);

typedef VariableTestName<TName, int(&&)[1]> T13Var1;
typedef VariableTestName<TName, const int(&&)[1]> T13Var2;
typedef VariableTestName<TName, volatile int(&&)[1]> T13Var3;
typedef VariableTestName<TName, const volatile int(&&)[1]> T13Var4;

T13Var1 t13_var1;
T13Var2 t13_var2;
T13Var3 t13_var3;
T13Var4 t13_var4;

REGISTER_TEST(t13, new TestName<Cases, T13Var1, T13Var2,
    T13Var3, T13Var4>(t13_var1, t13_var2, t13_var3, t13_var4));

BASIC_TEST_TYPE_NAME("int(*)[1]", int(*)[1]);
BASIC_TEST_TYPE_NAME("const int(*)[1]", const int(*)[1]);
BASIC_TEST_TYPE_NAME("volatile int(*)[1]", volatile int(*)[1]);
BASIC_TEST_TYPE_NAME("const volatile int(*)[1]", const volatile int(*)[1]);
BASIC_TEST_TYPE_NAME("int(*const)[1]", int(*const)[1]);
BASIC_TEST_TYPE_NAME("int(*volatile)[1]", int(*volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*const volatile)[1]", int(*const volatile)[1]);

typedef VariableTestName<TName, int(*)[1]> T14Var1;
typedef VariableTestName<TName, const int(*)[1]> T14Var2;
typedef VariableTestName<TName, volatile int(*)[1]> T14Var3;
typedef VariableTestName<TName, const volatile int(*)[1]> T14Var4;
typedef VariableTestName<TName, int(*const)[1]> T14Var5;
typedef VariableTestName<TName, int(*volatile)[1]> T14Var6;
typedef VariableTestName<TName, int(*const volatile)[1]> T14Var7;

T14Var1 t14_var1;
T14Var2 t14_var2;
T14Var3 t14_var3;
T14Var4 t14_var4;
T14Var5 t14_var5;
T14Var6 t14_var6;
T14Var7 t14_var7;

REGISTER_TEST(t14, new TestName<Cases, T14Var1, T14Var2,
    T14Var3, T14Var4, T14Var5, T14Var6, T14Var7>(t14_var1, t14_var2, t14_var3, 
        t14_var4, t14_var5, t14_var6, t14_var7));

BASIC_TEST_TYPE_NAME("int(**)[1]", int(**)[1]);
BASIC_TEST_TYPE_NAME("const int(**)[1]", const int(**)[1]);
BASIC_TEST_TYPE_NAME("volatile int(**)[1]", volatile int(**)[1]);
BASIC_TEST_TYPE_NAME("const volatile int(**)[1]", const volatile int(**)[1]);
BASIC_TEST_TYPE_NAME("int(**const)[1]", int(**const)[1]);
BASIC_TEST_TYPE_NAME("int(**volatile)[1]", int(**volatile)[1]);
BASIC_TEST_TYPE_NAME("int(**const volatile)[1]", int(**const volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*const*)[1]", int(*const*)[1]);
BASIC_TEST_TYPE_NAME("int(*const*const)[1]", int(*const*const)[1]);
BASIC_TEST_TYPE_NAME("int(*const*volatile)[1]", int(*const*volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*const*const volatile)[1]", int(*const*const volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*volatile*)[1]", int(*volatile*)[1]);
BASIC_TEST_TYPE_NAME("int(*volatile*const)[1]", int(*volatile*const)[1]);
BASIC_TEST_TYPE_NAME("int(*volatile*volatile)[1]", int(*volatile*volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*volatile*const volatile)[1]", int(*volatile*const volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*const volatile*)[1]", int(*const volatile*)[1]);
BASIC_TEST_TYPE_NAME("int(*const volatile*const)[1]", int(*const volatile*const)[1]);
BASIC_TEST_TYPE_NAME("int(*const volatile*volatile)[1]", int(*const volatile*volatile)[1]);
BASIC_TEST_TYPE_NAME("int(*const volatile*const volatile)[1]", int(*const volatile*const volatile)[1]);

typedef VariableTestName<TName, int(**)[1]> T15Var1;
typedef VariableTestName<TName, const int(**)[1]> T15Var2;
typedef VariableTestName<TName, volatile int(**)[1]> T15Var3;
typedef VariableTestName<TName, const volatile int(**)[1]> T15Var4;
typedef VariableTestName<TName, int(**const)[1]> T15Var5;
typedef VariableTestName<TName, int(**volatile)[1]> T15Var6;
typedef VariableTestName<TName, int(**const volatile)[1]> T15Var7;
typedef VariableTestName<TName, int(*const*)[1]> T15Var8;
typedef VariableTestName<TName, int(*const*const)[1]> T15Var9;
typedef VariableTestName<TName, int(*const*volatile)[1]> T15Var10;
typedef VariableTestName<TName, int(*const*const volatile)[1]> T15Var11;
typedef VariableTestName<TName, int(*volatile*)[1]> T15Var12;
typedef VariableTestName<TName, int(*volatile*const)[1]> T15Var13;
typedef VariableTestName<TName, int(*volatile*volatile)[1]> T15Var14;
typedef VariableTestName<TName, int(*volatile*const volatile)[1]> T15Var15;
typedef VariableTestName<TName, int(*const volatile*)[1]> T15Var16;
typedef VariableTestName<TName, int(*const volatile*const)[1]> T15Var17;
typedef VariableTestName<TName, int(*const volatile*volatile)[1]> T15Var18;
typedef VariableTestName<TName, int(*const volatile*const volatile)[1]> T15Var19;

T15Var1 t15_var1;
T15Var2 t15_var2;
T15Var3 t15_var3;
T15Var4 t15_var4;
T15Var5 t15_var5;
T15Var6 t15_var6;
T15Var7 t15_var7;
T15Var8 t15_var8;
T15Var9 t15_var9;
T15Var10 t15_var10;
T15Var11 t15_var11;
T15Var12 t15_var12;
T15Var13 t15_var13;
T15Var14 t15_var14;
T15Var15 t15_var15;
T15Var16 t15_var16;
T15Var17 t15_var17;
T15Var18 t15_var18;
T15Var19 t15_var19;

REGISTER_TEST(t15, new TestName<Cases, T15Var1, T15Var2,
    T15Var3, T15Var4, T15Var5, T15Var6, T15Var7, T15Var8, T15Var9, T15Var10, 
    T15Var11, T15Var12, T15Var13, T15Var14, T15Var15, T15Var16, T15Var17, 
    T15Var18, T15Var19>(t15_var1, t15_var2, t15_var3, t15_var4, t15_var5, 
        t15_var6, t15_var7, t15_var8, t15_var9, t15_var10, t15_var11, 
        t15_var12, t15_var13, t15_var14, t15_var15, t15_var16, t15_var17, 
        t15_var18, t15_var19));

BASIC_TEST_TYPE_NAME("int()", int());
BASIC_TEST_TYPE_NAME("int(char)", int(char));
BASIC_TEST_TYPE_NAME("int(char, short)", int(char, short));
BASIC_TEST_TYPE_NAME("int(char, short, int, long)", int(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int()", const int());
BASIC_TEST_TYPE_NAME("volatile int()", volatile int());
BASIC_TEST_TYPE_NAME("const volatile int()", const volatile int());
BASIC_TEST_TYPE_NAME("int() const", int() const);
BASIC_TEST_TYPE_NAME("int() volatile", int() volatile);
BASIC_TEST_TYPE_NAME("int() const volatile", int() const volatile);
BASIC_TEST_TYPE_NAME("int() &", int() &);
BASIC_TEST_TYPE_NAME("int() const &", int() const &);
BASIC_TEST_TYPE_NAME("int() volatile &", int() volatile &);
BASIC_TEST_TYPE_NAME("int() const volatile &", int() const volatile &);
BASIC_TEST_TYPE_NAME("int() &&", int() &&);
BASIC_TEST_TYPE_NAME("int() const &&", int() const &&);
BASIC_TEST_TYPE_NAME("int() volatile &&", int() volatile &&);
BASIC_TEST_TYPE_NAME("int() const volatile &&", int() const volatile &&);

typedef VariableTestName<TName, int()> T16Var1;
typedef VariableTestName<TName, int(char)> T16Var2;
typedef VariableTestName<TName, int(char, short)> T16Var3;
typedef VariableTestName<TName, int(char, short, int, long)> T16Var4;
typedef VariableTestName<TName, const int()> T16Var5;
typedef VariableTestName<TName, volatile int()> T16Var6;
typedef VariableTestName<TName, const volatile int()> T16Var7;
typedef VariableTestName<TName, int() const> T16Var8;
typedef VariableTestName<TName, int() volatile> T16Var9;
typedef VariableTestName<TName, int() const volatile> T16Var10;
typedef VariableTestName<TName, int() &> T16Var11;
typedef VariableTestName<TName, int() const &> T16Var12;
typedef VariableTestName<TName, int() volatile &> T16Var13;
typedef VariableTestName<TName, int() const volatile &> T16Var14;
typedef VariableTestName<TName, int() &&> T16Var15;
typedef VariableTestName<TName, int() const &&> T16Var16;
typedef VariableTestName<TName, int() volatile &&> T16Var17;
typedef VariableTestName<TName, int() const volatile &&> T16Var18;

T16Var1 t16_var1;
T16Var2 t16_var2;
T16Var3 t16_var3;
T16Var4 t16_var4;
T16Var5 t16_var5;
T16Var6 t16_var6;
T16Var7 t16_var7;
T16Var8 t16_var8;
T16Var9 t16_var9;
T16Var10 t16_var10;
T16Var11 t16_var11;
T16Var12 t16_var12;
T16Var13 t16_var13;
T16Var14 t16_var14;
T16Var15 t16_var15;
T16Var16 t16_var16;
T16Var17 t16_var17;
T16Var18 t16_var18;

REGISTER_TEST(t16, new TestName<Cases, T16Var1, T16Var2, T16Var3, T16Var4,
    T16Var5, T16Var6, T16Var7, T16Var8, T16Var9, T16Var10, T16Var11, T16Var12, 
    T16Var13, T16Var14, T16Var15, T16Var16, T16Var17 ,T16Var18>(t16_var1, 
        t16_var2, t16_var3, t16_var4, t16_var5, t16_var6, t16_var7, t16_var8, 
        t16_var9, t16_var10, t16_var11, t16_var12, t16_var13, t16_var14, 
        t16_var15, t16_var16, t16_var17, t16_var18));

BASIC_TEST_TYPE_NAME("int(&)()", int(&)());
BASIC_TEST_TYPE_NAME("int(&)(char)", int(&)(char));
BASIC_TEST_TYPE_NAME("int(&)(char, short)", int(&)(char, short));
BASIC_TEST_TYPE_NAME("int(&)(char, short, int, long)", int(&)(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int(&)()", const int(&)());
BASIC_TEST_TYPE_NAME("volatile int(&)()", volatile int(&)());
BASIC_TEST_TYPE_NAME("const volatile int(&)()", const volatile int(&)());

typedef VariableTestName<TName, int(&)()> T17Var1;
typedef VariableTestName<TName, int(&)(char)> T17Var2;
typedef VariableTestName<TName, int(&)(char, short)> T17Var3;
typedef VariableTestName<TName, int(&)(char, short, int, long)> T17Var4;
typedef VariableTestName<TName, const int(&)()> T17Var5;
typedef VariableTestName<TName, volatile int(&)()> T17Var6;
typedef VariableTestName<TName, const volatile int(&)()> T17Var7;

T17Var1 t17_var1;
T17Var2 t17_var2;
T17Var3 t17_var3;
T17Var4 t17_var4;
T17Var5 t17_var5;
T17Var6 t17_var6;
T17Var7 t17_var7;

REGISTER_TEST(t17, new TestName<Cases, T17Var1, T17Var2, T17Var3, T17Var4,
    T17Var5, T17Var6, T17Var7>(t17_var1, t17_var2, t17_var3, t17_var4, 
    t17_var5, t17_var6, t17_var7));

BASIC_TEST_TYPE_NAME("int(&&)()", int(&&)());
BASIC_TEST_TYPE_NAME("int(&&)(char)", int(&&)(char));
BASIC_TEST_TYPE_NAME("int(&&)(char, short)", int(&&)(char, short));
BASIC_TEST_TYPE_NAME("int(&&)(char, short, int, long)", int(&&)(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int(&&)()", const int(&&)());
BASIC_TEST_TYPE_NAME("volatile int(&&)()", volatile int(&&)());
BASIC_TEST_TYPE_NAME("const volatile int(&&)()", const volatile int(&&)());

typedef VariableTestName<TName, int(&&)()> T18Var1;
typedef VariableTestName<TName, int(&&)(char)> T18Var2;
typedef VariableTestName<TName, int(&&)(char, short)> T18Var3;
typedef VariableTestName<TName, int(&&)(char, short, int, long)> T18Var4;
typedef VariableTestName<TName, const int(&&)()> T18Var5;
typedef VariableTestName<TName, volatile int(&&)()> T18Var6;
typedef VariableTestName<TName, const volatile int(&&)()> T18Var7;

T18Var1 t18_var1;
T18Var2 t18_var2;
T18Var3 t18_var3;
T18Var4 t18_var4;
T18Var5 t18_var5;
T18Var6 t18_var6;
T18Var7 t18_var7;

REGISTER_TEST(t18, new TestName<Cases, T18Var1, T18Var2, T18Var3, T18Var4,
    T18Var5, T18Var6, T18Var7>(t18_var1, t18_var2, t18_var3, t18_var4, 
    t18_var5, t18_var6, t18_var7));

BASIC_TEST_TYPE_NAME("int(*)()", int(*)());
BASIC_TEST_TYPE_NAME("int(*)(char)", int(*)(char));
BASIC_TEST_TYPE_NAME("int(*)(char, short)", int(*)(char, short));
BASIC_TEST_TYPE_NAME("int(*)(char, short, int, long)", int(*)(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int(*)()", const int(*)());
BASIC_TEST_TYPE_NAME("volatile int(*)()", volatile int(*)());
BASIC_TEST_TYPE_NAME("const volatile int(*)()", const volatile int(*)());
BASIC_TEST_TYPE_NAME("int(*const)()", int(*const)());
BASIC_TEST_TYPE_NAME("int(*volatile)()", int(*volatile)());
BASIC_TEST_TYPE_NAME("int(*const volatile)()", int(*const volatile)());

typedef VariableTestName<TName, int(*)()> T19Var1;
typedef VariableTestName<TName, int(*)(char)> T19Var2;
typedef VariableTestName<TName, int(*)(char, short)> T19Var3;
typedef VariableTestName<TName, int(*)(char, short, int, long)> T19Var4;
typedef VariableTestName<TName, const int(*)()> T19Var5;
typedef VariableTestName<TName, volatile int(*)()> T19Var6;
typedef VariableTestName<TName, const volatile int(*)()> T19Var7;
typedef VariableTestName<TName, int(*const)()> T19Var8;
typedef VariableTestName<TName, int(*volatile)()> T19Var9;
typedef VariableTestName<TName, int(*const volatile)()> T19Var10;

T19Var1 t19_var1;
T19Var2 t19_var2;
T19Var3 t19_var3;
T19Var4 t19_var4;
T19Var5 t19_var5;
T19Var6 t19_var6;
T19Var7 t19_var7;
T19Var8 t19_var8;
T19Var9 t19_var9;
T19Var10 t19_var10;

REGISTER_TEST(t19, new TestName<Cases, T19Var1, T19Var2, T19Var3, T19Var4,
    T19Var5, T19Var6, T19Var7, T19Var8, T19Var9, T19Var10>(t19_var1, t19_var2, 
        t19_var3, t19_var4, t19_var5, t19_var6, t19_var7, t19_var8, t19_var9, 
        t19_var10));

BASIC_TEST_TYPE_NAME("int(**)()", int(**)());
BASIC_TEST_TYPE_NAME("int(**)(char)", int(**)(char));
BASIC_TEST_TYPE_NAME("int(**)(char, short)", int(**)(char, short));
BASIC_TEST_TYPE_NAME("int(**)(char, short, int, long)", int(**)(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int(**)()", const int(**)());
BASIC_TEST_TYPE_NAME("volatile int(**)()", volatile int(**)());
BASIC_TEST_TYPE_NAME("const volatile int(**)()", const volatile int(**)());
BASIC_TEST_TYPE_NAME("int(**const)()", int(**const)());
BASIC_TEST_TYPE_NAME("int(**volatile)()", int(**volatile)());
BASIC_TEST_TYPE_NAME("int(**const volatile)()", int(**const volatile)());
BASIC_TEST_TYPE_NAME("int(*const*)()", int(*const*)());
BASIC_TEST_TYPE_NAME("int(*const*const)()", int(*const*const)());
BASIC_TEST_TYPE_NAME("int(*const*volatile)()", int(*const*volatile)());
BASIC_TEST_TYPE_NAME("int(*const*const volatile)()", int(*const*const volatile)());
BASIC_TEST_TYPE_NAME("int(*volatile*)()", int(*volatile*)());
BASIC_TEST_TYPE_NAME("int(*volatile*const)()", int(*volatile*const)());
BASIC_TEST_TYPE_NAME("int(*volatile*volatile)()", int(*volatile*volatile)());
BASIC_TEST_TYPE_NAME("int(*volatile*const volatile)()", int(*volatile*const volatile)());
BASIC_TEST_TYPE_NAME("int(*const volatile*)()", int(*const volatile*)());
BASIC_TEST_TYPE_NAME("int(*const volatile*const)()", int(*const volatile*const)());
BASIC_TEST_TYPE_NAME("int(*const volatile*volatile)()", int(*const volatile*volatile)());
BASIC_TEST_TYPE_NAME("int(*const volatile*const volatile)()", int(*const volatile*const volatile)());

typedef VariableTestName<TName, int(**)()> T20Var1;
typedef VariableTestName<TName, int(**)(char)> T20Var2;
typedef VariableTestName<TName, int(**)(char, short)> T20Var3;
typedef VariableTestName<TName, int(**)(char, short, int, long)> T20Var4;
typedef VariableTestName<TName, const int(**)()> T20Var5;
typedef VariableTestName<TName, volatile int(**)()> T20Var6;
typedef VariableTestName<TName, const volatile int(**)()> T20Var7;
typedef VariableTestName<TName, int(**const)()> T20Var8;
typedef VariableTestName<TName, int(**volatile)()> T20Var9;
typedef VariableTestName<TName, int(**const volatile)()> T20Var10;
typedef VariableTestName<TName, int(*const*)()> T20Var11;
typedef VariableTestName<TName, int(*const*const)()> T20Var12;
typedef VariableTestName<TName, int(*const*volatile)()> T20Var13;
typedef VariableTestName<TName, int(*const*const volatile)()> T20Var14;
typedef VariableTestName<TName, int(*volatile*)()> T20Var15;
typedef VariableTestName<TName, int(*volatile*const)()> T20Var16;
typedef VariableTestName<TName, int(*volatile*volatile)()> T20Var17;
typedef VariableTestName<TName, int(*volatile*const volatile)()> T20Var18;
typedef VariableTestName<TName, int(*const volatile*)()> T20Var19;
typedef VariableTestName<TName, int(*const volatile*const)()> T20Var20;
typedef VariableTestName<TName, int(*const volatile*volatile)()> T20Var21;
typedef VariableTestName<TName, int(*const volatile*const volatile)()> T20Var22;

T20Var1 t20_var1;
T20Var2 t20_var2;
T20Var3 t20_var3;
T20Var4 t20_var4;
T20Var5 t20_var5;
T20Var6 t20_var6;
T20Var7 t20_var7;
T20Var8 t20_var8;
T20Var9 t20_var9;
T20Var10 t20_var10;
T20Var11 t20_var11;
T20Var12 t20_var12;
T20Var13 t20_var13;
T20Var14 t20_var14;
T20Var15 t20_var15;
T20Var16 t20_var16;
T20Var17 t20_var17;
T20Var18 t20_var18;
T20Var19 t20_var19;
T20Var20 t20_var20;
T20Var21 t20_var21;
T20Var22 t20_var22;

REGISTER_TEST(t20, new TestName<Cases, T20Var1, T20Var2, T20Var3, T20Var4,
    T20Var5, T20Var6, T20Var7, T20Var8, T20Var9, T20Var10, T20Var11, T20Var12,
    T20Var13, T20Var14, T20Var15, T20Var16, T20Var17, T20Var18, T20Var19, 
    T20Var20, T20Var21, T20Var22>(t20_var1, t20_var2, t20_var3, t20_var4, 
        t20_var5, t20_var6, t20_var7, t20_var8, t20_var9, t20_var10, t20_var11,
        t20_var12, t20_var13, t20_var14, t20_var15, t20_var16, t20_var17, 
        t20_var18, t20_var19, t20_var20, t20_var21, t20_var22));

BASIC_TEST_TYPE_NAME("int A::*", int A::*);
BASIC_TEST_TYPE_NAME("const int A::*", const int A::*);
BASIC_TEST_TYPE_NAME("volatile int A::*", volatile int A::*);
BASIC_TEST_TYPE_NAME("const volatile int A::*", const volatile int A::*);
BASIC_TEST_TYPE_NAME("int A::*const", int A::*const);
BASIC_TEST_TYPE_NAME("int A::*volatile", int A::*volatile);
BASIC_TEST_TYPE_NAME("int A::*const volatile", int A::*const volatile);

typedef VariableTestName<TName, int A::*> T21Var1;
typedef VariableTestName<TName, const int A::*> T21Var2;
typedef VariableTestName<TName, volatile int A::*> T21Var3;
typedef VariableTestName<TName, const volatile int A::*> T21Var4;
typedef VariableTestName<TName, int A::*const> T21Var5;
typedef VariableTestName<TName, int A::*volatile> T21Var6;
typedef VariableTestName<TName, int A::*const volatile> T21Var7;

T21Var1 t21_var1;
T21Var2 t21_var2;
T21Var3 t21_var3;
T21Var4 t21_var4;
T21Var5 t21_var5;
T21Var6 t21_var6;
T21Var7 t21_var7;

REGISTER_TEST(t21, new TestName<Cases, T21Var1, T21Var2,
    T21Var3, T21Var4, T21Var5, T21Var6, T21Var7>(t21_var1, t21_var2, t21_var3, 
        t21_var4, t21_var5, t21_var6, t21_var7));

BASIC_TEST_TYPE_NAME("int A::**", int A::**);
BASIC_TEST_TYPE_NAME("const int A::**", const int A::**);
BASIC_TEST_TYPE_NAME("volatile int A::**", volatile int A::**);
BASIC_TEST_TYPE_NAME("const volatile int A::**", const volatile int A::**);
BASIC_TEST_TYPE_NAME("int A::**const", int A::**const);
BASIC_TEST_TYPE_NAME("int A::**volatile", int A::**volatile);
BASIC_TEST_TYPE_NAME("int A::**const volatile", int A::**const volatile);
BASIC_TEST_TYPE_NAME("int A::*const*", int A::*const*);
BASIC_TEST_TYPE_NAME("int A::*const*const", int A::*const*const);
BASIC_TEST_TYPE_NAME("int A::*const*volatile", int A::*const*volatile);
BASIC_TEST_TYPE_NAME("int A::*const*const volatile", int A::*const*const volatile);
BASIC_TEST_TYPE_NAME("int A::*volatile*", int A::*volatile*);
BASIC_TEST_TYPE_NAME("int A::*volatile*const", int A::*volatile*const);
BASIC_TEST_TYPE_NAME("int A::*volatile*volatile", int A::*volatile*volatile);
BASIC_TEST_TYPE_NAME("int A::*volatile*const volatile", int A::*volatile*const volatile);
BASIC_TEST_TYPE_NAME("int A::*const volatile*", int A::*const volatile*);
BASIC_TEST_TYPE_NAME("int A::*const volatile*const", int A::*const volatile*const);
BASIC_TEST_TYPE_NAME("int A::*const volatile*volatile", int A::*const volatile*volatile);
BASIC_TEST_TYPE_NAME("int A::*const volatile*const volatile", int A::*const volatile*const volatile);

typedef VariableTestName<TName, int A::**> T22Var1;
typedef VariableTestName<TName, const int A::**> T22Var2;
typedef VariableTestName<TName, volatile int A::**> T22Var3;
typedef VariableTestName<TName, const volatile int A::**> T22Var4;
typedef VariableTestName<TName, int A::**const> T22Var5;
typedef VariableTestName<TName, int A::**volatile> T22Var6;
typedef VariableTestName<TName, int A::**const volatile> T22Var7;
typedef VariableTestName<TName, int A::*const*> T22Var8;
typedef VariableTestName<TName, int A::*const*const> T22Var9;
typedef VariableTestName<TName, int A::*const*volatile> T22Var10;
typedef VariableTestName<TName, int A::*const*const volatile> T22Var11;
typedef VariableTestName<TName, int A::*volatile*> T22Var12;
typedef VariableTestName<TName, int A::*volatile*const> T22Var13;
typedef VariableTestName<TName, int A::*volatile*volatile> T22Var14;
typedef VariableTestName<TName, int A::*volatile*const volatile> T22Var15;
typedef VariableTestName<TName, int A::*const volatile*> T22Var16;
typedef VariableTestName<TName, int A::*const volatile*const> T22Var17;
typedef VariableTestName<TName, int A::*const volatile*volatile> T22Var18;
typedef VariableTestName<TName, int A::*const volatile*const volatile> T22Var19;

T22Var1 t22_var1;
T22Var2 t22_var2;
T22Var3 t22_var3;
T22Var4 t22_var4;
T22Var5 t22_var5;
T22Var6 t22_var6;
T22Var7 t22_var7;
T22Var8 t22_var8;
T22Var9 t22_var9;
T22Var10 t22_var10;
T22Var11 t22_var11;
T22Var12 t22_var12;
T22Var13 t22_var13;
T22Var14 t22_var14;
T22Var15 t22_var15;
T22Var16 t22_var16;
T22Var17 t22_var17;
T22Var18 t22_var18;
T22Var19 t22_var19;

REGISTER_TEST(t22, new TestName<Cases, T22Var1, T22Var2,
    T22Var3, T22Var4, T22Var5, T22Var6, T22Var7, T22Var8, T22Var9, T22Var10, 
    T22Var11, T22Var12, T22Var13, T22Var14, T22Var15, T22Var16, T22Var17,
    T22Var18, T22Var19>(t22_var1, t22_var2, t22_var3, t22_var4, t22_var5, 
        t22_var6, t22_var7, t22_var8, t22_var9, t22_var10, t22_var11,
        t22_var12, t22_var13, t22_var14, t22_var15, t22_var16, t22_var17, 
        t22_var18, t22_var19));

BASIC_TEST_TYPE_NAME("int(A::*)()", int(A::*)());
BASIC_TEST_TYPE_NAME("int(A::*)(char)", int(A::*)(char));
BASIC_TEST_TYPE_NAME("int(A::*)(char, short)", int(A::*)(char, short));
BASIC_TEST_TYPE_NAME("int(A::*)(char, short, int, long)", int(A::*)(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int(A::*)()", const int(A::*)());
BASIC_TEST_TYPE_NAME("volatile int(A::*)()", volatile int(A::*)());
BASIC_TEST_TYPE_NAME("const volatile int(A::*)()", const volatile int(A::*)());
BASIC_TEST_TYPE_NAME("int(A::*)() const", int(A::*)() const);
BASIC_TEST_TYPE_NAME("int(A::*)() volatile", int(A::*)() volatile);
BASIC_TEST_TYPE_NAME("int(A::*)() const volatile", int(A::*)() const volatile);
BASIC_TEST_TYPE_NAME("int(A::*)() &", int(A::*)() &);
BASIC_TEST_TYPE_NAME("int(A::*)() const &", int(A::*)() const &);
BASIC_TEST_TYPE_NAME("int(A::*)() volatile &", int(A::*)() volatile &);
BASIC_TEST_TYPE_NAME("int(A::*)() const volatile &", int(A::*)() const volatile &);
BASIC_TEST_TYPE_NAME("int(A::*)() &&", int(A::*)() &&);
BASIC_TEST_TYPE_NAME("int(A::*)() const &&", int(A::*)() const &&);
BASIC_TEST_TYPE_NAME("int(A::*)() volatile &&", int(A::*)() volatile &&);
BASIC_TEST_TYPE_NAME("int(A::*)() const volatile &&", int(A::*)() const volatile &&);
BASIC_TEST_TYPE_NAME("int(A::*const)()", int(A::*const)());
BASIC_TEST_TYPE_NAME("int(A::*volatile)()", int(A::*volatile)());
BASIC_TEST_TYPE_NAME("int(A::*const volatile)()", int(A::*const volatile)());

typedef VariableTestName<TName, int(A::*)()> T23Var1;
typedef VariableTestName<TName, int(A::*)(char)> T23Var2;
typedef VariableTestName<TName, int(A::*)(char, short)> T23Var3;
typedef VariableTestName<TName, int(A::*)(char, short, int, long)> T23Var4;
typedef VariableTestName<TName, const int(A::*)()> T23Var5;
typedef VariableTestName<TName, volatile int(A::*)()> T23Var6;
typedef VariableTestName<TName, const volatile int(A::*)()> T23Var7;
typedef VariableTestName<TName, int(A::*)() const> T23Var8;
typedef VariableTestName<TName, int(A::*)() volatile> T23Var9;
typedef VariableTestName<TName, int(A::*)() const volatile> T23Var10;
typedef VariableTestName<TName, int(A::*)() &> T23Var11;
typedef VariableTestName<TName, int(A::*)() const &> T23Var12;
typedef VariableTestName<TName, int(A::*)() volatile &> T23Var13;
typedef VariableTestName<TName, int(A::*)() const volatile &> T23Var14;
typedef VariableTestName<TName, int(A::*)() &&> T23Var15;
typedef VariableTestName<TName, int(A::*)() const &&> T23Var16;
typedef VariableTestName<TName, int(A::*)() volatile &&> T23Var17;
typedef VariableTestName<TName, int(A::*)() const volatile &&> T23Var18;
typedef VariableTestName<TName, int(A::*const)()> T23Var19;
typedef VariableTestName<TName, int(A::*volatile)()> T23Var20;
typedef VariableTestName<TName, int(A::*const volatile)()> T23Var21;

T23Var1 t23_var1;
T23Var2 t23_var2;
T23Var3 t23_var3;
T23Var4 t23_var4;
T23Var5 t23_var5;
T23Var6 t23_var6;
T23Var7 t23_var7;
T23Var8 t23_var8;
T23Var9 t23_var9;
T23Var10 t23_var10;
T23Var11 t23_var11;
T23Var12 t23_var12;
T23Var13 t23_var13;
T23Var14 t23_var14;
T23Var15 t23_var15;
T23Var16 t23_var16;
T23Var17 t23_var17;
T23Var18 t23_var18;
T23Var19 t23_var19;
T23Var20 t23_var20;
T23Var21 t23_var21;

REGISTER_TEST(t23, new TestName<Cases, T23Var1, T23Var2, T23Var3, T23Var4,
    T23Var5, T23Var6, T23Var7, T23Var8, T23Var9, T23Var10, T23Var11, T23Var12, 
    T23Var13, T23Var14, T23Var15, T23Var16, T23Var17, T23Var18, T23Var19, 
    T23Var20, T23Var21>(t23_var1, t23_var2, t23_var3, t23_var4, t23_var5, 
        t23_var6, t23_var7, t23_var8, t23_var9, t23_var10, t23_var11, 
        t23_var12, t23_var13, t23_var14, t23_var15, t23_var16, t23_var17, 
        t23_var18, t23_var19, t23_var20, t23_var21));

BASIC_TEST_TYPE_NAME("int(A::**)()", int(A::**)());
BASIC_TEST_TYPE_NAME("int(A::**)(char)", int(A::**)(char));
BASIC_TEST_TYPE_NAME("int(A::**)(char, short)", int(A::**)(char, short));
BASIC_TEST_TYPE_NAME("int(A::**)(char, short, int, long)", int(A::**)(char, short, int, long));
BASIC_TEST_TYPE_NAME("const int(A::**)()", const int(A::**)());
BASIC_TEST_TYPE_NAME("volatile int(A::**)()", volatile int(A::**)());
BASIC_TEST_TYPE_NAME("const volatile int(A::**)()", const volatile int(A::**)());
BASIC_TEST_TYPE_NAME("int(A::**)() const", int(A::**)() const);
BASIC_TEST_TYPE_NAME("int(A::**)() volatile", int(A::**)() volatile);
BASIC_TEST_TYPE_NAME("int(A::**)() const volatile", int(A::**)() const volatile);
BASIC_TEST_TYPE_NAME("int(A::**)() &", int(A::**)() &);
BASIC_TEST_TYPE_NAME("int(A::**)() const &", int(A::**)() const &);
BASIC_TEST_TYPE_NAME("int(A::**)() volatile &", int(A::**)() volatile &);
BASIC_TEST_TYPE_NAME("int(A::**)() const volatile &", int(A::**)() const volatile &);
BASIC_TEST_TYPE_NAME("int(A::**)() &&", int(A::**)() &&);
BASIC_TEST_TYPE_NAME("int(A::**)() const &&", int(A::**)() const &&);
BASIC_TEST_TYPE_NAME("int(A::**)() volatile &&", int(A::**)() volatile &&);
BASIC_TEST_TYPE_NAME("int(A::**)() const volatile &&", int(A::**)() const volatile &&);
BASIC_TEST_TYPE_NAME("int(A::**const)()", int(A::**const)());
BASIC_TEST_TYPE_NAME("int(A::**volatile)()", int(A::**volatile)());
BASIC_TEST_TYPE_NAME("int(A::**const volatile)()", int(A::**const volatile)());
BASIC_TEST_TYPE_NAME("int(A::*const*)()", int(A::*const*)());
BASIC_TEST_TYPE_NAME("int(A::*const*const)()", int(A::*const*const)());
BASIC_TEST_TYPE_NAME("int(A::*const*volatile)()", int(A::*const*volatile)());
BASIC_TEST_TYPE_NAME("int(A::*const*const volatile)()", int(A::*const*const volatile)());
BASIC_TEST_TYPE_NAME("int(A::*volatile*)()", int(A::*volatile*)());
BASIC_TEST_TYPE_NAME("int(A::*volatile*const)()", int(A::*volatile*const)());
BASIC_TEST_TYPE_NAME("int(A::*volatile*volatile)()", int(A::*volatile*volatile)());
BASIC_TEST_TYPE_NAME("int(A::*volatile*const volatile)()", int(A::*volatile*const volatile)());
BASIC_TEST_TYPE_NAME("int(A::*const volatile*)()", int(A::*const volatile*)());
BASIC_TEST_TYPE_NAME("int(A::*const volatile*const)()", int(A::*const volatile*const)());
BASIC_TEST_TYPE_NAME("int(A::*const volatile*volatile)()", int(A::*const volatile*volatile)());
BASIC_TEST_TYPE_NAME("int(A::*const volatile*const volatile)()", int(A::*const volatile*const volatile)());

typedef VariableTestName<TName, int(A::**)()> T24Var1;
typedef VariableTestName<TName, int(A::**)(char)> T24Var2;
typedef VariableTestName<TName, int(A::**)(char, short)> T24Var3;
typedef VariableTestName<TName, int(A::**)(char, short, int, long)> T24Var4;
typedef VariableTestName<TName, const int(A::**)()> T24Var5;
typedef VariableTestName<TName, volatile int(A::**)()> T24Var6;
typedef VariableTestName<TName, const volatile int(A::**)()> T24Var7;
typedef VariableTestName<TName, int(A::**)() const> T24Var8;
typedef VariableTestName<TName, int(A::**)() volatile> T24Var9;
typedef VariableTestName<TName, int(A::**)() const volatile> T24Var10;
typedef VariableTestName<TName, int(A::**)() &> T24Var11;
typedef VariableTestName<TName, int(A::**)() const &> T24Var12;
typedef VariableTestName<TName, int(A::**)() volatile &> T24Var13;
typedef VariableTestName<TName, int(A::**)() const volatile &> T24Var14;
typedef VariableTestName<TName, int(A::**)() &&> T24Var15;
typedef VariableTestName<TName, int(A::**)() const &&> T24Var16;
typedef VariableTestName<TName, int(A::**)() volatile &&> T24Var17;
typedef VariableTestName<TName, int(A::**)() const volatile &&> T24Var18;
typedef VariableTestName<TName, int(A::**const)()> T24Var19;
typedef VariableTestName<TName, int(A::**volatile)()> T24Var20;
typedef VariableTestName<TName, int(A::**const volatile)()> T24Var21;
typedef VariableTestName<TName, int(A::*const*)()> T24Var22;
typedef VariableTestName<TName, int(A::*const*const)()> T24Var23;
typedef VariableTestName<TName, int(A::*const*volatile)()> T24Var24;
typedef VariableTestName<TName, int(A::*const*const volatile)()> T24Var25;
typedef VariableTestName<TName, int(A::*volatile*)()> T24Var26;
typedef VariableTestName<TName, int(A::*volatile*const)()> T24Var27;
typedef VariableTestName<TName, int(A::*volatile*volatile)()> T24Var28;
typedef VariableTestName<TName, int(A::*volatile*const volatile)()> T24Var29;
typedef VariableTestName<TName, int(A::*const volatile*)()> T24Var30;
typedef VariableTestName<TName, int(A::*const volatile*const)()> T24Var31;
typedef VariableTestName<TName, int(A::*const volatile*volatile)()> T24Var32;
typedef VariableTestName<TName, int(A::*const volatile*const volatile)()> T24Var33;

T24Var1 t24_var1;
T24Var2 t24_var2;
T24Var3 t24_var3;
T24Var4 t24_var4;
T24Var5 t24_var5;
T24Var6 t24_var6;
T24Var7 t24_var7;
T24Var8 t24_var8;
T24Var9 t24_var9;
T24Var10 t24_var10;
T24Var11 t24_var11;
T24Var12 t24_var12;
T24Var13 t24_var13;
T24Var14 t24_var14;
T24Var15 t24_var15;
T24Var16 t24_var16;
T24Var17 t24_var17;
T24Var18 t24_var18;
T24Var19 t24_var19;
T24Var20 t24_var20;
T24Var21 t24_var21;
T24Var22 t24_var22;
T24Var23 t24_var23;
T24Var24 t24_var24;
T24Var25 t24_var25;
T24Var26 t24_var26;
T24Var27 t24_var27;
T24Var28 t24_var28;
T24Var29 t24_var29;
T24Var30 t24_var30;
T24Var31 t24_var31;
T24Var32 t24_var32;
T24Var33 t24_var33;

REGISTER_TEST(t24, new TestName<Cases, T24Var1, T24Var2, T24Var3, T24Var4,
    T24Var5, T24Var6, T24Var7, T24Var8, T24Var9, T24Var10, T24Var11, T24Var12, 
    T24Var13, T24Var14, T24Var15, T24Var16, T24Var17, T24Var18, T24Var19, 
    T24Var20, T24Var21, T24Var22, T24Var23, T24Var24, T24Var25, T24Var26, 
    T24Var27, T24Var28, T24Var29, T24Var30, T24Var31, T24Var32, 
    T24Var33>(t24_var1, t24_var2, t24_var3, t24_var4, t24_var5, 
        t24_var6, t24_var7, t24_var8, t24_var9, t24_var10, t24_var11, 
        t24_var12, t24_var13, t24_var14, t24_var15, t24_var16, t24_var17, 
        t24_var18, t24_var19, t24_var20, t24_var21, t24_var22, t24_var23, 
        t24_var24, t24_var25, t24_var26, t24_var27, t24_var28, t24_var29, 
        t24_var30, t24_var31, t24_var32, t24_var33));

int main()
{ 
    return RUN_TEST();
}
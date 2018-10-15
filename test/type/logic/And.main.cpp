#include "type/logic/And.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <typeinfo>
#include <type_traits>

struct CaseVTa {}; // case value and target
struct CaseV {}; // case value

template<typename TAnd, bool TValue>
using VariableTestAnd = basic::test::Variable<
    TAnd, 
    basic::test::type::Value<bool, TValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IAnd = 0;
constexpr std::size_t ITypeValValue = 1;
constexpr std::size_t IValFuncBoolToCString = 2;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeValue = basic::test::msg::arg::type::Value<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I, typename... TArgArgs>
using ArgValFunction = basic::test::msg::arg::val::Function<I, TArgArgs...>;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IAnd>,
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, 
    ArgTypeName<IAnd>,
    ArgTypeName<IAnd>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
class TestAnd :
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestAnd<TCases, TVars...>>,
    public basic::test::Case<TestAnd<TCases, TVars...>, TCases>,
    public basic::test::Base<TestAnd<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestAnd<TCases, TVars...>, TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestAnd<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestAnd<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseVTa::SetFormat;
    using MsgBaseCaseV::SetFormat;
public:
    using MsgBaseCaseVTa::Format;
    using MsgBaseCaseV::Format;
    using MsgBaseCaseVTa::Argument;
    using MsgBaseCaseV::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestAnd(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseVTa case_value_and_target;
        SetFormat(info, case_value_and_target, 
            "test compare between %s::value and %s\n");
        SetFormat(debug, case_value_and_target,
            "test compare between %s::value and %s\n");
        SetFormat(error, case_value_and_target,
            "error %s::value is not same with %s\n");

        CaseV case_value;
        SetFormat(info, case_value, 
            "test compare between %s::value and %s::Value\n");
        SetFormat(debug, case_value,
            "test compare between %s::value and %s::Value\n");
        SetFormat(error, case_value,
            "error %s::value is not same with %s::Value\n");
    }

    template<typename TAnd, bool TValue>
    bool Result(const CaseVTa&, VariableTestAnd<TAnd, TValue>& var)
    {
        return TAnd::value == TValue;
    }

    template<typename TAnd, bool TValue>
    bool Result(const CaseV&, VariableTestAnd<TAnd, TValue>& var)
    {
        return TAnd::value == TAnd::Value;
    }

};

using Cases = basic::test::type::Parameter<CaseVTa, CaseV>;

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);

#ifdef _WIN32
template<typename TTrue, typename TArg, typename... TArgs>
struct basic::test::type::Name<basic::type::logic::And<TTrue, TArg, TArgs...>>
#else
template<typename... TArgs>
struct basic::test::type::Name<basic::type::logic::And<TArgs...>>
#endif
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "basic::type::logic::And<%s>";
#ifdef _WIN32
        const auto& param_cstr = basic::test::type::param::Name<
            basic::test::type::Parameter<TTrue, TArg, TArgs...>>::CStr();
#else
        const auto& param_cstr = basic::test::type::param::Name<
            basic::test::type::Parameter<TArgs...>>::CStr();
#endif
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            param_cstr.Size(), _format_cstr, *param_cstr);\
    }
};

const char* true_cstr = "true";
const char* false_cstr = "false";

const char* BoolToString(bool&& b)
{
    return b ? true_cstr : false_cstr;
}

using TDefaultAnd1_1 = basic::type::logic::And<std::true_type, std::false_type>;
using TDefaultAnd1_2 = basic::type::logic::And<std::true_type, std::true_type>;

typedef VariableTestAnd<TDefaultAnd1_1, false> T1Var1;
typedef VariableTestAnd<TDefaultAnd1_2, true> T1Var2;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);
    
REGISTER_TEST(t1, new TestAnd<Cases,  T1Var1, T1Var2>(t1_var1,
    t1_var2));

using TDefaultAnd2_1 = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type>;
using TDefaultAnd2_2 = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type>;
using TDefaultAnd2_3 = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type>;
using TDefaultAnd2_4 = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type>;

typedef VariableTestAnd<TDefaultAnd2_1, false> T2Var1;
typedef VariableTestAnd<TDefaultAnd2_2, false> T2Var2;
typedef VariableTestAnd<TDefaultAnd2_3, false> T2Var3;
typedef VariableTestAnd<TDefaultAnd2_4, true> T2Var4;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);
T2Var3 t2_var3(&BoolToString);
T2Var4 t2_var4(&BoolToString);

REGISTER_TEST(t2, new TestAnd<Cases, T2Var1, T2Var2, T2Var3,
    T2Var4>(t2_var1, t2_var2, t2_var3, t2_var4));

using TDefaultAnd4_1 = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;
using TDefaultAnd4_2 = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>;
using TDefaultAnd4_3 = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>;
using TDefaultAnd4_4 = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>;
using TDefaultAnd4_5 = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;
using TDefaultAnd4_6 = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>;
using TDefaultAnd4_7 = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>;
using TDefaultAnd4_8 = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>;
using TDefaultAnd4_9 = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using TDefaultAnd4_10 = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>;
using TDefaultAnd4_11 = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>;
using TDefaultAnd4_12 = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>;
using TDefaultAnd4_13 = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>;
using TDefaultAnd4_14 = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>;
using TDefaultAnd4_15 = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>;
using TDefaultAnd4_16 = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>;

typedef VariableTestAnd<TDefaultAnd4_1, false> T3Var1;
typedef VariableTestAnd<TDefaultAnd4_2, false> T3Var2;
typedef VariableTestAnd<TDefaultAnd4_3, false> T3Var3;
typedef VariableTestAnd<TDefaultAnd4_4, false> T3Var4;
typedef VariableTestAnd<TDefaultAnd4_5, false> T3Var5;
typedef VariableTestAnd<TDefaultAnd4_6, false> T3Var6;
typedef VariableTestAnd<TDefaultAnd4_7, false> T3Var7;
typedef VariableTestAnd<TDefaultAnd4_8, false> T3Var8;
typedef VariableTestAnd<TDefaultAnd4_9, false> T3Var9;
typedef VariableTestAnd<TDefaultAnd4_10, false> T3Var10;
typedef VariableTestAnd<TDefaultAnd4_11, false> T3Var11;
typedef VariableTestAnd<TDefaultAnd4_12, false> T3Var12;
typedef VariableTestAnd<TDefaultAnd4_13, false> T3Var13;
typedef VariableTestAnd<TDefaultAnd4_14, false> T3Var14;
typedef VariableTestAnd<TDefaultAnd4_15, false> T3Var15;
typedef VariableTestAnd<TDefaultAnd4_16, true> T3Var16;

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
T3Var14 t3_var14(&BoolToString);
T3Var15 t3_var15(&BoolToString);
T3Var16 t3_var16(&BoolToString);

REGISTER_TEST(t3, new TestAnd<Cases, T3Var1, T3Var2, T3Var3, T3Var4, T3Var5,
    T3Var6, T3Var7, T3Var8, T3Var9, T3Var10, T3Var11, T3Var12, T3Var13, 
    T3Var14, T3Var15, T3Var16>(t3_var1, t3_var2, t3_var3, t3_var4, t3_var5,
        t3_var6, t3_var7, t3_var8, t3_var9, t3_var10, t3_var11, t3_var12,
        t3_var13, t3_var14, t3_var15, t3_var16));

int main()
{
    return RUN_TEST();
}

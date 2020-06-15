#include "type/logic/Xor.h"
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

template<typename TXor, bool TValue>
using VariableTestXor = basic::test::Variable<
    TXor, 
    basic::test::type::Value<bool, TValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IXor = 0;
constexpr std::size_t ITypeValValue = 1;
constexpr std::size_t IValFuncBoolToCString = 2;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeValue = basic::test::msg::arg::type::Value<I>;

template<std::size_t I, typename... TArgArgs>
using ArgValFunction = basic::test::msg::arg::val::Function<I, TArgArgs...>;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IXor>,
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, 
    ArgTypeName<IXor>,
    ArgTypeName<IXor>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;


template<typename TCases, typename... TVars>
class TestXor :
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestXor<TCases, TVars...>>,
    public basic::test::Case<TestXor<TCases, TVars...>, TCases>,
    public basic::test::Base<TestXor<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestXor<TCases, TVars...>, TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestXor<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestXor<TCases, TVars...>, 
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
    TestXor(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;
        
        CaseVTa case_value_and_target;
        SetFormat(info, case_value_and_target, 
            "test compare between %s::value and %s\n");
        SetFormat(debug, case_value_and_target,
            "test compare between %s::value and %s\n");
        SetFormat(err, case_value_and_target,
            "error %s::value is not same with %s\n");

        CaseV case_value;
        SetFormat(info, case_value, 
            "test compare between %s::value and %s::Value\n");
        SetFormat(debug, case_value,
            "test compare between %s::value and %s::Value\n");
        SetFormat(err, case_value,
            "error %s::value is not same with %s::Value\n");
    }

    template<typename TXor, bool TValue>
    bool Result(const CaseVTa&, VariableTestXor<TXor, TValue>& var)
    {
        return TXor::value == TValue;
    }

    template<typename TXor, bool TValue>
    bool Result(const CaseV&, VariableTestXor<TXor, TValue>& var)
    {
        return TXor::value == TXor::Value;
    }

};

using Cases = basic::test::type::Parameter<CaseVTa, CaseV>;

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);

#ifdef _WIN32
template<typename TTrue, typename TArg, typename... TArgs>
struct basic::test::type::Name<basic::type::logic::Xor<TTrue, TArg, TArgs...>>
#else
template<typename... TArgs>
struct basic::test::type::Name<basic::type::logic::Xor<TArgs...>>
#endif
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "basic::type::logic::Xor<%s>";
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

using TDefaultXor1_1 = basic::type::logic::Xor<std::true_type, std::false_type>;
using TDefaultXor1_2 = basic::type::logic::Xor<std::true_type, std::true_type>;

typedef VariableTestXor<TDefaultXor1_1, false> T1Var1;
typedef VariableTestXor<TDefaultXor1_2, false> T1Var2;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);
    
REGISTER_TEST(t1, new TestXor<Cases,  T1Var1, T1Var2>(t1_var1,
    t1_var2));

using TDefaultXor2_1 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type>;
using TDefaultXor2_2 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type>;
using TDefaultXor2_3 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type>;
using TDefaultXor2_4 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type>;

typedef VariableTestXor<TDefaultXor2_1, false> T2Var1;
typedef VariableTestXor<TDefaultXor2_2, true> T2Var2;
typedef VariableTestXor<TDefaultXor2_3, true> T2Var3;
typedef VariableTestXor<TDefaultXor2_4, false> T2Var4;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);
T2Var3 t2_var3(&BoolToString);
T2Var4 t2_var4(&BoolToString);

REGISTER_TEST(t2, new TestXor<Cases, T2Var1, T2Var2, T2Var3,
    T2Var4>(t2_var1, t2_var2, t2_var3, t2_var4));

using TDefaultXor4_1 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;
using TDefaultXor4_2 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>;
using TDefaultXor4_3 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>;
using TDefaultXor4_4 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>;
using TDefaultXor4_5 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;
using TDefaultXor4_6 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>;
using TDefaultXor4_7 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>;
using TDefaultXor4_8 = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>;
using TDefaultXor4_9 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using TDefaultXor4_10 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>;
using TDefaultXor4_11 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>;
using TDefaultXor4_12 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>;
using TDefaultXor4_13 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>;
using TDefaultXor4_14 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>;
using TDefaultXor4_15 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>;
using TDefaultXor4_16 = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>;

typedef VariableTestXor<TDefaultXor4_1, false> T3Var1;
typedef VariableTestXor<TDefaultXor4_2, true> T3Var2;
typedef VariableTestXor<TDefaultXor4_3, true> T3Var3;
typedef VariableTestXor<TDefaultXor4_4, true> T3Var4;
typedef VariableTestXor<TDefaultXor4_5, true> T3Var5;
typedef VariableTestXor<TDefaultXor4_6, true> T3Var6;
typedef VariableTestXor<TDefaultXor4_7, true> T3Var7;
typedef VariableTestXor<TDefaultXor4_8, true> T3Var8;
typedef VariableTestXor<TDefaultXor4_9, true> T3Var9;
typedef VariableTestXor<TDefaultXor4_10, true> T3Var10;
typedef VariableTestXor<TDefaultXor4_11, true> T3Var11;
typedef VariableTestXor<TDefaultXor4_12, true> T3Var12;
typedef VariableTestXor<TDefaultXor4_13, true> T3Var13;
typedef VariableTestXor<TDefaultXor4_14, true> T3Var14;
typedef VariableTestXor<TDefaultXor4_15, true> T3Var15;
typedef VariableTestXor<TDefaultXor4_16, false> T3Var16;

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

REGISTER_TEST(t3, new TestXor<Cases, T3Var1, T3Var2, T3Var3, T3Var4, T3Var5,
    T3Var6, T3Var7, T3Var8, T3Var9, T3Var10, T3Var11, T3Var12, T3Var13, 
    T3Var14, T3Var15, T3Var16>(t3_var1, t3_var2, t3_var3, t3_var4, t3_var5,
        t3_var6, t3_var7, t3_var8, t3_var9, t3_var10, t3_var11, t3_var12,
        t3_var13, t3_var14, t3_var15, t3_var16));

int main()
{
    return RUN_TEST();
}

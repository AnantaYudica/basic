#include "type/conditional/Switch.h"
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

struct CaseATTa {}; // case alias type and target
struct CaseAT {}; // case alias type
struct CaseITa {}; // case index and target
struct CaseI {}; // Case index
struct CaseSTa {}; // case size and target
struct CaseS {}; // case size

template<typename TSwitch, typename TAliasType, typename TIndex,
    typename TSize>
using VariableTestSwitch = basic::test::Variable<
    TSwitch, 
    TAliasType, 
    basic::test::Value<TIndex>,
    basic::test::Value<TSize>>;

constexpr std::size_t ISwitch = 0;
constexpr std::size_t IAliasType = 1;
constexpr std::size_t IValIndex = 2;
constexpr std::size_t IValSize = 3;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

typedef basic::test::msg::Argument<CaseATTa,
     ArgTypeName<ISwitch>,
    ArgTypeName<IAliasType>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseAT, 
    ArgTypeName<ISwitch>,
    ArgTypeName<ISwitch>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseITa, 
    ArgTypeName<ISwitch>,
    ArgValue<IValIndex>> ArgCaseITa;

typedef basic::test::msg::Base<CaseITa, char, ArgCaseITa, 
    ArgCaseITa, ArgCaseITa> MsgBaseCaseITa;

typedef basic::test::msg::Argument<CaseI, 
    ArgTypeName<ISwitch>,
    ArgTypeName<ISwitch>> ArgCaseI;

typedef basic::test::msg::Base<CaseI, char, ArgCaseI, 
    ArgCaseI, ArgCaseI> MsgBaseCaseI;

typedef basic::test::msg::Argument<CaseSTa,
    ArgTypeName<ISwitch>,
    ArgValue<IValSize>> ArgCaseSTa;

typedef basic::test::msg::Base<CaseSTa, char, ArgCaseSTa, 
    ArgCaseSTa, ArgCaseSTa> MsgBaseCaseSTa;

typedef basic::test::msg::Argument<CaseS, 
    ArgTypeName<ISwitch>,
    ArgTypeName<ISwitch>> ArgCaseS;

typedef basic::test::msg::Base<CaseS, char, ArgCaseS, 
    ArgCaseS, ArgCaseS> MsgBaseCaseS;


template<typename TCases, typename... TVars>
class TestSwitch :
    public MsgBaseCaseATTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseITa,
    public MsgBaseCaseI,
    public MsgBaseCaseSTa,
    public MsgBaseCaseS,
    public basic::test::Message<BASIC_TEST, TestSwitch<TCases, TVars...>>,
    public basic::test::Case<TestSwitch<TCases, TVars...>, TCases>,
    public basic::test::Base<TestSwitch<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestSwitch<TCases, TVars...>, TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestSwitch<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestSwitch<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseATTa::SetFormat;
    using MsgBaseCaseAT::SetFormat;
    using MsgBaseCaseITa::SetFormat;
    using MsgBaseCaseI::SetFormat;
    using MsgBaseCaseSTa::SetFormat;
    using MsgBaseCaseS::SetFormat;
public:
    using MsgBaseCaseATTa::Format;
    using MsgBaseCaseAT::Format;
    using MsgBaseCaseITa::Format;
    using MsgBaseCaseI::Format;
    using MsgBaseCaseSTa::Format;
    using MsgBaseCaseS::Format;
    using MsgBaseCaseATTa::Argument;
    using MsgBaseCaseAT::Argument;
    using MsgBaseCaseITa::Argument;
    using MsgBaseCaseI::Argument;
    using MsgBaseCaseSTa::Argument;
    using MsgBaseCaseS::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestSwitch(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseATTa case_alias_type_and_target;
        SetFormat(info, case_alias_type_and_target, 
            "test compare between %s::type and %s\n");
        SetFormat(debug, case_alias_type_and_target,
            "test compare between %s::type and %s\n");
        SetFormat(error, case_alias_type_and_target,
            "error %s::type is not same with %s\n");
            
        CaseAT case_alias_type;
        SetFormat(info, case_alias_type, 
            "test compare between %s::type and %s::Type\n");
        SetFormat(debug, case_alias_type,
            "test compare between %s::type and %s::Type\n");
        SetFormat(error, case_alias_type,
            "error %s::type is not same with %s::Type\n");

        CaseITa case_index_and_target;
        SetFormat(info, case_index_and_target, 
            "test compare between %s::index and %d\n");
        SetFormat(debug, case_index_and_target,
            "test compare between %s::index and %d\n");
        SetFormat(error, case_index_and_target,
            "error %s::index is not same with %d\n");

        CaseI case_index;
        SetFormat(info, case_index, 
            "test compare between %s::index and %s::Index\n");
        SetFormat(debug, case_index,
            "test compare between %s::index and %s::Index\n");
        SetFormat(error, case_index,
            "error %s::index is not same with %s::Index\n");

        CaseSTa case_size_and_target;
        SetFormat(info, case_size_and_target, 
            "test compare between %s::size and %d\n");
        SetFormat(debug, case_size_and_target,
            "test compare between %s::size and %d\n");
        SetFormat(error, case_size_and_target,
            "error %s::size is not same with %d\n");

        CaseS case_size;
        SetFormat(info, case_size, 
            "test compare between %s::size and %s::Size\n");
        SetFormat(debug, case_size,
            "test compare between %s::size and %s::Size\n");
        SetFormat(error, case_size,
            "error %s::size is not same with %s::Size\n");
    }
 
    template<typename TSwitch, typename TAliasType, typename TIndex,
        typename TSize>
    bool Result(const CaseATTa&, VariableTestSwitch<TSwitch, TAliasType, TIndex, 
        TSize>& var)
    {
        return typeid(typename TSwitch::type).hash_code() ==
            typeid(TAliasType).hash_code();
    }

    template<typename TSwitch, typename TAliasType, typename TIndex,
        typename TSize>
    bool Result(const CaseAT&, VariableTestSwitch<TSwitch, TAliasType, TIndex, 
        TSize>& var)
    {
        return typeid(typename TSwitch::type).hash_code() ==
            typeid(typename TSwitch::Type).hash_code();
    }

    template<typename TSwitch, typename TAliasType, typename TIndex,
        typename TSize>
    bool Result(const CaseITa&, VariableTestSwitch<TSwitch, TAliasType, TIndex, 
        TSize>& var)
    {
        return TSwitch::index == basic::test::var::At<
            IValIndex>(var).Get().Get();
    }

    template<typename TSwitch, typename TAliasType, typename TIndex,
        typename TSize>
    bool Result(const CaseI&, VariableTestSwitch<TSwitch, TAliasType, TIndex, 
        TSize>& var)
    {
        return TSwitch::index == TSwitch::Index;
    }

    template<typename TSwitch, typename TAliasType, typename TIndex,
        typename TSize>
    bool Result(const CaseSTa&, VariableTestSwitch<TSwitch, TAliasType, TIndex, 
        TSize>& var)
    {
        return TSwitch::size == basic::test::var::At<
            IValSize>(var).Get().Get();
    }

    template<typename TSwitch, typename TAliasType, typename TIndex,
        typename TSize>
    bool Result(const CaseS&, VariableTestSwitch<TSwitch, TAliasType, TIndex, 
        TSize>& var)
    {
        return TSwitch::size == TSwitch::Size;
    }
};

using Cases = basic::test::type::Parameter<CaseATTa, CaseAT, CaseITa, 
    CaseI, CaseSTa, CaseS>;

struct A {};
struct B {};
struct C {};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("B", B);
BASIC_TEST_TYPE_NAME("C", C);

template<typename... TArgs>
struct basic::test::type::Name<basic::type::conditional::Switch<TArgs...>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format_cstr[] = "basic::type::conditional::Switch<%s>";
        const auto& param_cstr = basic::test::type::param::Name<
            basic::test::type::Parameter<TArgs...>>::CStr();
        return basic::test::cstr::Format(sizeof(_format_cstr) +
            param_cstr.Size(), _format_cstr, *param_cstr);\
    }
};

using TDefaultSwitch0_0 = basic::type::conditional::Switch<std::false_type>;

BASIC_TEST_TYPE_NAME("basic::type::conditional::Switch<std::false_type>",
    basic::type::conditional::Switch<std::false_type>);

typedef VariableTestSwitch<TDefaultSwitch0_0, std::false_type,
    std::size_t, std::size_t> T1Var1;

T1Var1 t1_var1(0, 0);
    
REGISTER_TEST(t1, new TestSwitch<Cases, T1Var1>(t1_var1));

using TDefaultSwitch1_0 = basic::type::conditional::Switch<std::false_type, 
    std::true_type>;
using TDefaultSwitch1_1 = basic::type::conditional::Switch<std::false_type, 
    std::false_type>;

typedef VariableTestSwitch<TDefaultSwitch1_0, std::true_type,
    std::size_t, std::size_t> T2Var1;
typedef VariableTestSwitch<TDefaultSwitch1_1, std::false_type,
    std::size_t, std::size_t> T2Var2;

T2Var1 t2_var1(0, 1);
T2Var2 t2_var2(1, 1);

REGISTER_TEST(t2, new TestSwitch<Cases, T2Var1, T2Var2>(t2_var1, t2_var2));

using TDefaultSwitch2_0 = basic::type::conditional::Switch<std::false_type, 
    std::true_type, std::false_type>;
using TDefaultSwitch2_1 = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::true_type>;  
using TDefaultSwitch2_2 = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type>;

typedef VariableTestSwitch<TDefaultSwitch2_0, std::true_type,
    std::size_t, std::size_t> T3Var1;
typedef VariableTestSwitch<TDefaultSwitch2_1, std::true_type,
    std::size_t, std::size_t> T3Var2;
typedef VariableTestSwitch<TDefaultSwitch2_2, std::false_type,
    std::size_t, std::size_t> T3Var3;

T3Var1 t3_var1(0, 2);
T3Var2 t3_var2(1, 2);
T3Var3 t3_var3(2, 2);

REGISTER_TEST(t3, new TestSwitch<Cases, T3Var1, T3Var2, T3Var3>(t3_var1,
    t3_var2, t3_var3));

using TDefaultSwitch4_0 = basic::type::conditional::Switch<std::false_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using TDefaultSwitch4_1 = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;  
using TDefaultSwitch4_2 = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>; 
using TDefaultSwitch4_3 = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>; 
using TDefaultSwitch4_4 = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;    

typedef VariableTestSwitch<TDefaultSwitch4_0, std::true_type,
    std::size_t, std::size_t> T4Var1;
typedef VariableTestSwitch<TDefaultSwitch4_1, std::true_type,
    std::size_t, std::size_t> T4Var2;
typedef VariableTestSwitch<TDefaultSwitch4_2, std::true_type,
    std::size_t, std::size_t> T4Var3;
typedef VariableTestSwitch<TDefaultSwitch4_3, std::true_type,
    std::size_t, std::size_t> T4Var4;
typedef VariableTestSwitch<TDefaultSwitch4_4, std::false_type,
    std::size_t, std::size_t> T4Var5;

T4Var1 t4_var1(0, 4);
T4Var2 t4_var2(1, 4);
T4Var3 t4_var3(2, 4);
T4Var4 t4_var4(3, 4);
T4Var5 t4_var5(4, 4);

REGISTER_TEST(t4, new TestSwitch<Cases, T4Var1, T4Var2, T4Var3, T4Var4, 
    T4Var5>(t4_var1, t4_var2, t4_var3, t4_var4, t4_var5));

using TASwitch3_1 = basic::type::conditional::Switch<A, A, B, C>;
using TBSwitch3_2 = basic::type::conditional::Switch<B, A, B, C>;
using TCSwitch3_3 = basic::type::conditional::Switch<C, A, B, C>;
using TASwitch3_4 = basic::type::conditional::Switch<A, B, C, A>;
using TBSwitch3_5 = basic::type::conditional::Switch<B, B, C, A>;
using TCSwitch3_6 = basic::type::conditional::Switch<C, B, C, A>;
using TASwitch3_7 = basic::type::conditional::Switch<A, C, A, B>;
using TBSwitch3_8 = basic::type::conditional::Switch<B, C, A, B>;
using TCSwitch3_9 = basic::type::conditional::Switch<C, C, A, B>;

typedef VariableTestSwitch<TASwitch3_1, B,std::size_t, std::size_t> T5Var1;
typedef VariableTestSwitch<TBSwitch3_2, A,std::size_t, std::size_t> T5Var2;
typedef VariableTestSwitch<TCSwitch3_3, A,std::size_t, std::size_t> T5Var3;
typedef VariableTestSwitch<TASwitch3_4, B,std::size_t, std::size_t> T5Var4;
typedef VariableTestSwitch<TBSwitch3_5, C,std::size_t, std::size_t> T5Var5;
typedef VariableTestSwitch<TCSwitch3_6, B,std::size_t, std::size_t> T5Var6;
typedef VariableTestSwitch<TASwitch3_7, C,std::size_t, std::size_t> T5Var7;
typedef VariableTestSwitch<TBSwitch3_8, C,std::size_t, std::size_t> T5Var8;
typedef VariableTestSwitch<TCSwitch3_9, A,std::size_t, std::size_t> T5Var9;

T5Var1 t5_var1(1, 3);
T5Var2 t5_var2(0, 3);
T5Var3 t5_var3(0, 3);
T5Var4 t5_var4(0, 3);
T5Var5 t5_var5(1, 3);
T5Var6 t5_var6(0, 3);
T5Var7 t5_var7(0, 3);
T5Var8 t5_var8(0, 3);
T5Var9 t5_var9(1, 3);

REGISTER_TEST(t5, new TestSwitch<Cases, T5Var1, T5Var2, T5Var3, T5Var4,
    T5Var5, T5Var6, T5Var7, T5Var8, T5Var9>(t5_var1, t5_var2, t5_var3,
        t5_var4, t5_var5, t5_var6, t5_var7, t5_var8, t5_var9));

int main()
{
    return RUN_TEST();
}

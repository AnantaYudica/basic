#include "macro/IsSameWith.h"
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

struct CaseAVTTa {}; // case alias value type and target
struct CaseAVT {}; // case alias value type
struct CaseVTa {}; // case value and target
struct CaseV {}; // case value 

template<typename TIsSame, typename TAliasVal, TAliasVal AliasValue>
using VariableTestIsSame = basic::test::Variable<
    TIsSame,
    TAliasVal,  
    basic::test::type::Value<TAliasVal, AliasValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IIsSame = 0;
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
    ArgTypeName<IIsSame>,
    ArgTypeName<1>> ArgCaseAVTTa;

typedef basic::test::msg::Base<CaseAVTTa, char, ArgCaseAVTTa, 
    ArgCaseAVTTa, ArgCaseAVTTa> MsgBaseCaseAVTTa;

typedef basic::test::msg::Argument<CaseAVT, 
    ArgTypeName<IIsSame>,
    ArgTypeName<IIsSame>> ArgCaseAVT;

typedef basic::test::msg::Base<CaseAVT, char, ArgCaseAVT, 
    ArgCaseAVT, ArgCaseAVT> MsgBaseCaseAVT;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IIsSame>,
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValAliasValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, 
    ArgTypeName<IIsSame>,
    ArgTypeName<IIsSame>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
class TestIsSame :
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestIsSame<TCases,
         TVars...>>,
    public basic::test::Case<TestIsSame<TCases, TVars...>, TCases>,
    public basic::test::Base<TestIsSame<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestIsSame<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestIsSame<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestIsSame<TCases, TVars...>, 
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
    TestIsSame(TVars&... vars) :
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
    
    template<typename TIsSame, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVTTa&, VariableTestIsSame<
        TIsSame, TAliasVal, AliasValue>& var)
    {
        return typeid(typename TIsSame::value_type).hash_code() ==
            typeid(TAliasVal).hash_code();
    }
    
    template<typename TIsSame, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVT&, VariableTestIsSame<
        TIsSame, TAliasVal, AliasValue>& var)
    {
        return typeid(typename TIsSame::value_type).hash_code() ==
            typeid(typename TIsSame::ValueType).hash_code();
    }
    
    template<typename TIsSame, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseVTa&, VariableTestIsSame<
        TIsSame, TAliasVal, AliasValue>& var)
    {
        return AliasValue == TIsSame::value;
    }
    
    template<typename TIsSame, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseV&, VariableTestIsSame<
        TIsSame, TAliasVal, AliasValue>& var)
    {
        return TIsSame::value == TIsSame::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A
{};

struct B
{};

template<typename>
struct C
{};

template<typename>
struct D
{};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);

const char* true_cstr = "true";
const char* false_cstr = "false";

const char* BoolToString(bool&& b)
{
    return b ? true_cstr : false_cstr;
}

/**
 *  template<T> 
 *  struct IsSame1
 *  { 
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = false;
 *      static constexpr ValueType Value = false;
 *  };
 *  template<>
 *  struct IsSame1<A>
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = true;
 *      static constexpr ValueType Value = true;
 *  }
 * */

__DEFINE_IS_SAME_WITH_(IsSame1, T,,, A);

template<typename T>
using TIsSame1 = IsSame1<T>;

BASIC_TEST_TYPE_NAME("IsSame1<A>", IsSame1<A>);
BASIC_TEST_TYPE_NAME("IsSame1<B>", IsSame1<B>);

typedef VariableTestIsSame<TIsSame1<A>, bool, true> T1Var1;
typedef VariableTestIsSame<TIsSame1<B>, bool, false> T1Var2;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);

REGISTER_TEST(t1, new TestIsSame<Cases, T1Var1, 
    T1Var2>(t1_var1, t1_var2));

/**
 *  template<typename T, typename = void> 
 *  struct IsSame2
 *  { 
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = false;
 *      static constexpr ValueType Value = false;
 *  };
 *  template<>
 *  struct IsSame2<A>
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = true;
 *      static constexpr ValueType Value = true;
 *  }
 * */

#define __DEFINE_IS_SAME_WITH_TMPL_PARAM_LIST_PRIMARY_TPLP1(\
    __T_NAME__)\
typename __T_NAME__, typename = void

__DEFINE_IS_SAME_WITH_(IsSame2, T, TPLP1,, A);

template<typename T>
using TIsSame2 = IsSame2<T>;

BASIC_TEST_TYPE_NAME("IsSame2<A>", IsSame2<A>);
BASIC_TEST_TYPE_NAME("IsSame2<B>", IsSame2<B>);

typedef VariableTestIsSame<TIsSame2<A>, bool, true> T2Var1;
typedef VariableTestIsSame<TIsSame2<B>, bool, false> T2Var2;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);

REGISTER_TEST(t2, new TestIsSame<Cases, T2Var1, 
    T2Var2>(t2_var1, t2_var2));

/**
 *  template<typename T> 
 *  struct IsSame3
 *  { 
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = false;
 *      static constexpr ValueType Value = false;
 *  };
 *  template<typename T1>
 *  struct IsSame3<C<T1>>
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = true;
 *      static constexpr ValueType Value = true;
 *  }
 * */

#define __DEFINE_IS_SAME_WITH_TMPL_PARAM_LIST_SPECIALIZE_TPLS1(\
    __T_NAME__)\
typename T1

__DEFINE_IS_SAME_WITH_(IsSame3, T,, TPLS1, C<T1>);

template<typename T>
using TIsSame3 = IsSame3<T>;

BASIC_TEST_TYPE_NAME("IsSame3<C<void>>", IsSame3<C<void>>);
BASIC_TEST_TYPE_NAME("IsSame3<D<void>>", IsSame3<D<void>>);
BASIC_TEST_TYPE_NAME("IsSame3<A>", IsSame3<A>);

typedef VariableTestIsSame<TIsSame3<C<void>>, bool, true> T3Var1;
typedef VariableTestIsSame<TIsSame3<D<void>>, bool, false> T3Var2;
typedef VariableTestIsSame<TIsSame3<A>, bool, false> T3Var3;

T3Var1 t3_var1(&BoolToString);
T3Var2 t3_var2(&BoolToString);
T3Var3 t3_var3(&BoolToString);

REGISTER_TEST(t3, new TestIsSame<Cases, T3Var1, T3Var2,
    T3Var3>(t3_var1, t3_var2, t3_var3));

int main()
{
    return RUN_TEST();
}

#include "type/Identification.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"

#include <type_traits>
#include <typeinfo>

struct CaseIsId {};
struct CaseValidIdValue {};
struct CaseValidIdHasType {};
struct CaseValidIdType {};

template<typename T>
auto HasType(int) -> decltype(std::declval<typename T::Type>(), 
    std::declval<typename T::type>(), std::true_type());

template<typename T>
std::false_type HasType(...); 

template<typename T>
auto GetType1(int) -> decltype(std::declval<typename T::Type>());

template<typename T>
void GetType1(...);

template<typename T>
auto GetType2(int) -> decltype(std::declval<typename T::type>());

template<typename T>
void GetType2(...);

template<typename TId, bool TIIdVal, bool TVIdVVal, typename... TArgs>
using VariableIdentification = basic::test::Variable<TId, 
    basic::test::type::Value<bool, TIIdVal>,
    basic::test::var::Value<const char*>,
    basic::test::type::Value<bool, TVIdVVal>, 
    basic::test::var::Value<const char*>,
    basic::test::type::Parameter<TArgs...>>;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgTypeValue = basic::test::msg::arg::type::Value<I>;

template<std::size_t I>
using ArgVarValue = basic::test::msg::arg::var::Value<I>;

typedef basic::test::msg::Argument<CaseIsId, ArgTypeName<0>, 
    ArgTypeName<0>, ArgVarValue<2>> ArgCaseIsId;

typedef basic::test::msg::Base<CaseIsId, char, ArgCaseIsId, 
    ArgCaseIsId, ArgCaseIsId> MsgBaseCaseIsId;

typedef basic::test::msg::Argument<CaseValidIdValue, ArgTypeName<0>, 
    ArgTypeParamName<5>, ArgTypeName<0>, ArgTypeParamName<5>, 
    ArgVarValue<4>> ArgCaseValidIdValue;

typedef basic::test::msg::Base<CaseValidIdValue, char, ArgCaseValidIdValue, 
    ArgCaseValidIdValue, ArgCaseValidIdValue> MsgBaseCaseValidIdValue;

typedef basic::test::msg::Argument<CaseValidIdHasType, ArgTypeName<0>,
    ArgTypeParamName<5>> ArgCaseValidIdHasType;

typedef basic::test::msg::Base<CaseValidIdHasType, char, ArgCaseValidIdHasType, 
    ArgCaseValidIdHasType, ArgCaseValidIdHasType> MsgBaseCaseValidIdHasType;

typedef basic::test::msg::Argument<CaseValidIdType, ArgTypeName<0>,
    ArgTypeParamName<5>, ArgTypeName<0>, ArgTypeParamName<5>, 
    ArgTypeName<0>> ArgCaseValidIdType;

typedef basic::test::msg::Base<CaseValidIdType, char, ArgCaseValidIdType, 
    ArgCaseValidIdType, ArgCaseValidIdType> MsgBaseCaseValidIdType;

template<typename TCases, typename... TVars>
class TestIdentification :
    public MsgBaseCaseIsId,
    public MsgBaseCaseValidIdValue,
    public MsgBaseCaseValidIdHasType,
    public MsgBaseCaseValidIdType,
    public basic::test::Message<BASIC_TEST, TestIdentification<TCases, 
        TVars...>>,
    public basic::test::Case<TestIdentification<TCases, TVars...>, TCases>,
    public basic::test::Base<TestIdentification<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestIdentification<TCases, TVars...>, 
        TVars...> BaseType;
    typedef basic::test::Case<TestIdentification<TCases, TVars...>, 
        TCases> BaseCaseType;
    typedef basic::test::Message<BASIC_TEST, TestIdentification<TCases, 
        TVars...>> BaseMessageType;
protected:
    using MsgBaseCaseIsId::SetFormat;
    using MsgBaseCaseValidIdValue::SetFormat;
    using MsgBaseCaseValidIdHasType::SetFormat;
    using MsgBaseCaseValidIdType::SetFormat;
public:
    using MsgBaseCaseIsId::Format;
    using MsgBaseCaseValidIdValue::Format;
    using MsgBaseCaseValidIdHasType::Format;
    using MsgBaseCaseValidIdType::Format;
    using MsgBaseCaseIsId::Argument;
    using MsgBaseCaseValidIdValue::Argument;
    using MsgBaseCaseValidIdHasType::Argument;
    using MsgBaseCaseValidIdType::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestIdentification(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        CaseIsId case_is_identification;
        SetFormat(info, case_is_identification, 
            "test compare between { basic::type::IsIdentification<"
            "%s>::value or between basic::type::IsIdentification<"
            "%s>::Value } and %s\n");
        SetFormat(debug, case_is_identification,
            "test compare between { basic::type::IsIdentification<"
            "%s>::value or between basic::type::IsIdentification<"
            "%s>::Value } and %s\n");
        SetFormat(error, case_is_identification,
            "error { basic::type::IsIdentification<%s>::value or "
            "basic::type::IsIdentification<%s>::Value } "
            "is not same with %s\n");

        CaseValidIdValue case_valid_id_val;
        SetFormat(info, case_valid_id_val, 
            "test compare between { basic::type::Validation<"
            "%s, %s>::value or basic::type::Validation<"
            "%s, %s>::Value } and %s\n");
        SetFormat(debug, case_valid_id_val,
            "test compare between { basic::type::Validation<"
            "%s, %s>::value or basic::type::Validation<"
            "%s, %s>::Value } and %s\n");
        SetFormat(error, case_valid_id_val,
            "error { basic::type::Validation<%s, %s>::value or "
            "basic::type::Validation<%s, %s>::Value }"
            "is not same with %s\n");

        CaseValidIdHasType case_valid_id_has_type;
        SetFormat(info, case_valid_id_has_type, 
            "test type definition basic::type::Validation<%s, %s> has "
            "a members { type and Type }\n");
        SetFormat(debug, case_valid_id_has_type,
            "test type definition basic::type::Validation<%s, %s> has "
            "a members { type and Type }\n");
        SetFormat(error, case_valid_id_has_type,
            "error basic::type::Validation<%s, %s> has no members "
            "{ type and Type }\n");

        CaseValidIdType case_valid_id_type;
        SetFormat(info, case_valid_id_type, 
            "test compare between { basic::type::Validation<%s, %s>::type or "
            "between basic::type::Validation<%s, %s>::Type } and %s\n");
        SetFormat(debug, case_valid_id_type,
            "test compare between { basic::type::Validation<%s, %s>::type or "
            "between basic::type::Validation<%s, %s>::Type } and %s\n");
        SetFormat(error, case_valid_id_type,
            "error compare between { basic::type::Validation<%s, %s>::type or "
            "between basic::type::Validation<%s, %s>::Type } "
            "is not same with %s\n");
    }
public:
    template<typename TId, bool TIIdVal, bool TVIdVVal, typename... TArgs>
    bool Result(const CaseIsId&, VariableIdentification<TId, 
        TIIdVal, TVIdVVal, TArgs...>& var)
    {
        return basic::type::IsIdentification<TId>::Value == TIIdVal &&
            basic::type::IsIdentification<TId>::value == TIIdVal;
    }

    template<typename TId, bool TIIdVal, bool TVIdVVal, typename... TArgs>
    bool Result(const CaseValidIdValue&, VariableIdentification<TId, 
        TIIdVal, TVIdVVal, TArgs...>& var)
    {
        return basic::type::Validation<TId, TArgs...>::Value == TVIdVVal;
    }

    template<typename TId, bool TIIdVal, bool TVIdVVal, typename... TArgs>
    bool Result(const CaseValidIdHasType&, VariableIdentification<TId, 
        TIIdVal, TVIdVVal, TArgs...>& var)
    {
        return typeid(decltype(HasType<basic::type::
            Validation<TId, TArgs...>>(0))).hash_code() ==
            typeid(std::true_type).hash_code();
    }

    template<typename TId, bool TIIdVal, bool TVIdVVal, typename... TArgs>
    bool Result(const CaseValidIdType&, VariableIdentification<TId, 
        TIIdVal, TVIdVVal, TArgs...>& var)
    {
        return typeid(decltype(GetType1<basic::type::Validation<TId, 
            TArgs...>>(0))).hash_code() == typeid(TId).hash_code() &&
            typeid(decltype(GetType2<basic::type::Validation<TId, 
                TArgs...>>(0))).hash_code() == typeid(TId).hash_code();
    }
};


BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("float", float);

const char * true_cstr = "true";
const char * false_cstr = "false";

typedef VariableIdentification<int, false, false> T1Var1Type;
typedef VariableIdentification<int, false, false, int> T1Var2Type;

T1Var1Type t1_var1(false_cstr, false_cstr);
T1Var2Type t1_var2(false_cstr, false_cstr);

REGISTER_TEST(t1, new TestIdentification<basic::test::type::
    Parameter<CaseIsId, CaseValidIdValue>, T1Var1Type, T1Var2Type>(t1_var1, 
        t1_var2));

struct Number
{};

typedef basic::type::Identification<Number> NumberId;

BASIC_TEST_TYPE_NAME("Number", Number);

struct Integer
{};

template<>
struct basic::type::Identification<Integer> : NumberId
{};

typedef basic::type::Identification<Integer> IntegerId;

BASIC_TEST_TYPE_NAME("Integer", Integer);

struct Floating
{};

template<>
struct basic::type::Identification<Floating> : NumberId
{};

typedef basic::type::Identification<Floating> FloatingId;

BASIC_TEST_TYPE_NAME("Floating", Floating);

template<>
struct basic::type::Identification<char> : IntegerId
{};

typedef basic::type::Identification<char> CharId;

template<>
struct basic::type::Identification<int> : IntegerId
{};

typedef basic::type::Identification<int> IntId;

template<>
struct basic::type::Identification<float> : FloatingId
{};

typedef basic::type::Identification<float> FloatId;

template<typename T>
struct basic::test::type::Name<basic::type::Identification<T>>
{
    template<typename TChar= char>
    static basic::test::CString<TChar> CStr()
    {
        static TChar format_id_name[] = "basic::type::Identification<%s>";
        const auto& name_cstr = basic::test::type::Name<T>::CStr();
        return basic::test::cstr::Format(30 + name_cstr.Size(), 
            format_id_name, *name_cstr);
    }
};

typedef VariableIdentification<NumberId, true, true, NumberId> T2Var1Type;
typedef VariableIdentification<IntegerId, true, true, NumberId, 
    IntegerId> T2Var2Type;
typedef VariableIdentification<FloatingId, true, true, NumberId, 
    FloatingId> T2Var3Type;
typedef VariableIdentification<CharId, true, true, CharId, 
    IntegerId, NumberId> T2Var4Type;
typedef VariableIdentification<IntId, true, true, IntId, 
    IntegerId, NumberId> T2Var5Type;
typedef VariableIdentification<FloatId, true, true, FloatId,
    FloatingId, NumberId> T2Var6Type;

T2Var1Type t2_var1(true_cstr, true_cstr);
T2Var2Type t2_var2(true_cstr, true_cstr);
T2Var3Type t2_var3(true_cstr, true_cstr);
T2Var4Type t2_var4(true_cstr, true_cstr);
T2Var5Type t2_var5(true_cstr, true_cstr);
T2Var6Type t2_var6(true_cstr, true_cstr);

REGISTER_TEST(t2, new TestIdentification<
    basic::test::type::Parameter<CaseIsId, CaseValidIdValue, 
        CaseValidIdHasType, CaseValidIdType>, 
    T2Var1Type, T2Var2Type, T2Var3Type, T2Var4Type, T2Var5Type, 
    T2Var6Type>(t2_var1, t2_var2, t2_var3, t2_var4, t2_var5, t2_var6));

typedef VariableIdentification<CharId, true, false, FloatingId,
    NumberId> T3Var1Type;
typedef VariableIdentification<IntId, true, false, FloatingId,
    NumberId> T3Var2Type;
typedef VariableIdentification<FloatId, true, false, IntegerId,
    NumberId> T3Var3Type;
typedef VariableIdentification<NumberId, true, false, int> T3Var4Type;

T3Var1Type t3_var1(true_cstr, false_cstr);
T3Var2Type t3_var2(true_cstr, false_cstr);
T3Var3Type t3_var3(true_cstr, false_cstr);
T3Var4Type t3_var4(true_cstr, false_cstr);

REGISTER_TEST(t3, new TestIdentification<
    basic::test::type::Parameter<CaseIsId, CaseValidIdValue>,
    T3Var1Type, T3Var2Type, T3Var3Type, T3Var4Type>(t3_var1, 
        t3_var2, t3_var3, t3_var4));

int main()
{
    return RUN_TEST();
}

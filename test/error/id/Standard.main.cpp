#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/id/Standard.h"
#include "error/id/rec/ToBytes.h"

#include <type_traits>
#include <utility>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

basic::test::CString<char> 
IdentificationToString(basic::error::Identification * && id)
{
    typedef typename basic::error::Identification::RecordType RecordType;
    constexpr std::size_t max_allocation = RecordType::MaximumAllocation();
    std::uint8_t block[max_allocation];
    std::size_t size_block = basic::error::id::rec::
        ToBytes((const RecordType &)*id, block, max_allocation);

    const std::size_t size = (size_block * 2);
    char * tmp = new char[size + 1];
    for(std::size_t i = 0, j = 0; i < size; i += 2, ++j)
    {
        std::uint8_t hex0 = block[j] >> 4;
        std::uint8_t hex1 = block[j] & std::uint8_t(0x0F);
        char ch0 = '0', ch1 = '0';
        ch0 += (hex0 <= 9 ? hex0 : (hex0 + 7));
        ch1 += (hex1 <= 9 ? hex1 : (hex1 + 7));
        tmp[i] = ch0;
        tmp[i + 1] = ch1;
    }
    tmp[size] = '\0';
    auto ret = basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "{Size : %d, Block : 0x%s}", size_block, tmp);
    delete[] tmp;
    return std::move(ret);
}

struct TestAliasCodeValueType {};
struct TestBaseOfIdentification {};
struct TestCastToIdentification {};

template<typename TObj>
using VariableTestIdStandard = basic::test::Variable<
    basic::error::defn::type::code::Value,
    basic::error::Identification,
    TObj,
    basic::test::Value<const char *>,
    basic::test::Value<TObj *>,
    basic::test::Value<basic::error::Identification *>,
    basic::test::type::Function<basic::test::CString<char>(basic::error::
        Identification * &&), &IdentificationToString>>;

constexpr std::size_t ICodeValueType = 0;
constexpr std::size_t IIdentificationType = 1;
constexpr std::size_t IObjType = 2;
constexpr std::size_t IObjName = 3;
constexpr std::size_t IObjValue = 4;
constexpr std::size_t IIdentificationValue = 5;
constexpr std::size_t IIdentificationToStringFunc = 6;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICodeValueType>> 
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestBaseOfIdentification,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IIdentificationType>> 
        ArgTestBaseOfIdentification;

typedef basic::test::msg::Base<TestBaseOfIdentification, char, 
    ArgTestBaseOfIdentification, ArgTestBaseOfIdentification, 
    ArgTestBaseOfIdentification> MessageBaseTestBaseOfIdentification;

typedef basic::test::msg::Argument<TestCastToIdentification,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::type::Function<IIdentificationToStringFunc,
        basic::test::msg::arg::Value<IIdentificationValue>>> 
        ArgTestCastToIdentification;

typedef basic::test::msg::Base<TestCastToIdentification, char, 
    ArgTestCastToIdentification, ArgTestCastToIdentification, 
    ArgTestCastToIdentification> MessageBaseTestCastToIdentification;


template<typename TCases, typename... TVariables>
struct TestIdStandard :
    public basic::test::Message<BASIC_TEST, TestIdStandard<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdStandard<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdStandard<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestBaseOfIdentification,
    public MessageBaseTestCastToIdentification
{
public:
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestBaseOfIdentification::Format;
    using MessageBaseTestBaseOfIdentification::SetFormat;
    using MessageBaseTestBaseOfIdentification::Argument;
    using MessageBaseTestCastToIdentification::Format;
    using MessageBaseTestCastToIdentification::SetFormat;
    using MessageBaseTestCastToIdentification::Argument;
    using basic::test::Case<TestIdStandard<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdStandard<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdStandard(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdStandard<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdStandard<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdStandard<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType {%s} is same with %s\n");
        SetFormat(error, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType {%s} is not same with %s\n");

        TestBaseOfIdentification testBaseOfIdentification;
        SetFormat(info, testBaseOfIdentification, "Test %s {%s} is base of "
            "%s\n");
        SetFormat(debug, testBaseOfIdentification, "Test %s {%s} is base of "
            "%s\n");
        SetFormat(error, testBaseOfIdentification, "Error %s {%s} is not "
            "base of %s\n");
        
        TestCastToIdentification testCastToIdentification;
        SetFormat(info, testCastToIdentification, "Test %s {%s} is same with "
            "%s %s\n");
        SetFormat(debug, testCastToIdentification, "Test %s {%s} is same with "
            "%s %s\n");
        SetFormat(error, testCastToIdentification, "Error %s {%s} is not "
            "same with %s %s\n");

    }
    template<typename TObj>
    bool Result(const TestAliasCodeValueType &, 
        VariableTestIdStandard<TObj> & var)
    {
        return typeid(typename basic::error::id::Standard::CodeValueType).
            hash_code() == typeid(basic::error::defn::type::code::Value).
            hash_code();
    }
    template<typename TObj>
    bool Result(const TestBaseOfIdentification &, 
        VariableTestIdStandard<TObj> & var)
    {
        return std::is_base_of<basic::error::Identification, TObj>::value;
    }
    template<typename TObj>
    bool Result(const TestCastToIdentification &, 
        VariableTestIdStandard<TObj> & var)
    {
        const auto & id_standard = *basic::test::var::At<IObjValue>(var).
            Get().Get();
        const auto & id = *basic::test::var::At<IIdentificationValue>(var).
            Get().Get();
        const bool check_error = id_standard.IsSystem() ? true :
            (id_standard.Error().Code() == id.Error().Code());
        const bool check_error_sys = !id_standard.IsSystem() ? true :
            (id_standard.ErrorSystem().Code() == id.ErrorSystem().Code() &&
                id_standard.ErrorSystem().Category() == 
                    id.ErrorSystem().Category());
        return id_standard.IsDefault() == id.IsDefault() &&
            id_standard.IsBad() == id.IsBad() &&
            id_standard.IsStandard() == id.IsStandard() &&
            id_standard.IsCatch() == id.IsCatch() &&
            id_standard.IsSystem() == id.IsSystem() &&
            check_error && check_error_sys;
    }
};

using Case1 = basic::test::type::Parameter<TestAliasCodeValueType,
    TestBaseOfIdentification, TestCastToIdentification>;

BASIC_TEST_TYPE_NAME("signed char", signed char);
BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("unsigned char", unsigned char);
BASIC_TEST_TYPE_NAME("short", short);
BASIC_TEST_TYPE_NAME("unsigned short", unsigned short);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("unsigned int", unsigned int);
BASIC_TEST_TYPE_NAME("long", long);
BASIC_TEST_TYPE_NAME("unsigned long", unsigned long);
BASIC_TEST_TYPE_NAME("long long", long long);
BASIC_TEST_TYPE_NAME("unsigned long long", unsigned long long);

BASIC_TEST_TYPE_NAME("basic::error::id::Standard", basic::error::id::Standard);
BASIC_TEST_TYPE_NAME("basic::error::Identification", 
    basic::error::Identification);

typedef VariableTestIdStandard<basic::error::id::Standard> T1Var1;

constexpr typename basic::error::id::Standard::CodeValueType code_value1 = 4;

basic::error::id::Standard obj1_1;
basic::error::id::Standard obj1_2{code_value1};

basic::error::Identification id1_1;
basic::error::Identification id1_2{basic::error::id::flag::Standard{}, 
    code_value1};

T1Var1 t1_var1{"obj1_1", &obj1_1, &id1_1};
T1Var1 t1_var2{"obj1_2", &obj1_2, &id1_2};

REGISTER_TEST(t1, new TestIdStandard<Case1, T1Var1, T1Var1>(t1_var1, t1_var2));

basic::error::id::Standard obj2_1{obj1_1};
basic::error::id::Standard obj2_2{obj1_2};

T1Var1 t2_var1{"obj2_1", &obj2_1, &id1_1};
T1Var1 t2_var2{"obj2_2", &obj2_2, &id1_2};

REGISTER_TEST(t2, new TestIdStandard<Case1, T1Var1, T1Var1>(t2_var1, t2_var2));

basic::error::id::Standard obj2_1_c{obj2_1};
basic::error::id::Standard obj2_2_c{obj2_2};

basic::error::id::Standard obj3_1{std::move(obj2_1_c)};
basic::error::id::Standard obj3_2{std::move(obj2_2_c)};

T1Var1 t3_var1{"obj3_1", &obj3_1, &id1_1};
T1Var1 t3_var2{"obj3_2", &obj3_2, &id1_2};

T1Var1 t3_var3{"obj2_1_c", &obj2_1_c, &id1_1};
T1Var1 t3_var4{"obj2_2_c", &obj2_2_c, &id1_1};

REGISTER_TEST(t3, new TestIdStandard<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1>(t3_var1, t3_var2, t3_var3, t3_var4));

int main()
{
    return RUN_TEST();
}

#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/id/System.h"
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

struct TestAliasSystemCategoryValueType {};
struct TestAliasSystemCodeValueType {};
struct TestBaseOfIdentification {};
struct TestCastToIdentification {};

template<typename TObj>
using VariableTestIdSystem = basic::test::Variable<
    basic::error::defn::type::code::Value,
    basic::error::defn::type::sys::categ::Value,
    basic::error::defn::type::sys::code::Value,
    basic::error::Identification,
    TObj,
    basic::test::Value<const char *>,
    basic::test::Value<TObj *>,
    basic::test::Value<basic::error::Identification *>,
    basic::test::type::Function<basic::test::CString<char>(basic::error::
        Identification * &&), &IdentificationToString>>;

constexpr std::size_t ICodeValueType = 0;
constexpr std::size_t ISystemCategoryValueType = 1;
constexpr std::size_t ISystemCodeValueType = 2;
constexpr std::size_t IIdentificationType = 3;
constexpr std::size_t IObjType = 4;
constexpr std::size_t IObjName = 5;
constexpr std::size_t IObjValue = 6;
constexpr std::size_t IIdentificationValue = 7;
constexpr std::size_t IIdentificationToStringFunc = 8;

typedef basic::test::msg::Argument<TestAliasSystemCategoryValueType,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ISystemCategoryValueType>> 
        ArgTestAliasSystemCategoryValueType;

typedef basic::test::msg::Base<TestAliasSystemCategoryValueType, char, 
    ArgTestAliasSystemCategoryValueType, ArgTestAliasSystemCategoryValueType, 
    ArgTestAliasSystemCategoryValueType> 
        MessageBaseTestAliasSystemCategoryValueType;

typedef basic::test::msg::Argument<TestAliasSystemCodeValueType,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ISystemCodeValueType>> 
        ArgTestAliasSystemCodeValueType;

typedef basic::test::msg::Base<TestAliasSystemCodeValueType, char, 
    ArgTestAliasSystemCodeValueType, ArgTestAliasSystemCodeValueType, 
    ArgTestAliasSystemCodeValueType> 
        MessageBaseTestAliasSystemCodeValueType;

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
struct TestIdSystem :
    public basic::test::Message<BASIC_TEST, TestIdSystem<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdSystem<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdSystem<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasSystemCategoryValueType,
    public MessageBaseTestAliasSystemCodeValueType,
    public MessageBaseTestBaseOfIdentification,
    public MessageBaseTestCastToIdentification
{
public:
    using MessageBaseTestAliasSystemCategoryValueType::Format;
    using MessageBaseTestAliasSystemCategoryValueType::SetFormat;
    using MessageBaseTestAliasSystemCategoryValueType::Argument;
    using MessageBaseTestAliasSystemCodeValueType::Format;
    using MessageBaseTestAliasSystemCodeValueType::SetFormat;
    using MessageBaseTestAliasSystemCodeValueType::Argument;
    using MessageBaseTestBaseOfIdentification::Format;
    using MessageBaseTestBaseOfIdentification::SetFormat;
    using MessageBaseTestBaseOfIdentification::Argument;
    using MessageBaseTestCastToIdentification::Format;
    using MessageBaseTestCastToIdentification::SetFormat;
    using MessageBaseTestCastToIdentification::Argument;
    using basic::test::Case<TestIdSystem<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdSystem<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdSystem(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdSystem<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdSystem<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdSystem<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestAliasSystemCategoryValueType testAliasSystemCategoryValueType;
        SetFormat(info, testAliasSystemCategoryValueType, "Test alias type "
            "%s::SystemCategoryValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasSystemCategoryValueType, "Test alias type "
            "%s::SystemCategoryValueType {%s} is same with %s\n");
        SetFormat(error, testAliasSystemCategoryValueType, "Error alias type "
            "%s::SystemCategoryValueType {%s} is not same with %s\n");

        TestAliasSystemCodeValueType testAliasSystemCodeValueType;
        SetFormat(info, testAliasSystemCodeValueType, "Test alias type "
            "%s::SystemCodeValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasSystemCodeValueType, "Test alias type "
            "%s::SystemCodeValueType {%s} is same with %s\n");
        SetFormat(error, testAliasSystemCodeValueType, "Error alias type "
            "%s::SystemCodeValueType {%s} is not same with %s\n");

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
    bool Result(const TestAliasSystemCategoryValueType &, 
        VariableTestIdSystem<TObj> & var)
    {
        return typeid(typename basic::error::id::System::
            SystemCategoryValueType).hash_code() == typeid(basic::error::
            defn::type::sys::categ::Value).hash_code();
    }
    template<typename TObj>
    bool Result(const TestAliasSystemCodeValueType &, 
        VariableTestIdSystem<TObj> & var)
    {
        return typeid(typename basic::error::id::System::
            SystemCodeValueType).hash_code() == typeid(basic::error::
            defn::type::sys::code::Value).hash_code();
    }
    template<typename TObj>
    bool Result(const TestBaseOfIdentification &, 
        VariableTestIdSystem<TObj> & var)
    {
        return std::is_base_of<basic::error::Identification, TObj>::value;
    }
    template<typename TObj>
    bool Result(const TestCastToIdentification &, 
        VariableTestIdSystem<TObj> & var)
    {
        const auto & id_sys = *basic::test::var::At<IObjValue>(var).
            Get().Get();
        const auto & id = *basic::test::var::At<IIdentificationValue>(var).
            Get().Get();
        const bool check_error = id_sys.IsSystem() ? true :
            (id_sys.Error().Code() == id.Error().Code());
        const bool check_error_sys = !id_sys.IsSystem() ? true :
            (id_sys.ErrorSystem().Code() == id.ErrorSystem().Code() &&
                id_sys.ErrorSystem().Category() == 
                    id.ErrorSystem().Category());
        return id_sys.IsDefault() == id.IsDefault() &&
            id_sys.IsBad() == id.IsBad() &&
            id_sys.IsStandard() == id.IsStandard() &&
            id_sys.IsCatch() == id.IsCatch() &&
            id_sys.IsSystem() == id.IsSystem() &&
            check_error && check_error_sys;
    }
};

using Case1 = basic::test::type::Parameter<TestAliasSystemCategoryValueType, 
    TestAliasSystemCodeValueType, TestBaseOfIdentification, 
    TestCastToIdentification>;

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

BASIC_TEST_TYPE_NAME("basic::error::id::System", basic::error::id::System);
BASIC_TEST_TYPE_NAME("basic::error::Identification", 
    basic::error::Identification);

typedef VariableTestIdSystem<basic::error::id::System> T1Var1;

constexpr typename basic::error::id::System::CodeValueType code_value1 = 4;
constexpr typename basic::error::id::System::CategoryValueType 
    categ_value1 = 0xB;

basic::error::id::System obj1_1;
basic::error::id::System obj1_2{categ_value1, code_value1};
basic::error::id::System obj1_3{basic::error::id::flag::Standard{}, 
    categ_value1, code_value1};

basic::error::Identification id1_1;
basic::error::Identification id1_2{basic::error::id::flag::System{}, 
    categ_value1, code_value1};
basic::error::Identification id1_3{basic::error::id::flag::System{},
    basic::error::id::flag::Standard{}, categ_value1, code_value1};

T1Var1 t1_var1{"obj1_1", &obj1_1, &id1_1};
T1Var1 t1_var2{"obj1_2", &obj1_2, &id1_2};
T1Var1 t1_var3{"obj1_3", &obj1_3, &id1_3};

REGISTER_TEST(t1, new TestIdSystem<Case1, T1Var1, T1Var1, T1Var1>(t1_var1,
    t1_var2, t1_var3));

basic::error::id::System obj2_1{obj1_1};
basic::error::id::System obj2_2{obj1_2};
basic::error::id::System obj2_3{obj1_3};

T1Var1 t2_var1{"obj2_1", &obj2_1, &id1_1};
T1Var1 t2_var2{"obj2_2", &obj2_2, &id1_2};
T1Var1 t2_var3{"obj2_3", &obj2_3, &id1_3};

REGISTER_TEST(t2, new TestIdSystem<Case1, T1Var1, T1Var1, T1Var1>(t2_var1,
    t2_var2, t2_var3));

basic::error::id::System obj2_1_c{obj2_1};
basic::error::id::System obj2_2_c{obj2_2};
basic::error::id::System obj2_3_c{obj2_3};

basic::error::id::System obj3_1{std::move(obj2_1_c)};
basic::error::id::System obj3_2{std::move(obj2_2_c)};
basic::error::id::System obj3_3{std::move(obj2_3_c)};

T1Var1 t3_var1{"obj3_1", &obj3_1, &id1_1};
T1Var1 t3_var2{"obj3_2", &obj3_2, &id1_2};
T1Var1 t3_var3{"obj3_3", &obj3_3, &id1_3};

T1Var1 t3_var4{"obj3_1_c", &obj2_1_c, &id1_1};
T1Var1 t3_var5{"obj3_2_c", &obj2_2_c, &id1_1};
T1Var1 t3_var6{"obj3_3_c", &obj2_3_c, &id1_1};

REGISTER_TEST(t3, new TestIdSystem<Case1, T1Var1, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1>(t3_var1, t3_var2, t3_var3, t3_var4,t3_var5, t3_var6));

int main()
{
    return RUN_TEST();
}
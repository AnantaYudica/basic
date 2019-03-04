#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/id/Catch.h"
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
struct TestAliasSystemCategoryValueType {};
struct TestAliasSystemCodeValueType {};
struct TestBaseOfIdentification {};
struct TestCastToIdentification {};

template<typename TObj>
using VariableTestIdCatch = basic::test::Variable<
    basic::error::defn::type::code::Value,
    basic::error::defn::type::system::categ::Value,
    basic::error::defn::type::system::code::Value,
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

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICodeValueType>> 
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

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
struct TestIdCatch :
    public basic::test::Message<BASIC_TEST, TestIdCatch<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdCatch<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdCatch<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasSystemCategoryValueType,
    public MessageBaseTestAliasSystemCodeValueType,
    public MessageBaseTestBaseOfIdentification,
    public MessageBaseTestCastToIdentification
{
public:
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
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
    using basic::test::Case<TestIdCatch<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdCatch<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdCatch(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdCatch<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdCatch<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdCatch<TCases, TVariables...>, 
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
    bool Result(const TestAliasCodeValueType &, 
        VariableTestIdCatch<TObj> & var)
    {
        return typeid(typename basic::error::id::Catch::CodeValueType).
            hash_code() == typeid(basic::error::defn::type::code::Value).
            hash_code();
    }
    template<typename TObj>
    bool Result(const TestAliasSystemCategoryValueType &, 
        VariableTestIdCatch<TObj> & var)
    {
        return typeid(typename basic::error::id::Catch::
            SystemCategoryValueType).hash_code() == typeid(basic::error::
            defn::type::system::categ::Value).hash_code();
    }
    template<typename TObj>
    bool Result(const TestAliasSystemCodeValueType &, 
        VariableTestIdCatch<TObj> & var)
    {
        return typeid(typename basic::error::id::Catch::
            SystemCodeValueType).hash_code() == typeid(basic::error::
            defn::type::system::code::Value).hash_code();
    }
    template<typename TObj>
    bool Result(const TestBaseOfIdentification &, 
        VariableTestIdCatch<TObj> & var)
    {
        return std::is_base_of<basic::error::Identification, TObj>::value;
    }
    template<typename TObj>
    bool Result(const TestCastToIdentification &, 
        VariableTestIdCatch<TObj> & var)
    {
        const auto & id_catch = *basic::test::var::At<IObjValue>(var).
            Get().Get();
        const auto & id = *basic::test::var::At<IIdentificationValue>(var).
            Get().Get();
        const bool check_error = id_catch.IsSystem() ? true :
            (id_catch.Error().Code() == id.Error().Code());
        const bool check_error_system = !id_catch.IsSystem() ? true :
            (id_catch.ErrorSystem().Code() == id.ErrorSystem().Code() &&
                id_catch.ErrorSystem().Category() == 
                    id.ErrorSystem().Category());
        return id_catch.IsDefault() == id.IsDefault() &&
            id_catch.IsBad() == id.IsBad() &&
            id_catch.IsStandard() == id.IsStandard() &&
            id_catch.IsCatch() == id.IsCatch() &&
            id_catch.IsSystem() == id.IsSystem() &&
            check_error && check_error_system;
    }
};

using Case1 = basic::test::type::Parameter<TestAliasCodeValueType,
    TestAliasSystemCategoryValueType, TestAliasSystemCodeValueType,
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

BASIC_TEST_TYPE_NAME("basic::error::id::Catch", basic::error::id::Catch);
BASIC_TEST_TYPE_NAME("basic::error::Identification", 
    basic::error::Identification);

typedef VariableTestIdCatch<basic::error::id::Catch> T1Var1;

constexpr typename basic::error::id::Catch::CodeValueType code_value1 = 4;
constexpr typename basic::error::id::Catch::SystemCategoryValueType
    categ_value1 = 0xB;

basic::error::id::Catch obj1_1;
basic::error::id::Catch obj1_2{code_value1};
basic::error::id::Catch obj1_3{basic::error::id::flag::Standard{}, 
    code_value1};
basic::error::id::Catch obj1_4{basic::error::id::flag::System{},
    categ_value1, code_value1};
basic::error::id::Catch obj1_5{basic::error::id::flag::System{},
    basic::error::id::flag::Standard{}, categ_value1, code_value1};

basic::error::Identification id1_1;
basic::error::Identification id1_2{basic::error::id::flag::Catch{},
    code_value1};
basic::error::Identification id1_3{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, code_value1};
basic::error::Identification id1_4{basic::error::id::flag::Catch{},
    basic::error::id::flag::System{}, categ_value1, code_value1};
basic::error::Identification id1_5{basic::error::id::flag::Catch{},
    basic::error::id::flag::System{}, basic::error::id::flag::Standard{}, 
    categ_value1, code_value1};

T1Var1 t1_var1{"obj1_1", &obj1_1, &id1_1};
T1Var1 t1_var2{"obj1_2", &obj1_2, &id1_2};
T1Var1 t1_var3{"obj1_3", &obj1_3, &id1_3};
T1Var1 t1_var4{"obj1_4", &obj1_4, &id1_4};
T1Var1 t1_var5{"obj1_5", &obj1_5, &id1_5};

REGISTER_TEST(t1, new TestIdCatch<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

basic::error::Identification id2_1;
basic::error::Identification id2_2{code_value1};
basic::error::Identification id2_3{basic::error::id::flag::Standard{}, 
    code_value1};
basic::error::Identification id2_4{basic::error::id::flag::System{}, 
    categ_value1, code_value1};
basic::error::Identification id2_5{basic::error::id::flag::System{}, 
    basic::error::id::flag::Standard{}, categ_value1, code_value1};

basic::error::Identification id2_0{basic::error::id::flag::Catch{},
    basic::error::Identification{}};

basic::error::id::Catch obj2_1{id2_1};
basic::error::id::Catch obj2_2{id2_2};
basic::error::id::Catch obj2_3{id2_3};
basic::error::id::Catch obj2_4{id2_4};
basic::error::id::Catch obj2_5{id2_5};

T1Var1 t2_var1{"obj2_1", &obj2_1, &id2_0};
T1Var1 t2_var2{"obj2_2", &obj2_2, &id1_2};
T1Var1 t2_var3{"obj2_3", &obj2_3, &id1_3};
T1Var1 t2_var4{"obj2_4", &obj2_4, &id1_4};
T1Var1 t2_var5{"obj2_5", &obj2_5, &id1_5};

REGISTER_TEST(t2, new TestIdCatch<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t2_var1, t2_var2, t2_var3, t2_var4, t2_var5));

basic::error::Identification id3_1;
basic::error::Identification id3_2{code_value1};
basic::error::Identification id3_3{basic::error::id::flag::System{}, 
    categ_value1, code_value1};

basic::error::Identification id3_0{basic::error::id::flag::Catch{},
    basic::error::id::flag::Standard{}, basic::error::Identification{}};

basic::error::id::Catch obj3_1{basic::error::id::flag::Standard{}, id3_1};
basic::error::id::Catch obj3_2{basic::error::id::flag::Standard{}, id3_2};
basic::error::id::Catch obj3_3{basic::error::id::flag::Standard{}, id3_3};

T1Var1 t3_var1{"obj3_1", &obj3_1, &id3_0};
T1Var1 t3_var2{"obj3_2", &obj3_2, &id1_3};
T1Var1 t3_var3{"obj3_3", &obj3_3, &id1_5};

REGISTER_TEST(t3, new TestIdCatch<Case1, T1Var1, T1Var1, T1Var1>(t3_var1, 
    t3_var2, t3_var3));

basic::error::id::Catch obj4_1{obj2_1};
basic::error::id::Catch obj4_2{obj3_1};
basic::error::id::Catch obj4_3{obj1_1};
basic::error::id::Catch obj4_4{obj1_2};
basic::error::id::Catch obj4_5{obj1_3};
basic::error::id::Catch obj4_6{obj1_4};
basic::error::id::Catch obj4_7{obj1_5};

T1Var1 t4_var1{"obj4_1", &obj4_1, &id2_0};
T1Var1 t4_var2{"obj4_2", &obj4_2, &id3_0};
T1Var1 t4_var3{"obj4_3", &obj4_3, &id1_1};
T1Var1 t4_var4{"obj4_4", &obj4_4, &id1_2};
T1Var1 t4_var5{"obj4_5", &obj4_5, &id1_3};
T1Var1 t4_var6{"obj4_6", &obj4_6, &id1_4};
T1Var1 t4_var7{"obj4_7", &obj4_7, &id1_5};

REGISTER_TEST(t4, new TestIdCatch<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1, T1Var1, T1Var1>(t4_var1, t4_var2, t4_var3, t4_var4,
        t4_var5, t4_var6, t4_var7));

basic::error::id::Catch obj4_1_c{obj4_1};
basic::error::id::Catch obj4_2_c{obj4_2};
basic::error::id::Catch obj4_3_c{obj4_3};
basic::error::id::Catch obj4_4_c{obj4_4};
basic::error::id::Catch obj4_5_c{obj4_5};
basic::error::id::Catch obj4_6_c{obj4_6};
basic::error::id::Catch obj4_7_c{obj4_7};

basic::error::id::Catch obj5_1{std::move(obj4_1_c)};
basic::error::id::Catch obj5_2{std::move(obj4_2_c)};
basic::error::id::Catch obj5_3{std::move(obj4_3_c)};
basic::error::id::Catch obj5_4{std::move(obj4_4_c)};
basic::error::id::Catch obj5_5{std::move(obj4_5_c)};
basic::error::id::Catch obj5_6{std::move(obj4_6_c)};
basic::error::id::Catch obj5_7{std::move(obj4_7_c)};

T1Var1 t5_var1{"obj5_1", &obj5_1, &id2_0};
T1Var1 t5_var2{"obj5_2", &obj5_2, &id3_0};
T1Var1 t5_var3{"obj5_3", &obj5_3, &id1_1};
T1Var1 t5_var4{"obj5_4", &obj5_4, &id1_2};
T1Var1 t5_var5{"obj5_5", &obj5_5, &id1_3};
T1Var1 t5_var6{"obj5_6", &obj5_6, &id1_4};
T1Var1 t5_var7{"obj5_7", &obj5_7, &id1_5};

T1Var1 t5_var8{"obj4_1_c", &obj4_1_c, &id1_1};
T1Var1 t5_var9{"obj4_2_c", &obj4_2_c, &id1_1};
T1Var1 t5_var10{"obj4_3_c", &obj4_3_c, &id1_1};
T1Var1 t5_var11{"obj4_4_c", &obj4_4_c, &id1_1};
T1Var1 t5_var12{"obj4_5_c", &obj4_5_c, &id1_1};
T1Var1 t5_var13{"obj4_6_c", &obj4_6_c, &id1_1};
T1Var1 t5_var14{"obj4_7_c", &obj4_7_c, &id1_1};

REGISTER_TEST(t5, new TestIdCatch<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1, T1Var1>(t5_var1, t5_var2, t5_var3, t5_var4,
        t5_var5, t5_var6, t5_var7, t5_var8, t5_var9, t5_var10, t5_var11,
        t5_var12, t5_var13, t5_var14));

int main()
{
    return RUN_TEST();
}
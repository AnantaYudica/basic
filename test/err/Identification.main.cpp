#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/Identification.h"
#include "err/id/rec/ToBytes.h"

#include <sstream>
#include <utility>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

const char * BoolToString(bool && b)
{
    return (b ? "true" : "false");
}

basic::test::CString<char> FlagToString(basic::err::id::Flag * && flag)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "0x%02X", reinterpret_cast<typename basic::err::id::
            Flag::ValueType &&>(*flag));
}

template<typename TErrorCodeValue>
basic::test::CString<char> ErrorToString(basic::err::id::rec::
    Error<TErrorCodeValue> * && err)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "%d", err->Code());
}

template<typename TErrorSystemCategoryValue, typename TErrorSystemCodeValue>
basic::test::CString<char> ErrorSystemToString(basic::err::id::rec::
    ErrorSystem<TErrorSystemCategoryValue, TErrorSystemCodeValue> * && err_sys)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "%d, %d", err_sys->Category(), err_sys->Code());
}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
basic::test::CString<char> RecordToString(basic::err::id::
    Record<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue> * && rec)
{
    constexpr std::size_t max_allocation = basic::err::id::
        Record<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue>::MaximumAllocation();
    std::uint8_t block[max_allocation];
    std::size_t size_block = basic::err::id::rec::
        ToBytes(*rec, block, max_allocation);

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

struct TestAliasFlagType {};
struct TestAliasCodeValueType {};
struct TestAliasSystemCategoryValueType {};
struct TestAliasSystemCodeValueType {};
struct TestAliasRecordType {};
struct TestAliasErrorType {};
struct TestAliasErrorSystemType {};
struct TestValueIsDefault {};
struct TestValueIsBad {};
struct TestValueIsStandard {};
struct TestValueIsCatch {};
struct TestValueIsSystem {};
struct TestValueFlag {};
struct TestValueError {};
struct TestValueErrorSystem {};
struct TestValueCastRecord {};
struct TestValueStream {};

using VariableTestIdentification = basic::test::Variable<
    basic::err::id::Flag,
    basic::err::defn::type::code::Value,
    basic::err::defn::type::sys::categ::Value,
    basic::err::defn::type::sys::code::Value,
    basic::err::defn::type::id::Record,
    typename basic::err::defn::type::id::Record::ErrorType,
    typename basic::err::defn::type::id::Record::ErrorSystemType,
    basic::err::Identification,
    basic::test::Value<const char *>,
    basic::test::Value<basic::err::Identification *>,
    basic::test::val::Sequence<bool, 5>,
    basic::test::Value<basic::err::id::Flag *>,
    basic::test::Value<typename basic::err::defn::type::id::
        Record::ErrorType *>,
    basic::test::Value<typename basic::err::defn::type::id::
        Record::ErrorSystemType *>,
    basic::test::Value<basic::err::defn::type::id::Record *>,
    basic::test::Value<const char *>,
    basic::test::type::Function<const char *(bool &&), &BoolToString>,
    basic::test::type::Function<basic::test::
        CString<char> (basic::err::id::Flag * &&), &FlagToString>,
    basic::test::type::Function<basic::test::CString<char>(
        typename basic::err::defn::type::id::Record::ErrorType * &&), 
        &ErrorToString>,
    basic::test::type::Function<basic::test::CString<char>(
        typename basic::err::defn::type::id::Record::ErrorSystemType * &&), 
        &ErrorSystemToString>,
    basic::test::type::Function<basic::test::CString<char>(basic::err::defn::
        type::id::Record * &&), &RecordToString>>;

constexpr std::size_t IFlagType = 0;
constexpr std::size_t ICodeValueType = 1;
constexpr std::size_t ISystemCategoryValueType = 2;
constexpr std::size_t ISystemCodeValueType = 3;
constexpr std::size_t IRecordType = 4;
constexpr std::size_t IErrorType = 5;
constexpr std::size_t IErrorSystemType = 6;
constexpr std::size_t IIdentificationType = 7;
constexpr std::size_t IObjName = 8;
constexpr std::size_t IObjValue = 9;
constexpr std::size_t IBoolSequenceValue = 10;
constexpr std::size_t IFlagValue = 11;
constexpr std::size_t IErrorValue = 12;
constexpr std::size_t IErrorSystemValue = 13;
constexpr std::size_t IRecordValue = 14;
constexpr std::size_t IStreamValue = 15;
constexpr std::size_t IBoolToString = 16;
constexpr std::size_t IFlagToString = 17;
constexpr std::size_t IErrorToString = 18;
constexpr std::size_t IErrorSystemToString = 19;
constexpr std::size_t IRecordToString = 20;

typedef basic::test::msg::Argument<TestAliasFlagType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IFlagType>> 
        ArgTestAliasFlagType;

typedef basic::test::msg::Base<TestAliasFlagType, char, 
    ArgTestAliasFlagType, ArgTestAliasFlagType, 
    ArgTestAliasFlagType> MessageBaseTestAliasFlagType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICodeValueType>> 
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasSystemCategoryValueType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ISystemCategoryValueType>> 
        ArgTestAliasSystemCategoryValueType;

typedef basic::test::msg::Base<TestAliasSystemCategoryValueType, char, 
    ArgTestAliasSystemCategoryValueType, ArgTestAliasSystemCategoryValueType, 
    ArgTestAliasSystemCategoryValueType> 
        MessageBaseTestAliasSystemCategoryValueType;

typedef basic::test::msg::Argument<TestAliasSystemCodeValueType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ISystemCodeValueType>> 
        ArgTestAliasSystemCodeValueType;

typedef basic::test::msg::Base<TestAliasSystemCodeValueType, char, 
    ArgTestAliasSystemCodeValueType, ArgTestAliasSystemCodeValueType, 
    ArgTestAliasSystemCodeValueType> MessageBaseTestAliasSystemCodeValueType;

typedef basic::test::msg::Argument<TestAliasRecordType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecordType>> 
        ArgTestAliasRecordType;

typedef basic::test::msg::Base<TestAliasRecordType, char, 
    ArgTestAliasRecordType, ArgTestAliasRecordType, 
    ArgTestAliasRecordType> MessageBaseTestAliasRecordType;

typedef basic::test::msg::Argument<TestAliasErrorType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorType>> 
        ArgTestAliasErrorType;

typedef basic::test::msg::Base<TestAliasErrorType, char, 
    ArgTestAliasErrorType, ArgTestAliasErrorType, 
    ArgTestAliasErrorType> MessageBaseTestAliasErrorType;

typedef basic::test::msg::Argument<TestAliasErrorSystemType,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorSystemType>> 
        ArgTestAliasErrorSystemType;

typedef basic::test::msg::Base<TestAliasErrorSystemType, char, 
    ArgTestAliasErrorSystemType, ArgTestAliasErrorSystemType, 
    ArgTestAliasErrorSystemType> MessageBaseTestAliasErrorSystemType;

typedef basic::test::msg::Argument<TestValueIsDefault,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToString,
        basic::test::msg::arg::val::seq::At<IBoolSequenceValue, 0>>> 
            ArgTestValueIsDefault;

typedef basic::test::msg::Base<TestValueIsDefault, char, 
    ArgTestValueIsDefault, ArgTestValueIsDefault, 
    ArgTestValueIsDefault> MessageBaseTestValueIsDefault;

typedef basic::test::msg::Argument<TestValueIsBad,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToString,
        basic::test::msg::arg::val::seq::At<IBoolSequenceValue, 1>>> 
            ArgTestValueIsBad;

typedef basic::test::msg::Base<TestValueIsBad, char, 
    ArgTestValueIsBad, ArgTestValueIsBad, 
    ArgTestValueIsBad> MessageBaseTestValueIsBad;

typedef basic::test::msg::Argument<TestValueIsStandard,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToString,
        basic::test::msg::arg::val::seq::At<IBoolSequenceValue, 2>>> 
            ArgTestValueIsStandard;

typedef basic::test::msg::Base<TestValueIsStandard, char, 
    ArgTestValueIsStandard, ArgTestValueIsStandard, 
    ArgTestValueIsStandard> MessageBaseTestValueIsStandard;

typedef basic::test::msg::Argument<TestValueIsCatch,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToString,
        basic::test::msg::arg::val::seq::At<IBoolSequenceValue, 3>>> 
            ArgTestValueIsCatch;

typedef basic::test::msg::Base<TestValueIsCatch, char, 
    ArgTestValueIsCatch, ArgTestValueIsCatch, 
    ArgTestValueIsCatch> MessageBaseTestValueIsCatch;

typedef basic::test::msg::Argument<TestValueIsSystem,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToString,
        basic::test::msg::arg::val::seq::At<IBoolSequenceValue, 4>>> 
            ArgTestValueIsSystem;

typedef basic::test::msg::Base<TestValueIsSystem, char, 
    ArgTestValueIsSystem, ArgTestValueIsSystem, 
    ArgTestValueIsSystem> MessageBaseTestValueIsSystem;

typedef basic::test::msg::Argument<TestValueFlag,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IFlagType>,
    basic::test::msg::arg::type::Function<IFlagToString,
        basic::test::msg::arg::Value<IFlagValue>>> ArgTestValueFlag;

typedef basic::test::msg::Base<TestValueFlag, char, 
    ArgTestValueFlag, ArgTestValueFlag, 
    ArgTestValueFlag> MessageBaseTestValueFlag;

typedef basic::test::msg::Argument<TestValueError,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Function<IErrorToString,
        basic::test::msg::arg::Value<IErrorValue>>> ArgTestValueError;

typedef basic::test::msg::Base<TestValueError, char, 
    ArgTestValueError, ArgTestValueError, 
    ArgTestValueError> MessageBaseTestValueError;

typedef basic::test::msg::Argument<TestValueErrorSystem,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorSystemType>,
    basic::test::msg::arg::type::Function<IErrorSystemToString,
        basic::test::msg::arg::Value<IErrorSystemValue>>> 
            ArgTestValueErrorSystem;

typedef basic::test::msg::Base<TestValueErrorSystem, char, 
    ArgTestValueErrorSystem, ArgTestValueErrorSystem, 
    ArgTestValueErrorSystem> MessageBaseTestValueErrorSystem;

typedef basic::test::msg::Argument<TestValueCastRecord,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::type::Function<IRecordToString,
        basic::test::msg::arg::Value<IRecordValue>>> 
            ArgTestValueCastRecord;

typedef basic::test::msg::Base<TestValueCastRecord, char, 
    ArgTestValueCastRecord, ArgTestValueCastRecord, 
    ArgTestValueCastRecord> MessageBaseTestValueCastRecord;

typedef basic::test::msg::Argument<TestValueStream,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::Value<IStreamValue>> ArgTestValueStream;

typedef basic::test::msg::Base<TestValueStream, char, 
    ArgTestValueStream, ArgTestValueStream, 
    ArgTestValueStream> MessageBaseArgTestValueStream;

template<typename TCases, typename... TVariables>
struct TestIdentification :
    public basic::test::Message<BASIC_TEST, TestIdentification<TCases, 
        TVariables...>>,
    public basic::test::Case<TestIdentification<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestIdentification<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasFlagType,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasSystemCategoryValueType,
    public MessageBaseTestAliasSystemCodeValueType,
    public MessageBaseTestAliasRecordType,
    public MessageBaseTestAliasErrorType,
    public MessageBaseTestAliasErrorSystemType,
    public MessageBaseTestValueIsDefault,
    public MessageBaseTestValueIsBad,
    public MessageBaseTestValueIsStandard,
    public MessageBaseTestValueIsCatch,
    public MessageBaseTestValueIsSystem,
    public MessageBaseTestValueFlag,
    public MessageBaseTestValueError,
    public MessageBaseTestValueErrorSystem,
    public MessageBaseTestValueCastRecord,
    public MessageBaseArgTestValueStream
{
public:
    using MessageBaseTestAliasFlagType::Format;
    using MessageBaseTestAliasFlagType::SetFormat;
    using MessageBaseTestAliasFlagType::Argument;
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestAliasSystemCategoryValueType::Format;
    using MessageBaseTestAliasSystemCategoryValueType::SetFormat;
    using MessageBaseTestAliasSystemCategoryValueType::Argument;
    using MessageBaseTestAliasSystemCodeValueType::Format;
    using MessageBaseTestAliasSystemCodeValueType::SetFormat;
    using MessageBaseTestAliasSystemCodeValueType::Argument;
    using MessageBaseTestAliasRecordType::Format;
    using MessageBaseTestAliasRecordType::SetFormat;
    using MessageBaseTestAliasRecordType::Argument;
    using MessageBaseTestAliasErrorType::Format;
    using MessageBaseTestAliasErrorType::SetFormat;
    using MessageBaseTestAliasErrorType::Argument;
    using MessageBaseTestAliasErrorSystemType::Format;
    using MessageBaseTestAliasErrorSystemType::SetFormat;
    using MessageBaseTestAliasErrorSystemType::Argument;
    using MessageBaseTestValueIsDefault::Format;
    using MessageBaseTestValueIsDefault::SetFormat;
    using MessageBaseTestValueIsDefault::Argument;
    using MessageBaseTestValueIsBad::Format;
    using MessageBaseTestValueIsBad::SetFormat;
    using MessageBaseTestValueIsBad::Argument;
    using MessageBaseTestValueIsStandard::Format;
    using MessageBaseTestValueIsStandard::SetFormat;
    using MessageBaseTestValueIsStandard::Argument;
    using MessageBaseTestValueIsCatch::Format;
    using MessageBaseTestValueIsCatch::SetFormat;
    using MessageBaseTestValueIsCatch::Argument;
    using MessageBaseTestValueIsSystem::Format;
    using MessageBaseTestValueIsSystem::SetFormat;
    using MessageBaseTestValueIsSystem::Argument;
    using MessageBaseTestValueFlag::Format;
    using MessageBaseTestValueFlag::SetFormat;
    using MessageBaseTestValueFlag::Argument;
    using MessageBaseTestValueError::Format;
    using MessageBaseTestValueError::SetFormat;
    using MessageBaseTestValueError::Argument;
    using MessageBaseTestValueErrorSystem::Format;
    using MessageBaseTestValueErrorSystem::SetFormat;
    using MessageBaseTestValueErrorSystem::Argument;
    using MessageBaseTestValueCastRecord::Format;
    using MessageBaseTestValueCastRecord::SetFormat;
    using MessageBaseTestValueCastRecord::Argument;
    using MessageBaseArgTestValueStream::Format;
    using MessageBaseArgTestValueStream::SetFormat;
    using MessageBaseArgTestValueStream::Argument;
    using basic::test::Case<TestIdentification<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestIdentification<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestIdentification(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestIdentification<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestIdentification<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestIdentification<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestAliasFlagType testAliasFlagType;
        SetFormat(info, testAliasFlagType, "Test alias type "
            "%s::FlagType {%s} is same with %s\n");
        SetFormat(debug, testAliasFlagType, "Test alias type "
            "%s::FlagType {%s} is same with %s\n");
        SetFormat(err, testAliasFlagType, "Error alias type "
            "%s::FlagType {%s} is not same with %s\n");

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType {%s} is same with %s\n");
        SetFormat(err, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType {%s} is not same with %s\n");

        TestAliasSystemCategoryValueType testAliasSystemCategoryValueType;
        SetFormat(info, testAliasSystemCategoryValueType, "Test alias type "
            "%s::SystemCategoryValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasSystemCategoryValueType, "Test alias type "
            "%s::SystemCategoryValueType {%s} is same with %s\n");
        SetFormat(err, testAliasSystemCategoryValueType, "Error alias type "
            "%s::SystemCategoryValueType {%s} is not same with %s\n");

        TestAliasSystemCodeValueType testAliasSystemCodeValueType;
        SetFormat(info, testAliasSystemCodeValueType, "Test alias type "
            "%s::SystemCodeValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasSystemCodeValueType, "Test alias type "
            "%s::SystemCodeValueType {%s} is same with %s\n");
        SetFormat(err, testAliasSystemCodeValueType, "Error alias type "
            "%s::SystemCodeValueType {%s} is not same with %s\n");

        TestAliasRecordType testAliasRecordType;
        SetFormat(info, testAliasRecordType, "Test alias type "
            "%s::RecordType {%s} is same with %s\n");
        SetFormat(debug, testAliasRecordType, "Test alias type "
            "%s::RecordType {%s} is same with %s\n");
        SetFormat(err, testAliasRecordType, "Error alias type "
            "%s::RecordType {%s} is not same with %s\n");

        TestAliasErrorType testAliasErrorType;
        SetFormat(info, testAliasErrorType, "Test alias type "
            "%s::ErrorType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorType, "Test alias type "
            "%s::ErrorType {%s} is same with %s\n");
        SetFormat(err, testAliasErrorType, "Error alias type "
            "%s::ErrorType {%s} is not same with %s\n");

        TestAliasErrorSystemType testAliasErrorSystemType;
        SetFormat(info, testAliasErrorSystemType, "Test alias type "
            "%s::ErrorSystemType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorSystemType, "Test alias type "
            "%s::ErrorSystemType {%s} is same with %s\n");
        SetFormat(err, testAliasErrorSystemType, "Error alias type "
            "%s::ErrorSystemType {%s} is not same with %s\n");

        TestValueIsDefault testValueIsDefault;
        SetFormat(info, testValueIsDefault, "Test return value "
            "%s::IsDefault() {%s} is same with %s\n");
        SetFormat(debug, testValueIsDefault, "Test return value "
            "%s::IsDefault() {%s} is same with %s\n");
        SetFormat(err, testValueIsDefault, "Error return value "
            "%s::IsDefault() {%s} is not same with %s\n");

        TestValueIsBad testValueIsBad;
        SetFormat(info, testValueIsBad, "Test return value "
            "%s::IsBad() {%s} is same with %s\n");
        SetFormat(debug, testValueIsBad, "Test return value "
            "%s::IsBad() {%s} is same with %s\n");
        SetFormat(err, testValueIsBad, "Error return value "
            "%s::IsBad() {%s} is not same with %s\n");

        TestValueIsStandard testValueIsStandard;
        SetFormat(info, testValueIsStandard, "Test return value "
            "%s::IsStandard() {%s} is same with %s\n");
        SetFormat(debug, testValueIsStandard, "Test return value "
            "%s::IsStandard() {%s} is same with %s\n");
        SetFormat(err, testValueIsStandard, "Error return value "
            "%s::IsStandard() {%s} is not same with %s\n");

        TestValueIsCatch testValueIsCatch;
        SetFormat(info, testValueIsCatch, "Test return value "
            "%s::IsCatch() {%s} is same with %s\n");
        SetFormat(debug, testValueIsCatch, "Test return value "
            "%s::IsCatch() {%s} is same with %s\n");
        SetFormat(err, testValueIsCatch, "Error return value "
            "%s::IsCatch() {%s} is not same with %s\n");

        TestValueIsSystem testValueIsSystem;
        SetFormat(info, testValueIsSystem, "Test return value "
            "%s::IsSystem() {%s} is same with %s\n");
        SetFormat(debug, testValueIsSystem, "Test return value "
            "%s::IsSystem() {%s} is same with %s\n");
        SetFormat(err, testValueIsSystem, "Error return value "
            "%s::IsSystem() {%s} is not same with %s\n");
        
        TestValueFlag testValueFlag;
        SetFormat(info, testValueFlag, "Test return value "
            "%s::Flag() {%s} is same with %s {%s}\n");
        SetFormat(debug, testValueFlag, "Test return value "
            "%s::Flag() {%s} is same with %s {%s}\n");
        SetFormat(err, testValueFlag, "Error return value "
            "%s::Flag() {%s} is not same with %s {%s}\n");

        TestValueError testValueError;
        SetFormat(info, testValueError, "Test return value "
            "%s::Error() {%s} is same with %s {%s}\n");
        SetFormat(debug, testValueError, "Test return value "
            "%s::Error() {%s} is same with %s {%s}\n");
        SetFormat(err, testValueError, "Error return value "
            "%s::Error() {%s} is not same with %s {%s}\n");

        TestValueErrorSystem testValueErrorSystem;
        SetFormat(info, testValueErrorSystem, "Test return value "
            "%s::ErrorSystem() {%s} is same with %s {%s}\n");
        SetFormat(debug, testValueErrorSystem, "Test return value "
            "%s::ErrorSystem() {%s} is same with %s {%s}\n");
        SetFormat(err, testValueErrorSystem, "Error return value "
            "%s::ErrorSystem() {%s} is not same with %s {%s}\n");
        
        TestValueCastRecord testValueCastRecord;
        SetFormat(info, testValueCastRecord, "Test cast from "
            "%s {%s} to %s is same with %s\n");
        SetFormat(debug, testValueCastRecord, "Test cast from "
            "%s {%s} to %s is same with %s\n");
        SetFormat(err, testValueCastRecord, "Error cast from "
            "%s {%s} to %s is not same with %s\n");

        TestValueStream testValueStream;
        SetFormat(info, testValueStream, "Test output %s {%s} "
            "to std::stringstream is same with \"%s\"\n");
        SetFormat(debug, testValueStream, "Test output %s {%s} "
            "to std::stringstream is same with \"%s\"\n");
        SetFormat(err, testValueStream, "Error output %s {%s} "
            "to std::stringstream is not same with \"%s\"\n");
    }
    bool Result(const TestAliasFlagType &, VariableTestIdentification & var)
    {
        return typeid(typename basic::err::Identification::FlagType).
            hash_code() == typeid(basic::err::id::Flag).hash_code();
    }
    bool Result(const TestAliasCodeValueType &, 
        VariableTestIdentification & var)
    {
        return typeid(typename basic::err::Identification::CodeValueType).
            hash_code() == typeid(basic::err::defn::type::code::
            Value).hash_code();
    }
    bool Result(const TestAliasSystemCategoryValueType &, 
        VariableTestIdentification & var)
    {
        return typeid(typename basic::err::
            Identification::SystemCategoryValueType).hash_code() == 
            typeid(basic::err::defn::type::sys::categ::Value).
            hash_code();
    }
    bool Result(const TestAliasSystemCodeValueType &, 
        VariableTestIdentification & var)
    {
        return typeid(typename basic::err::
            Identification::SystemCodeValueType).hash_code() == 
            typeid(basic::err::defn::type::sys::code::Value).hash_code();
    }
    bool Result(const TestAliasRecordType &, VariableTestIdentification & var)
    {
        return typeid(typename basic::err::Identification::RecordType).
            hash_code() == typeid(basic::err::defn::type::id::
            Record).hash_code();
    }
    bool Result(const TestAliasErrorType &, VariableTestIdentification & var)
    {
        return typeid(typename basic::err::Identification::ErrorType).
            hash_code() == typeid(typename basic::err::defn::type::id::
            Record::ErrorType).hash_code();
    }
    bool Result(const TestAliasErrorSystemType &, 
        VariableTestIdentification & var)
    {
        return typeid(typename basic::err::Identification::ErrorSystemType).
            hash_code() == typeid(typename basic::err::defn::type::id::
            Record::ErrorSystemType).hash_code();
    }
    bool Result(const TestValueIsDefault &, VariableTestIdentification & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->IsDefault()
            == basic::test::var::At<IBoolSequenceValue>(var).Get().
            template At<0>();
    }
    bool Result(const TestValueIsBad &, VariableTestIdentification & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->IsBad()
            == basic::test::var::At<IBoolSequenceValue>(var).Get().
            template At<1>();
    }
    bool Result(const TestValueIsStandard &, VariableTestIdentification & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->IsStandard()
            == basic::test::var::At<IBoolSequenceValue>(var).Get().
            template At<2>();
    }
    bool Result(const TestValueIsCatch &, VariableTestIdentification & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->IsCatch()
            == basic::test::var::At<IBoolSequenceValue>(var).Get().
            template At<3>();
    }
    bool Result(const TestValueIsSystem &, VariableTestIdentification & var)
    {
        return basic::test::var::At<IObjValue>(var).Get().Get()->IsSystem()
            == basic::test::var::At<IBoolSequenceValue>(var).Get().
            template At<4>();
    }
    bool Result(const TestValueFlag &, VariableTestIdentification & var)
    {
        const auto & flag = basic::test::var::At<IObjValue>(var).Get().
            Get()->Flag();
        const auto & flag_other = *basic::test::var::At<IFlagValue>(var).Get().
            Get();
        return flag.IsDefault() == flag_other.IsDefault() &&
            flag.IsBad() == flag_other.IsBad() &&
            flag.IsCatch() == flag_other.IsCatch() &&
            flag.IsStandard() == flag_other.IsStandard() &&
            flag.IsSystem() == flag_other.IsSystem();
    }
    bool Result(const TestValueError &, VariableTestIdentification & var)
    {
        const auto & err = basic::test::var::At<IObjValue>(var).Get().
            Get()->Error();
        const auto & err_other = *basic::test::var::At<IErrorValue>(var).Get().
            Get();
        return err.Code() == err_other.Code();
    }
    bool Result(const TestValueErrorSystem &, VariableTestIdentification & var)
    {
        const auto & err_sys = basic::test::var::At<IObjValue>(var).Get().
            Get()->ErrorSystem();
        const auto & err_sys_other = *basic::test::var::
            At<IErrorSystemValue>(var).Get().Get();
        return err_sys.Category() == err_sys_other.Category() &&
            err_sys.Code() == err_sys_other.Code();
    }
    bool Result(const TestValueCastRecord &, VariableTestIdentification & var)
    {
        typedef typename basic::err::Identification::RecordType RecordType;
        const auto & rec = static_cast<const RecordType&>(*basic::test::var::
            At<IObjValue>(var).Get().Get());
        const auto & rec_other = *basic::test::var::
            At<IRecordValue>(var).Get().Get();
        constexpr std::size_t max_alloc = RecordType::MaximumAllocation();
        std::uint8_t rec_block[max_alloc];
        std::uint8_t rec_other_block[max_alloc];
        std::size_t rec_block_size = basic::err::id::rec::
            ToBytes(rec, rec_block, max_alloc);
        std::size_t rec_other_block_size = basic::err::id::rec::
            ToBytes(rec_other, rec_other_block, max_alloc);
        if (rec_block_size != rec_other_block_size) return false;
        for(std::size_t i = 0; i < rec_block_size; ++i)
            if (rec_block[i] != rec_other_block[i]) return false;
        return true;
    }
    bool Result(const TestValueStream &, VariableTestIdentification & var)
    {
        const auto & iden = *basic::test::var::At<IObjValue>(var).Get().Get();
        const char * ss_res = basic::test::var::At<IStreamValue>(var).Get().Get();
        std::stringstream ss{""};
        ss << iden;
        auto s = ss.str();
        for (std::size_t i = 0; i < s.size(); ++i)
            if (s[i] != ss_res[i]) return false;
        return ss_res[s.size()] == '\0';
    }
};

using Case1 = basic::test::type::Parameter<TestAliasFlagType, 
    TestAliasCodeValueType, TestAliasSystemCategoryValueType, 
    TestAliasSystemCodeValueType, TestAliasRecordType, TestAliasErrorType,
    TestAliasErrorSystemType, TestValueIsDefault, TestValueIsBad,
    TestValueIsStandard, TestValueIsCatch, TestValueIsSystem, TestValueFlag,
    TestValueError, TestValueErrorSystem, TestValueCastRecord,
    TestValueStream>;
using Case2 = basic::test::type::Parameter<TestAliasFlagType, 
    TestAliasCodeValueType, TestAliasSystemCategoryValueType, 
    TestAliasSystemCodeValueType, TestAliasRecordType, TestAliasErrorType,
    TestAliasErrorSystemType, TestValueIsDefault, TestValueIsBad,
    TestValueIsStandard, TestValueIsCatch, TestValueIsSystem, TestValueFlag,
    TestValueError, TestValueCastRecord, TestValueStream>;
using Case3 = basic::test::type::Parameter<TestAliasFlagType, 
    TestAliasCodeValueType, TestAliasSystemCategoryValueType, 
    TestAliasSystemCodeValueType, TestAliasRecordType, TestAliasErrorType,
    TestAliasErrorSystemType, TestValueIsDefault, TestValueIsBad,
    TestValueIsStandard, TestValueIsCatch, TestValueIsSystem, TestValueFlag,
    TestValueErrorSystem, TestValueCastRecord, TestValueStream>;

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

BASIC_TEST_TYPE_NAME("basic::err::id::Flag", basic::err::id::Flag);
BASIC_TEST_TYPE_NAME("basic::err::Identification", 
    basic::err::Identification);

template<typename TArg1>
struct basic::test::type::Name<basic::err::id::rec::Error<TArg1>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::id::rec::Error<%s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + 
            tArg1CStr.Size(), _format, *tArg1CStr);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::err::id::rec::ErrorSystem<TArg1, 
    TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::id::rec::ErrorSystem<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<basic::err::id::Record<TArg1, TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::id::Record<%s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        basic::test::CString<char> tArg3CStr = 
            std::move(basic::test::type::Name<TArg3>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 9 + 
            tArg1CStr.Size() + tArg2CStr.Size() + tArg3CStr.Size(), 
            _format, *tArg1CStr, *tArg2CStr, *tArg3CStr);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::err::id::rec::Code<TArg1, 
    TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::id::rec::Code<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};

basic::err::id::Flag flag1{};
typename basic::err::Identification::ErrorType err1{};

constexpr typename basic::err::Identification::SystemCategoryValueType
    err_sys_categ_value1 = 0;

typename basic::err::Identification::ErrorSystemType 
    err_sys1{err_sys_categ_value1};
typename basic::err::Identification::RecordType record1{flag1};

basic::err::Identification obj1;

typedef VariableTestIdentification T1Var1;

T1Var1 t1_var1{"obj1", &obj1, true, false, false, false, false, &flag1, 
    &err1, &err_sys1, &record1, "0x01"};

REGISTER_TEST(t1, new TestIdentification<Case1, T1Var1>(t1_var1));

constexpr typename basic::err::Identification::CodeValueType
    err_code_value1 = 4;

basic::err::id::Flag flag2_1{basic::err::id::flag::Error{}};
basic::err::id::Flag flag2_2{basic::err::id::flag::Error{},
    basic::err::id::flag::Standard{}};
basic::err::id::Flag flag2_3{basic::err::id::flag::Catch{}};
basic::err::id::Flag flag2_4{basic::err::id::flag::Catch{},
    basic::err::id::flag::Standard{}};

typename basic::err::Identification::ErrorType err2{err_code_value1};

typename basic::err::Identification::RecordType record2_1{flag2_1,
    err_code_value1};
typename basic::err::Identification::RecordType record2_2{flag2_2,
    err_code_value1};
typename basic::err::Identification::RecordType record2_3{flag2_3,
    err_code_value1};
typename basic::err::Identification::RecordType record2_4{flag2_4,
    err_code_value1};

basic::err::Identification obj2_1{err_code_value1};
basic::err::Identification obj2_2{basic::err::id::flag::Standard{},
    err_code_value1};
basic::err::Identification obj2_3{basic::err::id::flag::Catch{}, 
    err_code_value1};
basic::err::Identification obj2_4{basic::err::id::flag::Catch{}, 
    basic::err::id::flag::Standard{}, err_code_value1};
basic::err::Identification obj2_5{basic::err::id::flag::Catch{}, obj2_1};
basic::err::Identification obj2_6{basic::err::id::flag::Catch{}, obj2_2};
basic::err::Identification obj2_7{basic::err::id::flag::Catch{}, 
    basic::err::id::flag::Standard{}, obj2_1};

T1Var1 t2_var1{"obj2_1", &obj2_1, false, false, false, false, false, &flag2_1, 
    &err2, nullptr, &record2_1, "0x000004"};
T1Var1 t2_var2{"obj2_2", &obj2_2, false, false, true, false, false, &flag2_2, 
    &err2, nullptr, &record2_2, "0x040004"};
T1Var1 t2_var3{"obj2_3", &obj2_3, false, false, false, true, false, &flag2_3, 
    &err2, nullptr, &record2_3, "0x080004"};
T1Var1 t2_var4{"obj2_4", &obj2_4, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
T1Var1 t2_var5{"obj2_5", &obj2_5, false, false, false, true, false, &flag2_3, 
    &err2, nullptr, &record2_3, "0x080004"};
T1Var1 t2_var6{"obj2_6", &obj2_6, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
T1Var1 t2_var7{"obj2_7", &obj2_7, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};

REGISTER_TEST(t2, new TestIdentification<Case2, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1, T1Var1, T1Var1>(t2_var1, t2_var2, t2_var3, t2_var4, 
    t2_var5, t2_var6, t2_var7));

constexpr typename basic::err::Identification::SystemCategoryValueType
    err_categ_value2 = 14;
constexpr typename basic::err::Identification::SystemCodeValueType
    err_code_value2 = 1040;

basic::err::id::Flag flag3_1{basic::err::id::flag::System{}};
basic::err::id::Flag flag3_2{basic::err::id::flag::System{},
    basic::err::id::flag::Standard{}};
basic::err::id::Flag flag3_3{basic::err::id::flag::Catch{}, 
    basic::err::id::flag::System{}};
basic::err::id::Flag flag3_4{basic::err::id::flag::Catch{},
    basic::err::id::flag::System{}, basic::err::id::flag::Standard{}};

typename basic::err::Identification::ErrorSystemType err_sys2{
    err_categ_value2, err_code_value2};

typename basic::err::Identification::RecordType record3_1{flag3_1,
    err_categ_value2, err_code_value2};
typename basic::err::Identification::RecordType record3_2{flag3_2,
    err_categ_value2, err_code_value2};
typename basic::err::Identification::RecordType record3_3{flag3_3,
    err_categ_value2, err_code_value2};
typename basic::err::Identification::RecordType record3_4{flag3_4,
    err_categ_value2, err_code_value2};

basic::err::Identification obj3_1{basic::err::id::flag::System{},
    err_categ_value2, err_code_value2};
basic::err::Identification obj3_2{basic::err::id::flag::System{},
    basic::err::id::flag::Standard{}, err_categ_value2, 
    err_code_value2};
basic::err::Identification obj3_3{basic::err::id::flag::Catch{},
    basic::err::id::flag::System{}, err_categ_value2, 
    err_code_value2};
basic::err::Identification obj3_4{basic::err::id::flag::Catch{},
    basic::err::id::flag::System{}, basic::err::id::flag::Standard{}, 
    err_categ_value2, err_code_value2};
basic::err::Identification obj3_5{basic::err::id::flag::Catch{}, obj3_1};
basic::err::Identification obj3_6{basic::err::id::flag::Catch{}, obj3_2};
basic::err::Identification obj3_7{basic::err::id::flag::Catch{}, 
    basic::err::id::flag::Standard{}, obj3_1};

T1Var1 t3_var1{"obj3_1", &obj3_1, false, false, false, false, true, &flag3_1, 
    nullptr, &err_sys2, &record3_1, "0x100E0410"};
T1Var1 t3_var2{"obj3_2", &obj3_2, false, false, true, false, true, &flag3_2, 
    nullptr, &err_sys2, &record3_2, "0x140E0410"};
T1Var1 t3_var3{"obj3_3", &obj3_3, false, false, false, true, true, &flag3_3, 
    nullptr, &err_sys2, &record3_3, "0x180E0410"};
T1Var1 t3_var4{"obj3_4", &obj3_4, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};
T1Var1 t3_var5{"obj3_5", &obj3_5, false, false, false, true, true, &flag3_3, 
    nullptr, &err_sys2, &record3_3, "0x180E0410"};
T1Var1 t3_var6{"obj3_6", &obj3_6, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};
T1Var1 t3_var7{"obj3_7", &obj3_7, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};

REGISTER_TEST(t3, new TestIdentification<Case3, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1, T1Var1, T1Var1>(t3_var1, t3_var2, t3_var3, t3_var4, 
    t3_var5, t3_var6, t3_var7));

basic::err::Identification obj4_1{obj2_1};
basic::err::Identification obj4_2{obj2_2};
basic::err::Identification obj4_3{obj2_3};
basic::err::Identification obj4_4{obj2_4};
basic::err::Identification obj4_5{obj2_5};
basic::err::Identification obj4_6{obj2_6};
basic::err::Identification obj4_7{obj2_7};

T1Var1 t4_var1{"obj4_1", &obj4_1, false, false, false, false, false, &flag2_1, 
    &err2, nullptr, &record2_1, "0x000004"};
T1Var1 t4_var2{"obj4_2", &obj4_2, false, false, true, false, false, &flag2_2, 
    &err2, nullptr, &record2_2, "0x040004"};
T1Var1 t4_var3{"obj4_3", &obj4_3, false, false, false, true, false, &flag2_3, 
    &err2, nullptr, &record2_3, "0x080004"};
T1Var1 t4_var4{"obj4_4", &obj4_4, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
T1Var1 t4_var5{"obj4_5", &obj4_5, false, false, false, true, false, &flag2_3, 
    &err2, nullptr, &record2_3, "0x080004"};
T1Var1 t4_var6{"obj4_6", &obj4_6, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
T1Var1 t4_var7{"obj4_7", &obj4_7, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};

REGISTER_TEST(t4, new TestIdentification<Case2, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1, T1Var1, T1Var1>(t4_var1, t4_var2, t4_var3, t4_var4, 
    t4_var5, t4_var6, t4_var7));

basic::err::Identification obj5_1{obj3_1};
basic::err::Identification obj5_2{obj3_2};
basic::err::Identification obj5_3{obj3_3};
basic::err::Identification obj5_4{obj3_4};
basic::err::Identification obj5_5{obj3_5};
basic::err::Identification obj5_6{obj3_6};
basic::err::Identification obj5_7{obj3_7};

T1Var1 t5_var1{"obj5_1", &obj5_1, false, false, false, false, true, &flag3_1, 
    nullptr, &err_sys2, &record3_1, "0x100E0410"};
T1Var1 t5_var2{"obj5_2", &obj5_2, false, false, true, false, true, &flag3_2, 
    nullptr, &err_sys2, &record3_2, "0x140E0410"};
T1Var1 t5_var3{"obj5_3", &obj5_3, false, false, false, true, true, &flag3_3, 
    nullptr, &err_sys2, &record3_3, "0x180E0410"};
T1Var1 t5_var4{"obj5_4", &obj5_4, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};
T1Var1 t5_var5{"obj5_5", &obj5_5, false, false, false, true, true, &flag3_3, 
    nullptr, &err_sys2, &record3_3, "0x180E0410"};
T1Var1 t5_var6{"obj5_6", &obj5_6, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};
T1Var1 t5_var7{"obj5_7", &obj5_7, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};

REGISTER_TEST(t5, new TestIdentification<Case3, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1, T1Var1, T1Var1>(t5_var1, t5_var2, t5_var3, t5_var4, 
    t5_var5, t5_var6, t5_var7));
    
basic::err::Identification obj4_1_c{obj4_1};
basic::err::Identification obj4_2_c{obj4_2};
basic::err::Identification obj4_3_c{obj4_3};
basic::err::Identification obj4_4_c{obj4_4};
basic::err::Identification obj4_5_c{obj4_5};
basic::err::Identification obj4_6_c{obj4_6};
basic::err::Identification obj4_7_c{obj4_7};

basic::err::Identification obj6_1{std::move(obj4_1_c)};
basic::err::Identification obj6_2{std::move(obj4_2_c)};
basic::err::Identification obj6_3{std::move(obj4_3_c)};
basic::err::Identification obj6_4{std::move(obj4_4_c)};
basic::err::Identification obj6_5{std::move(obj4_5_c)};
basic::err::Identification obj6_6{std::move(obj4_6_c)};
basic::err::Identification obj6_7{std::move(obj4_7_c)};

T1Var1 t6_var1{"obj6_1", &obj6_1, false, false, false, false, false, &flag2_1, 
    &err2, nullptr, &record2_1, "0x000004"};
T1Var1 t6_var2{"obj6_2", &obj6_2, false, false, true, false, false, &flag2_2, 
    &err2, nullptr, &record2_2, "0x040004"};
T1Var1 t6_var3{"obj6_3", &obj6_3, false, false, false, true, false, &flag2_3, 
    &err2, nullptr, &record2_3, "0x080004"};
T1Var1 t6_var4{"obj6_4", &obj6_4, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
T1Var1 t6_var5{"obj6_5", &obj6_5, false, false, false, true, false, &flag2_3, 
    &err2, nullptr, &record2_3, "0x080004"};
T1Var1 t6_var6{"obj6_6", &obj6_6, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
T1Var1 t6_var7{"obj6_7", &obj6_7, false, false, true, true, false, &flag2_4, 
    &err2, nullptr, &record2_4, "0x0C0004"};
    
T1Var1 t6_var8{"obj4_1_c", &obj4_1_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};
T1Var1 t6_var9{"obj4_2_c", &obj4_2_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};
T1Var1 t6_var10{"obj4_3_c", &obj4_3_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};
T1Var1 t6_var11{"obj4_4_c", &obj4_4_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};
T1Var1 t6_var12{"obj4_5_c", &obj4_5_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};
T1Var1 t6_var13{"obj4_6_c", &obj4_6_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};
T1Var1 t6_var14{"obj4_7_c", &obj4_7_c, true, false, false, false, false, 
    &flag1, &err1, nullptr, &record1, "0x01"};

REGISTER_TEST(t6, new TestIdentification<Case2, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t6_var1, t6_var2, t6_var3, t6_var4, t6_var5, t6_var6, 
        t6_var7, t6_var8, t6_var9, t6_var10, t6_var11, t6_var12, t6_var13, 
        t6_var14));

basic::err::Identification obj5_1_c{obj5_1};
basic::err::Identification obj5_2_c{obj5_2};
basic::err::Identification obj5_3_c{obj5_3};
basic::err::Identification obj5_4_c{obj5_4};
basic::err::Identification obj5_5_c{obj5_5};
basic::err::Identification obj5_6_c{obj5_6};
basic::err::Identification obj5_7_c{obj5_7};

basic::err::Identification obj7_1{std::move(obj5_1_c)};
basic::err::Identification obj7_2{std::move(obj5_2_c)};
basic::err::Identification obj7_3{std::move(obj5_3_c)};
basic::err::Identification obj7_4{std::move(obj5_4_c)};
basic::err::Identification obj7_5{std::move(obj5_5_c)};
basic::err::Identification obj7_6{std::move(obj5_6_c)};
basic::err::Identification obj7_7{std::move(obj5_7_c)};

T1Var1 t7_var1{"obj7_1", &obj7_1, false, false, false, false, true, &flag3_1, 
    nullptr, &err_sys2, &record3_1, "0x100E0410"};
T1Var1 t7_var2{"obj7_2", &obj7_2, false, false, true, false, true, &flag3_2, 
    nullptr, &err_sys2, &record3_2, "0x140E0410"};
T1Var1 t7_var3{"obj7_3", &obj7_3, false, false, false, true, true, &flag3_3, 
    nullptr, &err_sys2, &record3_3, "0x180E0410"};
T1Var1 t7_var4{"obj7_4", &obj7_4, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};
T1Var1 t7_var5{"obj7_5", &obj7_5, false, false, false, true, true, &flag3_3, 
    nullptr, &err_sys2, &record3_3, "0x180E0410"};
T1Var1 t7_var6{"obj7_6", &obj7_6, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};
T1Var1 t7_var7{"obj7_7", &obj7_7, false, false, true, true, true, &flag3_4, 
    nullptr, &err_sys2, &record3_4, "0x1C0E0410"};

T1Var1 t7_var8{"obj5_1_c", &obj5_1_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};
T1Var1 t7_var9{"obj5_2_c", &obj5_2_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};
T1Var1 t7_var10{"obj5_3_c", &obj5_3_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};
T1Var1 t7_var11{"obj5_4_c", &obj5_4_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};
T1Var1 t7_var12{"obj5_5_c", &obj5_5_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};
T1Var1 t7_var13{"obj5_6_c", &obj5_6_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};
T1Var1 t7_var14{"obj5_7_c", &obj5_7_c, true, false, false, false, false, 
    &flag1, nullptr, &err_sys1, &record1, "0x01"};

REGISTER_TEST(t7, new TestIdentification<Case3, T1Var1, T1Var1, T1Var1,
    T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t7_var1, t7_var2, t7_var3, t7_var4, t7_var5, t7_var6,
    t7_var7, t7_var8, t7_var9, t7_var10, t7_var11, t7_var12, t7_var13, 
    t7_var14));

int main()
{
    return RUN_TEST();
}

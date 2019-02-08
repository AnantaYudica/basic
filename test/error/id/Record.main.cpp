#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/CString.h"
#include "test/cstr/Format.h"
#include "test/cstr/out/Argument.h"

#include "error/id/Record.h"
#include "error/id/rec/Code.h"
#include "error/id/rec/Error.h"
#include "error/id/rec/ErrorSystem.h"
#include "error/id/rec/ToBytes.h"

#include <cstdint>
#include <utility>
#include <cstring>

#define BUFFER_FORMAT_CSTRING 256

BASIC_TEST_CONSTRUCT;

basic::test::CString<char> FlagToString(basic::error::id::Flag && flag)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "%d", reinterpret_cast<typename basic::error::id::
            Flag::ValueType &&>(flag));
}

template<typename TErrorCodeValue>
basic::test::CString<char> ErrorToString(basic::error::id::rec::
    Error<TErrorCodeValue> && err)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "%d", err.Code());
}

template<typename TErrorSystemCategoryValue, typename TErrorSystemCodeValue>
basic::test::CString<char> ErrorSystemToString(basic::error::id::rec::
    ErrorSystem<TErrorSystemCategoryValue, TErrorSystemCodeValue> && err_sys)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "%d, %d", err_sys.Category(), err_sys.Code());
}

struct Bytes
{
    enum EndianType
    {
        little = 0,
        big
    };
    std::size_t Size;
    std::uint8_t * Block;
    EndianType Endian;
    static EndianType SystemCheck();
    Bytes();
    template<typename... TArgs>
    Bytes(TArgs... args);
    Bytes(const Bytes & cpy);
    Bytes(Bytes && mov);
    ~Bytes();
};

typename Bytes::EndianType SystemCheck()
{
    static const std::uint16_t tmp = 1;
    static const bool is_big = ((const std::uint8_t *)&tmp)[0] == 1;
    return is_big ? Bytes::big : Bytes::little;
}

Bytes::Bytes() :
    Size(0),
    Block(nullptr),
    Endian(big)
{}

template<typename... TArgs>
Bytes::Bytes(TArgs... args) :
    Size(sizeof...(args)),
    Block(new std::uint8_t[sizeof...(args)]),
    Endian(big)
{
    std::uint8_t tmp[] = {std::uint8_t(args)...};
    memcpy(Block, tmp, sizeof...(args));
}

Bytes::Bytes(const Bytes & cpy) :
    Size(cpy.Size),
    Block(new std::uint8_t[cpy.Size]),
    Endian(cpy.Endian)
{
    memcpy(Block, cpy.Block, Size);
}

Bytes::Bytes(Bytes && mov) :
    Size(mov.Size),
    Block(mov.Block),
    Endian(mov.Endian)
{
    mov.Size = 0;
    mov.Block = nullptr;
    mov.Endian = Bytes::big;
}

Bytes::~Bytes()
{
    if (Block != nullptr)
        delete[] Block;
}

basic::test::CString<char> BytesToString(Bytes && bytes)
{
    if (bytes.Size == 0) return "";
    const std::size_t size = (bytes.Size * 2);
    char * tmp = new char[size + 1];
    for(std::size_t i = 0, j = 0; i < size; i += 2, ++j)
    {
        std::uint8_t hex0 = bytes.Block[j] >> 4;
        std::uint8_t hex1 = bytes.Block[j] & std::uint8_t(0x0F);
        char ch0 = '0', ch1 = '0';
        ch0 += (hex0 <= 9 ? hex0 : (hex0 + 7));
        ch1 += (hex1 <= 9 ? hex1 : (hex1 + 7));
        tmp[i] = ch0;
        tmp[i + 1] = ch1;
    }
    tmp[size] = '\0';
    auto ret = basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "{Size : %d, Block : 0x%s}", bytes.Size, tmp);
    delete[] tmp;
    return std::move(ret);
}

struct TestAliasFlagType {};
struct TestAliasErrorCodeValueType {};
struct TestAliasErrorSystemCategoryValueType {};
struct TestAliasErrorSystemCodeValueType {};
struct TestAliasErrorType {};
struct TestAliasErrorSystemType {};
struct TestAliasUnionCodeType {};
struct TestValueMaximumAllocation {};
struct TestValueFlag {};
struct TestValueError {};
struct TestValueErrorSystem {};
struct TestValueToBytes {};

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue, typename TAssignment = int>
using VariableTestRecord = basic::test::Variable<
    TErrorCodeValue,
    TErrorSystemCategoryValue,
    TErrorSystemCodeValue,
    TAssignment,
    basic::error::id::Flag,
    basic::error::id::rec::Error<TErrorCodeValue>,
    basic::error::id::rec::ErrorSystem<TErrorSystemCategoryValue,
        TErrorSystemCodeValue>,
    basic::error::id::rec::Code<TErrorCodeValue, TErrorSystemCodeValue>,
    basic::error::id::Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue>,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::id::Record<TErrorCodeValue, 
        TErrorSystemCategoryValue, TErrorSystemCodeValue> *>,
    basic::test::Value<TAssignment>,
    basic::test::Value<std::size_t>,
    basic::test::Value<basic::error::id::Flag>,
    basic::test::Value<basic::error::id::rec::Error<TErrorCodeValue>>,
    basic::test::Value<basic::error::id::rec::ErrorSystem<
        TErrorSystemCategoryValue, TErrorSystemCodeValue>>,
    basic::test::Value<Bytes>,
    basic::test::type::Function<basic::test::
        CString<char> (basic::error::id::Flag &&), &FlagToString>,
    basic::test::type::Function<basic::test::
        CString<char> (basic::error::id::rec::Error<TErrorCodeValue> &&), 
        &ErrorToString>,
    basic::test::type::Function<basic::test::
        CString<char> (basic::error::id::rec::ErrorSystem<
        TErrorSystemCategoryValue, TErrorSystemCodeValue> &&), 
        &ErrorSystemToString>,
    basic::test::type::Function<basic::test::
        CString<char> (Bytes &&), &BytesToString>>;

constexpr std::size_t IErrorCodeValueType = 0;
constexpr std::size_t IErrorSystemCategoryValueType = 1;
constexpr std::size_t IErrorSystemCodeValueType = 2;
constexpr std::size_t IAssignmentType = 3;
constexpr std::size_t IFlagType = 4;
constexpr std::size_t IRecErrorType = 5;
constexpr std::size_t IRecErrorSystemType = 6;
constexpr std::size_t IRecCodeType = 7;
constexpr std::size_t IRecordType = 8;
constexpr std::size_t IObjName = 9;
constexpr std::size_t IObjValue = 10;
constexpr std::size_t IAssignmentValue = 11;
constexpr std::size_t IMaximumAllocationValue = 12;
constexpr std::size_t IFlagValue = 13;
constexpr std::size_t IErrorValue = 14;
constexpr std::size_t IErrorSystemValue = 15;
constexpr std::size_t IBytesValue = 16;
constexpr std::size_t IFlagToCStrFunc = 17;
constexpr std::size_t IErrorToCStrFunc = 18;
constexpr std::size_t IErrorSystemToCStrFunc = 19;
constexpr std::size_t IBytesToCStrFunc = 20;

typedef basic::test::msg::Argument<TestAliasFlagType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IFlagType>> 
        ArgTestAliasFlagType;

typedef basic::test::msg::Base<TestAliasFlagType, char, 
    ArgTestAliasFlagType, ArgTestAliasFlagType, 
    ArgTestAliasFlagType> MessageBaseTestAliasFlagType;

typedef basic::test::msg::Argument<TestAliasErrorCodeValueType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorCodeValueType>> 
        ArgTestAliasErrorCodeValueType;

typedef basic::test::msg::Base<TestAliasErrorCodeValueType, char, 
    ArgTestAliasErrorCodeValueType, ArgTestAliasErrorCodeValueType, 
    ArgTestAliasErrorCodeValueType> MessageBaseTestAliasErrorCodeValueType;

typedef basic::test::msg::Argument<TestAliasErrorSystemCategoryValueType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorSystemCategoryValueType>> 
        ArgTestAliasErrorSystemCategoryValueType;

typedef basic::test::msg::Base<TestAliasErrorSystemCategoryValueType, char, 
    ArgTestAliasErrorSystemCategoryValueType, 
    ArgTestAliasErrorSystemCategoryValueType, 
    ArgTestAliasErrorSystemCategoryValueType> 
        MessageBaseTestAliasErrorSystemCategoryValueType;

typedef basic::test::msg::Argument<TestAliasErrorSystemCodeValueType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IErrorSystemCodeValueType>> 
        ArgTestAliasErrorSystemCodeValueType;

typedef basic::test::msg::Base<TestAliasErrorSystemCodeValueType, char, 
    ArgTestAliasErrorSystemCodeValueType, 
    ArgTestAliasErrorSystemCodeValueType, 
    ArgTestAliasErrorSystemCodeValueType> 
        MessageBaseTestAliasErrorSystemCodeValueType;

typedef basic::test::msg::Argument<TestAliasErrorType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecErrorType>> 
        ArgTestAliasErrorType;

typedef basic::test::msg::Base<TestAliasErrorType, char, 
    ArgTestAliasErrorType, ArgTestAliasErrorType, 
    ArgTestAliasErrorType> MessageBaseTestAliasErrorType;

typedef basic::test::msg::Argument<TestAliasErrorSystemType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecErrorSystemType>> 
        ArgTestAliasErrorSystemType;

typedef basic::test::msg::Base<TestAliasErrorSystemType, char, 
    ArgTestAliasErrorSystemType, ArgTestAliasErrorSystemType, 
    ArgTestAliasErrorSystemType> MessageBaseTestAliasErrorSystemType;

typedef basic::test::msg::Argument<TestAliasUnionCodeType,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecCodeType>> 
        ArgTestAliasUnionCodeType;

typedef basic::test::msg::Base<TestAliasUnionCodeType, char, 
    ArgTestAliasUnionCodeType, ArgTestAliasUnionCodeType, 
    ArgTestAliasUnionCodeType> MessageBaseTestAliasUnionCodeType;

typedef basic::test::msg::Argument<TestValueMaximumAllocation,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::Value<IMaximumAllocationValue>> 
        ArgTestValueMaximumAllocation;

typedef basic::test::msg::Base<TestValueMaximumAllocation, char, 
    ArgTestValueMaximumAllocation, ArgTestValueMaximumAllocation, 
    ArgTestValueMaximumAllocation> MessageBaseTestValueMaximumAllocation;

typedef basic::test::msg::Argument<TestValueFlag,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IFlagToCStrFunc,
        basic::test::msg::arg::Value<IFlagValue>>> ArgTestValueFlag;

typedef basic::test::msg::Base<TestValueFlag, char, 
    ArgTestValueFlag, ArgTestValueFlag, 
    ArgTestValueFlag> MessageBaseTestValueFlag;

typedef basic::test::msg::Argument<TestValueError,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecErrorType>,
    basic::test::msg::arg::type::Function<IErrorToCStrFunc,
        basic::test::msg::arg::Value<IErrorValue>>> ArgTestValueError;

typedef basic::test::msg::Base<TestValueError, char, 
    ArgTestValueError, ArgTestValueError, 
    ArgTestValueError> MessageBaseTestValueError;

typedef basic::test::msg::Argument<TestValueErrorSystem,
    basic::test::msg::arg::type::Name<IRecordType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IRecErrorSystemType>,
    basic::test::msg::arg::type::Function<IErrorSystemToCStrFunc,
        basic::test::msg::arg::Value<IErrorSystemValue>>> 
            ArgTestValueErrorSystem;

typedef basic::test::msg::Base<TestValueErrorSystem, char, 
    ArgTestValueErrorSystem, ArgTestValueErrorSystem, 
    ArgTestValueErrorSystem> MessageBaseTestValueErrorSystem;

typedef basic::test::msg::Argument<TestValueToBytes,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBytesToCStrFunc,
        basic::test::msg::arg::Value<IBytesValue>>> 
            ArgTestValueToBytes;

typedef basic::test::msg::Base<TestValueToBytes, char, 
    ArgTestValueToBytes, ArgTestValueToBytes, 
    ArgTestValueToBytes> MessageBaseTestValueToBytes;

template<typename TCases, typename... TVariables>
struct TestRecord :
    public MessageBaseTestAliasFlagType,
    public MessageBaseTestAliasErrorCodeValueType,
    public MessageBaseTestAliasErrorSystemCategoryValueType,
    public MessageBaseTestAliasErrorSystemCodeValueType,
    public MessageBaseTestAliasErrorType,
    public MessageBaseTestAliasErrorSystemType,
    public MessageBaseTestAliasUnionCodeType,
    public MessageBaseTestValueMaximumAllocation,
    public MessageBaseTestValueFlag,
    public MessageBaseTestValueError,
    public MessageBaseTestValueErrorSystem,
    public MessageBaseTestValueToBytes,
    public basic::test::Message<BASIC_TEST, TestRecord<TCases, 
        TVariables...>>,
    public basic::test::Case<TestRecord<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestRecord<TCases, TVariables...>, 
        TVariables...>
{
public:
    using MessageBaseTestAliasFlagType::Format;
    using MessageBaseTestAliasFlagType::SetFormat;
    using MessageBaseTestAliasFlagType::Argument;
    using MessageBaseTestAliasErrorCodeValueType::Format;
    using MessageBaseTestAliasErrorCodeValueType::SetFormat;
    using MessageBaseTestAliasErrorCodeValueType::Argument;
    using MessageBaseTestAliasErrorSystemCategoryValueType::Format;
    using MessageBaseTestAliasErrorSystemCategoryValueType::SetFormat;
    using MessageBaseTestAliasErrorSystemCategoryValueType::Argument;
    using MessageBaseTestAliasErrorSystemCodeValueType::Format;
    using MessageBaseTestAliasErrorSystemCodeValueType::SetFormat;
    using MessageBaseTestAliasErrorSystemCodeValueType::Argument;
    using MessageBaseTestAliasErrorType::Format;
    using MessageBaseTestAliasErrorType::SetFormat;
    using MessageBaseTestAliasErrorType::Argument;
    using MessageBaseTestAliasErrorSystemType::Format;
    using MessageBaseTestAliasErrorSystemType::SetFormat;
    using MessageBaseTestAliasErrorSystemType::Argument;
    using MessageBaseTestAliasUnionCodeType::Format;
    using MessageBaseTestAliasUnionCodeType::SetFormat;
    using MessageBaseTestAliasUnionCodeType::Argument;
    using MessageBaseTestValueMaximumAllocation::Format;
    using MessageBaseTestValueMaximumAllocation::SetFormat;
    using MessageBaseTestValueMaximumAllocation::Argument;
    using MessageBaseTestValueFlag::Format;
    using MessageBaseTestValueFlag::SetFormat;
    using MessageBaseTestValueFlag::Argument;
    using MessageBaseTestValueError::Format;
    using MessageBaseTestValueError::SetFormat;
    using MessageBaseTestValueError::Argument;
    using MessageBaseTestValueErrorSystem::Format;
    using MessageBaseTestValueErrorSystem::SetFormat;
    using MessageBaseTestValueErrorSystem::Argument;
    using MessageBaseTestValueToBytes::Format;
    using MessageBaseTestValueToBytes::SetFormat;
    using MessageBaseTestValueToBytes::Argument;
    using basic::test::Case<TestRecord<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestRecord<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestRecord(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestRecord<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestRecord<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestRecord<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestAliasFlagType testAliasFlagType;
        SetFormat(info, testAliasFlagType, "Test alias type "
            "%s::FlagType {%s} is same with %s\n");
        SetFormat(debug, testAliasFlagType, "Test alias type "
            "%s::FlagType {%s} is same with %s\n");
        SetFormat(error, testAliasFlagType, "Error alias type "
            "%s::FlagType {%s} is not same with %s\n");

        TestAliasErrorCodeValueType testAliasErrorCodeValueType;
        SetFormat(info, testAliasErrorCodeValueType, "Test alias type "
            "%s::ErrorCodeValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorCodeValueType, "Test alias type "
            "%s::ErrorCodeValueType {%s} is same with %s\n");
        SetFormat(error, testAliasErrorCodeValueType, "Error alias type "
            "%s::ErrorCodeValueType {%s} is not same with %s\n");

        TestAliasErrorSystemCategoryValueType 
            testAliasErrorSystemCategoryValueType;
        SetFormat(info, testAliasErrorSystemCategoryValueType, "Test alias "
            "type %s::ErrorSystemCategoryValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorSystemCategoryValueType, "Test alias "
            "type %s::ErrorSystemCategoryValueType {%s} is same with %s\n");
        SetFormat(error, testAliasErrorSystemCategoryValueType, "Error alias "
            "type %s::ErrorSystemCategoryValueType {%s} is "
            "not same with %s\n");
        
        TestAliasErrorSystemCodeValueType testAliasErrorSystemCodeValueType;
        SetFormat(info, testAliasErrorSystemCodeValueType, "Test alias "
            "type %s::ErrorSystemCodeValueType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorSystemCodeValueType, "Test alias "
            "type %s::ErrorSystemCodeValueType {%s} is same with %s\n");
        SetFormat(error, testAliasErrorSystemCodeValueType, "Error alias "
            "type %s::ErrorSystemCodeValueType {%s} is "
            "not same with %s\n");

        TestAliasErrorType testAliasErrorType;
        SetFormat(info, testAliasErrorType, "Test alias "
            "type %s::ErrorType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorType, "Test alias "
            "type %s::ErrorType {%s} is same with %s\n");
        SetFormat(error, testAliasErrorType, "Error alias "
            "type %s::ErrorType {%s} is "
            "not same with %s\n");
        
        TestAliasErrorSystemType testAliasErrorSystemType;
        SetFormat(info, testAliasErrorSystemType, "Test alias "
            "type %s::ErrorSystemType {%s} is same with %s\n");
        SetFormat(debug, testAliasErrorSystemType, "Test alias "
            "type %s::ErrorSystemType {%s} is same with %s\n");
        SetFormat(error, testAliasErrorSystemType, "Error alias "
            "type %s::ErrorSystemType {%s} is "
            "not same with %s\n");
        
        TestAliasUnionCodeType testAliasUnionCodeType;
        SetFormat(info, testAliasUnionCodeType, "Test alias "
            "type %s::UnionCodeType {%s} is same with %s\n");
        SetFormat(debug, testAliasUnionCodeType, "Test alias "
            "type %s::UnionCodeType {%s} is same with %s\n");
        SetFormat(error, testAliasUnionCodeType, "Error alias "
            "type %s::UnionCodeType {%s} is "
            "not same with %s\n");
        
        TestValueMaximumAllocation testValueMaximumAllocation;
        SetFormat(info, testValueMaximumAllocation, "Test return value "
            "%s::MaximumValue() {%s} is same with %d\n");
        SetFormat(debug, testValueMaximumAllocation, "Test return value "
            "%s::MaximumValue() {%s} is same with %d\n");
        SetFormat(error, testValueMaximumAllocation, "Error return value "
            "%s::Flag() {%s} is not same with %d\n");
        
        TestValueFlag testValueFlag;
        SetFormat(info, testValueFlag, "Test return value %s::Flag() {%s} "
            "is same with %s\n");
        SetFormat(debug, testValueFlag, "Test return value %s::Flag() {%s} "
            "is same with %s\n");
        SetFormat(error, testValueFlag, "Error return value %s::Flag() {%s} "
            "is not same with %s\n");

        TestValueError testValueError;
        SetFormat(info, testValueError, "Test return value %s::Error() {%s} "
            "is same with %s{%s}\n");
        SetFormat(debug, testValueError, "Test return value %s::Error() {%s} "
            "is same with %s{%s}\n");
        SetFormat(error, testValueError, "Error return value %s::Error() {%s} "
            "is not same with %s{%s}\n");

        TestValueErrorSystem testValueErrorSystem;
        SetFormat(info, testValueErrorSystem, "Test return value "
            "%s::ErrorSystem() {%s} is same with %s{%s}\n");
        SetFormat(debug, testValueErrorSystem, "Test return value "
            "%s::ErrorSystem() {%s} is same with %s{%s}\n");
        SetFormat(error, testValueErrorSystem, "Error return value "
            "%s::ErrorSystem() {%s} is not same with %s{%s}\n");

        TestValueToBytes testValueToBytes;
        SetFormat(info, testValueToBytes, "Test return value "
            "basic::error::id::rec::ToBytes(%s) is same with %s\n");
        SetFormat(debug, testValueToBytes, "Test return value "
            "basic::error::id::rec::ToBytes(%s) is same with %s\n");
        SetFormat(error, testValueToBytes, "Error return value "
            "basic::error::id::rec::ToBytes(%s) is not same with %s\n");
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasFlagType &, VariableTestRecord<
        TErrorCodeValue, TErrorSystemCategoryValue, TErrorSystemCodeValue, 
        TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::FlagType).
            hash_code() == typeid(basic::error::id::Flag).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasErrorCodeValueType &, VariableTestRecord<
        TErrorCodeValue, TErrorSystemCategoryValue, TErrorSystemCodeValue, 
        TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
                ErrorCodeValueType).hash_code() == 
            typeid(TErrorCodeValue).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasErrorSystemCategoryValueType &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
                ErrorSystemCategoryValueType).hash_code() == 
            typeid(TErrorSystemCategoryValue).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasErrorSystemCodeValueType &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
                ErrorSystemCodeValueType).hash_code() == 
            typeid(TErrorSystemCodeValue).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasErrorType &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
                ErrorType).hash_code() == 
            typeid(basic::error::id::rec::Error<TErrorCodeValue>).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasErrorSystemType &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
                ErrorSystemType).hash_code() == 
            typeid(basic::error::id::rec::ErrorSystem<
                TErrorSystemCategoryValue, TErrorSystemCodeValue>).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestAliasUnionCodeType &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        return typeid(typename basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
                UnionCodeType).hash_code() == 
            typeid(basic::error::id::rec::Code<
                TErrorCodeValue, TErrorSystemCodeValue>).hash_code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestValueMaximumAllocation &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        const std::size_t & max_alloc = basic::test::var::
            At<IMaximumAllocationValue>(var).Get().Get();
        return basic::error::id::Record<TErrorCodeValue, 
            TErrorSystemCategoryValue, TErrorSystemCodeValue>::
            MaximumAllocation() == max_alloc;
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestValueFlag &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        const basic::error::id::Flag & rec_flag = basic::test::var::
            At<IObjValue>(var).Get().Get()->Flag();
        const basic::error::id::Flag & flag = basic::test::var::
            At<IFlagValue>(var).Get().Get();
        return rec_flag.IsBad() == flag.IsBad() &&
            rec_flag.IsCatch() == flag.IsCatch() &&
            rec_flag.IsDefault() == flag.IsDefault() &&
            rec_flag.IsStandard() == flag.IsStandard() &&
            rec_flag.IsSystem() == flag.IsSystem();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestValueError &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        const auto & rec_error = basic::test::var::
            At<IObjValue>(var).Get().Get()->Error();
        const auto & error = basic::test::var::
            At<IErrorValue>(var).Get().Get();
        return rec_error.Code() == error.Code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestValueErrorSystem &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        const auto & rec_error = basic::test::var::
            At<IObjValue>(var).Get().Get()->ErrorSystem();
        const auto & error_system = basic::test::var::
            At<IErrorSystemValue>(var).Get().Get();
        return rec_error.Category() == error_system.Category() &&
            rec_error.Code() == error_system.Code();
    }
    template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
        typename TErrorSystemCodeValue, typename TAssignment = int>
    bool Result(const TestValueToBytes &, 
        VariableTestRecord<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue, TAssignment> & var)
    {
        constexpr std::size_t flag_size = sizeof(typename basic::error::id::
            Flag::ValueType);
        constexpr std::size_t err_code_size = sizeof(TErrorCodeValue);
        constexpr std::size_t err_size = flag_size + err_code_size;
        constexpr std::size_t err_sys_cat_size = 
            sizeof(TErrorSystemCategoryValue);
        constexpr std::size_t err_sys_code_size = 
            sizeof(TErrorSystemCodeValue);
        constexpr std::size_t err_sys_size = flag_size + err_sys_cat_size +
            err_sys_code_size;

        const Bytes & bytes = basic::test::var::At<IBytesValue>(var).
            Get().Get();
        const auto & rec = *basic::test::var::At<IObjValue>(var).Get().Get();
        static std::uint16_t val{1};
        static typename Bytes::EndianType endian = 
            ((std::uint8_t *)&val)[1] == 1 ? Bytes::big : Bytes::little;
        constexpr std::size_t rec_bytes_size = basic::error::id::
            Record<TErrorCodeValue, TErrorSystemCategoryValue, 
            TErrorSystemCodeValue>::MaximumAllocation();
            
        std::uint8_t check_a[rec_bytes_size * 2];
        std::uint8_t check_b[rec_bytes_size * 2];
        
        std::size_t size_a = basic::error::id::rec::ToBytes(rec, check_a,
            rec_bytes_size * 2);
        std::size_t size_b = basic::error::id::rec::ToBytes<0x0100>(rec, 
            check_b, rec_bytes_size * 2);
        if (size_a != bytes.Size || size_b != bytes.Size) return false;

        if (bytes.Endian == Bytes::big)
        {
            for(std::size_t i = 0; i < size_a; ++i)
                if (bytes.Block[i] != check_a[i]) return false;
        }
        else
        {
            for(std::size_t i = 0, j = size_a; i < size_a; ++i, --j)
                if (bytes.Block[j - 1] != check_a[i]) return false;
        }

        if (bytes.Endian == Bytes::big)
        {
            for(std::size_t i = 0, j = flag_size; i < flag_size; ++i, --j)
                if (bytes.Block[i] != check_b[j - 1]) return false;
        }
        else
        {
            for(std::size_t i = 0, j = flag_size; i < flag_size; ++i, --j)
                if (bytes.Block[j - 1] != check_b[j - 1]) return false;
        }
        
        
        if (rec.Flag().IsSystem())
        {
            constexpr std::size_t flag_cat_size = flag_size + err_sys_cat_size;
            if (bytes.Endian == Bytes::big)
            {
                for(std::size_t i = flag_size, j = flag_cat_size; 
                    i < flag_cat_size; ++i, --j)
                        if (bytes.Block[i] != check_b[j - 1]) return false;
                for(std::size_t i = flag_cat_size, j = err_sys_size; 
                    i < err_sys_size; ++i, --j)
                        if (bytes.Block[i] != check_b[j - 1]) return false;
            }
            else
            {
                for(std::size_t i = flag_size, j = flag_cat_size; 
                    i < flag_cat_size; ++i, --j)
                        if (bytes.Block[j - 1] != check_b[j - 1]) return false;
                for(std::size_t i = flag_cat_size, j = err_sys_size; 
                    i < err_sys_size; ++i, --j)
                        if (bytes.Block[j - 1] != check_b[j - 1]) return false;
            }
        }
        else
        {
            if (bytes.Endian == Bytes::big)
            {
                for(std::size_t i = flag_size, j = err_size; 
                    i < err_size; ++i, --j)
                        if (bytes.Block[i] != check_b[j - 1]) return false;
            }
            else
            {
                for(std::size_t i = flag_size, j = err_size; 
                    i < err_size; ++i, --j)
                        if (bytes.Block[j - 1] != check_b[j - 1]) return false;
            }
        }

        return true;
    }
};

using Case1 = basic::test::type::Parameter<TestAliasFlagType,
    TestAliasErrorCodeValueType, TestAliasErrorSystemCategoryValueType, 
    TestAliasErrorSystemCodeValueType, TestAliasErrorType,
    TestAliasErrorSystemType, TestAliasUnionCodeType, 
    TestValueMaximumAllocation, TestValueFlag, TestValueError,
    TestValueErrorSystem, TestValueToBytes>;
using Case2 = basic::test::type::Parameter<TestValueFlag, TestValueError,
    TestValueToBytes>;
using Case3 = basic::test::type::Parameter<TestValueFlag, TestValueErrorSystem,
    TestValueToBytes>;

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

BASIC_TEST_TYPE_NAME("basic::error::id::Flag", basic::error::id::Flag);

template<typename TArg1>
struct basic::test::type::Name<basic::error::id::rec::Error<TArg1>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::rec::Error<%s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + 
            tArg1CStr.Size(), _format, *tArg1CStr);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::error::id::rec::ErrorSystem<TArg1, 
    TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::rec::ErrorSystem<%s, %s>";
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
struct basic::test::type::Name<basic::error::id::Record<TArg1, TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::Record<%s, %s, %s>";
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
struct basic::test::type::Name<basic::error::id::rec::Code<TArg1, 
    TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::rec::Code<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};

template<typename T1, typename T2, typename T3>
constexpr std::size_t RecordMaximumAllocation()
{
    return sizeof(basic::error::id::Flag) + sizeof(T2) + 
        (sizeof(T1) > sizeof(T3) ? sizeof(T1) : sizeof(T3));
}

Bytes t1_bytes1{1};

typedef basic::error::id::Record<std::uint8_t, std::uint8_t, 
    std::uint8_t> T1Obj1;
typedef basic::error::id::Record<std::uint64_t, std::uint64_t, 
    std::uint64_t> T1Obj2;
typedef basic::error::id::Record<std::uint8_t, std::uint16_t,
    std::uint32_t> T1Obj3;
typedef basic::error::id::Record<std::uint64_t, std::uint32_t, 
    std::uint16_t> T1Obj4;
typedef basic::error::id::Record<std::int8_t, std::uint16_t, 
    std::uint32_t> T1Obj5;
typedef basic::error::id::Record<std::uint16_t, std::int32_t,
    std::uint64_t> T1Obj6;
typedef basic::error::id::Record<std::int32_t, std::uint16_t, 
    std::int8_t> T1Obj7;
typedef basic::error::id::Record<std::uint64_t, std::int32_t, 
    std::int16_t> T1Obj8;

constexpr std::size_t size_alloc_t1_obj1 = 
    RecordMaximumAllocation<std::uint8_t, std::uint8_t, std::uint8_t>();
constexpr std::size_t size_alloc_t1_obj2 = 
    RecordMaximumAllocation<std::uint64_t, std::uint64_t, std::uint64_t>();
constexpr std::size_t size_alloc_t1_obj3 = 
    RecordMaximumAllocation<std::uint8_t, std::uint16_t, std::uint32_t>();
constexpr std::size_t size_alloc_t1_obj4 = 
    RecordMaximumAllocation<std::uint64_t, std::uint32_t, std::uint16_t>();
constexpr std::size_t size_alloc_t1_obj5 = 
    RecordMaximumAllocation<std::int8_t, std::uint16_t, std::uint32_t>();
constexpr std::size_t size_alloc_t1_obj6 = 
    RecordMaximumAllocation<std::uint16_t, std::int32_t, std::uint64_t>();
constexpr std::size_t size_alloc_t1_obj7 = 
    RecordMaximumAllocation<std::int32_t, std::uint16_t, std::int8_t>();
constexpr std::size_t size_alloc_t1_obj8 = 
    RecordMaximumAllocation<std::uint64_t, std::int32_t, std::int16_t>();

typedef basic::error::id::rec::Error<std::uint8_t> T1Err1;
typedef basic::error::id::rec::Error<std::uint64_t> T1Err2;
typedef basic::error::id::rec::Error<std::uint8_t> T1Err3;
typedef basic::error::id::rec::Error<std::uint64_t> T1Err4;
typedef basic::error::id::rec::Error<std::int8_t> T1Err5;
typedef basic::error::id::rec::Error<std::uint16_t> T1Err6;
typedef basic::error::id::rec::Error<std::int32_t> T1Err7;
typedef basic::error::id::rec::Error<std::uint64_t> T1Err8;

typedef basic::error::id::rec::ErrorSystem<std::uint8_t, 
    std::uint8_t> T1ErrSys1;
typedef basic::error::id::rec::ErrorSystem<std::uint64_t, 
    std::uint64_t> T1ErrSys2;
typedef basic::error::id::rec::ErrorSystem<std::uint16_t, 
    std::uint32_t> T1ErrSys3;
typedef basic::error::id::rec::ErrorSystem<std::uint32_t, 
    std::uint16_t> T1ErrSys4;
typedef basic::error::id::rec::ErrorSystem<std::uint16_t, 
    std::uint32_t> T1ErrSys5;
typedef basic::error::id::rec::ErrorSystem<std::int32_t, 
    std::uint64_t> T1ErrSys6;
typedef basic::error::id::rec::ErrorSystem<std::uint16_t, 
    std::int8_t> T1ErrSys7;
typedef basic::error::id::rec::ErrorSystem<std::int32_t, 
    std::int16_t> T1ErrSys8;

typedef VariableTestRecord<std::uint8_t, std::uint8_t, std::uint8_t> T1Var1;
typedef VariableTestRecord<std::uint64_t, std::uint64_t, std::uint64_t> T1Var2;
typedef VariableTestRecord<std::uint8_t, std::uint16_t, std::uint32_t> T1Var3;
typedef VariableTestRecord<std::uint64_t, std::uint32_t, std::uint16_t> T1Var4;
typedef VariableTestRecord<std::int8_t, std::uint16_t, std::uint32_t> T1Var5;
typedef VariableTestRecord<std::uint16_t, std::int32_t, std::uint64_t> T1Var6;
typedef VariableTestRecord<std::int32_t, std::uint16_t, std::int8_t> T1Var7;
typedef VariableTestRecord<std::uint64_t, std::int32_t, std::int16_t> T1Var8;

T1Obj1 Obj1_1{basic::error::id::Flag{}};
T1Obj2 Obj1_2{basic::error::id::Flag{}};
T1Obj3 Obj1_3{basic::error::id::Flag{}};
T1Obj4 Obj1_4{basic::error::id::Flag{}};
T1Obj5 Obj1_5{basic::error::id::Flag{}};
T1Obj6 Obj1_6{basic::error::id::Flag{}};
T1Obj7 Obj1_7{basic::error::id::Flag{}};
T1Obj8 Obj1_8{basic::error::id::Flag{}};

T1Var1 t1_var1{"Obj1_1", &Obj1_1, 0, size_alloc_t1_obj1, 
    basic::error::id::Flag{}, T1Err1{}, T1ErrSys1{0}, t1_bytes1};
T1Var2 t1_var2{"Obj1_2", &Obj1_2, 0, size_alloc_t1_obj2, 
    basic::error::id::Flag{}, T1Err2{}, T1ErrSys2{0}, t1_bytes1};
T1Var3 t1_var3{"Obj1_3", &Obj1_3, 0, size_alloc_t1_obj3, 
    basic::error::id::Flag{}, T1Err3{}, T1ErrSys3{0}, t1_bytes1};
T1Var4 t1_var4{"Obj1_4", &Obj1_4, 0, size_alloc_t1_obj4, 
    basic::error::id::Flag{}, T1Err4{}, T1ErrSys4{0}, t1_bytes1};
T1Var5 t1_var5{"Obj1_5", &Obj1_5, 0, size_alloc_t1_obj5, 
    basic::error::id::Flag{}, T1Err5{}, T1ErrSys5{0}, t1_bytes1};
T1Var6 t1_var6{"Obj1_6", &Obj1_6, 0, size_alloc_t1_obj6, 
    basic::error::id::Flag{}, T1Err6{}, T1ErrSys6{0}, t1_bytes1};
T1Var7 t1_var7{"Obj1_7", &Obj1_7, 0, size_alloc_t1_obj7, 
    basic::error::id::Flag{}, T1Err7{}, T1ErrSys7{0}, t1_bytes1};
T1Var8 t1_var8{"Obj1_8", &Obj1_8, 0, size_alloc_t1_obj8, 
    basic::error::id::Flag{}, T1Err8{}, T1ErrSys8{0}, t1_bytes1};

REGISTER_TEST(t1, new TestRecord<Case1, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t1_var1, t1_var2, t1_var3, t1_var4,
    t1_var5, t1_var6, t1_var7, t1_var8));

basic::error::id::Flag flag2_1{basic::error::id::flag::Error{}};

std::uint8_t error_uint8_t_1 = 16;
std::int8_t error_int8_t_1 = -52;
std::uint16_t error_uint16_t_1 = 21845;
std::int16_t error_int16_t_1 = -21845;
std::int32_t error_int32_t_1 = -357913941;
std::uint32_t error_uint32_t_1 = 357913941;
std::uint64_t error_uint64_t_1 = 17446244071708550724ull;

Bytes t2_bytes1{0x00, 0x10};
Bytes t2_bytes2{0x00, 0xCC};
Bytes t2_bytes3{0x00, 0x55, 0x55};
Bytes t2_bytes4{0x00, 0xEA, 0xAA, 0xAA, 0xAB};
Bytes t2_bytes5{0x00, 0xF2, 0x1D, 0x82, 0x8C, 0x8E, 0xF3, 0xE6, 0x44};

T1Obj1 Obj2_1{flag2_1, error_uint8_t_1};
T1Obj2 Obj2_2{flag2_1, error_uint64_t_1};
T1Obj3 Obj2_3{flag2_1, error_uint8_t_1};
T1Obj4 Obj2_4{flag2_1, error_uint64_t_1};
T1Obj5 Obj2_5{flag2_1, error_int8_t_1};
T1Obj6 Obj2_6{flag2_1, error_uint16_t_1};
T1Obj7 Obj2_7{flag2_1, error_int32_t_1};
T1Obj8 Obj2_8{flag2_1, error_uint64_t_1};

T1Var1 t2_var1{"Obj2_1", &Obj2_1, 0, 0, flag2_1, T1Err1{error_uint8_t_1}, 
    T1ErrSys1{0}, t2_bytes1};
T1Var2 t2_var2{"Obj2_2", &Obj2_2, 0, 0, flag2_1, T1Err2{error_uint64_t_1}, 
    T1ErrSys2{0}, t2_bytes5};
T1Var3 t2_var3{"Obj2_3", &Obj2_3, 0, 0, flag2_1, T1Err3{error_uint8_t_1}, 
    T1ErrSys3{0}, t2_bytes1};
T1Var4 t2_var4{"Obj2_4", &Obj2_4, 0, 0, flag2_1, T1Err4{error_uint64_t_1}, 
    T1ErrSys4{0}, t2_bytes5};
T1Var5 t2_var5{"Obj2_5", &Obj2_5, 0, 0, flag2_1, T1Err5{error_int8_t_1}, 
    T1ErrSys5{0}, t2_bytes2};
T1Var6 t2_var6{"Obj2_6", &Obj2_6, 0, 0, flag2_1, T1Err6{error_uint16_t_1},
    T1ErrSys6{0}, t2_bytes3};
T1Var7 t2_var7{"Obj2_7", &Obj2_7, 0, 0, flag2_1, T1Err7{error_int32_t_1}, 
    T1ErrSys7{0}, t2_bytes4};
T1Var8 t2_var8{"Obj2_8", &Obj2_8, 0, 0, flag2_1, T1Err8{error_uint64_t_1}, 
    T1ErrSys8{0}, t2_bytes5};

REGISTER_TEST(t2, new TestRecord<Case2, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t2_var1, t2_var2, t2_var3, t2_var4,
    t2_var5, t2_var6, t2_var7, t2_var8));

basic::error::id::Flag flag3_1{basic::error::id::flag::System{},
    basic::error::id::flag::Standard{}};

std::uint8_t category_uint8_t_1 = 114;
std::uint64_t category_uint64_t_1 = 56249071708950721ull;
std::uint16_t category_uint16_t_1 = 53535;
std::uint32_t category_uint32_t_1 = 1234060096ul;
std::int32_t category_int32_t_1 = -1234060096l;

Bytes t3_bytes1{0x14, 0x72, 0x10};
Bytes t3_bytes2{0x14, 0x00, 0xC7, 0xD6, 0x3B, 0x92, 0x28, 0x50, 0xC1,
    0xF2, 0x1D, 0x82, 0x8C, 0x8E, 0xF3, 0xE6, 0x44};
Bytes t3_bytes3{0x14, 0xD1, 0x1F, 0x15, 0x55, 0x55, 0x55};
Bytes t3_bytes4{0x14, 0x49, 0x8E, 0x43, 0x40, 0x55, 0x55};
Bytes t3_bytes5{0x14, 0xD1, 0x1F, 0x15, 0x55, 0x55, 0x55};
Bytes t3_bytes6{0x14, 0xB6, 0x71, 0xBC, 0xC0,
    0xF2, 0x1D, 0x82, 0x8C, 0x8E, 0xF3, 0xE6, 0x44};
Bytes t3_bytes7{0x14, 0xD1, 0x1F, 0xCC}; 
Bytes t3_bytes8{0x14, 0xB6, 0x71, 0xBC, 0xC0, 0xAA, 0xAB};

T1Obj1 Obj3_1{flag3_1, category_uint8_t_1, error_uint8_t_1};
T1Obj2 Obj3_2{flag3_1, category_uint64_t_1, error_uint64_t_1};
T1Obj3 Obj3_3{flag3_1, category_uint16_t_1, error_uint32_t_1};
T1Obj4 Obj3_4{flag3_1, category_uint32_t_1, error_uint16_t_1};
T1Obj5 Obj3_5{flag3_1, category_uint16_t_1, error_uint32_t_1};
T1Obj6 Obj3_6{flag3_1, category_int32_t_1, error_uint64_t_1};
T1Obj7 Obj3_7{flag3_1, category_uint16_t_1, error_int8_t_1};
T1Obj8 Obj3_8{flag3_1, category_int32_t_1, error_int16_t_1};

T1Var1 t3_var1{"Obj3_1", &Obj3_1, 0, 0, flag3_1, T1Err1{0}, 
    T1ErrSys1{category_uint8_t_1, error_uint8_t_1}, t3_bytes1};
T1Var2 t3_var2{"Obj3_2", &Obj3_2, 0, 0, flag3_1, T1Err2{0}, 
    T1ErrSys2{category_uint64_t_1, error_uint64_t_1}, t3_bytes2};
T1Var3 t3_var3{"Obj3_3", &Obj3_3, 0, 0, flag3_1, T1Err3{0}, 
    T1ErrSys3{category_uint16_t_1, error_uint32_t_1}, t3_bytes3};
T1Var4 t3_var4{"Obj3_4", &Obj3_4, 0, 0, flag3_1, T1Err4{0}, 
    T1ErrSys4{category_uint32_t_1, error_uint16_t_1}, t3_bytes4};
T1Var5 t3_var5{"Obj3_5", &Obj3_5, 0, 0, flag3_1, T1Err5{0}, 
    T1ErrSys5{category_uint16_t_1, error_uint32_t_1}, t3_bytes5};
T1Var6 t3_var6{"Obj3_6", &Obj3_6, 0, 0, flag3_1, T1Err6{0},
    T1ErrSys6{category_int32_t_1, error_uint64_t_1}, t3_bytes6};
T1Var7 t3_var7{"Obj3_7", &Obj3_7, 0, 0, flag3_1, T1Err7{0}, 
    T1ErrSys7{category_uint16_t_1, error_int8_t_1}, t3_bytes7};
T1Var8 t3_var8{"Obj3_8", &Obj3_8, 0, 0, flag3_1, T1Err8{0}, 
    T1ErrSys8{category_int32_t_1, error_int16_t_1}, t3_bytes8};

REGISTER_TEST(t3, new TestRecord<Case3, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t3_var1, t3_var2, t3_var3, t3_var4,
    t3_var5, t3_var6, t3_var7, t3_var8));

basic::error::id::Flag flag4_1{basic::error::id::flag::Catch{}, 
    basic::error::id::flag::Standard{}, flag2_1};

Bytes t4_bytes1{0x0C, 0x10};
Bytes t4_bytes2{0x0C, 0xCC};
Bytes t4_bytes3{0x0C, 0x55, 0x55};
Bytes t4_bytes4{0x0C, 0xEA, 0xAA, 0xAA, 0xAB};
Bytes t4_bytes5{0x0C, 0xF2, 0x1D, 0x82, 0x8C, 0x8E, 0xF3, 0xE6, 0x44};

T1Obj1 Obj4_1{flag4_1, Obj2_1};
T1Obj2 Obj4_2{flag4_1, Obj2_2};
T1Obj3 Obj4_3{flag4_1, Obj2_3};
T1Obj4 Obj4_4{flag4_1, Obj2_4};
T1Obj5 Obj4_5{flag4_1, Obj2_5};
T1Obj6 Obj4_6{flag4_1, Obj2_6};
T1Obj7 Obj4_7{flag4_1, Obj2_7};
T1Obj8 Obj4_8{flag4_1, Obj2_8};

T1Var1 t4_var1{"Obj4_1", &Obj4_1, 0, 0, flag4_1, T1Err1{error_uint8_t_1}, 
    T1ErrSys1{0}, t4_bytes1};
T1Var2 t4_var2{"Obj4_2", &Obj4_2, 0, 0, flag4_1, T1Err2{error_uint64_t_1}, 
    T1ErrSys2{0}, t4_bytes5};
T1Var3 t4_var3{"Obj4_3", &Obj4_3, 0, 0, flag4_1, T1Err3{error_uint8_t_1}, 
    T1ErrSys3{0}, t4_bytes1};
T1Var4 t4_var4{"Obj4_4", &Obj4_4, 0, 0, flag4_1, T1Err4{error_uint64_t_1}, 
    T1ErrSys4{0}, t4_bytes5};
T1Var5 t4_var5{"Obj4_5", &Obj4_5, 0, 0, flag4_1, T1Err5{error_int8_t_1}, 
    T1ErrSys5{0}, t4_bytes2};
T1Var6 t4_var6{"Obj4_6", &Obj4_6, 0, 0, flag4_1, T1Err6{error_uint16_t_1},
    T1ErrSys6{0}, t4_bytes3};
T1Var7 t4_var7{"Obj4_7", &Obj4_7, 0, 0, flag4_1, T1Err7{error_int32_t_1}, 
    T1ErrSys7{0}, t4_bytes4};
T1Var8 t4_var8{"Obj4_8", &Obj4_8, 0, 0, flag4_1, T1Err8{error_uint64_t_1}, 
    T1ErrSys8{0}, t4_bytes5};

REGISTER_TEST(t4, new TestRecord<Case2, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t4_var1, t4_var2, t4_var3, t4_var4,
    t4_var5, t4_var6, t4_var7, t4_var8));

basic::error::id::Flag flag5_1{basic::error::id::flag::Catch{}, flag3_1};

Bytes t5_bytes1{0x1C, 0x72, 0x10};
Bytes t5_bytes2{0x1C, 0x00, 0xC7, 0xD6, 0x3B, 0x92, 0x28, 0x50, 0xC1,
    0xF2, 0x1D, 0x82, 0x8C, 0x8E, 0xF3, 0xE6, 0x44};
Bytes t5_bytes3{0x1C, 0xD1, 0x1F, 0x15, 0x55, 0x55, 0x55};
Bytes t5_bytes4{0x1C, 0x49, 0x8E, 0x43, 0x40, 0x55, 0x55};
Bytes t5_bytes5{0x1C, 0xD1, 0x1F, 0x15, 0x55, 0x55, 0x55};
Bytes t5_bytes6{0x1C, 0xB6, 0x71, 0xBC, 0xC0,
    0xF2, 0x1D, 0x82, 0x8C, 0x8E, 0xF3, 0xE6, 0x44};
Bytes t5_bytes7{0x1C, 0xD1, 0x1F, 0xCC}; 
Bytes t5_bytes8{0x1C, 0xB6, 0x71, 0xBC, 0xC0, 0xAA, 0xAB};

T1Obj1 Obj5_1{flag5_1, Obj3_1};
T1Obj2 Obj5_2{flag5_1, Obj3_2};
T1Obj3 Obj5_3{flag5_1, Obj3_3};
T1Obj4 Obj5_4{flag5_1, Obj3_4};
T1Obj5 Obj5_5{flag5_1, Obj3_5};
T1Obj6 Obj5_6{flag5_1, Obj3_6};
T1Obj7 Obj5_7{flag5_1, Obj3_7};
T1Obj8 Obj5_8{flag5_1, Obj3_8};

T1Var1 t5_var1{"Obj5_1", &Obj5_1, 0, 0, flag5_1, T1Err1{0}, 
    T1ErrSys1{category_uint8_t_1, error_uint8_t_1}, t5_bytes1};
T1Var2 t5_var2{"Obj5_2", &Obj5_2, 0, 0, flag5_1, T1Err2{0}, 
    T1ErrSys2{category_uint64_t_1, error_uint64_t_1}, t5_bytes2};
T1Var3 t5_var3{"Obj5_3", &Obj5_3, 0, 0, flag5_1, T1Err3{0}, 
    T1ErrSys3{category_uint16_t_1, error_uint32_t_1}, t5_bytes3};
T1Var4 t5_var4{"Obj5_4", &Obj5_4, 0, 0, flag5_1, T1Err4{0}, 
    T1ErrSys4{category_uint32_t_1, error_uint16_t_1}, t5_bytes4};
T1Var5 t5_var5{"Obj5_5", &Obj5_5, 0, 0, flag5_1, T1Err5{0}, 
    T1ErrSys5{category_uint16_t_1, error_uint32_t_1}, t5_bytes5};
T1Var6 t5_var6{"Obj5_6", &Obj5_6, 0, 0, flag5_1, T1Err6{0},
    T1ErrSys6{category_int32_t_1, error_uint64_t_1}, t5_bytes6};
T1Var7 t5_var7{"Obj5_7", &Obj5_7, 0, 0, flag5_1, T1Err7{0}, 
    T1ErrSys7{category_uint16_t_1, error_int8_t_1}, t5_bytes7};
T1Var8 t5_var8{"Obj5_8", &Obj5_8, 0, 0, flag5_1, T1Err8{0}, 
    T1ErrSys8{category_int32_t_1, error_int16_t_1}, t5_bytes8};

REGISTER_TEST(t5, new TestRecord<Case3, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t5_var1, t5_var2, t5_var3, t5_var4,
    t5_var5, t5_var6, t5_var7, t5_var8));

T1Obj1 Obj6_1{Obj2_1};
T1Obj2 Obj6_2{Obj2_2};
T1Obj3 Obj6_3{Obj2_3};
T1Obj4 Obj6_4{Obj2_4};
T1Obj5 Obj6_5{Obj2_5};
T1Obj6 Obj6_6{Obj2_6};
T1Obj7 Obj6_7{Obj2_7};
T1Obj8 Obj6_8{Obj2_8};

T1Var1 t6_var1{"Obj6_1", &Obj6_1, 0, 0, flag2_1, T1Err1{error_uint8_t_1}, 
    T1ErrSys1{0}, t2_bytes1};
T1Var2 t6_var2{"Obj6_2", &Obj6_2, 0, 0, flag2_1, T1Err2{error_uint64_t_1}, 
    T1ErrSys2{0}, t2_bytes5};
T1Var3 t6_var3{"Obj6_3", &Obj6_3, 0, 0, flag2_1, T1Err3{error_uint8_t_1}, 
    T1ErrSys3{0}, t2_bytes1};
T1Var4 t6_var4{"Obj6_4", &Obj6_4, 0, 0, flag2_1, T1Err4{error_uint64_t_1}, 
    T1ErrSys4{0}, t2_bytes5};
T1Var5 t6_var5{"Obj6_5", &Obj6_5, 0, 0, flag2_1, T1Err5{error_int8_t_1}, 
    T1ErrSys5{0}, t2_bytes2};
T1Var6 t6_var6{"Obj6_6", &Obj6_6, 0, 0, flag2_1, T1Err6{error_uint16_t_1},
    T1ErrSys6{0}, t2_bytes3};
T1Var7 t6_var7{"Obj6_7", &Obj6_7, 0, 0, flag2_1, T1Err7{error_int32_t_1}, 
    T1ErrSys7{0}, t2_bytes4};
T1Var8 t6_var8{"Obj6_8", &Obj6_8, 0, 0, flag2_1, T1Err8{error_uint64_t_1}, 
    T1ErrSys8{0}, t2_bytes5};

REGISTER_TEST(t6, new TestRecord<Case2, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t6_var1, t6_var2, t6_var3, t6_var4,
    t6_var5, t6_var6, t6_var7, t6_var8));

T1Obj1 Obj7_1{Obj3_1};
T1Obj2 Obj7_2{Obj3_2};
T1Obj3 Obj7_3{Obj3_3};
T1Obj4 Obj7_4{Obj3_4};
T1Obj5 Obj7_5{Obj3_5};
T1Obj6 Obj7_6{Obj3_6};
T1Obj7 Obj7_7{Obj3_7};
T1Obj8 Obj7_8{Obj3_8};

T1Var1 t7_var1{"Obj7_1", &Obj7_1, 0, 0, flag3_1, T1Err1{0}, 
    T1ErrSys1{category_uint8_t_1, error_uint8_t_1}, t3_bytes1};
T1Var2 t7_var2{"Obj7_2", &Obj7_2, 0, 0, flag3_1, T1Err2{0}, 
    T1ErrSys2{category_uint64_t_1, error_uint64_t_1}, t3_bytes2};
T1Var3 t7_var3{"Obj7_3", &Obj7_3, 0, 0, flag3_1, T1Err3{0}, 
    T1ErrSys3{category_uint16_t_1, error_uint32_t_1}, t3_bytes3};
T1Var4 t7_var4{"Obj7_4", &Obj7_4, 0, 0, flag3_1, T1Err4{0}, 
    T1ErrSys4{category_uint32_t_1, error_uint16_t_1}, t3_bytes4};
T1Var5 t7_var5{"Obj7_5", &Obj7_5, 0, 0, flag3_1, T1Err5{0}, 
    T1ErrSys5{category_uint16_t_1, error_uint32_t_1}, t3_bytes5};
T1Var6 t7_var6{"Obj7_6", &Obj7_6, 0, 0, flag3_1, T1Err6{0},
    T1ErrSys6{category_int32_t_1, error_uint64_t_1}, t3_bytes6};
T1Var7 t7_var7{"Obj7_7", &Obj7_7, 0, 0, flag3_1, T1Err7{0}, 
    T1ErrSys7{category_uint16_t_1, error_int8_t_1}, t3_bytes7};
T1Var8 t7_var8{"Obj7_8", &Obj7_8, 0, 0, flag3_1, T1Err8{0}, 
    T1ErrSys8{category_int32_t_1, error_int16_t_1}, t3_bytes8};

REGISTER_TEST(t7, new TestRecord<Case3, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t7_var1, t7_var2, t7_var3, t7_var4,
    t7_var5, t7_var6, t7_var7, t7_var8));

T1Obj1 Obj6_1_c{Obj6_1};
T1Obj2 Obj6_2_c{Obj6_2};
T1Obj3 Obj6_3_c{Obj6_3};
T1Obj4 Obj6_4_c{Obj6_4};
T1Obj5 Obj6_5_c{Obj6_5};
T1Obj6 Obj6_6_c{Obj6_6};
T1Obj7 Obj6_7_c{Obj6_7};
T1Obj8 Obj6_8_c{Obj6_8};

T1Obj1 Obj8_1{std::move(Obj6_1_c)};
T1Obj2 Obj8_2{std::move(Obj6_2_c)};
T1Obj3 Obj8_3{std::move(Obj6_3_c)};
T1Obj4 Obj8_4{std::move(Obj6_4_c)};
T1Obj5 Obj8_5{std::move(Obj6_5_c)};
T1Obj6 Obj8_6{std::move(Obj6_6_c)};
T1Obj7 Obj8_7{std::move(Obj6_7_c)};
T1Obj8 Obj8_8{std::move(Obj6_8_c)};

T1Var1 t8_var1{"Obj8_1", &Obj8_1, 0, 0, flag2_1, T1Err1{error_uint8_t_1}, 
    T1ErrSys1{0}, t2_bytes1};
T1Var2 t8_var2{"Obj8_2", &Obj8_2, 0, 0, flag2_1, T1Err2{error_uint64_t_1}, 
    T1ErrSys2{0}, t2_bytes5};
T1Var3 t8_var3{"Obj8_3", &Obj8_3, 0, 0, flag2_1, T1Err3{error_uint8_t_1}, 
    T1ErrSys3{0}, t2_bytes1};
T1Var4 t8_var4{"Obj8_4", &Obj8_4, 0, 0, flag2_1, T1Err4{error_uint64_t_1}, 
    T1ErrSys4{0}, t2_bytes5};
T1Var5 t8_var5{"Obj8_5", &Obj8_5, 0, 0, flag2_1, T1Err5{error_int8_t_1}, 
    T1ErrSys5{0}, t2_bytes2};
T1Var6 t8_var6{"Obj8_6", &Obj8_6, 0, 0, flag2_1, T1Err6{error_uint16_t_1},
    T1ErrSys6{0}, t2_bytes3};
T1Var7 t8_var7{"Obj8_7", &Obj8_7, 0, 0, flag2_1, T1Err7{error_int32_t_1}, 
    T1ErrSys7{0}, t2_bytes4};
T1Var8 t8_var8{"Obj8_8", &Obj8_8, 0, 0, flag2_1, T1Err8{error_uint64_t_1}, 
    T1ErrSys8{0}, t2_bytes5};

T1Var1 t8_var9{"Obj6_1_c", &Obj6_1_c, 0, size_alloc_t1_obj1, 
    basic::error::id::Flag{}, T1Err1{}, T1ErrSys1{0}, t1_bytes1};
T1Var2 t8_var10{"Obj6_2_c", &Obj6_2_c, 0, size_alloc_t1_obj2, 
    basic::error::id::Flag{}, T1Err2{}, T1ErrSys2{0}, t1_bytes1};
T1Var3 t8_var11{"Obj6_3_c", &Obj6_3_c, 0, size_alloc_t1_obj3, 
    basic::error::id::Flag{}, T1Err3{}, T1ErrSys3{0}, t1_bytes1};
T1Var4 t8_var12{"Obj6_4_c", &Obj6_4_c, 0, size_alloc_t1_obj4, 
    basic::error::id::Flag{}, T1Err4{}, T1ErrSys4{0}, t1_bytes1};
T1Var5 t8_var13{"Obj6_5_c", &Obj6_5_c, 0, size_alloc_t1_obj5, 
    basic::error::id::Flag{}, T1Err5{}, T1ErrSys5{0}, t1_bytes1};
T1Var6 t8_var14{"Obj6_6_c", &Obj6_6_c, 0, size_alloc_t1_obj6, 
    basic::error::id::Flag{}, T1Err6{}, T1ErrSys6{0}, t1_bytes1};
T1Var7 t8_var15{"Obj6_7_c", &Obj6_7_c, 0, size_alloc_t1_obj7, 
    basic::error::id::Flag{}, T1Err7{}, T1ErrSys7{0}, t1_bytes1};
T1Var8 t8_var16{"Obj6_8_c", &Obj6_8_c, 0, size_alloc_t1_obj8, 
    basic::error::id::Flag{}, T1Err8{}, T1ErrSys8{0}, t1_bytes1};

REGISTER_TEST(t8, new TestRecord<Case2, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8, T1Var1, T1Var2, T1Var3, T1Var4,
    T1Var5, T1Var6, T1Var7, T1Var8>(t8_var1, t8_var2, t8_var3, t8_var4,
    t8_var5, t8_var6, t8_var7, t8_var8, t8_var9, t8_var10, t8_var11, 
    t8_var12, t8_var13, t8_var14, t8_var15, t8_var16));

int main()
{
    return RUN_TEST();
}

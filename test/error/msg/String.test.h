#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/msg/String.h"

#include <cstring>

const char * BoolToCString(bool && b)
{
    return (b ? "true" : "false");
}

struct TestAliasCharType {};
struct TestAliasStorageType {};
struct TestValueValue {};
struct TestCastToBool {};
struct TestBasiOfIntefaceExit {};
struct TestCleanUp {};
struct TestAssignmentCopy {};
struct TestAssignmentMove {};

using VariableTestMsgString = basic::test::Variable<
    basic::error::defn::type::Char,
    basic::error::defn::type::msg::str::Storage,
    basic::error::msg::String,
    basic::error::intf::Exit,
    basic::test::Value<const char *>,
    basic::test::Value<basic::error::msg::String *>,
    basic::test::Value<const char *>,
    basic::test::Value<bool>,
    basic::test::type::Function<const char *(bool &&), &BoolToCString>>;

constexpr std::size_t ICharType = 0;
constexpr std::size_t IStorageType = 1;
constexpr std::size_t IIntfExit = 2;
constexpr std::size_t IObjType = 3;
constexpr std::size_t IObjName = 4;
constexpr std::size_t IObjValue = 5;
constexpr std::size_t IValueValue = 6;
constexpr std::size_t IBoolValue = 7;
constexpr std::size_t IBoolToCstringFunc = 8;


typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<ICharType>> ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasStorageType,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IStorageType>> ArgTestAliasStorageType;

typedef basic::test::msg::Base<TestAliasStorageType, char, 
    ArgTestAliasStorageType, ArgTestAliasStorageType, 
    ArgTestAliasStorageType> MessageBaseTestAliasStorageType;

typedef basic::test::msg::Argument<TestValueValue,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IValueValue>> ArgTestValueValue;

typedef basic::test::msg::Base<TestValueValue, char, 
    ArgTestValueValue, ArgTestValueValue, 
    ArgTestValueValue> MessageBaseTestValueValue;

typedef basic::test::msg::Argument<TestCastToBool,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToCstringFunc,
        basic::test::msg::arg::Value<IBoolValue>>> ArgTestCastToBool;

typedef basic::test::msg::Base<TestCastToBool, char, 
    ArgTestCastToBool, ArgTestCastToBool, 
    ArgTestCastToBool> MessageBaseTestCastToBool;

template<typename TCases, typename... TVariables>
struct TestMsgString :
    public basic::test::Message<BASIC_TEST, TestMsgString<TCases, 
        TVariables...>>,
    public basic::test::Case<TestMsgString<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestMsgString<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasStorageType,
    public MessageBaseTestValueValue,
    public MessageBaseTestCastToBool
{
public:
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasStorageType::Format;
    using MessageBaseTestAliasStorageType::SetFormat;
    using MessageBaseTestAliasStorageType::Argument;
    using MessageBaseTestValueValue::Format;
    using MessageBaseTestValueValue::SetFormat;
    using MessageBaseTestValueValue::Argument;
    using MessageBaseTestCastToBool::Format;
    using MessageBaseTestCastToBool::SetFormat;
    using MessageBaseTestCastToBool::Argument;
    using basic::test::Case<TestMsgString<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestMsgString<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestMsgString(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestMsgString<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestMsgString<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestMsgString<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType {%s} is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType {%s} is same with %s\n");
        SetFormat(error, testAliasCharType, "Error alias type "
            "%s::CharType {%s} is not same with %s\n");
        
        TestAliasStorageType testAliasStorageType;
        SetFormat(info, testAliasStorageType, "Test alias type "
            "%s::StorageType {%s} is same with %s\n");
        SetFormat(debug, testAliasStorageType, "Test alias type "
            "%s::StorageType {%s} is same with %s\n");
        SetFormat(error, testAliasStorageType, "Error alias type "
            "%s::StorageType {%s} is not same with %s\n");

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test return value "
            "%s::Value() {%s} is same with \"%s\"\n");
        SetFormat(debug, testValueValue, "Test return value "
            "%s::Value() {%s} is same with \"%s\"\n");
        SetFormat(error, testValueValue, "Error return value "
            "%s::Value() {%s} is not same with \"%s\"\n");

        TestCastToBool testCastToBool;
        SetFormat(info, testCastToBool, "Test cast from "
            "%s {%s} to bool is same with bool {%s}\n");
        SetFormat(debug, testCastToBool, "Test cast from "
            "%s {%s} to bool is same with bool {%s}\n");
        SetFormat(error, testCastToBool, "Error cast from "
            "%s {%s} to bool is not same with bool {%s}\n");
    
    }
    bool Result(const TestAliasCharType &, VariableTestMsgString & var)
    {
        return typeid(typename basic::error::msg::String::CharType).
            hash_code() == typeid(basic::error::defn::type::Char).hash_code();
    }
    bool Result(const TestAliasStorageType &, VariableTestMsgString & var)
    {
        return typeid(typename basic::error::msg::String::StorageType).
            hash_code() == typeid(basic::error::defn::type::msg::str::
                Storage).hash_code();
    }
    bool Result(const TestValueValue &, VariableTestMsgString & var)
    {
        const char * cstring_val = basic::test::var::At<IObjValue>(var).
            Get().Get()->Value();
        return std::strcmp(cstring_val, basic::test::var::At<IValueValue>(var).
            Get().Get()) == 0;
    }
    bool Result(const TestCastToBool &, VariableTestMsgString & var)
    {
        bool cstring_bool = static_cast<bool>(*basic::test::var::
            At<IObjValue>(var).Get().Get());
        return cstring_bool == basic::test::var::At<IBoolValue>(var).
            Get().Get();
    }

};

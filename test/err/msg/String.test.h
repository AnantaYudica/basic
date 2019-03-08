#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/msg/String.h"
#include "err/intf/Exit.h"

#include <cstring>
#include <type_traits>
#include <utility>

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
struct TestCopyAssignment {};
struct TestMoveAssignment {};

using VariableTestMsgString = basic::test::Variable<
    basic::err::defn::type::Char,
    basic::err::defn::type::msg::str::Storage,
    basic::err::msg::String,
    basic::err::intf::Exit,
    basic::test::Value<const char *>,
    basic::test::Value<basic::err::msg::String *>,
    basic::test::Value<const char *>,
    basic::test::Value<bool>,
    basic::test::Value<int>,
    basic::test::Value<bool>,
    basic::test::Value<const char *>,
    basic::test::Value<basic::err::msg::String *>,
    basic::test::type::Function<const char *(bool &&), &BoolToCString>>;

constexpr std::size_t ICharType = 0;
constexpr std::size_t IStorageType = 1;
constexpr std::size_t IObjType = 2;
constexpr std::size_t IIntfExit = 3;
constexpr std::size_t IObjName = 4;
constexpr std::size_t IObjValue = 5;
constexpr std::size_t IValueValue = 6;
constexpr std::size_t IBoolValue = 7;
constexpr std::size_t ISignalValue = 8;
constexpr std::size_t ICleanupBoolValue = 9;
constexpr std::size_t IAssignmentName = 10;
constexpr std::size_t IAssignmentValue = 11;
constexpr std::size_t IBoolToCstringFunc = 12;

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
    basic::test::msg::arg::Value<IValueValue>> ArgTestValueValue;

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

typedef basic::test::msg::Argument<TestBasiOfIntefaceExit,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Name<IIntfExit>> 
        ArgTestBasiOfIntefaceExit;

typedef basic::test::msg::Base<TestBasiOfIntefaceExit, char, 
    ArgTestBasiOfIntefaceExit, ArgTestBasiOfIntefaceExit, 
    ArgTestBasiOfIntefaceExit> MessageBaseTestBasiOfIntefaceExit;

typedef basic::test::msg::Argument<TestCleanUp,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<ISignalValue>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::type::Function<IBoolToCstringFunc,
        basic::test::msg::arg::Value<ICleanupBoolValue>>> ArgTestCleanUp;

typedef basic::test::msg::Base<TestCleanUp, char, 
    ArgTestCleanUp, ArgTestCleanUp, ArgTestCleanUp> MessageBaseTestCleanUp;

typedef basic::test::msg::Argument<TestCopyAssignment,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::Value<IAssignmentName>> ArgTestCopyAssignment;

typedef basic::test::msg::Base<TestCopyAssignment, char, 
    ArgTestCopyAssignment, ArgTestCopyAssignment, 
    ArgTestCopyAssignment> MessageBaseTestCopyAssignment;

typedef basic::test::msg::Argument<TestMoveAssignment,
    basic::test::msg::arg::type::Name<IObjType>,
    basic::test::msg::arg::Value<IObjName>,
    basic::test::msg::arg::Value<IAssignmentName>> ArgTestMoveAssignment;

typedef basic::test::msg::Base<TestMoveAssignment, char, 
    ArgTestMoveAssignment, ArgTestMoveAssignment, 
    ArgTestMoveAssignment> MessageBaseTestMoveAssignment;

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
    public MessageBaseTestCastToBool,
    public MessageBaseTestBasiOfIntefaceExit,
    public MessageBaseTestCleanUp,
    public MessageBaseTestCopyAssignment,
    public MessageBaseTestMoveAssignment
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
    using MessageBaseTestBasiOfIntefaceExit::Format;
    using MessageBaseTestBasiOfIntefaceExit::SetFormat;
    using MessageBaseTestBasiOfIntefaceExit::Argument;
    using MessageBaseTestCleanUp::Format;
    using MessageBaseTestCleanUp::SetFormat;
    using MessageBaseTestCleanUp::Argument;
    using MessageBaseTestCopyAssignment::Format;
    using MessageBaseTestCopyAssignment::SetFormat;
    using MessageBaseTestCopyAssignment::Argument;
    using MessageBaseTestMoveAssignment::Format;
    using MessageBaseTestMoveAssignment::SetFormat;
    using MessageBaseTestMoveAssignment::Argument;
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
        basic::test::msg::base::Error err;

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType {%s} is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType {%s} is same with %s\n");
        SetFormat(err, testAliasCharType, "Error alias type "
            "%s::CharType {%s} is not same with %s\n");
        
        TestAliasStorageType testAliasStorageType;
        SetFormat(info, testAliasStorageType, "Test alias type "
            "%s::StorageType {%s} is same with %s\n");
        SetFormat(debug, testAliasStorageType, "Test alias type "
            "%s::StorageType {%s} is same with %s\n");
        SetFormat(err, testAliasStorageType, "Error alias type "
            "%s::StorageType {%s} is not same with %s\n");

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test return value "
            "%s::Value() {%s} is same with \"%s\"\n");
        SetFormat(debug, testValueValue, "Test return value "
            "%s::Value() {%s} is same with \"%s\"\n");
        SetFormat(err, testValueValue, "Error return value "
            "%s::Value() {%s} is not same with \"%s\"\n");

        TestCastToBool testCastToBool;
        SetFormat(info, testCastToBool, "Test cast from "
            "%s {%s} to bool and bool is same with %s\n");
        SetFormat(debug, testCastToBool, "Test cast from "
            "%s {%s} to bool and bool is same with %s\n");
        SetFormat(err, testCastToBool, "Error when cast from "
            "%s {%s} to bool and bool is not same with %s\n");

        TestBasiOfIntefaceExit testBasiOfIntefaceExit;
        SetFormat(info, testBasiOfIntefaceExit, "Test base of "
            "%s {%s} is %s\n");
        SetFormat(debug, testBasiOfIntefaceExit, "Test base of "
            "%s {%s} is %s\n");
        SetFormat(err, testBasiOfIntefaceExit, "Error base of "
            "%s {%s} is %s\n");

        TestCleanUp testCleanUp;
        SetFormat(info, testCleanUp, "Test call "
            "%s::CleanUp(%d) {%s} and %s cast to bool == %s\n");
        SetFormat(debug, testCleanUp, "Test call "
            "%s::CleanUp(%d) {%s} and %s cast to bool == %s\n");
        SetFormat(err, testCleanUp, "Error when call "
            "%s::CleanUp(%d) {%s} and %s cast to bool != %s\n");

        TestCopyAssignment testCopyAssignment;
        SetFormat(info, testCopyAssignment, "Test copy assigment of "
            "%s {%s} with %s\n");
        SetFormat(debug, testCopyAssignment, "Test copy assigment of "
            "%s {%s} with %s\n");
        SetFormat(err, testCopyAssignment, "Error copy assigment of "
            "%s {%s} with %s\n");

        TestMoveAssignment testMoveAssignment;
        SetFormat(info, testMoveAssignment, "Test move assigment of "
            "%s {%s} with %s\n");
        SetFormat(debug, testMoveAssignment, "Test move assigment of "
            "%s {%s} with %s\n");
        SetFormat(err, testMoveAssignment, "Error move assigment of "
            "%s {%s} with %s\n");
    
    }
    bool Result(const TestAliasCharType &, VariableTestMsgString & var)
    {
        return typeid(typename basic::err::msg::String::CharType).
            hash_code() == typeid(basic::err::defn::type::Char).hash_code();
    }
    bool Result(const TestAliasStorageType &, VariableTestMsgString & var)
    {
        return typeid(typename basic::err::msg::String::StorageType).
            hash_code() == typeid(basic::err::defn::type::msg::str::
                Storage).hash_code();
    }
    bool Result(const TestValueValue &, VariableTestMsgString & var)
    {
        const char * obj_val_val = basic::test::var::At<IObjValue>(var).
            Get().Get()->Value();
        const char * val_val = basic::test::var::At<IValueValue>(var).
            Get().Get();
        return std::strcmp(obj_val_val, val_val) == 0;
    }
    bool Result(const TestCastToBool &, VariableTestMsgString & var)
    {
        bool obj_val_bool = static_cast<bool>(*basic::test::var::
            At<IObjValue>(var).Get().Get());
        return obj_val_bool == basic::test::var::At<IBoolValue>(var).
            Get().Get();
    }
    bool Result(const TestBasiOfIntefaceExit &, VariableTestMsgString & var)
    {
        return std::is_base_of<basic::err::intf::Exit,
            basic::err::msg::String>::value;
    }
    bool Result(const TestCleanUp &, VariableTestMsgString & var)
    {
        auto * obj_val_ptr = basic::test::var::At<IObjValue>(var).Get().Get();
        auto * intf_exit_ptr = dynamic_cast<basic::err::intf::Exit *>(obj_val_ptr);
        intf_exit_ptr->Cleanup(basic::test::var::At<ISignalValue>(var).Get().Get());
        return static_cast<bool>(*obj_val_ptr) == 
            basic::test::var::At<ICleanupBoolValue>(var).Get().Get(); 
    }
    bool Result(const TestCopyAssignment &, VariableTestMsgString & var)
    {
        auto * obj_val_ptr = basic::test::var::At<IObjValue>(var).Get().Get();
        *obj_val_ptr = *basic::test::var::At<IAssignmentValue>(var).Get().Get();
        return true;
    }
    bool Result(const TestMoveAssignment &, VariableTestMsgString & var)
    {
        auto * obj_val_ptr = basic::test::var::At<IObjValue>(var).Get().Get();
        *obj_val_ptr = std::move(*basic::test::var::At<IAssignmentValue>(var).
            Get().Get());
        return true;
    }
};


BASIC_TEST_TYPE_NAME("const char", const char);
BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("const char *", const char *);
BASIC_TEST_TYPE_NAME("char *", char *);

template<std::size_t N>
struct basic::test::type::Name<char[N]>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "char[%d]";
        return basic::test::cstr::Format(sizeof(_format) + 18, 
            _format, N);
    }
};
    
BASIC_TEST_TYPE_NAME("basic::err::msg::String", 
    basic::err::msg::String);
BASIC_TEST_TYPE_NAME("basic::err::intf::Exit", 
    basic::err::intf::Exit);

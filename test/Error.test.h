#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "Error.defn.h"
#include "err/Information.h"
#include "err/defn/type/Char.h"
#include "err/defn/type/Output.h"
#include "err/defn/type/code/Value.h"
#include "err/Identification.h"

#include "err/tag/Trigger.h"

#include <cstddef>
#include <sstream>
#include <ostream>

#define BUFFER_FORMAT_CSTRING 256

const char * ToString(basic::err::Information * && info)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    std::stringstream ss;
    const auto * out = dynamic_cast<
        const basic::err::intf::Output *>(info);
    *out >> ss;
    strncpy(tmp, ss.str().c_str(), ss.str().size());
    return tmp;
}

const char * CategoryToString(basic::err::defn::type::sys::
    categ::Value * && val)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    std::stringstream ss;
    ss << (int)*val;
    strncpy(tmp, ss.str().c_str(), ss.str().size());
    return tmp;
}

const char * CodeToString(basic::err::defn::type::code::Value * && val)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    std::stringstream ss;
    ss << *val;
    strncpy(tmp, ss.str().c_str(), ss.str().size());
    return tmp;
}

template<typename TCode = basic::err::defn::type::sys::code::Value>
const typename std::enable_if<!std::is_same<TCode, 
    basic::err::defn::type::code::Value>::value, char>::type * 
CodeToString(TCode * && val)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    std::stringstream ss;
    ss << *val;
    strncpy(tmp, ss.str().c_str(), ss.str().size());
    return tmp;
}

const char * TriggerToString(const basic::Error<
    basic::err::tag::Trigger> * && val)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    std::stringstream ss;
    auto out = dynamic_cast<const basic::err::intf::Output *>(val);
    ss << *out;
    strncpy(tmp, ss.str().c_str(), ss.str().size());
    return tmp;
}

struct TestBaseOfInformation {};
struct TestBaseOfTrigger {};
struct TestAliasCharType {};
struct TestAliasOutputType {};
struct TestAliasCategoryValueType {};
struct TestAliasCodeValueType {};
struct TestAliasIdType {};
struct TestAliasInfoType {};
struct TestAliasTriggerType {};
struct TestValueMessage {};
struct TestValueCategory {};
struct TestValueCode {};
struct TestValueTrigger {};
struct TestValueOutput {};

template<typename TTag, typename TCode = basic::err::defn::type::code::Value,
    typename TTrigger = void>
using VariableTestError = basic::test::Variable<
    TTag,
    basic::Error<TTag>,
    basic::err::Information,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::defn::type::sys::categ::Value,
    TCode,
    TTrigger,
    basic::err::Identification,
    const basic::err::defn::type::Char *,
    const basic::err::defn::type::Char *,
    basic::test::Value<basic::Error<TTag> *>,
    basic::test::Value<
        const basic::err::defn::type::Char *>,
    basic::test::Value<
        basic::err::Information *>,
    basic::test::Value<basic::err::defn::type::sys::categ::Value *>,
    basic::test::Value<TCode *>,
    basic::test::Value<const TTrigger *>,
    basic::test::Value<
        const basic::err::defn::type::Char *>,
    basic::test::type::Function<const char *(basic::err::Information * &&),
        &ToString>,
    basic::test::type::Function<const char *(TCode * &&), &CodeToString>,
    basic::test::type::Function<const char *(basic::err::defn::type::sys::
        categ::Value * &&), &CategoryToString>,
    basic::test::type::Function<const char *(const basic::Error<
        basic::err::tag::Trigger> * &&), &TriggerToString>>;

enum : std::size_t
{
    ITagType,
    IErrorType,
    IInformationType,
    ICharType,
    IOutputType,
    ICategoryValueType,
    ICodeValueType,
    ITriggerValueType,
    IIdentificationType,
    IMessageCharType,
    IOutputCharType,
    IErrorValue,
    IMessageValue,
    IInformationValue,
    ICategoryValueValue,
    ICodeValueValue,
    ITriggerValueValue,
    IOutputValue,
    IInformationToStringTypeFunc,
    ICodeValueToStringTypeFunc,
    ICategoryValueToStringTypeFunc,
    ITriggerValueToStringTypeFunc
};

typedef basic::test::msg::Argument<TestBaseOfInformation,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<IInformationType>>
        ArgTestBaseOfInformation;

typedef basic::test::msg::Base<TestBaseOfInformation, char, 
    ArgTestBaseOfInformation, ArgTestBaseOfInformation, 
    ArgTestBaseOfInformation> MessageBaseTestBaseOfInformation;

typedef basic::test::msg::Argument<TestBaseOfTrigger,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ITriggerValueType>>
        ArgTestBaseOfTrigger;

typedef basic::test::msg::Base<TestBaseOfTrigger, char, 
    ArgTestBaseOfTrigger, ArgTestBaseOfTrigger, 
    ArgTestBaseOfTrigger> MessageBaseTestBaseOfTrigger;

typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICharType>>
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICharType>>
        ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestAliasCategoryValueType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasCategoryValueType;

typedef basic::test::msg::Base<TestAliasCategoryValueType, char, 
    ArgTestAliasCategoryValueType, ArgTestAliasCategoryValueType, 
    ArgTestAliasCategoryValueType> MessageBaseTestAliasCategoryValueType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasIdType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasIdType;

typedef basic::test::msg::Base<TestAliasIdType, char, 
    ArgTestAliasIdType, ArgTestAliasIdType, 
    ArgTestAliasIdType> MessageBaseTestAliasIdType;

typedef basic::test::msg::Argument<TestAliasInfoType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasInfoType;

typedef basic::test::msg::Base<TestAliasInfoType, char, 
    ArgTestAliasInfoType, ArgTestAliasInfoType, 
    ArgTestAliasInfoType> MessageBaseTestAliasInfoType;

typedef basic::test::msg::Argument<TestAliasTriggerType,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ITriggerValueType>>
        ArgTestAliasTriggerType;

typedef basic::test::msg::Base<TestAliasTriggerType, char, 
    ArgTestAliasTriggerType, ArgTestAliasTriggerType, 
    ArgTestAliasTriggerType> MessageBaseTestAliasTriggerType;

typedef basic::test::msg::Argument<TestValueMessage,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::Value<IMessageValue>, 
    basic::test::msg::arg::type::Name<IMessageCharType>>
        ArgTestValueMessage;

typedef basic::test::msg::Base<TestValueMessage, char, 
    ArgTestValueMessage, ArgTestValueMessage, ArgTestValueMessage> 
        MessageBaseTestValueMessage;

typedef basic::test::msg::Argument<TestValueCategory,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Function<ICategoryValueToStringTypeFunc,
        basic::test::msg::arg::Value<ICategoryValueValue>>, 
    basic::test::msg::arg::type::Name<ICategoryValueType>>
        ArgTestValueCategory;

typedef basic::test::msg::Base<TestValueCategory, char, 
    ArgTestValueCategory, ArgTestValueCategory, ArgTestValueCategory> 
        MessageBaseTestValueCategory;

typedef basic::test::msg::Argument<TestValueCode,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Function<ICodeValueToStringTypeFunc,
        basic::test::msg::arg::Value<ICodeValueValue>>, 
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestValueCode;

typedef basic::test::msg::Base<TestValueCode, char, 
    ArgTestValueCode, ArgTestValueCode, ArgTestValueCode> 
        MessageBaseTestValueCode;

typedef basic::test::msg::Argument<TestValueTrigger,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Function<ITriggerValueToStringTypeFunc,
        basic::test::msg::arg::Value<ITriggerValueValue>>, 
    basic::test::msg::arg::type::Name<ITriggerValueType>>
        ArgTestValueTrigger;

typedef basic::test::msg::Base<TestValueTrigger, char, 
    ArgTestValueTrigger, ArgTestValueTrigger, ArgTestValueTrigger> 
        MessageBaseTestValueTrigger;

typedef basic::test::msg::Argument<TestValueOutput,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::Value<IOutputValue>, 
    basic::test::msg::arg::type::Name<IOutputCharType>>
        ArgTestValueOutput;

typedef basic::test::msg::Base<TestValueOutput, char, 
    ArgTestValueOutput, ArgTestValueOutput, ArgTestValueOutput> 
        MessageBaseTestValueOutput;

template<typename TCases, typename... TVariables>
struct TestError :
    public basic::test::Message<BASIC_TEST, TestError<TCases, 
        TVariables...>>,
    public basic::test::Case<TestError<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestError<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfInformation,
    public MessageBaseTestBaseOfTrigger,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestAliasCategoryValueType,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasIdType,
    public MessageBaseTestAliasInfoType,
    public MessageBaseTestAliasTriggerType,
    public MessageBaseTestValueMessage,
    public MessageBaseTestValueCategory,
    public MessageBaseTestValueCode,
    public MessageBaseTestValueTrigger,
    public MessageBaseTestValueOutput
{
public:
    using basic::test::Case<TestError<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestError<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfInformation::Format;
    using MessageBaseTestBaseOfInformation::SetFormat;
    using MessageBaseTestBaseOfInformation::Argument;
    using MessageBaseTestBaseOfTrigger::Format;
    using MessageBaseTestBaseOfTrigger::SetFormat;
    using MessageBaseTestBaseOfTrigger::Argument;
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasOutputType::Format;
    using MessageBaseTestAliasOutputType::SetFormat;
    using MessageBaseTestAliasOutputType::Argument;
    using MessageBaseTestAliasCategoryValueType::Format;
    using MessageBaseTestAliasCategoryValueType::SetFormat;
    using MessageBaseTestAliasCategoryValueType::Argument;
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestAliasIdType::Format;
    using MessageBaseTestAliasIdType::SetFormat;
    using MessageBaseTestAliasIdType::Argument;
    using MessageBaseTestAliasInfoType::Format;
    using MessageBaseTestAliasInfoType::SetFormat;
    using MessageBaseTestAliasInfoType::Argument;
    using MessageBaseTestAliasTriggerType::Format;
    using MessageBaseTestAliasTriggerType::SetFormat;
    using MessageBaseTestAliasTriggerType::Argument;
    using MessageBaseTestValueMessage::Format;
    using MessageBaseTestValueMessage::SetFormat;
    using MessageBaseTestValueMessage::Argument;
    using MessageBaseTestValueCategory::Format;
    using MessageBaseTestValueCategory::SetFormat;
    using MessageBaseTestValueCategory::Argument;
    using MessageBaseTestValueCode::Format;
    using MessageBaseTestValueCode::SetFormat;
    using MessageBaseTestValueCode::Argument;
    using MessageBaseTestValueTrigger::Format;
    using MessageBaseTestValueTrigger::SetFormat;
    using MessageBaseTestValueTrigger::Argument;
    using MessageBaseTestValueOutput::Format;
    using MessageBaseTestValueOutput::SetFormat;
    using MessageBaseTestValueOutput::Argument;
public:
    TestError(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestError<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestError<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestError<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestBaseOfInformation testBaseOfInformation;
        SetFormat(info, testBaseOfInformation, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfInformation, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfInformation, 
            "Error Test %s is not base of %s\n");

        TestBaseOfTrigger testBaseOfTrigger;
        SetFormat(info, testBaseOfTrigger, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfTrigger, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfTrigger, 
            "Error Test %s is not base of %s\n");

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(err, testAliasCharType, "Error alias type "
            "%s::CharType is not same with %s\n");

        TestAliasOutputType testAliasOutputType;
        SetFormat(info, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(debug, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(err, testAliasOutputType, "Error alias type "
            "%s::OutputType is not same with %s\n");

        TestAliasCategoryValueType testAliasCategoryValueType;
        SetFormat(info, testAliasCategoryValueType, "Test alias type "
            "%s::CategoryValueType is same with %s\n");
        SetFormat(debug, testAliasCategoryValueType, "Test alias type "
            "%s::CategoryValueType is same with %s\n");
        SetFormat(err, testAliasCategoryValueType, "Error alias type "
            "%s::CategoryValueType is not same with %s\n");

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(err, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType is not same with %s\n");

        TestAliasIdType testAliasIdType;
        SetFormat(info, testAliasIdType, "Test alias type "
            "%s::IdType is same with %s\n");
        SetFormat(debug, testAliasIdType, "Test alias type "
            "%s::IdType is same with %s\n");
        SetFormat(err, testAliasIdType, "Error alias type "
            "%s::IdType is not same with %s\n");

        TestAliasInfoType testAliasInfoType;
        SetFormat(info, testAliasInfoType, "Test alias type "
            "%s::InfoType is same with %s\n");
        SetFormat(debug, testAliasInfoType, "Test alias type "
            "%s::InfoType is same with %s\n");
        SetFormat(err, testAliasInfoType, "Error alias type "
            "%s::InfoType is not same with %s\n");

        TestAliasTriggerType testAliasTriggerType;
        SetFormat(info, testAliasTriggerType, "Test alias type "
            "%s::TriggerType is same with %s\n");
        SetFormat(debug, testAliasTriggerType, "Test alias type "
            "%s::TriggerType is same with %s\n");
        SetFormat(err, testAliasTriggerType, "Error alias type "
            "%s::TriggerType is not same with %s\n");

        TestValueMessage testValueMessage;
        SetFormat(info, testValueMessage, "Test Value %s::"
            "Message() is same with \"%s\" {%s}\n");
        SetFormat(debug, testValueMessage, "Test Value %s::"
            "Message() is same with \"%s\" {%s}\n");
        SetFormat(err, testValueMessage, "Error Value %s::"
            "Message() is not same with \"%s\" {%s}\n");

        TestValueCategory testValueCategory;
        SetFormat(info, testValueCategory, "Test Value %s::"
            "Category() is same with %s {%s}\n");
        SetFormat(debug, testValueCategory, "Test Value %s::"
            "Category() is same with %s {%s}\n");
        SetFormat(err, testValueCategory, "Error Value %s::"
            "Category() is not same with %s {%s}\n");

        TestValueCode testValueCode;
        SetFormat(info, testValueCode, "Test Value %s::"
            "Code() is same with %s {%s}\n");
        SetFormat(debug, testValueCode, "Test Value %s::"
            "Code() is same with %s {%s}\n");
        SetFormat(err, testValueCode, "Error Value %s::"
            "Code() is not same with %s {%s}\n");

        TestValueTrigger testValueTrigger;
        SetFormat(info, testValueTrigger, "Test Value %s::"
            "Trigger() is same with %s {%s}\n");
        SetFormat(debug, testValueTrigger, "Test Value %s::"
            "Trigger() is same with %s {%s}\n");
        SetFormat(err, testValueTrigger, "Error Value %s::"
            "Trigger() is not same with %s {%s}\n");

        TestValueOutput testValueOutput;
        SetFormat(info, testValueOutput, "Test Value Output of %s "
            "is same with \"%s\" {%s}\n");
        SetFormat(debug, testValueOutput, "Test Value Output of %s "
            "is same with \"%s\" {%s}\n");
        SetFormat(err, testValueOutput, "Error Value Output of %s "
            "is not same with \"%s\" {%s}\n");
    }
    template<typename... TArgs>
    bool Result(const TestBaseOfInformation &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IInformationType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        return std::is_base_of<BaseType, ErrorType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestBaseOfTrigger &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ITriggerValueType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        return std::is_base_of<BaseType, ErrorType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasCharType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<ICharType,
            basic::test::Variable<TArgs...>>::Type CharType;
        return typeid(typename ErrorType::CharType).hash_code() == 
            typeid(CharType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasOutputType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<IOutputType,
            basic::test::Variable<TArgs...>>::Type OutputType;
        return typeid(typename ErrorType::OutputType).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasCategoryValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<ICategoryValueType,
            basic::test::Variable<TArgs...>>::Type CategoryValueType;
        return typeid(typename ErrorType::CategoryValueType).hash_code() == 
            typeid(CategoryValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasCodeValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<ICodeValueType,
            basic::test::Variable<TArgs...>>::Type CodeValueType;
        return typeid(typename ErrorType::CodeValueType).hash_code() == 
            typeid(CodeValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasIdType &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<IIdentificationType,
            basic::test::Variable<TArgs...>>::Type IdType;
        return typeid(typename ErrorType::IdType).hash_code() == 
            typeid(IdType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasInfoType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<IInformationType,
            basic::test::Variable<TArgs...>>::Type InfoType;
        return typeid(typename ErrorType::InfoType).hash_code() == 
            typeid(InfoType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasTriggerType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IErrorType,
            basic::test::Variable<TArgs...>>::Type ErrorType;
        typedef typename basic::test::var::Element<ITriggerValueType,
            basic::test::Variable<TArgs...>>::Type TriggerType;
        return typeid(typename ErrorType::TriggerType).hash_code() == 
            typeid(TriggerType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestValueMessage &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * err = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * msg = basic::test::var::At<IMessageValue>(var).Get().Get();
        if (!err || !msg) return false;
        return strcmp(err->Message(), msg) == 0;
    }
    template<typename... TArgs>
    bool Result(const TestValueCategory &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * err = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * categval = basic::test::var::At<ICategoryValueValue>(var).Get().
            Get();
        if (!err || !categval) return false;
        return err->Category() == *categval;
    }
    template<typename... TArgs>
    bool Result(const TestValueCode &, basic::test::Variable<TArgs...> & var)
    {
        auto * err = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * codeval = basic::test::var::At<ICodeValueValue>(var).Get().
            Get();
        if (!err || !codeval) return false;
        return err->Code() == *codeval;
    }
    template<typename... TArgs>
    bool Result(const TestValueTrigger &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IInformationType,
            basic::test::Variable<TArgs...>>::Type InformationType;
        auto * err = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * triggerval = basic::test::var::At<ITriggerValueValue>(var).
            Get().Get();
        if (!err || !triggerval) return false;
        auto * err_info = dynamic_cast<
            const InformationType *>(&(err->Trigger()));
        auto * info = dynamic_cast<const InformationType *>(triggerval);
        if (!err_info || !info) return false;
        auto & err_id = err_info->Identification();
        auto & id = info->Identification();
        if (reinterpret_cast<const unsigned char&>(err_id.Flag()) != 
            reinterpret_cast<const unsigned char&>(id.Flag())) return false;
        if (id.IsSystem()) return err_id.ErrorSystem().Category() == 
            id.ErrorSystem().Category() && err_id.ErrorSystem().Code() == 
            id.ErrorSystem().Code(); 
        return err_id.Error().Code() == id.Error().Code();
    }
    template<typename... TArgs>
    bool Result(const TestValueOutput &, basic::test::Variable<TArgs...> & var)
    {
        auto * err = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * out = basic::test::var::At<IOutputValue>(var).Get().
            Get();
        if (!err || !out) return false;
        auto * errout = dynamic_cast<const basic::err::intf::Output *>(err);
        if (!errout) return false;
        std::stringstream ss;
        *errout >> ss;
        return ss.str().compare(out) == 0;
    }
};

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
BASIC_TEST_TYPE_NAME("basic::err::Information", basic::err::Information);
BASIC_TEST_TYPE_NAME("basic::err::Identification", 
    basic::err::Identification);

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<std::basic_ostream<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::basic_ostream<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, *tArg1CStr,
            *tArg2CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<std::char_traits<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::char_traits<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::Error<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::Error<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<const TArg>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "const %s";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<TArg *>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "%s *";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

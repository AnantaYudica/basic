#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/Information.h"

#include <cstdio>
#include <cstring>
#include <cstddef>
#include <type_traits>
#include <sstream>

#define BUFFER_FORMAT_CSTRING 256

const char * ToString(const basic::err::Identification * && id)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    if (id->IsSystem())
    {
        const auto & errsys = id->ErrorSystem();
        snprintf(tmp, BUFFER_FORMAT_CSTRING, "{flag:%x, category:%d, "
            "code:%d}", reinterpret_cast<const unsigned char&>(id->Flag()), 
            errsys.Category(), errsys.Code());
        return tmp;
    }
    const auto & err = id->Error();
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "{flag:%x, code:%d}", 
        reinterpret_cast<const unsigned char&>(id->Flag()), err.Code());
    return tmp;
}

struct TestBaseOfIntfOutput {};
struct TestAliasOutputType {};
struct TestValueIdentification {};
struct TestValueFile {};
struct TestValueLine {};
struct TestValueOutput {};

using VariableTestInformation = basic::test::Variable<
    basic::err::Information,
    basic::err::intf::Output,
    basic::err::defn::type::Output,
    basic::err::Identification,
    const char *,
    const std::size_t,
    const char *,
    basic::test::Value<
        basic::err::Information *>,
    basic::test::Value<
        const basic::err::Identification *>,
    basic::test::Value<const char *>,
    basic::test::Value<std::size_t>,
    basic::test::Value<const char *>,
    basic::test::type::Function<
        const char *(const basic::err::Identification * &&), &ToString>>;

enum : std::size_t
{
    IInformationType,
    IIntfOutputType,
    IOutputType,
    IIndentificationType,
    IFileType,
    ILineType,
    IOutputCharType,
    IInformationValue,
    IIndentificationValue,
    IFileValue,
    ILineValue,
    IOutputValue,
    IIndentificationToStringTypeFunc
};

typedef basic::test::msg::Argument<TestBaseOfIntfOutput,
    basic::test::msg::arg::type::Name<IInformationType>,
    basic::test::msg::arg::type::Name<IIntfOutputType>>
        ArgTestBaseOfIntfOutput;

typedef basic::test::msg::Base<TestBaseOfIntfOutput, char, 
    ArgTestBaseOfIntfOutput, ArgTestBaseOfIntfOutput, 
    ArgTestBaseOfIntfOutput> MessageBaseTestBaseOfIntfOutput;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<IInformationType>,
    basic::test::msg::arg::type::Name<IOutputType>>
        ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestValueIdentification,
    basic::test::msg::arg::type::Name<IInformationType>,
    basic::test::msg::arg::type::Function<IIndentificationToStringTypeFunc,
        basic::test::msg::arg::Value<IIndentificationValue>>, 
    basic::test::msg::arg::type::Name<IIndentificationType>>
        ArgTestValueIdentification;

typedef basic::test::msg::Base<TestValueIdentification, char, 
    ArgTestValueIdentification, ArgTestValueIdentification, 
    ArgTestValueIdentification> MessageBaseTestValueIdentification;

typedef basic::test::msg::Argument<TestValueFile,
    basic::test::msg::arg::type::Name<IInformationType>,
    basic::test::msg::arg::Value<IFileValue>, 
    basic::test::msg::arg::type::Name<IFileType>>
        ArgTestValueFile;

typedef basic::test::msg::Base<TestValueFile, char, 
    ArgTestValueFile, ArgTestValueFile, ArgTestValueFile> 
        MessageBaseTestValueFile;

typedef basic::test::msg::Argument<TestValueLine,
    basic::test::msg::arg::type::Name<IInformationType>,
    basic::test::msg::arg::Value<ILineValue>, 
    basic::test::msg::arg::type::Name<ILineType>>
        ArgTestValueLine;

typedef basic::test::msg::Base<TestValueLine, char, 
    ArgTestValueLine, ArgTestValueLine, ArgTestValueLine> 
        MessageBaseTestValueLine;

typedef basic::test::msg::Argument<TestValueOutput,
    basic::test::msg::arg::type::Name<IInformationType>,
    basic::test::msg::arg::Value<IOutputValue>, 
    basic::test::msg::arg::type::Name<IOutputCharType>>
        ArgTestValueOutput;

typedef basic::test::msg::Base<TestValueOutput, char, 
    ArgTestValueOutput, ArgTestValueOutput, ArgTestValueOutput> 
        MessageBaseTestValueOutput;

template<typename TCases, typename... TVariables>
struct TestInformation :
    public basic::test::Message<BASIC_TEST, TestInformation<TCases, 
        TVariables...>>,
    public basic::test::Case<TestInformation<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestInformation<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfIntfOutput,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestValueIdentification,
    public MessageBaseTestValueFile,
    public MessageBaseTestValueLine,
    public MessageBaseTestValueOutput
{
public:
    using basic::test::Case<TestInformation<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestInformation<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfIntfOutput::Format;
    using MessageBaseTestBaseOfIntfOutput::SetFormat;
    using MessageBaseTestBaseOfIntfOutput::Argument;
    using MessageBaseTestAliasOutputType::Format;
    using MessageBaseTestAliasOutputType::SetFormat;
    using MessageBaseTestAliasOutputType::Argument;
    using MessageBaseTestValueIdentification::Format;
    using MessageBaseTestValueIdentification::SetFormat;
    using MessageBaseTestValueIdentification::Argument;
    using MessageBaseTestValueFile::Format;
    using MessageBaseTestValueFile::SetFormat;
    using MessageBaseTestValueFile::Argument;
    using MessageBaseTestValueLine::Format;
    using MessageBaseTestValueLine::SetFormat;
    using MessageBaseTestValueLine::Argument;
    using MessageBaseTestValueOutput::Format;
    using MessageBaseTestValueOutput::SetFormat;
    using MessageBaseTestValueOutput::Argument;
public:
    TestInformation(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestInformation<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestInformation<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestInformation<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestBaseOfIntfOutput testBaseOfIntfOutput;
        SetFormat(info, testBaseOfIntfOutput, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfIntfOutput, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfIntfOutput, 
            "Error Test %s is not base of %s\n");

        TestAliasOutputType testAliasOutputType;
        SetFormat(info, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(debug, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(err, testAliasOutputType, "Error alias type "
            "%s::OutputType is not same with %s\n");

        TestValueIdentification testValueIdentification;
        SetFormat(info, testValueIdentification, "Test Value %s::"
            "Identification() is same with %s {%s}\n");
        SetFormat(debug, testValueIdentification, "Test Value %s::"
            "Identification() is same with %s {%s}\n");
        SetFormat(err, testValueIdentification, "Error Value %s::"
            "Identification() is not same with %s {%s}\n");

        TestValueFile testValueFile;
        SetFormat(info, testValueFile, "Test Value %s::"
            "File() is same with \"%s\" {%s}\n");
        SetFormat(debug, testValueFile, "Test Value %s::"
            "File() is same with \"%s\" {%s}\n");
        SetFormat(err, testValueFile, "Error Value %s::"
            "File() is not same with \"%s\" {%s}\n");

        TestValueLine testValueLine;
        SetFormat(info, testValueLine, "Test Value %s::"
            "Line() is same with %d {%s}\n");
        SetFormat(debug, testValueLine, "Test Value %s::"
            "Line() is same with %d {%s}\n");
        SetFormat(err, testValueLine, "Error Value %s::"
            "Line() is not same with %d {%s}\n");

        TestValueOutput testValueOutput;
        SetFormat(info, testValueOutput, "Test Value output of %s "
            "is same with \"%s\" {%s}\n");
        SetFormat(debug, testValueOutput, "Test Value output of %s "
            "is same with \"%s\" {%s}\n");
        SetFormat(err, testValueOutput, "Test Value output of %s "
            "is not same with \"%s\" {%s}\n");

    }
    template<typename... TArgs>
    bool Result(const TestBaseOfIntfOutput &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IIntfOutputType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<IInformationType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        return std::is_base_of<BaseType, CategoryType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasOutputType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IInformationType,
            basic::test::Variable<TArgs...>>::Type InformationType;
        typedef typename basic::test::var::Element<IOutputType,
            basic::test::Variable<TArgs...>>::Type OutputType;
        return typeid(typename InformationType::OutputType).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestValueIdentification &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * info = basic::test::var::At<IInformationValue>(var).Get().Get();
        auto * id = basic::test::var::At<IIndentificationValue>(var).Get().
            Get();
        if (!info || !id || reinterpret_cast<const unsigned char&>(
            info->Identification().Flag()) != reinterpret_cast<
            const unsigned char&>(id->Flag())) return false;
        if (id->IsSystem())
            return info->Identification().ErrorSystem().Category() == 
                id->ErrorSystem().Category() && info->Identification().
                ErrorSystem().Code() == id->ErrorSystem().Code(); 
        return info->Identification().Error().Code() == id->Error().Code();
    }
    template<typename... TArgs>
    bool Result(const TestValueFile &, basic::test::Variable<TArgs...> & var)
    {
        auto * info = basic::test::var::At<IInformationValue>(var).Get().Get();
        auto * file = basic::test::var::At<IFileValue>(var).Get().Get();
        if (info->File() == nullptr && file == nullptr) return true;
        return strcmp(info->File(), file) == 0;
    }
    template<typename... TArgs>
    bool Result(const TestValueLine &, basic::test::Variable<TArgs...> & var)
    {
        auto * info = basic::test::var::At<IInformationValue>(var).Get().Get();
        auto & line = basic::test::var::At<ILineValue>(var).Get().Get();
        return info->Line() == line;
    }
    template<typename... TArgs>
    bool Result(const TestValueOutput &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IIntfOutputType,
            basic::test::Variable<TArgs...>>::Type IntfOutputType;
        auto * info = basic::test::var::At<IInformationValue>(var).Get().Get();
        auto * out = basic::test::var::At<IOutputValue>(var).Get().Get();
        auto * info_out = dynamic_cast<IntfOutputType *>(info);
        std::stringstream ss;
        *info_out >> ss;
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
BASIC_TEST_TYPE_NAME("basic::err::Identification", basic::err::Identification);
BASIC_TEST_TYPE_NAME("basic::err::intf::Output", basic::err::intf::Output);

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


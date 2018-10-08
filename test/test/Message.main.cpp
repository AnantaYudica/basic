#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Register.h"
#include "test/Message.h"

#include <cstdio>
#include <cstring>
#include <utility>

#define OUTPUT_BUFFER_SIZE 1024

struct Output
{
    char* m_bufferStr;
    std::size_t m_offset;
    static Output ms_output;
    Output() : 
        m_bufferStr(new char[OUTPUT_BUFFER_SIZE]),
        m_offset(0)
    {}
    ~Output()
    {
        delete[] m_bufferStr;
    }
    template<typename... Targs>
    static void Info(const char* info_msg_cstr, Targs&&... args)
    {
        assert(ms_output.m_bufferStr != NULL);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
        sprintf_s(ms_output.m_bufferStr + ms_output.m_offset, 
            OUTPUT_BUFFER_SIZE, info_msg_cstr, std::forward<Targs>(args)...);
#else
        sprintf(ms_output.m_bufferStr + ms_output.m_offset, 
            info_msg_cstr, std::forward<Targs>(args)...);
#endif
    }
    template<typename... Targs>
    static void Debug(const char* debug_msg_cstr, Targs&&... args)
    {
        assert(ms_output.m_bufferStr != NULL);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
        sprintf_s(ms_output.m_bufferStr + ms_output.m_offset,
            OUTPUT_BUFFER_SIZE, debug_msg_cstr, std::forward<Targs>(args)...);
#else
        sprintf(ms_output.m_bufferStr + ms_output.m_offset, 
            debug_msg_cstr, std::forward<Targs>(args)...);
#endif
    }
    template<typename... Targs>
    static void Error(const char* error_msg_cstr, Targs&&... args)
    {
        assert(ms_output.m_bufferStr != NULL);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
        sprintf_s(ms_output.m_bufferStr + ms_output.m_offset,
            OUTPUT_BUFFER_SIZE, error_msg_cstr, std::forward<Targs>(args)...);
#else
        sprintf(ms_output.m_bufferStr + ms_output.m_offset, 
            error_msg_cstr, std::forward<Targs>(args)...);
#endif
    }
};

Output Output::ms_output;

struct Case1 {};
struct Case2 {};
struct Case3 {};
struct Case4 {};

#define CASE1_CSTR "case1"
#define CASE2_CSTR "case2"
#define CASE3_CSTR "case3"
#define CASE4_CSTR "case4"

#define MAX_CASE_CSTR 10
        
char case1_cstr[] = CASE1_CSTR;
char case2_cstr[] = CASE2_CSTR;
char case3_cstr[] = CASE3_CSTR;
char case4_cstr[] = CASE4_CSTR;

constexpr int info_int = 4;
constexpr int debug_int = 14;
constexpr int error_int = 44;

typedef basic::test::msg::Argument<Case1,
    basic::test::msg::arg::Value<0>> InfoArgCase1;
typedef basic::test::msg::Argument<Case1,
    basic::test::msg::arg::Value<1>> DebugArgCase1;
typedef basic::test::msg::Argument<Case1,
    basic::test::msg::arg::Value<2>> ErrorArgCase1;
typedef basic::test::msg::Base<Case1, char, InfoArgCase1,
    DebugArgCase1, ErrorArgCase1> MessageBaseCase1;

typedef basic::test::msg::Argument<Case2,
    basic::test::msg::arg::Value<0>> InfoArgCase2;
typedef basic::test::msg::Argument<Case2,
    basic::test::msg::arg::Value<1>> DebugArgCase2;
typedef basic::test::msg::Argument<Case2,
    basic::test::msg::arg::Value<2>> ErrorArgCase2;
typedef basic::test::msg::Base<Case2, char, InfoArgCase2,
    DebugArgCase2, ErrorArgCase2> MessageBaseCase2;

typedef basic::test::msg::Argument<Case3,
    basic::test::msg::arg::Value<0>> InfoArgCase3;
typedef basic::test::msg::Argument<Case3,
    basic::test::msg::arg::Value<1>> DebugArgCase3;
typedef basic::test::msg::Argument<Case3,
    basic::test::msg::arg::Value<2>> ErrorArgCase3;
typedef basic::test::msg::Base<Case3, char, InfoArgCase3,
    DebugArgCase3, ErrorArgCase3> MessageBaseCase3;

typedef basic::test::msg::Argument<Case4,
    basic::test::msg::arg::type::Index<0,
        basic::test::msg::arg::type::val::seq::At>> ArgCase4Index;

typedef basic::test::msg::Base<Case4, char, ArgCase4Index,
    ArgCase4Index, ArgCase4Index> MessageBaseCase4;

class TestA :
    public MessageBaseCase1,
    public MessageBaseCase2,
    public MessageBaseCase3,
    public MessageBaseCase4,
    public basic::test::Message<Output, TestA>
{
public:
    using MessageBaseCase1::Format;
    using MessageBaseCase2::Format;
    using MessageBaseCase3::Format;
    using MessageBaseCase4::Format;
    using MessageBaseCase1::SetFormat;
    using MessageBaseCase2::SetFormat;
    using MessageBaseCase3::SetFormat;
    using MessageBaseCase4::SetFormat;
    using MessageBaseCase1::Argument;
    using MessageBaseCase2::Argument;
    using MessageBaseCase3::Argument;
    using MessageBaseCase4::Argument;
public:
    TestA() :
        basic::test::Message<Output, TestA>(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        Case1 case1;
        Case2 case2;
        Case3 case3;
        Case4 case4;

        SetFormat(debug, case1, CASE1_CSTR " : %d\n");
        SetFormat(info, case1, CASE1_CSTR " : %d\n");
        SetFormat(error, case1, CASE1_CSTR " : %d\n");

        basic::test::msg::Format<char> formatCase2(CASE2_CSTR " : %s\n");
        char argFormatCase2[] = "%d";
        SetFormat(debug, case2, { formatCase2,
            formatCase2.Size() + sizeof(argFormatCase2), argFormatCase2});
        SetFormat(info, case2, { formatCase2,
            formatCase2.Size() + sizeof(argFormatCase2), argFormatCase2 });
        SetFormat(error, case2, { formatCase2,
            formatCase2.Size() + sizeof(argFormatCase2), argFormatCase2 });

        basic::test::msg::Format<char> InfoFormatCase3(CASE3_CSTR " : %d\n");
        basic::test::msg::Format<char> DebugFormatCase3(CASE3_CSTR " : %d\n");
        basic::test::msg::Format<char> ErrorFormatCase3(CASE3_CSTR " : %d\n");
        SetFormat(debug, case3, std::move(InfoFormatCase3));
        SetFormat(info, case3, std::move(DebugFormatCase3));
        SetFormat(error, case3, std::move(ErrorFormatCase3));
        
        basic::test::msg::Format<char> formatCase4(CASE4_CSTR " : %d\n");
        SetFormat(debug, case4, formatCase4);
        SetFormat(info, case4, formatCase4);
        SetFormat(error, case4, formatCase4);
    }
};

int main()
{
    TestA a;
    
    basic::test::Variable<
        basic::test::Value<int>, 
        basic::test::Value<int>,
        basic::test::Value<int>> var1(info_int, debug_int, error_int);
    char * cstr = new char[MAX_CASE_CSTR];
    int value = 0;

    a.Info(Case1{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr, 
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case1_cstr) == 0);
    assert(value == info_int);

    a.Debug(Case1{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr, 
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case1_cstr) == 0);
    assert(value == debug_int);

    a.Error(Case1{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr, 
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case1_cstr) == 0);
    assert(value == error_int);
    
    a.Info(Case2{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case2_cstr) == 0);
    assert(value == info_int);

    a.Debug(Case2{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case2_cstr) == 0);
    assert(value == debug_int);

    a.Error(Case2{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case2_cstr) == 0);
    assert(value == error_int);

    
    a.Info(Case3{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case3_cstr) == 0);
    assert(value == info_int);

    a.Debug(Case3{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case3_cstr) == 0);
    assert(value == debug_int);

    a.Error(Case3{}, var1);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case3_cstr) == 0);
    assert(value == error_int);
    
    basic::test::Variable<
        basic::test::type::val::Sequence<int, info_int,
        debug_int, error_int>> var2;

    a.Info(basic::test::type::Index<Case4, 0>{}, var2);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case4_cstr) == 0);
    assert(value == info_int);

    a.Debug(basic::test::type::Index<Case4, 1>{}, var2);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case4_cstr) == 0);
    assert(value == debug_int);

    a.Error(basic::test::type::Index<Case4, 2>{}, var2);
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    sscanf_s(Output::ms_output.m_bufferStr, "%s : %d", cstr,
        MAX_CASE_CSTR, &value);
#else
    sscanf(Output::ms_output.m_bufferStr, "%s : %d", cstr, &value);
#endif
    printf("%s : %d\n", cstr, value);
    assert(strcmp(cstr, case4_cstr) == 0);
    assert(value == error_int);

    delete[] cstr;
}

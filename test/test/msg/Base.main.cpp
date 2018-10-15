#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Variable.h"
#include "test/msg/arg/type/Name.h"
#include "test/msg/arg/type/Value.h"
#include "test/msg/arg/type/param/Name.h"
#include "test/msg/Base.h"

#include "test/cstr/out/Argument.h"

#include <cstdio>
#include <cstring>
#include <utility>

struct Case1 {};
struct Case2 {};
struct Case3 {};
struct Case4 {};

#define BUFFER_SIZE 1024

#define CASE1_CSTR "case1"
#define CASE2_CSTR "case2"
#define CASE3_CSTR "case3"
#define CASE4_CSTR "case4"

#define FORMAT_INT_CSTR "%d"
#define FORMAT_CSTR_CSTR "%s"
#define COLOM_CSTR ":"
#define SPACE_CSTR " "

#define MAX_CASE_CSTR 10

char case1_cstr[] = CASE1_CSTR;
char case2_cstr[] = CASE2_CSTR;
char case3_cstr[] = CASE3_CSTR;
char case4_cstr[] = CASE4_CSTR;

#define INFO_INT 4
#define INFO_CSTR "4"
#define DEBUG_INT 14
#define DEBUG_CSTR "14"
#define ERROR_INT 44
#define ERROR_CSTR "44"

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
    public MessageBaseCase4
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
    TestA() {}
public:
    template<typename TCaseId, typename TTag, typename... TArgs>
    void Print(char* buffer, const std::size_t& size, 
        const TTag& tag, const TCaseId& case_id, TArgs&&... args)
    {
        snprintf(buffer, size, *Format(tag, case_id),
            basic::test::out::Argument<TArgs>::Value(args)...);
    }
};

int main()
{
    char * buffer = new char[BUFFER_SIZE];
    std::size_t buff_size = BUFFER_SIZE;
    TestA testa1;

    basic::test::msg::base::Info info;
    basic::test::msg::base::Debug debug;
    basic::test::msg::base::Error error;

    Case1 case1;
    Case2 case2;
    Case3 case3;
    Case4 case4;

    testa1.SetFormat(info, case1, CASE1_CSTR SPACE_CSTR COLOM_CSTR
        SPACE_CSTR FORMAT_INT_CSTR);
    printf("format : \"%s\"\n", *testa1.Format(info, case1));
    assert(strcmp(*testa1.Format(info, case1), CASE1_CSTR SPACE_CSTR COLOM_CSTR
        SPACE_CSTR FORMAT_INT_CSTR) == 0);

    testa1.SetFormat(debug, case1, CASE1_CSTR SPACE_CSTR COLOM_CSTR
        SPACE_CSTR FORMAT_INT_CSTR);
    printf("format : \"%s\"\n", *testa1.Format(debug, case1));
    assert(strcmp(*testa1.Format(debug, case1), CASE1_CSTR SPACE_CSTR 
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    testa1.SetFormat(error, case1, CASE1_CSTR SPACE_CSTR COLOM_CSTR
        SPACE_CSTR FORMAT_INT_CSTR);
    printf("format : \"%s\"\n", *testa1.Format(error, case1));
    assert(strcmp(*testa1.Format(error, case1), CASE1_CSTR SPACE_CSTR 
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    basic::test::msg::Format<char> case2_format(CASE2_CSTR SPACE_CSTR 
        COLOM_CSTR SPACE_CSTR FORMAT_CSTR_CSTR);
    char case2_arg_format[] = FORMAT_INT_CSTR;
    testa1.SetFormat(debug, case2, { case2_format,
        case2_format.Size() + sizeof(case2_arg_format), case2_arg_format });
    printf("format : \"%s\"\n", *testa1.Format(debug, case2));
    assert(strcmp(*testa1.Format(debug, case2), CASE2_CSTR SPACE_CSTR 
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    testa1.SetFormat(info, case2, { case2_format,
        case2_format.Size() + sizeof(case2_arg_format), case2_arg_format });
    printf("format : \"%s\"\n", *testa1.Format(info, case2));
    assert(strcmp(*testa1.Format(info, case2), CASE2_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    testa1.SetFormat(error, case2, { case2_format,
        case2_format.Size() + sizeof(case2_arg_format), case2_arg_format });
    printf("format : \"%s\"\n", *testa1.Format(error, case2));
    assert(strcmp(*testa1.Format(error, case2), CASE2_CSTR SPACE_CSTR 
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    basic::test::msg::Format<char> case3_info_format(CASE3_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR);
    testa1.SetFormat(debug, case3, std::move(case3_info_format));
    printf("format : \"%s\"\n", *testa1.Format(debug, case3));
    assert(strcmp(*testa1.Format(debug, case3), CASE3_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    basic::test::msg::Format<char> case3_debug_format(CASE3_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR);
    testa1.SetFormat(info, case3, std::move(case3_debug_format));
    printf("format : \"%s\"\n", *testa1.Format(info, case3));
    assert(strcmp(*testa1.Format(info, case3), CASE3_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    basic::test::msg::Format<char> case3_error_format(CASE3_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR);
    testa1.SetFormat(error, case3, std::move(case3_error_format));
    printf("format : \"%s\"\n", *testa1.Format(error, case3));
    assert(strcmp(*testa1.Format(error, case3), CASE3_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    basic::test::msg::Format<char> case4_format(CASE4_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR);
    testa1.SetFormat(debug, case4, case4_format);
    printf("format : \"%s\"\n", *testa1.Format(debug, case4));
    assert(strcmp(*testa1.Format(debug, case4), CASE4_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    testa1.SetFormat(info, case4, case4_format);
    printf("format : \"%s\"\n", *testa1.Format(info, case4));
    assert(strcmp(*testa1.Format(info, case4), CASE4_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    testa1.SetFormat(error, case4, case4_format);
    printf("format : \"%s\"\n", *testa1.Format(error, case4));
    assert(strcmp(*testa1.Format(error, case4), CASE4_CSTR SPACE_CSTR
        COLOM_CSTR SPACE_CSTR FORMAT_INT_CSTR) == 0);

    basic::test::Variable<
        basic::test::Value<int>,
        basic::test::Value<int>,
        basic::test::Value<int>> var1(INFO_INT, DEBUG_INT, ERROR_INT);

    testa1.Argument(info, case1).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer), 
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const Case1&>(case1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE1_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR 
        INFO_CSTR) == 0);

    testa1.Argument(debug, case1).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const Case1&>(case1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE1_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        DEBUG_CSTR) == 0);

    testa1.Argument(error, case1).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const Case1&>(case1));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE1_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        ERROR_CSTR) == 0);

    testa1.Argument(info, case2).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const Case2&>(case2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE2_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        INFO_CSTR) == 0);

    testa1.Argument(debug, case2).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const Case2&>(case2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE2_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        DEBUG_CSTR) == 0);

    testa1.Argument(error, case2).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const Case2&>(case2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE2_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        ERROR_CSTR) == 0);

    testa1.Argument(info, case2).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const Case2&>(case2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE2_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        INFO_CSTR) == 0);

    testa1.Argument(debug, case2).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const Case2&>(case2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE2_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        DEBUG_CSTR) == 0);

    testa1.Argument(error, case2).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const Case2&>(case2));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE2_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        ERROR_CSTR) == 0);

    testa1.Argument(info, case3).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const Case3&>(case3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE3_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        INFO_CSTR) == 0);

    testa1.Argument(debug, case3).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const Case3&>(case3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE3_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        DEBUG_CSTR) == 0);

    testa1.Argument(error, case3).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const Case3&>(case3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE3_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        ERROR_CSTR) == 0);

    testa1.Argument(info, case3).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const Case3&>(case3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE3_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        INFO_CSTR) == 0);

    testa1.Argument(debug, case3).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const Case3&>(case3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE3_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        DEBUG_CSTR) == 0);

    testa1.Argument(error, case3).Call<void>(&TestA::Print, testa1, var1,
        std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const Case3&>(case3));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE3_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        ERROR_CSTR) == 0);


    basic::test::Variable<
        basic::test::type::val::Sequence<int, INFO_INT, DEBUG_INT, 
            ERROR_INT>> var2;

    basic::test::type::Index<Case4, 0> case4_at0;
    testa1.Argument(info, case4).Call<void>(case4_at0, &TestA::Print, testa1,
        var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const Case4&>(case4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE4_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        INFO_CSTR) == 0);

    basic::test::type::Index<Case4, 1> case4_at1;
    testa1.Argument(debug, case4).Call<void>(case4_at1, &TestA::Print, testa1,
        var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const Case4&>(case4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE4_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        DEBUG_CSTR) == 0);

    basic::test::type::Index<Case4, 2> case4_at2;
    testa1.Argument(error, case4).Call<void>(case4_at2, &TestA::Print, testa1,
        var2, std::forward<char*>(buffer),
        std::forward<const std::size_t&>(buff_size),
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const Case4&>(case4));
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, CASE4_CSTR SPACE_CSTR COLOM_CSTR SPACE_CSTR
        ERROR_CSTR) == 0);

    delete[] buffer;
}

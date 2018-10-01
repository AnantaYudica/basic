#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Variable.h"
#include "test/msg/arg/type/Name.h"
#include "test/msg/arg/type/Value.h"
#include "test/msg/arg/type/param/Name.h"
#include "test/msg/Base.h"

#include "test/cstr/out/Argument.h"

#include <cstdio>
#include <utility>

struct TestA1 {};
struct TestA2 {};
struct TestA3 {};
struct TestA4 {};

typedef basic::test::msg::Argument<TestA1, 
    basic::test::msg::arg::type::Name<0>> InfoArgTestA1;
typedef basic::test::msg::Argument<TestA2, 
    basic::test::msg::arg::type::Name<0>> InfoArgTestA2;
typedef basic::test::msg::Argument<TestA3, 
    basic::test::msg::arg::type::Name<0>> InfoArgTestA3;

typedef basic::test::msg::Argument<TestA1, 
    basic::test::msg::arg::type::Value<1>> DebugArgTestA1;
typedef basic::test::msg::Argument<TestA2, 
    basic::test::msg::arg::type::Value<1>> DebugArgTestA2;
typedef basic::test::msg::Argument<TestA3, 
    basic::test::msg::arg::type::Value<1>> DebugArgTestA3;
    
typedef basic::test::msg::Argument<TestA1, 
    basic::test::msg::arg::Value<2>> ErrorArgTestA1;
typedef basic::test::msg::Argument<TestA2, 
    basic::test::msg::arg::Value<2>> ErrorArgTestA2;
typedef basic::test::msg::Argument<TestA3, 
    basic::test::msg::arg::Value<2>> ErrorArgTestA3;
    
typedef basic::test::msg::Argument<TestA4, 
    basic::test::msg::arg::type::Index<1,
        basic::test::msg::arg::type::val::seq::At>> ArgTestA4Index;

typedef basic::test::msg::Base<TestA1, char, InfoArgTestA1,
    DebugArgTestA1, ErrorArgTestA1> MessageBaseTestA1;
typedef basic::test::msg::Base<TestA2, char, InfoArgTestA2,
    DebugArgTestA2, ErrorArgTestA2> MessageBaseTestA2;
typedef basic::test::msg::Base<TestA3, char, InfoArgTestA3,
    DebugArgTestA3, ErrorArgTestA3> MessageBaseTestA3;
typedef basic::test::msg::Base<TestA4, char, ArgTestA4Index,
    ArgTestA4Index, ArgTestA4Index> MessageBaseTestA4;

class TestA :
    public MessageBaseTestA1,
    public MessageBaseTestA2,
    public MessageBaseTestA3,
    public MessageBaseTestA4
{
public:
    using MessageBaseTestA1::Format;
    using MessageBaseTestA2::Format;
    using MessageBaseTestA3::Format;
    using MessageBaseTestA4::Format;
    using MessageBaseTestA1::SetFormat;
    using MessageBaseTestA2::SetFormat;
    using MessageBaseTestA3::SetFormat;
    using MessageBaseTestA4::SetFormat;
    using MessageBaseTestA1::Argument;
    using MessageBaseTestA2::Argument;
    using MessageBaseTestA3::Argument;
    using MessageBaseTestA4::Argument;
public:
    TestA()
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        TestA1 testa1;
        TestA2 testa2;
        TestA3 testa3;
        TestA4 testa4;

        basic::test::msg::Format<char> formatTestA1("Test TestA1 : %s");
        SetFormat(debug, testa1, {formatTestA1, 
            formatTestA1.Size() + 10, "type %d"});
        SetFormat(info, testa1, std::move(formatTestA1));
        SetFormat(error, testa1, "Error TestA1 msg %s");

        basic::test::msg::Format<char> formatTestA2("Test TestA1 : %s");
        SetFormat(debug, testa2, {formatTestA2, 
            formatTestA2.Size() + 10, "type %d"});
        SetFormat(info, testa2, std::move(formatTestA2));
        SetFormat(error, testa2, "Error TestA2 msg %s");

        basic::test::msg::Format<char> formatTestA3("Test TestA3 : %s");
        SetFormat(debug, testa3, {formatTestA3, 
            formatTestA3.Size() + 10, "type %d"});
        SetFormat(info, testa3, std::move(formatTestA3));
        SetFormat(error, testa3, "Error TestA3 msg %s");
        
        basic::test::msg::Format<char> formatTestA4("Test TestA4 : %d\n");
        SetFormat(debug, testa4, "debug type TestA4 %d\n");
        SetFormat(info, testa4, std::move(formatTestA4));
        SetFormat(error, testa4, "Error TestA4 msg %d\n");
    }
public:
    template<typename TCaseId, typename TTag, typename... TArgs>
    void Print(const TTag& tag, const TCaseId& case_id, TArgs&&... args)
    {
        printf(*Format(tag, case_id), basic::test::out::Argument<TArgs>::Value(args)...);
        printf("\n");
    }
};

BASIC_TEST_TYPE_NAME("int", int);

int main()
{
    basic::test::msg::base::Info info;
    basic::test::msg::base::Debug debug;
    basic::test::msg::base::Error error;
    TestA1 testa1;
    TestA2 testa2;
    TestA3 testa3;
    basic::test::CString<char> cstr1("test");
    basic::test::Variable<int, basic::test::type::Value<int, 4>,
        basic::test::Value<const char*>> var1(*cstr1);

    TestA a;
    a.Argument(info, testa1).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const TestA1&>(testa1));
    
    a.Argument(debug, testa1).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const TestA1&>(testa1));

    a.Argument(error, testa1).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const TestA1&>(testa1));

    a.Argument(info, testa2).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const TestA2&>(testa2));
    
    a.Argument(debug, testa2).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const TestA2&>(testa2));

    a.Argument(error, testa2).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const TestA2&>(testa2));

    a.Argument(info, testa3).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const TestA3&>(testa3));
    
    a.Argument(debug, testa3).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const TestA3&>(testa3));

    a.Argument(error, testa3).Call<void>(&TestA::Print, a, var1,
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const TestA3&>(testa3));

    TestA4 testa4;
    basic::test::type::Index<TestA4, 0> testa4_at0;

    basic::test::Variable<int, 
        basic::test::type::val::Sequence<int, 14, 41, 44>,
        basic::test::Value<const char*>> var2(*cstr1);
    
    a.Argument(info, testa4).Call<void>(testa4_at0, &TestA::Print, a, var2,
        static_cast<const basic::test::msg::base::Info&>(info),
        static_cast<const TestA4&>(testa4));
    
    a.Argument(debug, testa4).Call<void>(testa4_at0, &TestA::Print, a, var2,
        static_cast<const basic::test::msg::base::Debug&>(debug),
        static_cast<const TestA4&>(testa4));

    a.Argument(error, testa4).Call<void>(testa4_at0, &TestA::Print, a, var2,
        static_cast<const basic::test::msg::base::Error&>(error),
        static_cast<const TestA4&>(testa4));

}

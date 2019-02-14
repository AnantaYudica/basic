#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/type/val/seq/Make.h"
#include "test/type/val/seq/formula/Arithmetic.h"

#include "error/msg/str/At.h"

#include <cstring>

BASIC_TEST_CONSTRUCT;

template<typename TStorage>
const char * PointerToString(TStorage *&& storage)
{
    return *storage;
}


struct TestValueAt {};

template<typename TStorage, std::size_t Size, typename TChar = char>
using VariableTestStringAt = basic::test::Variable<
    TStorage,
    basic::test::Value<TStorage *>,
    basic::test::val::Sequence<TChar, Size>,
    typename basic::test::type::val::seq::Make<std::size_t, 0,
        Size, basic::test::type::val::seq::formula::Arithmetic<std::size_t,
            std::size_t, 1>>::Type,
    basic::test::type::Function<const char *(TStorage *&&), 
        &PointerToString>>;

typedef basic::test::msg::Argument<TestValueAt,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::type::Function<4,
        basic::test::msg::arg::Value<1>>,
    basic::test::msg::arg::type::Index<3,
        basic::test::msg::arg::type::val::seq::At>,
    basic::test::msg::arg::type::Index<2,
        basic::test::msg::arg::val::seq::At>,
    basic::test::msg::arg::type::Index<2,
        basic::test::msg::arg::val::seq::At>> ArgTestValueAt;

typedef basic::test::msg::Base<TestValueAt, char, 
    ArgTestValueAt, ArgTestValueAt, ArgTestValueAt> MessageBaseTestValueAt;

template<typename TCases, typename... TVariables>
struct TestStringAt :
    public basic::test::Message<BASIC_TEST, 
        TestStringAt<TCases, TVariables...>>,
    public basic::test::Case<TestStringAt<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestStringAt<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueAt
{
public:
    using MessageBaseTestValueAt::Format;
    using MessageBaseTestValueAt::SetFormat;
    using MessageBaseTestValueAt::Argument;
    using basic::test::Case<TestStringAt<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestStringAt<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestStringAt(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringAt< 
            TCases, TVariables...>>(*this),
        basic::test::Case<TestStringAt<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestStringAt<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        TestValueAt testValueAt;
        SetFormat(info, testValueAt, "test %s {\"%s\"} At %d "
            "same with \'%c\' {%d}\n");
        SetFormat(debug, testValueAt, "test %s {\"%s\"} At %d "
            "same with \'%c\' {%d}\n");
        SetFormat(error, testValueAt, "Error test %s {\"%s\"} At %d "
            "not same with \'%c\' {%d}\n");
    }
    template<std::size_t ICaseId, typename TStorage, std::size_t Size,
        typename TChar>
    bool Result(const basic::test::type::Index<TestValueAt, ICaseId> &, 
        VariableTestStringAt<TStorage, Size, TChar> & var)
    {
        const TStorage & storage = *basic::test::var::At<1>(var).Get().Get();
        TChar at_value = basic::test::var::At<2>(var).Get().
            template At<ICaseId>();
        return storage[ICaseId] == at_value;
    }
};

BASIC_TEST_TYPE_NAME("const char *", const char *);
BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("char [6]", char [6]);
BASIC_TEST_TYPE_NAME("const char [4]", const char [4]);

template<typename TCaseId, std::size_t ... TIndexs>
using CaseIndexes = basic::test::type::Parameter<
    basic::test::type::Index<TCaseId, TIndexs> ...>;

const char * obj1_1 = "test";

template<std::size_t I>
using T1Var1 = VariableTestStringAt<const char *, I>;

T1Var1<5> t1_var1{&obj1_1, 't', 'e', 's', 't', '\0'};

REGISTER_TEST(t1, new TestStringAt<CaseIndexes<TestValueAt, 
    0, 1, 2, 3, 4>, T1Var1<5>>(t1_var1));

char * obj2_1 = new char[7];

template<std::size_t I>
using T2Var1 = VariableTestStringAt<char *, I>;

T2Var1<7> t2_var1{&obj2_1, '1', '2', '3', '4', '5', '6', '\0'};

REGISTER_TEST(t2, new TestStringAt<CaseIndexes<TestValueAt, 
    0, 1, 2, 3, 4, 5, 6>, T2Var1<7>>(t2_var1));

char obj3_1[] = "78901";

template<std::size_t I>
using T3Var1 = VariableTestStringAt<char [6], I>;

T3Var1<6> t3_var1{&obj3_1, '7', '8', '9', '0', '1', '\0'};

REGISTER_TEST(t3, new TestStringAt<CaseIndexes<TestValueAt, 
    0, 1, 2, 3, 4, 5>, T3Var1<6>>(t3_var1));

char obj4_1[] = "234";

template<std::size_t I>
using T4Var1 = VariableTestStringAt<const char [4], I>;

T4Var1<4> t4_var1{&obj4_1, '2', '3', '4', '\0'};

REGISTER_TEST(t4, new TestStringAt<CaseIndexes<TestValueAt, 
    0, 1, 2, 3>, T4Var1<4>>(t4_var1));


int main()
{
    std::memcpy(obj2_1, "123456", 7);
    auto ret = RUN_TEST();
    delete[] obj2_1;
    return ret;
}

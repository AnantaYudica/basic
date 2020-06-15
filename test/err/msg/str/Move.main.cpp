#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/msg/str/Move.h"

#include <cstring>
#include <string>
#include <utility>

BASIC_TEST_CONSTRUCT;

template<typename TStorage>
const char * StorgeToString(TStorage * && storage)
{
    return *storage;
}

const char * DefaultToString(char ** && s)
{
    if (*s == nullptr) return "null";
    return *s;
}

template<typename TStorge>
const char * DefaultToString(TStorge * && s)
{
    return *s;
}


struct TestValueMove {};
struct TestMoveVariableDefault {};

template<typename TStorage, typename TMoveVar, typename TDefault>
using VariableTestStringMove = basic::test::Variable<
    TStorage,
    TMoveVar,
    TDefault,
    basic::test::Value<TStorage *>,
    basic::test::Value<TMoveVar *>,
    basic::test::Value<TMoveVar *>,
    basic::test::Value<TDefault *>,
    basic::test::type::Function<const char *(TStorage * &&), 
        &StorgeToString>,
    basic::test::type::Function<const char *(TDefault * &&),
        &DefaultToString>>;

typedef basic::test::msg::Argument<TestValueMove,
    basic::test::msg::arg::type::Name<0>,
    basic::test::msg::arg::type::Name<1>,
    basic::test::msg::arg::type::Function<7,
    basic::test::msg::arg::Value<5>>> ArgTestValueMove;

typedef basic::test::msg::Base<TestValueMove, char, 
    ArgTestValueMove, ArgTestValueMove, ArgTestValueMove> 
        MessageBaseTestValueMove;

typedef basic::test::msg::Argument<TestMoveVariableDefault,
    basic::test::msg::arg::type::Function<8,
        basic::test::msg::arg::Value<6>>> ArgTestMoveVariableDefault;

typedef basic::test::msg::Base<TestMoveVariableDefault, char, 
    ArgTestMoveVariableDefault, ArgTestMoveVariableDefault, 
    ArgTestMoveVariableDefault> MessageBaseTestMoveVariableDefault;

template<typename... TVariables>
struct TestStringMove :
    public basic::test::Message<BASIC_TEST, 
        TestStringMove<TVariables...>>,
    public basic::test::Case<TestStringMove<TVariables...>,
        basic::test::type::Parameter<TestValueMove, TestMoveVariableDefault>>,
    public basic::test::Base<TestStringMove<TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueMove,
    public MessageBaseTestMoveVariableDefault
{
public:
    using MessageBaseTestValueMove::Format;
    using MessageBaseTestValueMove::SetFormat;
    using MessageBaseTestValueMove::Argument;
    using MessageBaseTestMoveVariableDefault::Format;
    using MessageBaseTestMoveVariableDefault::SetFormat;
    using MessageBaseTestMoveVariableDefault::Argument;
    using basic::test::Case<TestStringMove<TVariables...>,
        basic::test::type::Parameter<TestValueMove, 
        TestMoveVariableDefault>>::Run;
    using basic::test::Base<TestStringMove<TVariables...>, 
        TVariables...>::Run;
public:
    TestStringMove(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestStringMove< 
            TVariables...>>(*this),
        basic::test::Case<TestStringMove<TVariables...>,
            basic::test::type::Parameter<TestValueMove, 
            TestMoveVariableDefault>>(*this),
        basic::test::Base<TestStringMove<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueMove testValueMove;
        SetFormat(info, testValueMove, "test Move "
            "%s with %s {\"%s\"} pass\n");
        SetFormat(debug, testValueMove, "test Move "
            "%s with %s {\"%s\"} pass\n");
        SetFormat(err, testValueMove, "Error Move "
            "%s with %s {\"%s\"}\n");

        TestMoveVariableDefault testMoveVariableDefault;
        SetFormat(info, testMoveVariableDefault, "test source variable "
            "become default {%s}\n");
        SetFormat(debug, testMoveVariableDefault, "test source variable "
            "become default {%s}\n");
        SetFormat(err, testMoveVariableDefault, "Error source variable "
            "not become default {%s}\n");
    }
    template<typename TStorage, typename TMoveVar, typename TDefault>
    bool Result(const TestValueMove &, VariableTestStringMove<TStorage, 
        TMoveVar, TDefault> & var)
    {
        TStorage & storage = *basic::test::var::At<3>(var).Get().Get();
        TMoveVar & other = *basic::test::var::At<4>(var).Get().Get();
        TMoveVar & copy_var = *basic::test::var::At<5>(var).Get().Get();
        basic::err::msg::str::Move(storage, std::move(other));
        return std::strcmp(storage, copy_var) == 0;
    }
    template<typename TStorage, typename TMoveVar>
    bool Result(const TestMoveVariableDefault &, 
        VariableTestStringMove<TStorage, TMoveVar, char *> & var)
    {
        TMoveVar & other = *basic::test::var::At<4>(var).Get().Get();
        return other == *basic::test::var::At<6>(var).Get().Get();
    }
    template<typename TStorage, typename TMoveVar, std::size_t Size>
    bool Result(const TestMoveVariableDefault &, 
        VariableTestStringMove<TStorage, TMoveVar, char[Size]> & var)
    {
        TMoveVar & other = *basic::test::var::At<4>(var).Get().Get();
        return std::strcmp(other, *basic::test::var::At<6>(var).
            Get().Get()) == 0;
    }
};

BASIC_TEST_TYPE_NAME("const char *", const char *);
BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("const std::string", const std::string);
BASIC_TEST_TYPE_NAME("char [11]", char [11]);
BASIC_TEST_TYPE_NAME("char [6]", char [6]);

char * pointer_default = nullptr;
char array_default[] = {'\0'};

char * obj1_1 = new char[5];
char * obj1_1_move = new char[5];
char * obj1_1_copy = new char[5];
char obj1_2[11];
char obj1_2_move[11] = "aabbccddee";
char obj1_2_copy[11] = "aabbccddee";

typedef VariableTestStringMove<char *, char *, char *> T1Var1;
typedef VariableTestStringMove<char [11], char [11], char[1]> T1Var2;

T1Var1 t1_var1{&obj1_1, &obj1_1_move, &obj1_1_copy, &pointer_default};
T1Var2 t1_var2{&obj1_2, &obj1_2_move, &obj1_2_copy, &array_default};

REGISTER_TEST(t1, new TestStringMove<T1Var1, T1Var2>(t1_var1, t1_var2));

int main()
{
    std::memcpy(obj1_1_move, "test", 5);
    std::memcpy(obj1_1_copy, "test", 5);
    auto ret = RUN_TEST();
    if (obj1_1 != nullptr)delete[] obj1_1;
    if (obj1_1_move != nullptr)delete[] obj1_1_move;
    if (obj1_1_copy != nullptr)delete[] obj1_1_copy;
    return ret;
}


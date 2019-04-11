#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/Equivalent.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include <type_traits>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;
typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;

enum class CodeEnum1_1
{
    value1 = 4
};
enum class ConditionEnum1_1
{
    value1 = 5
};

struct CategoryTrait1_1
{
    typedef CodeEnum1_1 CodeEnumType;
    typedef ConditionEnum1_1 ConditionEnumType;
    CategoryTrait1_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    CategoryValueType Value() const
    {
        return 11;
    }
};

enum class CodeEnum1_2
{
    value1 = 4
};
enum class ConditionEnum1_2
{
    value1 = 5
};

struct CategoryTrait1_2
{
    typedef CodeEnum1_2 CodeEnumType;
    typedef ConditionEnum1_2 ConditionEnumType;
    CategoryTrait1_2() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond - 1);
    }
    CategoryValueType Value() const
    {
        return 12;
    }
};

enum class CodeEnum1_3
{
    value1 = 4
};
enum class ConditionEnum1_3
{
    value1 = 5
};

struct CategoryTrait1_3
{
    typedef CodeEnum1_3 CodeEnumType;
    typedef ConditionEnum1_3 ConditionEnumType;
    CategoryTrait1_3() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 1);
    }
    CategoryValueType Value() const
    {
        return 13;
    }
};

enum class CodeEnum1_4
{
    value1 = 4
};
enum class ConditionEnum1_4
{
    value1 = 5
};

struct CategoryTrait1_4
{
    typedef CodeEnum1_4 CodeEnumType;
    typedef ConditionEnum1_4 ConditionEnumType;
    CategoryTrait1_4() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 1);
    }
    CategoryValueType Value() const
    {
        return 14;
    }
};

enum class CodeEnum2_1
{
    value1 = 4
};
enum class ConditionEnum2_1
{
    value1 = 5,
    value2 = 6
};

struct CategoryTrait2_1
{
    typedef CodeEnum2_1 CodeEnumType;
    typedef ConditionEnum2_1 ConditionEnumType;
    CategoryTrait2_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond - 2);
    }
    CategoryValueType Value() const
    {
        return 21;
    }
};

enum class CodeEnum2_2
{
    value1 = 4
};
enum class ConditionEnum2_2
{
    value1 = 5,
    value2 = 6
};

struct CategoryTrait2_2
{
    typedef CodeEnum2_2 CodeEnumType;
    typedef ConditionEnum2_2 ConditionEnumType;
    CategoryTrait2_2() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 2);
    }
    CategoryValueType Value() const
    {
        return 22;
    }
};

enum class CodeEnum2_3
{
    value1 = 4
};
enum class ConditionEnum2_3
{
    value1 = 5,
    value2 = 6
};

struct CategoryTrait2_3
{
    typedef CodeEnum2_3 CodeEnumType;
    typedef ConditionEnum2_3 ConditionEnumType;
    CategoryTrait2_3() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 2);
    }
    CategoryValueType Value() const
    {
        return 23;
    }
};

enum class CodeEnum2_4
{
    value1 = 4
};
enum class ConditionEnum2_4
{
    value1 = 5,
    value2 = 6
};

struct CategoryTrait2_4
{
    typedef CodeEnum2_4 CodeEnumType;
    typedef ConditionEnum2_4 ConditionEnumType;
    CategoryTrait2_4() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond -1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 2);
    }
    CategoryValueType Value() const
    {
        return 24;
    }
};

enum class CodeEnum2_5
{
    value1 = 4
};
enum class ConditionEnum2_5
{
    value1 = 5,
    value2 = 6
};

struct CategoryTrait2_5
{
    typedef CodeEnum2_5 CodeEnumType;
    typedef ConditionEnum2_5 ConditionEnumType;
    CategoryTrait2_5() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond -1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 2);
    }
    CategoryValueType Value() const
    {
        return 25;
    }
};

enum class CodeEnum2_6
{
    value1 = 4
};
enum class ConditionEnum2_6
{
    value1 = 5,
    value2 = 6
};

struct CategoryTrait2_6
{
    typedef CodeEnum2_6 CodeEnumType;
    typedef ConditionEnum2_6 ConditionEnumType;
    CategoryTrait2_6() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 2);
    }
    CategoryValueType Value() const
    {
        return 26;
    }
};

enum class CodeEnum3_1
{
    value1 = 4
};
enum class ConditionEnum3_1
{
    value1 = 5,
    value2 = 6,
    value3 = 7
};

struct CategoryTrait3_1
{
    typedef CodeEnum3_1 CodeEnumType;
    typedef ConditionEnum3_1 ConditionEnumType;
    CategoryTrait3_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond - 2);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 3);
    }
    CategoryValueType Value() const
    {
        return 31;
    }
};

enum class CodeEnum3_2
{
    value1 = 4
};
enum class ConditionEnum3_2
{
    value1 = 5,
    value2 = 6,
    value3 = 7
};

struct CategoryTrait3_2
{
    typedef CodeEnum3_2 CodeEnumType;
    typedef ConditionEnum3_2 ConditionEnumType;
    CategoryTrait3_2() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond - 2);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 3);
    }
    CategoryValueType Value() const
    {
        return 32;
    }
};

enum class CodeEnum3_3
{
    value1 = 4
};
enum class ConditionEnum3_3
{
    value1 = 5,
    value2 = 6,
    value3 = 7
};

struct CategoryTrait3_3
{
    typedef CodeEnum3_3 CodeEnumType;
    typedef ConditionEnum3_3 ConditionEnumType;
    CategoryTrait3_3() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() - 1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 2);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 3);
    }
    CategoryValueType Value() const
    {
        return 33;
    }
};

enum class CodeEnum3_4
{
    value1 = 4
};
enum class ConditionEnum3_4
{
    value1 = 5,
    value2 = 6,
    value3 = 7
};

struct CategoryTrait3_4
{
    typedef CodeEnum3_4 CodeEnumType;
    typedef ConditionEnum3_4 ConditionEnumType;
    CategoryTrait3_4() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond - 1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 2);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 3);
    }
    CategoryValueType Value() const
    {
        return 34;
    }
};

enum class CodeEnum4_1
{
    value1 = 4
};
enum class ConditionEnum4_1
{
    value1 = 5,
    value2 = 6,
    value3 = 7,
    value4 = 8
};

struct CategoryTrait4_1
{
    typedef CodeEnum4_1 CodeEnumType;
    typedef ConditionEnum4_1 ConditionEnumType;
    CategoryTrait4_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == (cond.Value() -1);
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == (cond - 2);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == (cond.Value() - 3);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == (cond - 4);
    }
    CategoryValueType Value() const
    {
        return 41;
    }
};

struct CategoryTrait5
{
    CategoryTrait5() = default;
    CategoryValueType Value() const
    {
        return 5;
    }
};

enum class CodeEnum6_1
{
    value1 = 4
};
enum class ConditionEnum6_1
{
    value1 = 5,
    value2 = 6,
    value3 = 7,
    value4 = 8,
    value5 = 9
};

struct CategoryTrait6_1
{
    typedef CodeEnum6_1 CodeEnumType;
    typedef ConditionEnum6_1 ConditionEnumType;
    CategoryTrait6_1() = default;
    bool Equivalent(const CodeEnumType & code, 
        const ConditionEnumType & cond) const
    {
        return (CodeValueType)code == ((ConditionValueType)cond - 1);
    }
    bool Equivalent(const CodeEnumType & code, 
        const ConditionType & cond) const
    {
        return (CodeValueType)code == (cond.Value() - 2);
    }
    bool Equivalent(const CodeEnumType & code, 
        const ConditionValueType & cond) const
    {
        return (CodeValueType)code == (cond - 3);
    }
    bool Equivalent(const CodeType & code, 
        const ConditionEnumType & cond) const
    {
        return code.Value() == ((ConditionValueType)cond - 4);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionEnumType & cond) const
    {
        return code == ((ConditionValueType)cond - 5);
    }
    CategoryValueType Value() const
    {
        return 61;
    }
};

enum class CodeEnum6_2
{
    value1 = 4
};
enum class ConditionEnum6_2
{
    value1 = 5,
    value2 = 6,
};

struct CategoryTrait6_2
{
    typedef CodeEnum6_2 CodeEnumType;
    typedef ConditionEnum6_2 ConditionEnumType;
    CategoryTrait6_2() = default;
    bool Equivalent(const CodeEnumType & code, 
        const ConditionType & cond) const
    {
        return (CodeValueType)code == (cond.Value() - 1);
    }
    bool Equivalent(const CodeType & code, 
        const ConditionEnumType & cond) const
    {
        return code.Value() == ((ConditionValueType)cond - 2);
    }
    CategoryValueType Value() const
    {
        return 62;
    }
};

enum class CodeEnum6_3
{
    value1 = 4
};
enum class ConditionEnum6_3
{
    value1 = 5,
    value2 = 6,
};

struct CategoryTrait6_3
{
    typedef CodeEnum6_3 CodeEnumType;
    typedef ConditionEnum6_3 ConditionEnumType;
    CategoryTrait6_3() = default;
    bool Equivalent(const CodeEnumType & code, 
        const ConditionValueType & cond) const
    {
        return (CodeValueType)code == (cond - 1);
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionEnumType & cond) const
    {
        return code == ((ConditionValueType)cond - 2);
    }
    CategoryValueType Value() const
    {
        return 63;
    }
};

enum class CodeEnum6_4
{
    value1 = 4
};
enum class ConditionEnum6_4
{
    value1 = 5
};

struct CategoryTrait6_4
{
    typedef CodeEnum6_4 CodeEnumType;
    typedef ConditionEnum6_4 ConditionEnumType;
    CategoryTrait6_4() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionEnumType & cond) const
    {
        return code.Value() == ((ConditionValueType)cond - 1);
    }
    CategoryValueType Value() const
    {
        return 64;
    }
};

enum class CodeEnum6_5
{
    value1 = 4
};
enum class ConditionEnum6_5
{
    value1 = 5
};

struct CategoryTrait6_5
{
    typedef CodeEnum6_5 CodeEnumType;
    typedef ConditionEnum6_5 ConditionEnumType;
    CategoryTrait6_5() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionEnumType & cond) const
    {
        return code == ((ConditionValueType)cond - 1);
    }
    CategoryValueType Value() const
    {
        return 65;
    }
};


template<typename TValue>
int PtrToInteger(TValue * && ptr)
{
    return (int)*ptr;
}

int PtrToInteger(CodeType * && ptr)
{
    return ptr->Value();
}

int PtrToInteger(ConditionType * && ptr)
{
    return ptr->Value();
}

int PtrToInteger(CodeValueType * && ptr)
{
    return *ptr;
}

template<typename TConditionValue = ConditionValueType>
std::enable_if<!std::is_same<TConditionValue,
    CodeValueType>::value, int> PtrToInteger(ConditionValueType * && ptr)
{
    return *ptr;
}

struct TestValueEquivalent {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TCode, typename TCondition>
using VariableTestEquivalent = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    bool,
    TCategoryTrait,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    TCode,
    TCondition,
    basic::test::Value<
        const basic::err::sys::tmpl::Category<TCategoryTrait> *>,
    basic::test::Value<TCode *>,
    basic::test::Value<TCondition *>,
    basic::test::Value<bool *>,
    basic::test::type::Function<int(TCode * &&), &PtrToInteger>,
    basic::test::type::Function<int(TCondition * &&), &PtrToInteger>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t IBoolType = 1;
constexpr std::size_t ICategoryTraitType = 2;
constexpr std::size_t ITmplCategoryType = 3;
constexpr std::size_t ICodeType = 4;
constexpr std::size_t IConditionType = 5;
constexpr std::size_t ITmplCategoryValue = 6;
constexpr std::size_t ICodeValue = 7;
constexpr std::size_t IConditionValue = 8;
constexpr std::size_t IBoolValue = 9;
constexpr std::size_t ICodePtrToIntegerFuncType = 10;
constexpr std::size_t IConditionPtrToIntegerFuncType = 11;

typedef basic::test::msg::Argument<TestValueEquivalent,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Function<ICodePtrToIntegerFuncType,
        basic::test::msg::arg::Value<ICodeValue>>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::type::Function<IConditionPtrToIntegerFuncType,
        basic::test::msg::arg::Value<IConditionValue>>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::type::Name<IBoolType>,
    basic::test::msg::arg::Value<IBoolValue>> 
        ArgTestValueEquivalent;

typedef basic::test::msg::Base<TestValueEquivalent, char, 
    ArgTestValueEquivalent, ArgTestValueEquivalent, 
    ArgTestValueEquivalent> MessageBaseTestValueEquivalent;

template<typename TCases, typename... TVariables>
struct TestEquivalent :
    public basic::test::Message<BASIC_TEST, TestEquivalent<TCases, 
        TVariables...>>,
    public basic::test::Case<TestEquivalent<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestEquivalent<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueEquivalent
{
public:
    using MessageBaseTestValueEquivalent::Format;
    using MessageBaseTestValueEquivalent::SetFormat;
    using MessageBaseTestValueEquivalent::Argument;
public:
    using basic::test::Case<TestEquivalent<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestEquivalent<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestEquivalent(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestEquivalent<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestEquivalent<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestEquivalent<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueEquivalent testValueEquivalent;
        SetFormat(info, testValueEquivalent, "Test value "
            "%s::Equivalent(%s(), %s {%d}, %s {%d}, %s {%s}) "
            "is same with %s{%s}\n");
        SetFormat(debug, testValueEquivalent, "Test value "
            "%s::Equivalent(%s(), %s {%d}, %s {%d}, %s {%s}) "
            "is same with %s{%s}\n");
        SetFormat(err, testValueEquivalent, "Error value "
            "%s::Equivalent(%s(), %s {%d}, %s {%d}, %s {%s}) "
            "is not same with %s{%s}\n");

    }
    template<typename TCategoryTrait, typename TCode, typename TCondition>
    bool Result(const TestValueEquivalent &, 
        VariableTestEquivalent<TCategoryTrait, TCode, TCondition> & var)
    {
        auto * tmpl_categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto * cond = basic::test::var::At<IConditionValue>(var).
            Get().Get();
        auto * b = basic::test::var::At<IBoolValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Equivalent(TCategoryTrait {}, *code, *cond, *tmpl_categ);
        return res == *b;
    }

};

typedef basic::test::type::Parameter<TestValueEquivalent> Case1;

typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeType, ConditionType> T1Var1_1;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeType, ConditionValueType> T1Var1_2;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeValueType, ConditionType> T1Var1_3;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeValueType, ConditionValueType> T1Var1_4;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeEnum1_1, ConditionEnum1_1> T1Var1_5;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeEnum1_1, ConditionType> T1Var1_6;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeEnum1_1, ConditionValueType> T1Var1_7;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeType, ConditionEnum1_1> T1Var1_8;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeValueType, ConditionEnum1_1> T1Var1_9;

typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeType, ConditionType> T2Var1;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeType, ConditionValueType> T2Var2;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeValueType, ConditionType> T2Var3;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeValueType, ConditionValueType> T2Var4;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeEnum1_2, ConditionEnum1_2> T2Var5;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeEnum1_2, ConditionType> T2Var6;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeEnum1_2, ConditionValueType> T2Var7;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeType, ConditionEnum1_2> T2Var8;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeValueType, ConditionEnum1_2> T2Var9;

typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeType, ConditionType> T3Var1;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeType, ConditionValueType> T3Var2;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeValueType, ConditionType> T3Var3;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeValueType, ConditionValueType> T3Var4;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeEnum1_3, ConditionEnum1_3> T3Var5;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeEnum1_3, ConditionType> T3Var6;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeEnum1_3, ConditionValueType> T3Var7;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeType, ConditionEnum1_3> T3Var8;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeValueType, ConditionEnum1_3> T3Var9;

typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeType, ConditionType> T1Var4_1;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeType, ConditionValueType> T1Var4_2;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeValueType, ConditionType> T1Var4_3;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeValueType, ConditionValueType> T1Var4_4;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeEnum1_4, ConditionEnum1_4> T1Var4_5;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeEnum1_4, ConditionType> T1Var4_6;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeEnum1_4, ConditionValueType> T1Var4_7;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeType, ConditionEnum1_4> T1Var4_8;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeValueType, ConditionEnum1_4> T1Var4_9;

typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeType, ConditionType> T2Var1_1;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeType, ConditionValueType> T2Var1_2;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeValueType, ConditionType> T2Var1_3;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeValueType, ConditionValueType> T2Var1_4;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeEnum2_1, ConditionEnum2_1> T2Var1_5;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeEnum2_1, ConditionType> T2Var1_6;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeEnum2_1, ConditionValueType> T2Var1_7;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeType, ConditionEnum2_1> T2Var1_8;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeValueType, ConditionEnum2_1> T2Var1_9;

typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeType, ConditionType> T2Var2_1;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeType, ConditionValueType> T2Var2_2;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeValueType, ConditionType> T2Var2_3;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeValueType, ConditionValueType> T2Var2_4;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeEnum2_2, ConditionEnum2_2> T2Var2_5;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeEnum2_2, ConditionType> T2Var2_6;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeEnum2_2, ConditionValueType> T2Var2_7;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeType, ConditionEnum2_2> T2Var2_8;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeValueType, ConditionEnum2_2> T2Var2_9;

typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeType, ConditionType> T2Var3_1;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeType, ConditionValueType> T2Var3_2;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeValueType, ConditionType> T2Var3_3;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeValueType, ConditionValueType> T2Var3_4;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeEnum2_3, ConditionEnum2_3> T2Var3_5;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeEnum2_3, ConditionType> T2Var3_6;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeEnum2_3, ConditionValueType> T2Var3_7;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeType, ConditionEnum2_3> T2Var3_8;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeValueType, ConditionEnum2_3> T2Var3_9;

typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeType, ConditionType> T2Var4_1;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeType, ConditionValueType> T2Var4_2;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeValueType, ConditionType> T2Var4_3;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeValueType, ConditionValueType> T2Var4_4;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeEnum2_4, ConditionEnum2_4> T2Var4_5;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeEnum2_4, ConditionType> T2Var4_6;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeEnum2_4, ConditionValueType> T2Var4_7;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeType, ConditionEnum2_4> T2Var4_8;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeValueType, ConditionEnum2_4> T2Var4_9;

typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeType, ConditionType> T2Var5_1;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeType, ConditionValueType> T2Var5_2;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeValueType, ConditionType> T2Var5_3;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeValueType, ConditionValueType> T2Var5_4;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeEnum2_5, ConditionEnum2_5> T2Var5_5;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeEnum2_5, ConditionType> T2Var5_6;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeEnum2_5, ConditionValueType> T2Var5_7;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeType, ConditionEnum2_5> T2Var5_8;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeValueType, ConditionEnum2_5> T2Var5_9;
    
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeType, ConditionType> T2Var6_1;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeType, ConditionValueType> T2Var6_2;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeValueType, ConditionType> T2Var6_3;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeValueType, ConditionValueType> T2Var6_4;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeEnum2_6, ConditionEnum2_6> T2Var6_5;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeEnum2_6, ConditionType> T2Var6_6;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeEnum2_6, ConditionValueType> T2Var6_7;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeType, ConditionEnum2_6> T2Var6_8;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeValueType, ConditionEnum2_6> T2Var6_9;

typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeType, ConditionType> T3Var1_1;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeType, ConditionValueType> T3Var1_2;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeValueType, ConditionType> T3Var1_3;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeValueType, ConditionValueType> T3Var1_4;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeEnum3_1, ConditionEnum3_1> T3Var1_5;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeEnum3_1, ConditionType> T3Var1_6;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeEnum3_1, ConditionValueType> T3Var1_7;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeType, ConditionEnum3_1> T3Var1_8;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeValueType, ConditionEnum3_1> T3Var1_9;

typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeType, ConditionType> T3Var2_1;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeType, ConditionValueType> T3Var2_2;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeValueType, ConditionType> T3Var2_3;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeValueType, ConditionValueType> T3Var2_4;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeEnum3_2, ConditionEnum3_2> T3Var2_5;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeEnum3_2, ConditionType> T3Var2_6;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeEnum3_2, ConditionValueType> T3Var2_7;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeType, ConditionEnum3_2> T3Var2_8;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeValueType, ConditionEnum3_2> T3Var2_9;

typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeType, ConditionType> T3Var3_1;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeType, ConditionValueType> T3Var3_2;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeValueType, ConditionType> T3Var3_3;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeValueType, ConditionValueType> T3Var3_4;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeEnum3_3, ConditionEnum3_3> T3Var3_5;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeEnum3_3, ConditionType> T3Var3_6;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeEnum3_3, ConditionValueType> T3Var3_7;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeType, ConditionEnum3_3> T3Var3_8;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeValueType, ConditionEnum3_3> T3Var3_9;

typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeType, ConditionType> T3Var4_1;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeType, ConditionValueType> T3Var4_2;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeValueType, ConditionType> T3Var4_3;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeValueType, ConditionValueType> T3Var4_4;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeEnum3_4, ConditionEnum3_4> T3Var4_5;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeEnum3_4, ConditionType> T3Var4_6;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeEnum3_4, ConditionValueType> T3Var4_7;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeType, ConditionEnum3_4> T3Var4_8;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeValueType, ConditionEnum3_4> T3Var4_9;

typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeType, ConditionType> T4Var1_1;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeType, ConditionValueType> T4Var1_2;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeValueType, ConditionType> T4Var1_3;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeValueType, ConditionValueType> T4Var1_4;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeEnum4_1, ConditionEnum4_1> T4Var1_5;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeEnum4_1, ConditionType> T4Var1_6;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeEnum4_1, ConditionValueType> T4Var1_7;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeType, ConditionEnum4_1> T4Var1_8;
typedef VariableTestEquivalent<CategoryTrait4_1, 
    CodeValueType, ConditionEnum4_1> T4Var1_9;

typedef VariableTestEquivalent<CategoryTrait5, 
    CodeType, ConditionType> T5Var1;
typedef VariableTestEquivalent<CategoryTrait5, 
    CodeType, ConditionValueType> T5Var2;
typedef VariableTestEquivalent<CategoryTrait5, 
    CodeValueType, ConditionType> T5Var3;
typedef VariableTestEquivalent<CategoryTrait5, 
    CodeValueType, ConditionValueType> T5Var4;

typedef VariableTestEquivalent<CategoryTrait6_1, 
    CodeEnum6_1, ConditionEnum6_1> T6Var1_1;
typedef VariableTestEquivalent<CategoryTrait6_1, 
    CodeEnum6_1, ConditionType> T6Var1_2;
typedef VariableTestEquivalent<CategoryTrait6_1, 
    CodeEnum6_1, ConditionValueType> T6Var1_3;
typedef VariableTestEquivalent<CategoryTrait6_1, 
    CodeType, ConditionEnum6_1> T6Var1_4;
typedef VariableTestEquivalent<CategoryTrait6_1, 
    CodeValueType, ConditionEnum6_1> T6Var1_5;

typedef VariableTestEquivalent<CategoryTrait6_2, 
    CodeEnum6_2, ConditionEnum6_2> T6Var2_1;
typedef VariableTestEquivalent<CategoryTrait6_2, 
    CodeEnum6_2, ConditionType> T6Var2_2;
typedef VariableTestEquivalent<CategoryTrait6_2, 
    CodeEnum6_2, ConditionValueType> T6Var2_3;
typedef VariableTestEquivalent<CategoryTrait6_2, 
    CodeType, ConditionEnum6_2> T6Var2_4;
typedef VariableTestEquivalent<CategoryTrait6_2, 
    CodeValueType, ConditionEnum6_2> T6Var2_5;

typedef VariableTestEquivalent<CategoryTrait6_3, 
    CodeEnum6_3, ConditionEnum6_3> T6Var3_1;
typedef VariableTestEquivalent<CategoryTrait6_3, 
    CodeEnum6_3, ConditionType> T6Var3_2;
typedef VariableTestEquivalent<CategoryTrait6_3, 
    CodeEnum6_3, ConditionValueType> T6Var3_3;
typedef VariableTestEquivalent<CategoryTrait6_3, 
    CodeType, ConditionEnum6_3> T6Var3_4;
typedef VariableTestEquivalent<CategoryTrait6_3, 
    CodeValueType, ConditionEnum6_3> T6Var3_5;
    
typedef VariableTestEquivalent<CategoryTrait6_4, 
    CodeEnum6_4, ConditionEnum6_4> T6Var4_1;
typedef VariableTestEquivalent<CategoryTrait6_4, 
    CodeType, ConditionEnum6_4> T6Var4_2;
typedef VariableTestEquivalent<CategoryTrait6_4, 
    CodeValueType, ConditionEnum6_4> T6Var4_3;

typedef VariableTestEquivalent<CategoryTrait6_5, 
    CodeEnum6_5, ConditionEnum6_5> T6Var5_1;
typedef VariableTestEquivalent<CategoryTrait6_5, 
    CodeType, ConditionEnum6_5> T6Var5_2;
typedef VariableTestEquivalent<CategoryTrait6_5, 
    CodeValueType, ConditionEnum6_5> T6Var5_3;

auto & tmplCategory1_1 = basic::err::sys::tmpl::
    Category<CategoryTrait1_1>::GetInstance();
auto & tmplCategory1_2 = basic::err::sys::tmpl::
    Category<CategoryTrait1_2>::GetInstance();
auto & tmplCategory1_3 = basic::err::sys::tmpl::
    Category<CategoryTrait1_3>::GetInstance();
auto & tmplCategory1_4 = basic::err::sys::tmpl::
    Category<CategoryTrait1_4>::GetInstance();
auto & tmplCategory2_1 = basic::err::sys::tmpl::
    Category<CategoryTrait2_1>::GetInstance();
auto & tmplCategory2_2 = basic::err::sys::tmpl::
    Category<CategoryTrait2_2>::GetInstance();
auto & tmplCategory2_3 = basic::err::sys::tmpl::
    Category<CategoryTrait2_3>::GetInstance();
auto & tmplCategory2_4 = basic::err::sys::tmpl::
    Category<CategoryTrait2_4>::GetInstance();
auto & tmplCategory2_5 = basic::err::sys::tmpl::
    Category<CategoryTrait2_5>::GetInstance();
auto & tmplCategory2_6 = basic::err::sys::tmpl::
    Category<CategoryTrait2_6>::GetInstance();
auto & tmplCategory3_1 = basic::err::sys::tmpl::
    Category<CategoryTrait3_1>::GetInstance();
auto & tmplCategory3_2 = basic::err::sys::tmpl::
    Category<CategoryTrait3_2>::GetInstance();
auto & tmplCategory3_3 = basic::err::sys::tmpl::
    Category<CategoryTrait3_3>::GetInstance();
auto & tmplCategory3_4 = basic::err::sys::tmpl::
    Category<CategoryTrait3_4>::GetInstance();
auto & tmplCategory4_1 = basic::err::sys::tmpl::
    Category<CategoryTrait4_1>::GetInstance();
auto & tmplCategory5 = basic::err::sys::tmpl::
    Category<CategoryTrait5>::GetInstance();
auto & tmplCategory6_1 = basic::err::sys::tmpl::
    Category<CategoryTrait6_1>::GetInstance();
auto & tmplCategory6_2 = basic::err::sys::tmpl::
    Category<CategoryTrait6_2>::GetInstance();
auto & tmplCategory6_3 = basic::err::sys::tmpl::
    Category<CategoryTrait6_3>::GetInstance();
auto & tmplCategory6_4 = basic::err::sys::tmpl::
    Category<CategoryTrait6_4>::GetInstance();
auto & tmplCategory6_5 = basic::err::sys::tmpl::
    Category<CategoryTrait6_5>::GetInstance();


bool bool_t{true};
bool bool_f{false};

CodeType code1_1_1{4, tmplCategory1_1};
ConditionType cond1_1_1{5, tmplCategory1_1};
CodeValueType code1_1_2{4};
ConditionValueType cond1_1_2{5};
CodeEnum1_1 code1_1_3 = CodeEnum1_1::value1;
ConditionEnum1_1 cond1_1_3 = ConditionEnum1_1::value1;

T1Var1_1 t1_var1_1{&tmplCategory1_1, &code1_1_1, &cond1_1_1, &bool_t};
T1Var1_2 t1_var1_2{&tmplCategory1_1, &code1_1_1, &cond1_1_2, &bool_t};
T1Var1_3 t1_var1_3{&tmplCategory1_1, &code1_1_2, &cond1_1_1, &bool_t};
T1Var1_4 t1_var1_4{&tmplCategory1_1, &code1_1_2, &cond1_1_2, &bool_t};
T1Var1_5 t1_var1_5{&tmplCategory1_1, &code1_1_3, &cond1_1_3, &bool_t};
T1Var1_6 t1_var1_6{&tmplCategory1_1, &code1_1_3, &cond1_1_1, &bool_t};
T1Var1_7 t1_var1_7{&tmplCategory1_1, &code1_1_3, &cond1_1_2, &bool_t};
T1Var1_8 t1_var1_8{&tmplCategory1_1, &code1_1_1, &cond1_1_3, &bool_t};
T1Var1_9 t1_var1_9{&tmplCategory1_1, &code1_1_2, &cond1_1_3, &bool_t};

CodeType code1_2_1{4, tmplCategory1_2};
ConditionType cond1_2_1{5, tmplCategory1_2};
CodeValueType code1_2_2{4};
ConditionValueType cond1_2_2{5};
CodeEnum1_2 code1_2_3 = CodeEnum1_2::value1;
ConditionEnum1_2 cond1_2_3 = ConditionEnum1_2::value1;

T2Var1 t1_var2_1{&tmplCategory1_2, &code1_2_1, &cond1_2_1, &bool_t};
T2Var2 t1_var2_2{&tmplCategory1_2, &code1_2_1, &cond1_2_2, &bool_t};
T2Var3 t1_var2_3{&tmplCategory1_2, &code1_2_2, &cond1_2_1, &bool_t};
T2Var4 t1_var2_4{&tmplCategory1_2, &code1_2_2, &cond1_2_2, &bool_t};
T2Var5 t1_var2_5{&tmplCategory1_2, &code1_2_3, &cond1_2_3, &bool_t};
T2Var6 t1_var2_6{&tmplCategory1_2, &code1_2_3, &cond1_2_1, &bool_t};
T2Var7 t1_var2_7{&tmplCategory1_2, &code1_2_3, &cond1_2_2, &bool_t};
T2Var8 t1_var2_8{&tmplCategory1_2, &code1_2_1, &cond1_2_3, &bool_t};
T2Var9 t1_var2_9{&tmplCategory1_2, &code1_2_2, &cond1_2_3, &bool_t};

CodeType code1_3_1{4, tmplCategory1_3};
ConditionType cond1_3_1{5, tmplCategory1_3};
CodeValueType code1_3_2{4};
ConditionValueType cond1_3_2{5};
CodeEnum1_3 code1_3_3 = CodeEnum1_3::value1;
ConditionEnum1_3 cond1_3_3 = ConditionEnum1_3::value1;

T3Var1 t3_var1{&tmplCategory1_3, &code1_3_1, &cond1_3_1, &bool_t};
T3Var2 t3_var2{&tmplCategory1_3, &code1_3_1, &cond1_3_2, &bool_t};
T3Var3 t3_var3{&tmplCategory1_3, &code1_3_2, &cond1_3_1, &bool_t};
T3Var4 t3_var4{&tmplCategory1_3, &code1_3_2, &cond1_3_2, &bool_t};
T3Var5 t3_var5{&tmplCategory1_3, &code1_3_3, &cond1_3_3, &bool_t};
T3Var6 t3_var6{&tmplCategory1_3, &code1_3_3, &cond1_3_1, &bool_t};
T3Var7 t3_var7{&tmplCategory1_3, &code1_3_3, &cond1_3_2, &bool_t};
T3Var8 t3_var8{&tmplCategory1_3, &code1_3_1, &cond1_3_3, &bool_t};
T3Var9 t3_var9{&tmplCategory1_3, &code1_3_2, &cond1_3_3, &bool_t};

CodeType code1_4_1{4, tmplCategory1_4};
ConditionType cond1_4_1{5, tmplCategory1_4};
CodeValueType code1_4_2{4};
ConditionValueType cond1_4_2{5};
CodeEnum1_4 code1_4_3 = CodeEnum1_4::value1;
ConditionEnum1_4 cond1_4_3 = ConditionEnum1_4::value1;

T1Var4_1 t1_var4_1{&tmplCategory1_4, &code1_4_1, &cond1_4_1, &bool_t};
T1Var4_2 t1_var4_2{&tmplCategory1_4, &code1_4_1, &cond1_4_2, &bool_t};
T1Var4_3 t1_var4_3{&tmplCategory1_4, &code1_4_2, &cond1_4_1, &bool_t};
T1Var4_4 t1_var4_4{&tmplCategory1_4, &code1_4_2, &cond1_4_2, &bool_t};
T1Var4_5 t1_var4_5{&tmplCategory1_4, &code1_4_3, &cond1_4_3, &bool_t};
T1Var4_6 t1_var4_6{&tmplCategory1_4, &code1_4_3, &cond1_4_1, &bool_t};
T1Var4_7 t1_var4_7{&tmplCategory1_4, &code1_4_3, &cond1_4_2, &bool_t};
T1Var4_8 t1_var4_8{&tmplCategory1_4, &code1_4_1, &cond1_4_3, &bool_t};
T1Var4_9 t1_var4_9{&tmplCategory1_4, &code1_4_2, &cond1_4_3, &bool_t};

CodeType code2_1_1{4, tmplCategory2_1};
ConditionType cond2_1_1_1{5, tmplCategory2_1};
ConditionType cond2_1_1_2{6, tmplCategory2_1};
CodeValueType code2_1_2{4};
ConditionValueType cond2_1_2_1{5};
ConditionValueType cond2_1_2_2{6};
CodeEnum2_1 code2_1_3 = CodeEnum2_1::value1;
ConditionEnum2_1 cond2_1_3_1 = ConditionEnum2_1::value1;
ConditionEnum2_1 cond2_1_3_2 = ConditionEnum2_1::value2;

REGISTER_TEST(t1, new TestEquivalent<Case1, T1Var1_1, T1Var1_2,
    T1Var1_3, T1Var1_4, T1Var1_5, T1Var1_6, T1Var1_7, 
    T1Var1_8, T1Var1_9, T2Var1, T2Var2, T2Var3,
    T2Var4, T2Var5, T2Var6, T2Var7, T2Var8, 
    T2Var9, T3Var1, T3Var2, T3Var3, T3Var4, 
    T3Var5, T3Var6, T3Var7, T3Var8, T3Var9,
    T1Var4_1, T1Var4_2, T1Var4_3, T1Var4_4, T1Var4_5, 
    T1Var4_6, T1Var4_7, T1Var4_8, T1Var4_9>(t1_var1_1, t1_var1_2, 
        t1_var1_3, t1_var1_4, t1_var1_5, 
        t1_var1_6, t1_var1_7, t1_var1_8, t1_var1_9, t1_var2_1,
        t1_var2_2, t1_var2_3, t1_var2_4, t1_var2_5, t1_var2_6, 
        t1_var2_7, t1_var2_8, t1_var2_9, t3_var1, t3_var2, 
        t3_var3, t3_var4, t3_var5, t3_var6, t3_var7, 
        t3_var8, t3_var9, t1_var4_1, t1_var4_2, t1_var4_3, 
        t1_var4_4, t1_var4_5, t1_var4_6, t1_var4_7, t1_var4_8, 
        t1_var4_9));

T2Var1_1 t1_var2_1_1{&tmplCategory2_1, &code2_1_1, &cond2_1_1_1, &bool_t};
T2Var1_2 t1_var2_1_2{&tmplCategory2_1, &code2_1_1, &cond2_1_2_2, &bool_t};
T2Var1_3 t1_var2_1_3{&tmplCategory2_1, &code2_1_2, &cond2_1_1_1, &bool_t};
T2Var1_4 t1_var2_1_4{&tmplCategory2_1, &code2_1_2, &cond2_1_2_2, &bool_t};
T2Var1_5 t1_var2_1_5{&tmplCategory2_1, &code2_1_3, &cond2_1_3_2, &bool_t};
T2Var1_6 t1_var2_1_6{&tmplCategory2_1, &code2_1_3, &cond2_1_1_1, &bool_t};
T2Var1_7 t1_var2_1_7{&tmplCategory2_1, &code2_1_3, &cond2_1_2_2, &bool_t};
T2Var1_8 t1_var2_1_8{&tmplCategory2_1, &code2_1_1, &cond2_1_3_2, &bool_t};
T2Var1_9 t1_var2_1_9{&tmplCategory2_1, &code2_1_2, &cond2_1_3_2, &bool_t};

CodeType code2_2_1{4, tmplCategory2_2};
ConditionType cond2_2_1_1{5, tmplCategory2_2};
ConditionType cond2_2_1_2{6, tmplCategory2_2};
CodeValueType code2_2_2{4};
ConditionValueType cond2_2_2_1{5};
ConditionValueType cond2_2_2_2{6};
CodeEnum2_2 code2_2_3 = CodeEnum2_2::value1;
ConditionEnum2_2 cond2_2_3_1 = ConditionEnum2_2::value1;
ConditionEnum2_2 cond2_2_3_2 = ConditionEnum2_2::value2;

T2Var2_1 t1_var2_2_1{&tmplCategory2_2, &code2_2_1, &cond2_2_1_1, &bool_t};
T2Var2_2 t1_var2_2_2{&tmplCategory2_2, &code2_2_1, &cond2_2_2_1, &bool_t};
T2Var2_3 t1_var2_2_3{&tmplCategory2_2, &code2_2_2, &cond2_2_1_2, &bool_t};
T2Var2_4 t1_var2_2_4{&tmplCategory2_2, &code2_2_2, &cond2_2_2_2, &bool_t};
T2Var2_5 t1_var2_2_5{&tmplCategory2_2, &code2_2_3, &cond2_2_3_2, &bool_t};
T2Var2_6 t1_var2_2_6{&tmplCategory2_2, &code2_2_3, &cond2_2_1_2, &bool_t};
T2Var2_7 t1_var2_2_7{&tmplCategory2_2, &code2_2_3, &cond2_2_2_2, &bool_t};
T2Var2_8 t1_var2_2_8{&tmplCategory2_2, &code2_2_1, &cond2_2_3_1, &bool_t};
T2Var2_9 t1_var2_2_9{&tmplCategory2_2, &code2_2_2, &cond2_2_3_2, &bool_t};

CodeType code2_3_1{4, tmplCategory2_3};
ConditionType cond2_3_1_1{5, tmplCategory2_3};
ConditionType cond2_3_1_2{6, tmplCategory2_3};
CodeValueType code2_3_2{4};
ConditionValueType cond2_3_2_1{5};
ConditionValueType cond2_3_2_2{6};
CodeEnum2_3 code2_3_3 = CodeEnum2_3::value1;
ConditionEnum2_3 cond2_3_3_1 = ConditionEnum2_3::value1;
ConditionEnum2_3 cond2_3_3_2 = ConditionEnum2_3::value2;

T2Var3_1 t1_var2_3_1{&tmplCategory2_3, &code2_3_1, &cond2_3_1_1, &bool_t};
T2Var3_2 t1_var2_3_2{&tmplCategory2_3, &code2_3_1, &cond2_3_2_1, &bool_t};
T2Var3_3 t1_var2_3_3{&tmplCategory2_3, &code2_3_2, &cond2_3_1_2, &bool_t};
T2Var3_4 t1_var2_3_4{&tmplCategory2_3, &code2_3_2, &cond2_3_2_2, &bool_t};
T2Var3_5 t1_var2_3_5{&tmplCategory2_3, &code2_3_3, &cond2_3_3_2, &bool_t};
T2Var3_6 t1_var2_3_6{&tmplCategory2_3, &code2_3_3, &cond2_3_1_1, &bool_t};
T2Var3_7 t1_var2_3_7{&tmplCategory2_3, &code2_3_3, &cond2_3_2_2, &bool_t};
T2Var3_8 t1_var2_3_8{&tmplCategory2_3, &code2_3_1, &cond2_3_3_1, &bool_t};
T2Var3_9 t1_var2_3_9{&tmplCategory2_3, &code2_3_2, &cond2_3_3_2, &bool_t};

CodeType code2_4_1{4, tmplCategory2_4};
ConditionType cond2_4_1_1{5, tmplCategory2_4};
ConditionType cond2_4_1_2{6, tmplCategory2_4};
CodeValueType code2_4_2{4};
ConditionValueType cond2_4_2_1{5};
ConditionValueType cond2_4_2_2{6};
CodeEnum2_4 code2_4_3 = CodeEnum2_4::value1;
ConditionEnum2_4 cond2_4_3_1 = ConditionEnum2_4::value1;
ConditionEnum2_4 cond2_4_3_2 = ConditionEnum2_4::value2;

T2Var4_1 t1_var2_4_1{&tmplCategory2_4, &code2_4_1, &cond2_4_1_1, &bool_t};
T2Var4_2 t1_var2_4_2{&tmplCategory2_4, &code2_4_1, &cond2_4_2_1, &bool_t};
T2Var4_3 t1_var2_4_3{&tmplCategory2_4, &code2_4_2, &cond2_4_1_2, &bool_t};
T2Var4_4 t1_var2_4_4{&tmplCategory2_4, &code2_4_2, &cond2_4_2_2, &bool_t};
T2Var4_5 t1_var2_4_5{&tmplCategory2_4, &code2_4_3, &cond2_4_3_2, &bool_t};
T2Var4_6 t1_var2_4_6{&tmplCategory2_4, &code2_4_3, &cond2_4_1_2, &bool_t};
T2Var4_7 t1_var2_4_7{&tmplCategory2_4, &code2_4_3, &cond2_4_2_1, &bool_t};
T2Var4_8 t1_var2_4_8{&tmplCategory2_4, &code2_4_1, &cond2_4_3_1, &bool_t};
T2Var4_9 t1_var2_4_9{&tmplCategory2_4, &code2_4_2, &cond2_4_3_2, &bool_t};

CodeType code2_5_1{4, tmplCategory2_5};
ConditionType cond2_5_1_1{5, tmplCategory2_5};
ConditionType cond2_5_1_2{6, tmplCategory2_5};
CodeValueType code2_5_2{4};
ConditionValueType cond2_5_2_1{5};
ConditionValueType cond2_5_2_2{6};
CodeEnum2_5 code2_5_3 = CodeEnum2_5::value1;
ConditionEnum2_5 cond2_5_3_1 = ConditionEnum2_5::value1;
ConditionEnum2_5 cond2_5_3_2 = ConditionEnum2_5::value2;

T2Var5_1 t1_var2_5_1{&tmplCategory2_5, &code2_5_1, &cond2_5_1_1, &bool_t};
T2Var5_2 t1_var2_5_2{&tmplCategory2_5, &code2_5_1, &cond2_5_2_1, &bool_t};
T2Var5_3 t1_var2_5_3{&tmplCategory2_5, &code2_5_2, &cond2_5_1_2, &bool_t};
T2Var5_4 t1_var2_5_4{&tmplCategory2_5, &code2_5_2, &cond2_5_2_2, &bool_t};
T2Var5_5 t1_var2_5_5{&tmplCategory2_5, &code2_5_3, &cond2_5_3_2, &bool_t};
T2Var5_6 t1_var2_5_6{&tmplCategory2_5, &code2_5_3, &cond2_5_1_2, &bool_t};
T2Var5_7 t1_var2_5_7{&tmplCategory2_5, &code2_5_3, &cond2_5_2_2, &bool_t};
T2Var5_8 t1_var2_5_8{&tmplCategory2_5, &code2_5_1, &cond2_5_3_1, &bool_t};
T2Var5_9 t1_var2_5_9{&tmplCategory2_5, &code2_5_2, &cond2_5_3_2, &bool_t};

CodeType code2_6_1{4, tmplCategory2_6};
ConditionType cond2_6_1_1{5, tmplCategory2_6};
ConditionType cond2_6_1_2{6, tmplCategory2_6};
CodeValueType code2_6_2{4};
ConditionValueType cond2_6_2_1{5};
ConditionValueType cond2_6_2_2{6};
CodeEnum2_6 code2_6_3 = CodeEnum2_6::value1;
ConditionEnum2_6 cond2_6_3_1 = ConditionEnum2_6::value1;
ConditionEnum2_6 cond2_6_3_2 = ConditionEnum2_6::value2;

T2Var6_1 t1_var2_6_1{&tmplCategory2_6, &code2_6_1, &cond2_6_1_1, &bool_t};
T2Var6_2 t1_var2_6_2{&tmplCategory2_6, &code2_6_1, &cond2_6_2_2, &bool_t};
T2Var6_3 t1_var2_6_3{&tmplCategory2_6, &code2_6_2, &cond2_6_1_1, &bool_t};
T2Var6_4 t1_var2_6_4{&tmplCategory2_6, &code2_6_2, &cond2_6_2_2, &bool_t};
T2Var6_5 t1_var2_6_5{&tmplCategory2_6, &code2_6_3, &cond2_6_3_2, &bool_t};
T2Var6_6 t1_var2_6_6{&tmplCategory2_6, &code2_6_3, &cond2_6_1_1, &bool_t};
T2Var6_7 t1_var2_6_7{&tmplCategory2_6, &code2_6_3, &cond2_6_2_2, &bool_t};
T2Var6_8 t1_var2_6_8{&tmplCategory2_6, &code2_6_1, &cond2_6_3_2, &bool_t};
T2Var6_9 t1_var2_6_9{&tmplCategory2_6, &code2_6_2, &cond2_6_3_2, &bool_t};

REGISTER_TEST(t2, new TestEquivalent<Case1, T2Var1_1,
    T2Var1_2, T2Var1_3, T2Var1_4, T2Var1_5, T2Var1_6, 
    T2Var1_7, T2Var1_8, T2Var1_9, T2Var2_1, T2Var2_2,
    T2Var2_3, T2Var2_4, T2Var2_5, T2Var2_6, T2Var2_7, 
    T2Var2_8, T2Var2_9, T2Var3_1, T2Var3_2, T2Var3_3,
    T2Var3_4, T2Var3_5, T2Var3_6, T2Var3_7, T2Var3_8, 
    T2Var3_9, T2Var4_1, T2Var4_2, T2Var4_3, T2Var4_4, 
    T2Var4_5, T2Var4_6, T2Var4_7, T2Var4_8, T2Var4_9,
    T2Var5_1, T2Var5_2, T2Var5_3, T2Var5_4, T2Var5_5, 
    T2Var5_6, T2Var5_7, T2Var5_8, T2Var5_9, T2Var6_1,
    T2Var6_2, T2Var6_3, T2Var6_4, T2Var6_5, T2Var6_6, 
    T2Var6_7, T2Var6_8, T2Var6_9>(t1_var2_1_1, t1_var2_1_2, t1_var2_1_3,
        t1_var2_1_4, t1_var2_1_5, t1_var2_1_6, t1_var2_1_7, t1_var2_1_8, 
        t1_var2_1_9, t1_var2_2_1, t1_var2_2_2, t1_var2_2_3, t1_var2_2_4, 
        t1_var2_2_5, t1_var2_2_6, t1_var2_2_7, t1_var2_2_8, t1_var2_2_9, 
        t1_var2_3_1, t1_var2_3_2, t1_var2_3_3, t1_var2_3_4, t1_var2_3_5, 
        t1_var2_3_6, t1_var2_3_7, t1_var2_3_8, t1_var2_3_9, t1_var2_4_1, 
        t1_var2_4_2, t1_var2_4_3, t1_var2_4_4, t1_var2_4_5, t1_var2_4_6, 
        t1_var2_4_7, t1_var2_4_8, t1_var2_4_9, t1_var2_5_1, t1_var2_5_2, 
        t1_var2_5_3, t1_var2_5_4, t1_var2_5_5, t1_var2_5_6, t1_var2_5_7, 
        t1_var2_5_8, t1_var2_5_9, t1_var2_6_1, t1_var2_6_2, t1_var2_6_3, 
        t1_var2_6_4, t1_var2_6_5, t1_var2_6_6, t1_var2_6_7, t1_var2_6_8, 
        t1_var2_6_9));

CodeType code3_1_1{4, tmplCategory3_1};
ConditionType cond3_1_1_1{5, tmplCategory3_1};
ConditionType cond3_1_1_2{6, tmplCategory3_1};
ConditionType cond3_1_1_3{7, tmplCategory3_1};
CodeValueType code3_1_2{4};
ConditionValueType cond3_1_2_1{5};
ConditionValueType cond3_1_2_2{6};
ConditionValueType cond3_1_2_3{7};
CodeEnum3_1 code3_1_3 = CodeEnum3_1::value1;
ConditionEnum3_1 cond3_1_3_1 = ConditionEnum3_1::value1;
ConditionEnum3_1 cond3_1_3_2 = ConditionEnum3_1::value2;
ConditionEnum3_1 cond3_1_3_3 = ConditionEnum3_1::value3;

T3Var1_1 t3_var1_1{&tmplCategory3_1, &code3_1_1, &cond3_1_1_1, &bool_t};
T3Var1_2 t3_var1_2{&tmplCategory3_1, &code3_1_1, &cond3_1_2_2, &bool_t};
T3Var1_3 t3_var1_3{&tmplCategory3_1, &code3_1_2, &cond3_1_1_3, &bool_t};
T3Var1_4 t3_var1_4{&tmplCategory3_1, &code3_1_2, &cond3_1_2_3, &bool_t};
T3Var1_5 t3_var1_5{&tmplCategory3_1, &code3_1_3, &cond3_1_3_3, &bool_t};
T3Var1_6 t3_var1_6{&tmplCategory3_1, &code3_1_3, &cond3_1_1_3, &bool_t};
T3Var1_7 t3_var1_7{&tmplCategory3_1, &code3_1_3, &cond3_1_2_2, &bool_t};
T3Var1_8 t3_var1_8{&tmplCategory3_1, &code3_1_1, &cond3_1_3_2, &bool_t};
T3Var1_9 t3_var1_9{&tmplCategory3_1, &code3_1_2, &cond3_1_3_3, &bool_t};

CodeType code3_2_1{4, tmplCategory3_2};
ConditionType cond3_2_1_1{5, tmplCategory3_2};
ConditionType cond3_2_1_2{6, tmplCategory3_2};
ConditionType cond3_2_1_3{7, tmplCategory3_2};
CodeValueType code3_2_2{4};
ConditionValueType cond3_2_2_1{5};
ConditionValueType cond3_2_2_2{6};
ConditionValueType cond3_2_2_3{7};
CodeEnum3_2 code3_2_3 = CodeEnum3_2::value1;
ConditionEnum3_2 cond3_2_3_1 = ConditionEnum3_2::value1;
ConditionEnum3_2 cond3_2_3_2 = ConditionEnum3_2::value2;
ConditionEnum3_2 cond3_2_3_3 = ConditionEnum3_2::value3;

T3Var2_1 t3_var2_1{&tmplCategory3_2, &code3_2_1, &cond3_2_1_1, &bool_t};
T3Var2_2 t3_var2_2{&tmplCategory3_2, &code3_2_1, &cond3_2_2_2, &bool_t};
T3Var2_3 t3_var2_3{&tmplCategory3_2, &code3_2_2, &cond3_2_1_3, &bool_t};
T3Var2_4 t3_var2_4{&tmplCategory3_2, &code3_2_2, &cond3_2_2_3, &bool_t};
T3Var2_5 t3_var2_5{&tmplCategory3_2, &code3_2_3, &cond3_2_3_3, &bool_t};
T3Var2_6 t3_var2_6{&tmplCategory3_2, &code3_2_3, &cond3_2_1_1, &bool_t};
T3Var2_7 t3_var2_7{&tmplCategory3_2, &code3_2_3, &cond3_2_2_3, &bool_t};
T3Var2_8 t3_var2_8{&tmplCategory3_2, &code3_2_1, &cond3_2_3_2, &bool_t};
T3Var2_9 t3_var2_9{&tmplCategory3_2, &code3_2_2, &cond3_2_3_3, &bool_t};

CodeType code3_3_1{4, tmplCategory3_3};
ConditionType cond3_3_1_1{5, tmplCategory3_3};
ConditionType cond3_3_1_2{6, tmplCategory3_3};
ConditionType cond3_3_1_3{7, tmplCategory3_3};
CodeValueType code3_3_2{4};
ConditionValueType cond3_3_2_1{5};
ConditionValueType cond3_3_2_2{6};
ConditionValueType cond3_3_2_3{7};
CodeEnum3_3 code3_3_3 = CodeEnum3_3::value1;
ConditionEnum3_3 cond3_3_3_1 = ConditionEnum3_3::value1;
ConditionEnum3_3 cond3_3_3_2 = ConditionEnum3_3::value2;
ConditionEnum3_3 cond3_3_3_3 = ConditionEnum3_3::value3;

T3Var3_1 t3_var3_1{&tmplCategory3_3, &code3_3_1, &cond3_3_1_1, &bool_t};
T3Var3_2 t3_var3_2{&tmplCategory3_3, &code3_3_1, &cond3_3_2_1, &bool_t};
T3Var3_3 t3_var3_3{&tmplCategory3_3, &code3_3_2, &cond3_3_1_2, &bool_t};
T3Var3_4 t3_var3_4{&tmplCategory3_3, &code3_3_2, &cond3_3_2_3, &bool_t};
T3Var3_5 t3_var3_5{&tmplCategory3_3, &code3_3_3, &cond3_3_3_3, &bool_t};
T3Var3_6 t3_var3_6{&tmplCategory3_3, &code3_3_3, &cond3_3_1_2, &bool_t};
T3Var3_7 t3_var3_7{&tmplCategory3_3, &code3_3_3, &cond3_3_2_3, &bool_t};
T3Var3_8 t3_var3_8{&tmplCategory3_3, &code3_3_1, &cond3_3_3_1, &bool_t};
T3Var3_9 t3_var3_9{&tmplCategory3_3, &code3_3_2, &cond3_3_3_3, &bool_t};

CodeType code3_4_1{4, tmplCategory3_4};
ConditionType cond3_4_1_1{5, tmplCategory3_4};
ConditionType cond3_4_1_2{6, tmplCategory3_4};
ConditionType cond3_4_1_3{7, tmplCategory3_4};
CodeValueType code3_4_2{4};
ConditionValueType cond3_4_2_1{5};
ConditionValueType cond3_4_2_2{6};
ConditionValueType cond3_4_2_3{7};
CodeEnum3_4 code3_4_3 = CodeEnum3_4::value1;
ConditionEnum3_4 cond3_4_3_1 = ConditionEnum3_4::value1;
ConditionEnum3_4 cond3_4_3_2 = ConditionEnum3_4::value2;
ConditionEnum3_4 cond3_4_3_3 = ConditionEnum3_4::value3;

T3Var4_1 t3_var4_1{&tmplCategory3_4, &code3_4_1, &cond3_4_1_1, &bool_t};
T3Var4_2 t3_var4_2{&tmplCategory3_4, &code3_4_1, &cond3_4_2_1, &bool_t};
T3Var4_3 t3_var4_3{&tmplCategory3_4, &code3_4_2, &cond3_4_1_2, &bool_t};
T3Var4_4 t3_var4_4{&tmplCategory3_4, &code3_4_2, &cond3_4_2_3, &bool_t};
T3Var4_5 t3_var4_5{&tmplCategory3_4, &code3_4_3, &cond3_4_3_3, &bool_t};
T3Var4_6 t3_var4_6{&tmplCategory3_4, &code3_4_3, &cond3_4_1_2, &bool_t};
T3Var4_7 t3_var4_7{&tmplCategory3_4, &code3_4_3, &cond3_4_2_3, &bool_t};
T3Var4_8 t3_var4_8{&tmplCategory3_4, &code3_4_1, &cond3_4_3_1, &bool_t};
T3Var4_9 t3_var4_9{&tmplCategory3_4, &code3_4_2, &cond3_4_3_3, &bool_t};

REGISTER_TEST(t3, new TestEquivalent<Case1, T3Var1_1, T3Var1_2,
    T3Var1_3, T3Var1_4, T3Var1_5, T3Var1_6, T3Var1_7, T3Var1_8, 
    T3Var1_9, T3Var2_1, T3Var2_2, T3Var2_3, T3Var2_4, T3Var2_5, 
    T3Var2_6, T3Var2_7, T3Var2_8, T3Var2_9, T3Var3_1, T3Var3_2, 
    T3Var3_3, T3Var3_4, T3Var3_5, T3Var3_6, T3Var3_7, T3Var3_8,
    T3Var3_9, T3Var4_1, T3Var4_2, T3Var4_3, T3Var4_4, T3Var4_5, 
    T3Var4_6, T3Var4_7, T3Var4_8, T3Var4_9>(t3_var1_1, 
        t3_var1_2, t3_var1_3, t3_var1_4, t3_var1_5, t3_var1_6, 
        t3_var1_7, t3_var1_8, t3_var1_9, t3_var2_1, t3_var2_2, 
        t3_var2_3, t3_var2_4, t3_var2_5, t3_var2_6, t3_var2_7, 
        t3_var2_8, t3_var2_9, t3_var3_1, t3_var3_2, t3_var3_3, 
        t3_var3_4, t3_var3_5, t3_var3_6, t3_var3_7, t3_var3_8, 
        t3_var3_9, t3_var4_1, t3_var4_2, t3_var4_3, t3_var4_4, 
        t3_var4_5, t3_var4_6, t3_var4_7, t3_var4_8, t3_var4_9));

CodeType code4_1_1{4, tmplCategory4_1};
ConditionType cond4_1_1_1{5, tmplCategory4_1};
ConditionType cond4_1_1_2{6, tmplCategory4_1};
ConditionType cond4_1_1_3{7, tmplCategory4_1};
ConditionType cond4_1_1_4{8, tmplCategory4_1};
CodeValueType code4_1_2{4};
ConditionValueType cond4_1_2_1{5};
ConditionValueType cond4_1_2_2{6};
ConditionValueType cond4_1_2_3{7};
ConditionValueType cond4_1_2_4{8};
CodeEnum4_1 code4_1_3 = CodeEnum4_1::value1;
ConditionEnum4_1 cond4_1_3_1 = ConditionEnum4_1::value1;
ConditionEnum4_1 cond4_1_3_2 = ConditionEnum4_1::value2;
ConditionEnum4_1 cond4_1_3_3 = ConditionEnum4_1::value3;
ConditionEnum4_1 cond4_1_3_4 = ConditionEnum4_1::value4;

T4Var1_1 t4_var1_1{&tmplCategory4_1, &code4_1_1, &cond4_1_1_1, &bool_t};
T4Var1_2 t4_var1_2{&tmplCategory4_1, &code4_1_1, &cond4_1_2_2, &bool_t};
T4Var1_3 t4_var1_3{&tmplCategory4_1, &code4_1_2, &cond4_1_1_3, &bool_t};
T4Var1_4 t4_var1_4{&tmplCategory4_1, &code4_1_2, &cond4_1_2_4, &bool_t};
T4Var1_5 t4_var1_5{&tmplCategory4_1, &code4_1_3, &cond4_1_3_4, &bool_t};
T4Var1_6 t4_var1_6{&tmplCategory4_1, &code4_1_3, &cond4_1_1_3, &bool_t};
T4Var1_7 t4_var1_7{&tmplCategory4_1, &code4_1_3, &cond4_1_2_4, &bool_t};
T4Var1_8 t4_var1_8{&tmplCategory4_1, &code4_1_1, &cond4_1_3_2, &bool_t};
T4Var1_9 t4_var1_9{&tmplCategory4_1, &code4_1_2, &cond4_1_3_4, &bool_t};

REGISTER_TEST(t4, new TestEquivalent<Case1, T4Var1_1, T4Var1_2, T4Var1_3, 
    T4Var1_4, T4Var1_5, T4Var1_6, T4Var1_7, T4Var1_8, T4Var1_9>(t4_var1_1, 
        t4_var1_2, t4_var1_3, t4_var1_4, t4_var1_5, t4_var1_6, t4_var1_7, 
        t4_var1_8, t4_var1_9));

CodeType code5_1{4, tmplCategory5};
ConditionType cond5_1{4, tmplCategory5};
CodeValueType code5_2{4};
ConditionValueType cond5_2{4};

T5Var1 t5_var1{&tmplCategory5, &code5_1, &cond5_1, &bool_f};
T5Var2 t5_var2{&tmplCategory5, &code5_1, &cond5_2, &bool_f};
T5Var3 t5_var3{&tmplCategory5, &code5_2, &cond5_1, &bool_f};
T5Var4 t5_var4{&tmplCategory5, &code5_2, &cond5_2, &bool_f};

REGISTER_TEST(t5, new TestEquivalent<Case1, T5Var1, T5Var2, T5Var3, 
    T5Var4>(t5_var1, t5_var2, t5_var3, t5_var4));

CodeType code6_1_1{4, tmplCategory6_1};
ConditionType cond6_1_1_1{5, tmplCategory6_1};
ConditionType cond6_1_1_2{6, tmplCategory6_1};
ConditionType cond6_1_1_3{7, tmplCategory6_1};
ConditionType cond6_1_1_4{8, tmplCategory6_1};
ConditionType cond6_1_1_5{9, tmplCategory6_1};
CodeValueType code6_1_2{4};
ConditionValueType cond6_1_2_1{5};
ConditionValueType cond6_1_2_2{6};
ConditionValueType cond6_1_2_3{7};
ConditionValueType cond6_1_2_4{8};
ConditionValueType cond6_1_2_5{9};
CodeEnum6_1 code6_1_3 = CodeEnum6_1::value1;
ConditionEnum6_1 cond6_1_3_1 = ConditionEnum6_1::value1;
ConditionEnum6_1 cond6_1_3_2 = ConditionEnum6_1::value2;
ConditionEnum6_1 cond6_1_3_3 = ConditionEnum6_1::value3;
ConditionEnum6_1 cond6_1_3_4 = ConditionEnum6_1::value4;
ConditionEnum6_1 cond6_1_3_5 = ConditionEnum6_1::value5;

T6Var1_1 t6_var1_1{&tmplCategory6_1, &code6_1_3, &cond6_1_3_1, &bool_t};
T6Var1_2 t6_var1_2{&tmplCategory6_1, &code6_1_3, &cond6_1_1_2, &bool_t};
T6Var1_3 t6_var1_3{&tmplCategory6_1, &code6_1_3, &cond6_1_2_3, &bool_t};
T6Var1_4 t6_var1_4{&tmplCategory6_1, &code6_1_1, &cond6_1_3_4, &bool_t};
T6Var1_5 t6_var1_5{&tmplCategory6_1, &code6_1_2, &cond6_1_3_5, &bool_t};

CodeType code6_2_1{4, tmplCategory6_2};
ConditionType cond6_2_1_1{5, tmplCategory6_2};
ConditionType cond6_2_1_2{6, tmplCategory6_2};
CodeValueType code6_2_2{4};
ConditionValueType cond6_2_2_1{5};
ConditionValueType cond6_2_2_2{6};
CodeEnum6_2 code6_2_3 = CodeEnum6_2::value1;
ConditionEnum6_2 cond6_2_3_1 = ConditionEnum6_2::value1;
ConditionEnum6_2 cond6_2_3_2 = ConditionEnum6_2::value2;

T6Var2_1 t6_var2_1{&tmplCategory6_2, &code6_2_3, &cond6_2_3_1, &bool_t};
T6Var2_2 t6_var2_2{&tmplCategory6_2, &code6_2_3, &cond6_2_1_1, &bool_t};
T6Var2_3 t6_var2_3{&tmplCategory6_2, &code6_2_3, &cond6_2_2_1, &bool_t};
T6Var2_4 t6_var2_4{&tmplCategory6_2, &code6_2_1, &cond6_2_3_2, &bool_t};
T6Var2_5 t6_var2_5{&tmplCategory6_2, &code6_2_2, &cond6_2_3_2, &bool_t};

CodeType code6_3_1{4, tmplCategory6_3};
ConditionType cond6_3_1_1{5, tmplCategory6_3};
ConditionType cond6_3_1_2{6, tmplCategory6_3};
CodeValueType code6_3_2{4};
ConditionValueType cond6_3_2_1{5};
ConditionValueType cond6_3_2_2{6};
CodeEnum6_3 code6_3_3 = CodeEnum6_3::value1;
ConditionEnum6_3 cond6_3_3_1 = ConditionEnum6_3::value1;
ConditionEnum6_3 cond6_3_3_2 = ConditionEnum6_3::value2;

T6Var3_1 t6_var3_1{&tmplCategory6_3, &code6_3_3, &cond6_3_3_1, &bool_t};
T6Var3_2 t6_var3_2{&tmplCategory6_3, &code6_3_3, &cond6_3_1_1, &bool_t};
T6Var3_3 t6_var3_3{&tmplCategory6_3, &code6_3_3, &cond6_3_2_1, &bool_t};
T6Var3_4 t6_var3_4{&tmplCategory6_3, &code6_3_1, &cond6_3_3_2, &bool_t};
T6Var3_5 t6_var3_5{&tmplCategory6_3, &code6_3_2, &cond6_3_3_2, &bool_t};

CodeType code6_4_1{4, tmplCategory6_4};
ConditionType cond6_4_1_1{5, tmplCategory6_4};
CodeValueType code6_4_2{4};
ConditionValueType cond6_4_2_1{5};
CodeEnum6_4 code6_4_3 = CodeEnum6_4::value1;
ConditionEnum6_4 cond6_4_3_1 = ConditionEnum6_4::value1;

T6Var4_1 t6_var4_1{&tmplCategory6_4, &code6_4_3, &cond6_4_3_1, &bool_t};
T6Var4_2 t6_var4_2{&tmplCategory6_4, &code6_4_1, &cond6_4_3_1, &bool_t};
T6Var4_3 t6_var4_3{&tmplCategory6_4, &code6_4_2, &cond6_4_3_1, &bool_t};

CodeType code6_5_1{4, tmplCategory6_5};
ConditionType cond6_5_1_1{5, tmplCategory6_5};
CodeValueType code6_5_2{4};
ConditionValueType cond6_5_2_1{5};
CodeEnum6_5 code6_5_3 = CodeEnum6_5::value1;
ConditionEnum6_5 cond6_5_3_1 = ConditionEnum6_5::value1;

T6Var5_1 t6_var5_1{&tmplCategory6_5, &code6_5_3, &cond6_5_3_1, &bool_t};
T6Var5_2 t6_var5_2{&tmplCategory6_5, &code6_5_1, &cond6_5_3_1, &bool_t};
T6Var5_3 t6_var5_3{&tmplCategory6_5, &code6_5_2, &cond6_5_3_1, &bool_t};

REGISTER_TEST(t6, new TestEquivalent<Case1, T6Var1_1, T6Var1_2, T6Var1_3, 
    T6Var1_4, T6Var1_5, T6Var2_1, T6Var2_2, T6Var2_3, T6Var2_4, T6Var2_5, 
    T6Var3_1, T6Var3_2, T6Var3_3, T6Var3_4, T6Var3_5, T6Var4_1, T6Var4_2,
    T6Var4_3, T6Var5_1, T6Var5_2, T6Var5_3>(t6_var1_1, t6_var1_2, t6_var1_3, 
        t6_var1_4, t6_var1_5, t6_var2_1, t6_var2_2, t6_var2_3, t6_var2_4, 
        t6_var2_5, t6_var3_1, t6_var3_2, t6_var3_3, t6_var3_4, t6_var3_5, 
        t6_var4_1, t6_var4_2, t6_var4_3, t6_var5_1, t6_var5_2, t6_var5_3));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1_1", CategoryTrait1_1);
BASIC_TEST_TYPE_NAME("CategoryTrait1_2", CategoryTrait1_2);
BASIC_TEST_TYPE_NAME("CategoryTrait1_3", CategoryTrait1_3);
BASIC_TEST_TYPE_NAME("CategoryTrait1_4", CategoryTrait1_4);
BASIC_TEST_TYPE_NAME("CategoryTrait2_1", CategoryTrait2_1);
BASIC_TEST_TYPE_NAME("CategoryTrait2_2", CategoryTrait2_2);
BASIC_TEST_TYPE_NAME("CategoryTrait2_3", CategoryTrait2_3);
BASIC_TEST_TYPE_NAME("CategoryTrait2_4", CategoryTrait2_4);
BASIC_TEST_TYPE_NAME("CategoryTrait2_5", CategoryTrait2_5);
BASIC_TEST_TYPE_NAME("CategoryTrait2_6", CategoryTrait2_6);
BASIC_TEST_TYPE_NAME("CategoryTrait3_1", CategoryTrait3_1);
BASIC_TEST_TYPE_NAME("CategoryTrait3_2", CategoryTrait3_2);
BASIC_TEST_TYPE_NAME("CategoryTrait3_3", CategoryTrait3_3);
BASIC_TEST_TYPE_NAME("CategoryTrait3_4", CategoryTrait3_4);
BASIC_TEST_TYPE_NAME("CategoryTrait4_1", CategoryTrait4_1);
BASIC_TEST_TYPE_NAME("CategoryTrait5", CategoryTrait5);
BASIC_TEST_TYPE_NAME("CategoryTrait6_1", CategoryTrait6_1);
BASIC_TEST_TYPE_NAME("CategoryTrait6_2", CategoryTrait6_2);
BASIC_TEST_TYPE_NAME("CategoryTrait6_3", CategoryTrait6_3);
BASIC_TEST_TYPE_NAME("CategoryTrait6_4", CategoryTrait6_4);
BASIC_TEST_TYPE_NAME("CategoryTrait6_5", CategoryTrait6_5);

BASIC_TEST_TYPE_NAME("CodeEnum1_1", CodeEnum1_1);
BASIC_TEST_TYPE_NAME("ConditionEnum1_1", ConditionEnum1_1);
BASIC_TEST_TYPE_NAME("CodeEnum1_2", CodeEnum1_2);
BASIC_TEST_TYPE_NAME("ConditionEnum1_2", ConditionEnum1_2);
BASIC_TEST_TYPE_NAME("CodeEnum1_3", CodeEnum1_3);
BASIC_TEST_TYPE_NAME("ConditionEnum1_3", ConditionEnum1_3);
BASIC_TEST_TYPE_NAME("CodeEnum1_4", CodeEnum1_4);
BASIC_TEST_TYPE_NAME("ConditionEnum1_4", ConditionEnum1_4);
BASIC_TEST_TYPE_NAME("CodeEnum2_1", CodeEnum2_1);
BASIC_TEST_TYPE_NAME("ConditionEnum2_1", ConditionEnum2_1);
BASIC_TEST_TYPE_NAME("CodeEnum2_2", CodeEnum2_2);
BASIC_TEST_TYPE_NAME("ConditionEnum2_2", ConditionEnum2_2);
BASIC_TEST_TYPE_NAME("CodeEnum2_3", CodeEnum2_3);
BASIC_TEST_TYPE_NAME("ConditionEnum2_3", ConditionEnum2_3);
BASIC_TEST_TYPE_NAME("CodeEnum2_4", CodeEnum2_4);
BASIC_TEST_TYPE_NAME("ConditionEnum2_4", ConditionEnum2_4);
BASIC_TEST_TYPE_NAME("CodeEnum2_5", CodeEnum2_5);
BASIC_TEST_TYPE_NAME("ConditionEnum2_5", ConditionEnum2_5);
BASIC_TEST_TYPE_NAME("CodeEnum2_6", CodeEnum2_6);
BASIC_TEST_TYPE_NAME("ConditionEnum2_6", ConditionEnum2_6);
BASIC_TEST_TYPE_NAME("CodeEnum3_1", CodeEnum3_1);
BASIC_TEST_TYPE_NAME("ConditionEnum3_1", ConditionEnum3_1);
BASIC_TEST_TYPE_NAME("CodeEnum3_2", CodeEnum3_2);
BASIC_TEST_TYPE_NAME("ConditionEnum3_2", ConditionEnum3_2);
BASIC_TEST_TYPE_NAME("CodeEnum3_3", CodeEnum3_3);
BASIC_TEST_TYPE_NAME("ConditionEnum3_3", ConditionEnum3_3);
BASIC_TEST_TYPE_NAME("CodeEnum3_4", CodeEnum3_4);
BASIC_TEST_TYPE_NAME("ConditionEnum3_4", ConditionEnum3_4);
BASIC_TEST_TYPE_NAME("CodeEnum4_1", CodeEnum4_1);
BASIC_TEST_TYPE_NAME("ConditionEnum4_1", ConditionEnum4_1);
BASIC_TEST_TYPE_NAME("CodeEnum6_1", CodeEnum6_1);
BASIC_TEST_TYPE_NAME("ConditionEnum6_1", ConditionEnum6_1);
BASIC_TEST_TYPE_NAME("CodeEnum6_2", CodeEnum6_2);
BASIC_TEST_TYPE_NAME("ConditionEnum6_2", ConditionEnum6_2);
BASIC_TEST_TYPE_NAME("CodeEnum6_3", CodeEnum6_3);
BASIC_TEST_TYPE_NAME("ConditionEnum6_3", ConditionEnum6_3);
BASIC_TEST_TYPE_NAME("CodeEnum6_4", CodeEnum6_4);
BASIC_TEST_TYPE_NAME("ConditionEnum6_4", ConditionEnum6_4);
BASIC_TEST_TYPE_NAME("CodeEnum6_5", CodeEnum6_5);
BASIC_TEST_TYPE_NAME("ConditionEnum6_5", ConditionEnum6_5);

BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);

BASIC_TEST_TYPE_NAME("bool", bool);

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

template<>
struct basic::err::sys::make::Category<CodeEnum1_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum1_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum1_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum1_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum1_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum1_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum1_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum1_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait1_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum2_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum2_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum2_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum2_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2_5>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_5>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum2_5>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_5>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum2_6>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_6>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum2_6>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait2_6>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum3_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum3_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum3_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum3_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum3_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum3_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum3_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum3_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait3_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum4_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait4_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum4_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait4_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum6_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum6_1>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_1>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum6_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum6_2>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_2>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum6_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum6_3>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_3>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum6_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum6_4>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_4>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<CodeEnum6_5>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_5>::
            GetInstance();
    }
};

template<>
struct basic::err::sys::make::Category<ConditionEnum6_5>
{
    Category() = delete;
    static const basic::err::sys::Category & GetInstance() noexcept
    {
        return basic::err::sys::tmpl::Category<CategoryTrait6_5>::
            GetInstance();
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::Category<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::Category<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TCategoryTrait>
struct basic::test::out::Argument<const basic::err::sys::tmpl::
    Category<TCategoryTrait> *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(const basic::err::sys::tmpl::
        Category<TCategoryTrait> * & categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", categ->Value()));
        return *ms_cstr;
    }
    static const char * Value(const basic::err::sys::tmpl::
        Category<TCategoryTrait> * && categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", categ->Value()));
        return *ms_cstr;
    }
};

template<typename TCategoryTrait>
basic::test::CString<char> basic::test::out::Argument<const basic::err::
    sys::tmpl::Category<TCategoryTrait> *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeValueType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeValueType * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
    static const char * Value(CodeValueType * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeValueType *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeType * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(CodeType * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeType *>::ms_cstr;

struct Void1 {};

template<>
struct basic::test::out::Argument<typename std::conditional<std::is_same<
    ConditionValueType, CodeValueType>::value, Void1, 
    ConditionValueType>::type *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionValueType * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
    static const char * Value(ConditionValueType * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<typename std::conditional<std::is_same<ConditionValueType, 
    CodeValueType>::value, Void1, ConditionValueType>::type *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionType * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", cond->Value()));
        return *ms_cstr;
    }
    static const char * Value(ConditionType * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", cond->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionType *>::ms_cstr;


template<>
struct basic::test::out::Argument<bool *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(bool * & b)
    {
        return *b ? "true" : "false"; 
    }
    static const char * Value(bool * && b)
    {
        return *b ? "true" : "false";
    }
};

template<>
struct basic::test::out::Argument<CodeEnum1_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum1_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum1_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum1_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum1_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum1_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum1_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum1_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum1_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum1_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum1_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum1_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum1_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum1_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum1_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum1_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum1_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum1_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum1_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum1_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum1_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum1_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum1_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum1_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum2_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum2_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum2_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum2_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum2_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum2_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum2_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum2_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum2_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum2_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum2_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum2_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum2_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum2_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum2_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum2_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2_5 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2_5 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2_5 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2_5 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum2_5 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum2_5 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum2_5 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum2_5 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum2_6 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum2_6 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum2_6 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum2_6 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum2_6 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum2_6 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum2_6 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum2_6 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum3_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum3_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum3_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum3_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum3_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum3_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum3_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum3_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum3_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum3_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum3_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum3_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum3_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum3_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum3_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum3_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum3_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum3_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum3_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum3_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum3_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum3_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum3_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum3_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum3_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum3_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum3_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum3_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum3_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum3_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum3_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum3_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum4_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum4_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum4_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum4_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum4_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum4_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum4_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum4_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum6_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum6_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum6_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum6_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum6_1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum6_1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum6_1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum6_1 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum6_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum6_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum6_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum6_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum6_2 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum6_2 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum6_2 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum6_2 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum6_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum6_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum6_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum6_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum6_3 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum6_3 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum6_3 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum6_3 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum6_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum6_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum6_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum6_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum6_4 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum6_4 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum6_4 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum6_4 *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum6_5 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum6_5 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum6_5 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (CodeValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum6_5 *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionEnum6_5 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum6_5 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum6_5 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (ConditionValueType)*code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum6_5 *>::ms_cstr;

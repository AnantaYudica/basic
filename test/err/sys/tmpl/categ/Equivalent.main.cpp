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

struct CategoryTrait1_1
{
    CategoryTrait1_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct CategoryTrait1_2
{
    CategoryTrait1_2() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    CategoryValueType Value() const
    {
        return 12;
    }
};

struct CategoryTrait1_3
{
    CategoryTrait1_3() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    CategoryValueType Value() const
    {
        return 13;
    }
};

struct CategoryTrait1_4
{
    CategoryTrait1_4() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 14;
    }
};


struct CategoryTrait2_1
{
    CategoryTrait2_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    CategoryValueType Value() const
    {
        return 21;
    }
};

struct CategoryTrait2_2
{
    CategoryTrait2_2() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    CategoryValueType Value() const
    {
        return 22;
    }
};

struct CategoryTrait2_3
{
    CategoryTrait2_3() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 23;
    }
};

struct CategoryTrait2_4
{
    CategoryTrait2_4() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    CategoryValueType Value() const
    {
        return 24;
    }
};

struct CategoryTrait2_5
{
    CategoryTrait2_5() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 25;
    }
};

struct CategoryTrait2_6
{
    CategoryTrait2_6() = default;
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 26;
    }
};


struct CategoryTrait3_1
{
    CategoryTrait3_1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    CategoryValueType Value() const
    {
        return 31;
    }
};

struct CategoryTrait3_2
{
    CategoryTrait3_2() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 32;
    }
};

struct CategoryTrait3_3
{
    CategoryTrait3_3() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 33;
    }
};

struct CategoryTrait3_4
{
    CategoryTrait3_4() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 34;
    }
};

struct CategoryTrait4
{
    CategoryTrait4() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionType & cond) const
    {
        return code.Value() == cond.Value();
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionValueType & cond) const
    {
        return code == cond;
    }
    CategoryValueType Value() const
    {
        return 4;
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

template<typename TValue>
int PtrToInteger(TValue * && ptr)
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
    CodeType, ConditionType> T1Var1_1_1;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeType, ConditionValueType> T1Var1_1_2;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeValueType, ConditionType> T1Var1_1_3;
typedef VariableTestEquivalent<CategoryTrait1_1, 
    CodeValueType, ConditionValueType> T1Var1_1_4;

typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeType, ConditionType> T1Var1_2_1;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeType, ConditionValueType> T1Var1_2_2;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeValueType, ConditionType> T1Var1_2_3;
typedef VariableTestEquivalent<CategoryTrait1_2, 
    CodeValueType, ConditionValueType> T1Var1_2_4;

typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeType, ConditionType> T1Var1_3_1;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeType, ConditionValueType> T1Var1_3_2;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeValueType, ConditionType> T1Var1_3_3;
typedef VariableTestEquivalent<CategoryTrait1_3, 
    CodeValueType, ConditionValueType> T1Var1_3_4;

typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeType, ConditionType> T1Var1_4_1;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeType, ConditionValueType> T1Var1_4_2;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeValueType, ConditionType> T1Var1_4_3;
typedef VariableTestEquivalent<CategoryTrait1_4, 
    CodeValueType, ConditionValueType> T1Var1_4_4;

typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeType, ConditionType> T1Var2_1_1;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeType, ConditionValueType> T1Var2_1_2;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeValueType, ConditionType> T1Var2_1_3;
typedef VariableTestEquivalent<CategoryTrait2_1, 
    CodeValueType, ConditionValueType> T1Var2_1_4;

typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeType, ConditionType> T1Var2_2_1;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeType, ConditionValueType> T1Var2_2_2;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeValueType, ConditionType> T1Var2_2_3;
typedef VariableTestEquivalent<CategoryTrait2_2, 
    CodeValueType, ConditionValueType> T1Var2_2_4;

typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeType, ConditionType> T1Var2_3_1;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeType, ConditionValueType> T1Var2_3_2;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeValueType, ConditionType> T1Var2_3_3;
typedef VariableTestEquivalent<CategoryTrait2_3, 
    CodeValueType, ConditionValueType> T1Var2_3_4;

typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeType, ConditionType> T1Var2_4_1;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeType, ConditionValueType> T1Var2_4_2;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeValueType, ConditionType> T1Var2_4_3;
typedef VariableTestEquivalent<CategoryTrait2_4, 
    CodeValueType, ConditionValueType> T1Var2_4_4;

typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeType, ConditionType> T1Var2_5_1;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeType, ConditionValueType> T1Var2_5_2;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeValueType, ConditionType> T1Var2_5_3;
typedef VariableTestEquivalent<CategoryTrait2_5, 
    CodeValueType, ConditionValueType> T1Var2_5_4;
    
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeType, ConditionType> T1Var2_6_1;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeType, ConditionValueType> T1Var2_6_2;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeValueType, ConditionType> T1Var2_6_3;
typedef VariableTestEquivalent<CategoryTrait2_6, 
    CodeValueType, ConditionValueType> T1Var2_6_4;

typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeType, ConditionType> T1Var3_1_1;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeType, ConditionValueType> T1Var3_1_2;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeValueType, ConditionType> T1Var3_1_3;
typedef VariableTestEquivalent<CategoryTrait3_1, 
    CodeValueType, ConditionValueType> T1Var3_1_4;

typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeType, ConditionType> T1Var3_2_1;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeType, ConditionValueType> T1Var3_2_2;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeValueType, ConditionType> T1Var3_2_3;
typedef VariableTestEquivalent<CategoryTrait3_2, 
    CodeValueType, ConditionValueType> T1Var3_2_4;

typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeType, ConditionType> T1Var3_3_1;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeType, ConditionValueType> T1Var3_3_2;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeValueType, ConditionType> T1Var3_3_3;
typedef VariableTestEquivalent<CategoryTrait3_3, 
    CodeValueType, ConditionValueType> T1Var3_3_4;

typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeType, ConditionType> T1Var3_4_1;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeType, ConditionValueType> T1Var3_4_2;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeValueType, ConditionType> T1Var3_4_3;
typedef VariableTestEquivalent<CategoryTrait3_4, 
    CodeValueType, ConditionValueType> T1Var3_4_4;

typedef VariableTestEquivalent<CategoryTrait4, 
    CodeType, ConditionType> T1Var4_1;
typedef VariableTestEquivalent<CategoryTrait4, 
    CodeType, ConditionValueType> T1Var4_2;
typedef VariableTestEquivalent<CategoryTrait4, 
    CodeValueType, ConditionType> T1Var4_3;
typedef VariableTestEquivalent<CategoryTrait4, 
    CodeValueType, ConditionValueType> T1Var4_4;

typedef VariableTestEquivalent<CategoryTrait5, 
    CodeType, ConditionType> T1Var5_1;
typedef VariableTestEquivalent<CategoryTrait5, 
    CodeType, ConditionValueType> T1Var5_2;
typedef VariableTestEquivalent<CategoryTrait5, 
    CodeValueType, ConditionType> T1Var5_3;
typedef VariableTestEquivalent<CategoryTrait5, 
    CodeValueType, ConditionValueType> T1Var5_4;

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
auto & tmplCategory4 = basic::err::sys::tmpl::
    Category<CategoryTrait4>::GetInstance();
auto & tmplCategory5 = basic::err::sys::tmpl::
    Category<CategoryTrait5>::GetInstance();


bool bool_true{true};
bool bool_false{false};
CodeValueType code_val{4};
ConditionValueType cond_val{4};

CodeType code1_1{code_val, tmplCategory1_1};
ConditionType cond1_1{cond_val, tmplCategory1_1};

T1Var1_1_1 t1_var1_1_1{&tmplCategory1_1, &code1_1, &cond1_1, &bool_true};
T1Var1_1_2 t1_var1_1_2{&tmplCategory1_1, &code1_1, &cond_val, &bool_true};
T1Var1_1_3 t1_var1_1_3{&tmplCategory1_1, &code_val, &cond1_1, &bool_true};
T1Var1_1_4 t1_var1_1_4{&tmplCategory1_1, &code_val, &cond_val, &bool_true};

CodeType code1_2{code_val, tmplCategory1_2};
ConditionType cond1_2{cond_val, tmplCategory1_2};

T1Var1_2_1 t1_var1_2_1{&tmplCategory1_2, &code1_2, &cond1_2, &bool_true};
T1Var1_2_2 t1_var1_2_2{&tmplCategory1_2, &code1_2, &cond_val, &bool_true};
T1Var1_2_3 t1_var1_2_3{&tmplCategory1_2, &code_val, &cond1_2, &bool_true};
T1Var1_2_4 t1_var1_2_4{&tmplCategory1_2, &code_val, &cond_val, &bool_true};

CodeType code1_3{code_val, tmplCategory1_3};
ConditionType cond1_3{cond_val, tmplCategory1_3};

T1Var1_3_1 t1_var1_3_1{&tmplCategory1_3, &code1_3, &cond1_3, &bool_true};
T1Var1_3_2 t1_var1_3_2{&tmplCategory1_3, &code1_3, &cond_val, &bool_true};
T1Var1_3_3 t1_var1_3_3{&tmplCategory1_3, &code_val, &cond1_3, &bool_true};
T1Var1_3_4 t1_var1_3_4{&tmplCategory1_3, &code_val, &cond_val, &bool_true};

CodeType code1_4{code_val, tmplCategory1_4};
ConditionType cond1_4{cond_val, tmplCategory1_4};

T1Var1_4_1 t1_var1_4_1{&tmplCategory1_4, &code1_4, &cond1_4, &bool_true};
T1Var1_4_2 t1_var1_4_2{&tmplCategory1_4, &code1_4, &cond_val, &bool_true};
T1Var1_4_3 t1_var1_4_3{&tmplCategory1_4, &code_val, &cond1_4, &bool_true};
T1Var1_4_4 t1_var1_4_4{&tmplCategory1_4, &code_val, &cond_val, &bool_true};

CodeType code2_1{code_val, tmplCategory2_1};
ConditionType cond2_1{cond_val, tmplCategory2_1};

T1Var2_1_1 t1_var2_1_1{&tmplCategory2_1, &code2_1, &cond2_1, &bool_true};
T1Var2_1_2 t1_var2_1_2{&tmplCategory2_1, &code2_1, &cond_val, &bool_true};
T1Var2_1_3 t1_var2_1_3{&tmplCategory2_1, &code_val, &cond2_1, &bool_true};
T1Var2_1_4 t1_var2_1_4{&tmplCategory2_1, &code_val, &cond_val, &bool_true};

CodeType code2_2{code_val, tmplCategory2_2};
ConditionType cond2_2{cond_val, tmplCategory2_2};

T1Var2_2_1 t1_var2_2_1{&tmplCategory2_2, &code2_2, &cond2_2, &bool_true};
T1Var2_2_2 t1_var2_2_2{&tmplCategory2_2, &code2_2, &cond_val, &bool_true};
T1Var2_2_3 t1_var2_2_3{&tmplCategory2_2, &code_val, &cond2_2, &bool_true};
T1Var2_2_4 t1_var2_2_4{&tmplCategory2_2, &code_val, &cond_val, &bool_true};

CodeType code2_3{code_val, tmplCategory2_3};
ConditionType cond2_3{cond_val, tmplCategory2_3};

T1Var2_3_1 t1_var2_3_1{&tmplCategory2_3, &code2_3, &cond2_3, &bool_true};
T1Var2_3_2 t1_var2_3_2{&tmplCategory2_3, &code2_3, &cond_val, &bool_true};
T1Var2_3_3 t1_var2_3_3{&tmplCategory2_3, &code_val, &cond2_3, &bool_true};
T1Var2_3_4 t1_var2_3_4{&tmplCategory2_3, &code_val, &cond_val, &bool_true};

CodeType code2_4{code_val, tmplCategory2_4};
ConditionType cond2_4{cond_val, tmplCategory2_4};

T1Var2_4_1 t1_var2_4_1{&tmplCategory2_4, &code2_4, &cond2_4, &bool_true};
T1Var2_4_2 t1_var2_4_2{&tmplCategory2_4, &code2_4, &cond_val, &bool_true};
T1Var2_4_3 t1_var2_4_3{&tmplCategory2_4, &code_val, &cond2_4, &bool_true};
T1Var2_4_4 t1_var2_4_4{&tmplCategory2_4, &code_val, &cond_val, &bool_true};

CodeType code2_5{code_val, tmplCategory2_5};
ConditionType cond2_5{cond_val, tmplCategory2_5};

T1Var2_5_1 t1_var2_5_1{&tmplCategory2_5, &code2_5, &cond2_5, &bool_true};
T1Var2_5_2 t1_var2_5_2{&tmplCategory2_5, &code2_5, &cond_val, &bool_true};
T1Var2_5_3 t1_var2_5_3{&tmplCategory2_5, &code_val, &cond2_5, &bool_true};
T1Var2_5_4 t1_var2_5_4{&tmplCategory2_5, &code_val, &cond_val, &bool_true};

CodeType code2_6{code_val, tmplCategory2_6};
ConditionType cond2_6{cond_val, tmplCategory2_6};

T1Var2_6_1 t1_var2_6_1{&tmplCategory2_6, &code2_6, &cond2_6, &bool_true};
T1Var2_6_2 t1_var2_6_2{&tmplCategory2_6, &code2_6, &cond_val, &bool_true};
T1Var2_6_3 t1_var2_6_3{&tmplCategory2_6, &code_val, &cond2_6, &bool_true};
T1Var2_6_4 t1_var2_6_4{&tmplCategory2_6, &code_val, &cond_val, &bool_true};

CodeType code3_1{code_val, tmplCategory3_1};
ConditionType cond3_1{cond_val, tmplCategory3_1};

T1Var3_1_1 t1_var3_1_1{&tmplCategory3_1, &code3_1, &cond3_1, &bool_true};
T1Var3_1_2 t1_var3_1_2{&tmplCategory3_1, &code3_1, &cond_val, &bool_true};
T1Var3_1_3 t1_var3_1_3{&tmplCategory3_1, &code_val, &cond3_1, &bool_true};
T1Var3_1_4 t1_var3_1_4{&tmplCategory3_1, &code_val, &cond_val, &bool_true};

CodeType code3_2{code_val, tmplCategory3_2};
ConditionType cond3_2{cond_val, tmplCategory3_2};

T1Var3_2_1 t1_var3_2_1{&tmplCategory3_2, &code3_2, &cond3_2, &bool_true};
T1Var3_2_2 t1_var3_2_2{&tmplCategory3_2, &code3_2, &cond_val, &bool_true};
T1Var3_2_3 t1_var3_2_3{&tmplCategory3_2, &code_val, &cond3_2, &bool_true};
T1Var3_2_4 t1_var3_2_4{&tmplCategory3_2, &code_val, &cond_val, &bool_true};

CodeType code3_3{code_val, tmplCategory3_3};
ConditionType cond3_3{cond_val, tmplCategory3_3};

T1Var3_3_1 t1_var3_3_1{&tmplCategory3_3, &code3_3, &cond3_3, &bool_true};
T1Var3_3_2 t1_var3_3_2{&tmplCategory3_3, &code3_3, &cond_val, &bool_true};
T1Var3_3_3 t1_var3_3_3{&tmplCategory3_3, &code_val, &cond3_3, &bool_true};
T1Var3_3_4 t1_var3_3_4{&tmplCategory3_3, &code_val, &cond_val, &bool_true};

CodeType code3_4{code_val, tmplCategory3_4};
ConditionType cond3_4{cond_val, tmplCategory3_4};

T1Var3_4_1 t1_var3_4_1{&tmplCategory3_4, &code3_4, &cond3_4, &bool_true};
T1Var3_4_2 t1_var3_4_2{&tmplCategory3_4, &code3_4, &cond_val, &bool_true};
T1Var3_4_3 t1_var3_4_3{&tmplCategory3_4, &code_val, &cond3_4, &bool_true};
T1Var3_4_4 t1_var3_4_4{&tmplCategory3_4, &code_val, &cond_val, &bool_true};

CodeType code4{code_val, tmplCategory4};
ConditionType cond4{cond_val, tmplCategory4};

T1Var4_1 t1_var4_1{&tmplCategory4, &code4, &cond4, &bool_true};
T1Var4_2 t1_var4_2{&tmplCategory4, &code4, &cond_val, &bool_true};
T1Var4_3 t1_var4_3{&tmplCategory4, &code_val, &cond4, &bool_true};
T1Var4_4 t1_var4_4{&tmplCategory4, &code_val, &cond_val, &bool_true};

CodeType code5{code_val, tmplCategory5};
ConditionType cond5{cond_val, tmplCategory5};

T1Var5_1 t1_var5_1{&tmplCategory5, &code5, &cond5, &bool_false};
T1Var5_2 t1_var5_2{&tmplCategory5, &code5, &cond_val, &bool_false};
T1Var5_3 t1_var5_3{&tmplCategory5, &code_val, &cond5, &bool_false};
T1Var5_4 t1_var5_4{&tmplCategory5, &code_val, &cond_val, &bool_false};


REGISTER_TEST(t1, new TestEquivalent<Case1, T1Var1_1_1, T1Var1_1_2,
    T1Var1_1_3, T1Var1_1_4, T1Var1_2_1, T1Var1_2_2, T1Var1_2_3,
    T1Var1_2_4, T1Var1_3_1, T1Var1_3_2, T1Var1_3_3, T1Var1_3_4,
    T1Var1_4_1, T1Var1_4_2, T1Var1_4_3, T1Var1_4_4, T1Var2_1_1,
    T1Var2_1_2, T1Var2_1_3, T1Var2_1_4, T1Var2_2_1, T1Var2_2_2,
    T1Var2_2_3, T1Var2_2_4, T1Var2_3_1, T1Var2_3_2, T1Var2_3_3,
    T1Var2_3_4, T1Var2_4_1, T1Var2_4_2, T1Var2_4_3, T1Var2_4_4,
    T1Var2_5_1, T1Var2_5_2, T1Var2_5_3, T1Var2_5_4, T1Var2_6_1,
    T1Var2_6_2, T1Var2_6_3, T1Var2_6_4, T1Var3_1_1, T1Var3_1_2,
    T1Var3_1_3, T1Var3_1_4, T1Var3_2_1, T1Var3_2_2, T1Var3_2_3,
    T1Var3_2_4, T1Var3_3_1, T1Var3_3_2, T1Var3_3_3, T1Var3_3_4,
    T1Var3_4_1, T1Var3_4_2, T1Var3_4_3, T1Var3_4_4, T1Var4_1, 
    T1Var4_2, T1Var4_3, T1Var4_4, T1Var5_1, T1Var5_2, T1Var5_3, 
    T1Var5_4 >(t1_var1_1_1, t1_var1_1_2, t1_var1_1_3, t1_var1_1_4, t1_var1_2_1,
        t1_var1_2_2, t1_var1_2_3, t1_var1_2_4, t1_var1_3_1, t1_var1_3_2, 
        t1_var1_3_3, t1_var1_3_4, t1_var1_4_1, t1_var1_4_2, t1_var1_4_3, 
        t1_var1_4_4, t1_var2_1_1, t1_var2_1_2, t1_var2_1_3, t1_var2_1_4, 
        t1_var2_2_1, t1_var2_2_2, t1_var2_2_3, t1_var2_2_4, t1_var2_3_1, 
        t1_var2_3_2, t1_var2_3_3, t1_var2_3_4, t1_var2_4_1, t1_var2_4_2, 
        t1_var2_4_3, t1_var2_4_4, t1_var2_5_1, t1_var2_5_2, t1_var2_5_3, 
        t1_var2_5_4, t1_var2_6_1, t1_var2_6_2, t1_var2_6_3, t1_var2_6_4, 
        t1_var3_1_1, t1_var3_1_2, t1_var3_1_3, t1_var3_1_4, t1_var3_2_1, 
        t1_var3_2_2, t1_var3_2_3, t1_var3_2_4, t1_var3_3_1, t1_var3_3_2, 
        t1_var3_3_3, t1_var3_3_4, t1_var3_4_1, t1_var3_4_2, t1_var3_4_3, 
        t1_var3_4_4, t1_var4_1, t1_var4_2, t1_var4_3, t1_var4_4, t1_var5_1,
        t1_var5_2, t1_var5_3, t1_var5_4));

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
BASIC_TEST_TYPE_NAME("CategoryTrait4", CategoryTrait4);
BASIC_TEST_TYPE_NAME("CategoryTrait5", CategoryTrait5);

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


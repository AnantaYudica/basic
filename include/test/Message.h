#ifndef BASIC_TEST_MESSAGE_H_
#define BASIC_TEST_MESSAGE_H_

#include "Variable.h"
#include "var/Value.h"
#include "var/type/Function.h"
#include "var/type/Value.h"
#include "var/type/val/Sequence.h"
#include "var/val/Function.h"
#include "var/val/Sequence.h"
#include "var/val/Parameter.h"

#include "msg/Base.h"

#include "type/Index.h"

#include <cstddef>

namespace basic
{
namespace test
{

template<typename TTest, typename TDerived>
class Message
{
private:
    TDerived& m_derived;
protected:
    Message(TDerived& d);
public:
    template<typename TCaseId, typename... TVarArgs>
    void Info(const TCaseId&, test::Variable<TVarArgs...>& var);
    template<typename TCaseId, typename... TVarArgs>
    void Debug(const TCaseId&, test::Variable<TVarArgs...>& var);
    template<typename TCaseId, typename... TVarArgs>
    void Error(const TCaseId&, test::Variable<TVarArgs...>& var);
public:
    template<typename TCaseId, std::size_t ICaseId, typename... TVarArgs>
    void Info(const type::Index<TCaseId, ICaseId>&, 
        test::Variable<TVarArgs...>& var);
    template<typename TCaseId, std::size_t ICaseId,  typename... TVarArgs>
    void Debug(const type::Index<TCaseId, ICaseId>&, 
        test::Variable<TVarArgs...>& var);
    template<typename TCaseId, std::size_t ICaseId,  typename... TVarArgs>
    void Error(const type::Index<TCaseId, ICaseId>&, 
        test::Variable<TVarArgs...>& var);
};

template<typename TTest, typename TDerived>
Message<TTest, TDerived>::Message(TDerived& d) :
    m_derived(d)
{}

template<typename TTest, typename TDerived>
template<typename TCaseId, typename... TVarArgs>
void Message<TTest, TDerived>::
    Info(const TCaseId& case_id, test::Variable<TVarArgs...>& var)
{
    msg::base::Info info;
    m_derived.Argument(info, case_id).template Call<void, 
        const char*>(&TTest::Info, var, std::move(*m_derived.Format(info, 
            case_id)));
}

template<typename TTest, typename TDerived>
template<typename TCaseId, typename... TVarArgs>
void Message<TTest, TDerived>::Debug(const TCaseId& case_id,
    test::Variable<TVarArgs...>& var)
{
    msg::base::Debug debug;
    m_derived.Argument(debug, case_id).template Call<void, 
        const char*>(&TTest::Debug, var, std::move(*m_derived.Format(debug,
            case_id)));
}

template<typename TTest, typename TDerived>
template<typename TCaseId, typename... TVarArgs>
void Message<TTest, TDerived>::Error(const TCaseId& case_id,
    test::Variable<TVarArgs...>& var)
{
    msg::base::Error err;
    m_derived.Argument(err, case_id).template Call<void, 
        const char*>(&TTest::Error, var, std::move(*m_derived.Format(err,
            case_id)));
}

template<typename TTest, typename TDerived>
template<typename TCaseId, std::size_t ICaseId, typename... TVarArgs>
void Message<TTest, TDerived>::Info(const test::type::Index<TCaseId, 
    ICaseId>& case_id, test::Variable<TVarArgs...>& var)
{
    msg::base::Info info;
    m_derived.Argument(info, TCaseId{}).template Call<void, 
        const char*>(case_id, &TTest::Info, var, 
            std::move(*m_derived.Format(info, TCaseId{})));
}

template<typename TTest, typename TDerived>
template<typename TCaseId, std::size_t ICaseId,  typename... TVarArgs>
void Message<TTest, TDerived>::Debug(const test::type::Index<TCaseId, 
    ICaseId>& case_id, test::Variable<TVarArgs...>& var)
{
    msg::base::Debug debug;
    m_derived.Argument(debug, TCaseId{}).template Call<void, 
        const char*>(case_id, &TTest::Debug, var, 
            std::move(*m_derived.Format(debug, TCaseId{})));}

template<typename TTest, typename TDerived>
template<typename TCaseId, std::size_t ICaseId,  typename... TVarArgs>
void Message<TTest, TDerived>::Error(const test::type::Index<TCaseId, 
    ICaseId>& case_id, test::Variable<TVarArgs...>& var)
{
    msg::base::Error err;
    m_derived.Argument(err, TCaseId{}).template Call<void, 
        const char*>(case_id, &TTest::Error, var, 
            std::move(*m_derived.Format(err, TCaseId{})));
}

} //!test

} //!basic

#endif //!BASIC_TEST_MESSAGE_H_

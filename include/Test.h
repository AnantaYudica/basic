#ifndef BASIC_TEST_H_
#define BASIC_TEST_H_

#include "test/Status.h"
#include "test/Output.h"
#include "test/Memory.h"
#include "test/Base.h"
#include "test/Register.h"
#include "test/Trace.h"
#include "test/reg/Base.h"
#include "test/type/Name.h"

#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <stack>

#ifndef BASIC_TEST_OUTPUT_FILENAME
#define BASIC_TEST_OUTPUT_FILENAME_EMPTY
#endif //!BASIC_TEST_OUTPUT_FILENAME


namespace _helper
{
namespace _basic
{
namespace _test
{

template<typename>
struct Void1T {};

} //!_test

} //!_basic

} //_helper

namespace basic
{

template<typename Ts = test::Status, 
    template<typename> class To = test::Output, 
    template<typename> class Tmem = _helper::_basic::_test::Void1T>
class Test
{
public:
    typedef Ts StatusType;
    typedef To<StatusType> OutputType;
    typedef Tmem<OutputType> MemoryType;
private:
    static Test<Ts, To, Tmem>* ms_instance;
private:
    bool m_initialized;
    StatusType m_status;
    OutputType m_output;
    MemoryType m_memory;
    std::vector<test::reg::Base*>* m_list;
    std::stack<test::Trace>* m_traces;
private:
    Test();
    Test(const Test<Ts, To, Tmem>& cpy) = delete;
    Test(Test<Ts, To, Tmem>&& mov);
public:
    ~Test();
public:
    Test<Ts, To, Tmem>& operator=(const Test<Ts, To, Tmem>& cpy) = delete;
    Test<Ts, To, Tmem>& operator=(Test<Ts, To, Tmem>&& mov) = delete;
public:
    template<typename... Targs>
    static void Info(const char* info_msg_cstr, Targs&&... args);
    template<typename... Targs>
    static void Debug(const char* debug_msg_cstr, Targs&&... args);
    template<typename... Targs>
    static void Error(const char* err_msg_cstr, Targs&&... args);
    static bool Assert(bool test, const char* err_msg_cstr, 
        const char* file, const int& line);
public:
    static Test<Ts, To, Tmem>& CreateInstance();
    static Test<Ts, To, Tmem>& GetInstance();
public:
    static const int& Run();
private:
    void Clear();
public:
    void Push(const test::Trace& trace);
    void Pop();
    std::stack<test::Trace> GetTrace();
public:
    typename Test<Ts, To, Tmem>::StatusType& Status();
    typename Test<Ts, To, Tmem>::OutputType& Output();
    typename Test<Ts, To, Tmem>::MemoryType& Memory();
    std::vector<test::reg::Base*>& List();
    std::stack<test::Trace>& Traces();
};

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>* Test<Ts, To, Tmem>::ms_instance;

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>::Test() :
    m_status(),
#ifdef BASIC_TEST_OUTPUT_FILENAME_EMPTY
    m_output(m_status),
#else //!BASIC_TEST_OUTPUT_FILENAME_EMPTY
    m_output(m_status, BASIC_TEST_OUTPUT_FILENAME),
#endif
#ifdef USING_BASIC_TEST_MEMORY
    m_memory(m_output),
#endif //USING_BASIC_TEST_MEMORY
    m_list(NULL),
    m_traces(NULL),
    m_initialized(true)
{
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>::Test(Test<Ts, To, Tmem>&& mov) :
    m_status(std::move(mov.m_status)),
    m_output(std::move(mov.m_output)),
#ifdef USING_BASIC_TEST_MEMORY
    m_memory(std::move(mov.m_memory)),
#endif //USING_BASIC_TEST_MEMORY
    m_list(std::move(mov.m_list)),
    m_traces(std::move(mov.m_traces)),
    m_initialized(true)
{
    m_output.Set(m_status);
#ifdef USING_BASIC_TEST_MEMORY
    m_memory.Set(m_output);
#endif //USING_BASIC_TEST_MEMORY
    mov.m_list = NULL;
    mov.m_traces = NULL;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>::~Test()
{
    assert(m_list == NULL);
    assert(m_traces == NULL);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Info(const char* info_msg_cstr,
    Targs&&... args)
{
    GetInstance().Output().Info(info_msg_cstr, 
        std::forward<Targs>(args)...);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Debug(const char* debug_msg_cstr, 
    Targs&&...args)
{
    GetInstance().Output().Debug(debug_msg_cstr,
        std::forward<Targs>(args)...);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Error(const char* err_msg_cstr, 
    Targs&&... args)
{
    GetInstance().Output().Error(err_msg_cstr,
        std::forward<Targs>(args)...);
    auto trace = GetInstance().GetTrace();
    while (!trace.empty())
    {
        GetInstance().Output().Error(" from file %s line %i\n",
        trace.top().File, trace.top().Line);
        trace.pop();
    }
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
bool Test<Ts, To, Tmem>::Assert(bool test, const char* err_msg_cstr,
    const char* file, const int& line)
{
    if (!test)
        Error("error %s file %s line %i\n", err_msg_cstr, file, line);
    return test;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>& Test<Ts, To, Tmem>::CreateInstance()
{
    assert(ms_instance == NULL);
    static Test<Ts, To, Tmem> instance;
    ms_instance = &instance;
    return instance;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>& Test<Ts, To, Tmem>::GetInstance()
{
    if (ms_instance == NULL)
        CreateInstance();
    return *ms_instance;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
const int& Test<Ts, To, Tmem>::Run()
{
    std::size_t i = 0, s = GetInstance().List().size();
    for (auto t : GetInstance().List())
    {
        Debug("Test %u of %u : \n", i + 1, s);
        GetInstance().Push(test::Trace(t->File(), t->Line()));
        t->Run();
        GetInstance().Pop();
        ++i;
    }
    GetInstance().Clear();
    return GetInstance().Status().Get();
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
void Test<Ts, To, Tmem>::Clear()
{
    m_list->clear();
    delete m_list;
    m_list = NULL;
    delete m_traces;
    m_traces = NULL;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
void Test<Ts, To, Tmem>::Push(const test::Trace& trace)
{
    Traces().push(trace);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
void Test<Ts, To, Tmem>::Pop()
{
    Traces().pop();
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
std::stack<test::Trace> Test<Ts, To, Tmem>::GetTrace()
{
    if (m_traces == NULL)
        return std::move(std::stack<test::Trace>());
    return *m_traces;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
typename Test<Ts, To, Tmem>::StatusType& Test<Ts, To, Tmem>::Status()
{
    return m_status;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
typename Test<Ts, To, Tmem>::OutputType& Test<Ts, To, Tmem>::Output()
{
    return m_output;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
typename Test<Ts, To, Tmem>::MemoryType& Test<Ts, To, Tmem>::Memory()
{
    return m_memory;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
std::vector<test::reg::Base*>& Test<Ts, To, Tmem>::List()
{
    if (m_list == NULL)
        m_list = new std::vector<test::reg::Base*>();
    return *m_list;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
std::stack<test::Trace>& Test<Ts, To, Tmem>::Traces()
{
    if (m_traces == NULL)
        m_traces = new std::stack<test::Trace>();
    return *m_traces;
}

} //!basic

#ifndef BASIC_TEST
#ifdef USING_BASIC_TEST_MEMORY
#define BASIC_TEST basic::Test<basic::test::Status,\
    basic::test::Output, basic::test::Memory>
#else //ELSE USING_BASIC_TEST_MEMORY
#define BASIC_TEST basic::Test<basic::test::Status>
#endif //!USING_BASIC_TEST_MEMORY
#endif //!BASIC_TEST

#ifdef USING_BASIC_TEST_MEMORY
#include <new>

void* operator new(std::size_t sz)
{
    auto p = std::malloc(sz);
    BASIC_TEST::GetInstance().Memory().Register(p, sz);
    return p;
}

void* operator new[]( std::size_t sz)
{
    auto p = std::malloc(sz);
    BASIC_TEST::GetInstance().Memory().Register(p, sz);
    return p;
}

template<std::size_t N>
void* operator new(std::size_t sz, const char (&file)[N], const int& line) 
{
    auto p = std::malloc(sz);
    BASIC_TEST::GetInstance().Memory().Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const char (&file)[N], const int& line)
{
    auto p = std::malloc(sz);
    BASIC_TEST::GetInstance().Memory().Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new (std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new(sz, tag);
    BASIC_TEST::GetInstance().Memory().Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new[](sz, tag);
    BASIC_TEST::GetInstance().Memory().Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new ( std::size_t sz, void* ptr,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new(sz, ptr);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, void* ptr,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new[](sz, ptr);
    return p;
}

void operator delete(void* p) noexcept
{
    BASIC_TEST::GetInstance().Memory().Unregister(p);
    std::free(p);
}

void operator delete[](void* p) noexcept
{
    BASIC_TEST::GetInstance().Memory().Unregister(p);
    std::free(p);
}

void operator delete ( void* p, const std::nothrow_t& tag )
{
    BASIC_TEST::GetInstance().Memory().Unregister(p);
    std::free(p);
}

void operator delete[]( void* p, const std::nothrow_t& tag )
{
    BASIC_TEST::GetInstance().Memory().Unregister(p);
    std::free(p);
}

#ifndef _WIN32
#define new(...) new(__VA_ARGS__, __FILE__, __LINE__)
#endif

#endif //!USING_BASIC_TEST_MEMORY

#ifndef INFO
#define INFO(__INFO_MESSAGE__, ...)\
    BASIC_TEST::Info(__INFO_MESSAGE__,##__VA_ARGS__)
#endif //!INFO

#ifndef DEBUG
#define DEBUG(__DEBUG_MESSAGE__, ...)\
    BASIC_TEST::Debug(__DEBUG_MESSAGE__,##__VA_ARGS__)
#endif //!DEBUG

#ifndef ERROR
#define INFO(__INFO_MESSAGE__, ...)\
    BASIC_TEST::Info(__INFO_MESSAGE__,##__VA_ARGS__)
#endif //!INFO

#ifndef ASSERT
#define ASSERT(__ERR_MESSAGE__, __TEST_BOOL__, ...)\
    BASIC_TEST::Assert(__TEST_BOOL__,##__VA_ARGS__,\
        __ERR_MESSAGE__, __FILE__, __LINE__)
#endif //!ASSERT

#ifndef REGISTER_TEST
#define REGISTER_TEST(Name, Test, ...) auto Name =\
    std::move(basic::test::reg::Make<BASIC_TEST>(Test,##__VA_ARGS__, \
        __FILE__, __LINE__));
#endif //!REGISTER_TEST

#ifndef RUN_TEST
#define RUN_TEST() BASIC_TEST::Run()
#endif //!RUN_TEST

#ifndef BASIC_TEST_CONSTRUCT
#define BASIC_TEST_CONSTRUCT BASIC_TEST& __test_instance_ = \
    BASIC_TEST::CreateInstance()
#endif //!BASIC_TEST_CONSTRUCT

#define BASIC_TEST_TYPE_NAME(__NAME__, __TYPE__, ...)\
template<>\
struct basic::test::type::Name<__TYPE__,##__VA_ARGS__>\
{\
    static basic::test::CString<const char> CStr()\
    {\
        static char _cstr[] = __NAME__;\
        return {_cstr};\
    }\
}

#endif //!BASIC_TEST_H_

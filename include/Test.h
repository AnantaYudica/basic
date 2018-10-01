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
public:
    static Test<Ts, To, Tmem> Instance;
public:
    StatusType Status;
    OutputType Output;
    MemoryType Memory;
    std::vector<test::reg::Base*> List;
    std::stack<test::Trace> Traces;
private:
    Test();
public:
    template<typename... Targs>
    static void Info(const char* info_msg_cstr, Targs&&... args);
    template<typename... Targs>
    static void Debug(const char* debug_msg_cstr, Targs&&... args);
    template<typename... Targs>
    static void Error(const char* error_msg_cstr, Targs&&... args);
    static bool Assert(bool test, const char* error_msg_cstr, 
        const char* file, const int& line);
public:
    static const int& Run();
public:
    void Push(const test::Trace& trace);
    void Pop();
    std::stack<test::Trace> GetTrace();
};

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem> Test<Ts, To, Tmem>::Instance;

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>::Test() :
    Status(),
#ifdef BASIC_TEST_OUTPUT_FILENAME_EMPTY
    Output(Status),
#else //!BASIC_TEST_OUTPUT_FILENAME_EMPTY
    Output(Status, BASIC_TEST_OUTPUT_FILENAME),
#endif
#ifdef USING_BASIC_TEST_MEMORY
    Memory(Output),
#endif //USING_BASIC_TEST_MEMORY
    List(),
    Traces()
{}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Info(const char* info_msg_cstr,
    Targs&&... args)
{
    Instance.Output.Info(info_msg_cstr, 
        std::forward<Targs>(args)...);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Debug(const char* debug_msg_cstr, 
    Targs&&...args)
{
    Instance.Output.Debug(debug_msg_cstr, 
        std::forward<Targs>(args)...);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Error(const char* error_msg_cstr, 
    Targs&&... args)
{
    Instance.Output.Error(error_msg_cstr, 
        std::forward<Targs>(args)...);
    auto trace = Instance.GetTrace();
    while (!trace.empty())
    {
        Instance.Output.Error(" from file %s line %i\n", 
        trace.top().File, trace.top().Line);
        trace.pop();
    }
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
bool Test<Ts, To, Tmem>::Assert(bool test, const char* error_msg_cstr,
    const char* file, const int& line)
{
    if (!test)
        Error("error %s file %s line %i\n", error_msg_cstr, file, line);
    return test;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
const int& Test<Ts, To, Tmem>::Run()
{
    std::size_t i = 0, s = Instance.List.size();
    for (auto t : Instance.List)
    {
        Debug("Test %u of %u : \n", i + 1, s);
        Instance.Push(test::Trace(t->File(), t->Line()));
        t->Run();
        Instance.Pop();
        ++i;
    }
    return Instance.Status.Get();
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
void Test<Ts, To, Tmem>::Push(const test::Trace& trace)
{
    Instance.Traces.push(trace);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
void Test<Ts, To, Tmem>::Pop()
{
    Instance.Traces.pop();
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
std::stack<test::Trace> Test<Ts, To, Tmem>::GetTrace()
{
    return Instance.Traces;
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
    BASIC_TEST::Instance.Memory.Register(p, sz);
    return p;
}

void* operator new[]( std::size_t sz)
{
    auto p = std::malloc(sz);
    BASIC_TEST::Instance.Memory.Register(p, sz);
    return p;
}

template<std::size_t N>
void* operator new(std::size_t sz, const char (&file)[N], const int& line) 
{
    auto p = std::malloc(sz);
    BASIC_TEST::Instance.Memory.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const char (&file)[N], const int& line)
{
    auto p = std::malloc(sz);
    BASIC_TEST::Instance.Memory.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new (std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new(sz, tag);
    BASIC_TEST::Instance.Memory.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new[](sz, tag);
    BASIC_TEST::Instance.Memory.Register(p, sz, file, line);
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
    BASIC_TEST::Instance.Memory.Unregister(p);
    std::free(p);
}

void operator delete[](void* p) noexcept
{
    BASIC_TEST::Instance.Memory.Unregister(p);
    std::free(p);
}

void operator delete ( void* p, const std::nothrow_t& tag )
{
    BASIC_TEST::Instance.Memory.Unregister(p);
    std::free(p);
}

void operator delete[]( void* p, const std::nothrow_t& tag )
{
    BASIC_TEST::Instance.Memory.Unregister(p);
    std::free(p);
}

#define new(...) new(__VA_ARGS__, __FILE__, __LINE__)

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
#define ASSERT(__ERROR_MESSAGE__, __TEST_BOOL__, ...)\
    BASIC_TEST::Assert(__TEST_BOOL__,##__VA_ARGS__,\
        __ERROR_MESSAGE__, __FILE__, __LINE__)
#endif //!ASSERT

#ifndef REGISTER_TEST
#define REGISTER_TEST(Name, Test, ...) auto Name =\
    std::move(basic::test::reg::Make<BASIC_TEST>(Test,##__VA_ARGS__,\
        __FILE__, __LINE__));
#endif //!REGISTER_TEST

#ifndef RUN_TEST
#define RUN_TEST() BASIC_TEST::Run()
#endif //!RUN_TEST

#ifndef BASIC_TEST_CONSTRUCT
#define BASIC_TEST_CONSTRUCT BASIC_TEST& __test_instance = BASIC_TEST::Instance
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

#ifndef BASIC_TEST_H_
#define BASIC_TEST_H_

#include "test/Status.h"
#include "test/Output.h"
#include "test/Memory.h"
#include "test/Base.h"
#include "test/Register.h"

#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

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
    std::vector<test::Register<Test<Ts, To, Tmem>>*> List;
private:
    Test();
public:
    template<typename... Targs>
    static void Info(const char* info_msg_cstr, Targs&&... args);
    static bool Assert(bool test, const char* error_msg_cstr, 
        const char* file, const int& line);
    template<typename... Targs>
    static void Debug(const char* debug_msg_cstr, Targs&&... args);
public:
    static const int& Run();
};

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem> Test<Ts, To, Tmem>::Instance;

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>::Test() :
    Status(),
#ifdef BASIC_TEST_OUTPUT_FILENAME_EMPTY
    Output(Status)
#else //!BASIC_TEST_OUTPUT_FILENAME_EMPTY
    Output(Status, BASIC_TEST_OUTPUT_FILENAME)
#endif
#ifdef USING_BASIC_TEST_MEMORY
    ,Memory(Output)
#endif //USING_BASIC_TEST_MEMORY
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
bool Test<Ts, To, Tmem>::Assert(bool test, const char* error_msg_cstr,
    const char* file, const int& line)
{
    if (!test)
    {
        Instance.Output.Error("error %s file %s line %i\n", 
            error_msg_cstr, file, line);
        auto trace = Instance.Output.GetTrace();
        while (!trace.empty())
        {
            Instance.Output.Error(" from file %s line %i\n", 
            trace.top().File, trace.top().Line);
            trace.pop();
        }
    }
    return test;
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
const int& Test<Ts, To, Tmem>::Run()
{
    std::size_t i = 0, s = Instance.List.size();
    for (auto t : Instance.List)
    {
        Debug("Test %u of %u : \n", i, s);
        Instance.Output.Push(test::out::Trace(t->File(),
            t->Line()));
        t->Run();
        Instance.Output.Pop();
        ++i;
    }
    return Instance.Status.Get();
}

} //!basic

#ifndef BasicTest
#ifdef USING_BASIC_TEST_MEMORY
#define BasicTest basic::Test<basic::test::Status,\
    basic::test::Output, basic::test::Memory>
#else //ELSE USING_BASIC_TEST_MEMORY
#define BasicTest basic::Test<basic::test::Status>
#endif //!USING_BASIC_TEST_MEMORY
#endif //!BasicTest

#ifdef USING_BASIC_TEST_MEMORY
#include <new>

void* operator new(std::size_t sz)
{
    auto p = std::malloc(sz);
    BasicTest::Instance.Memory.Register(p, sz);
    return p;
}

void* operator new[]( std::size_t sz)
{
    auto p = std::malloc(sz);
    BasicTest::Instance.Memory.Register(p, sz);
    return p;
}

template<std::size_t N>
void* operator new(std::size_t sz, const char (&file)[N], const int& line) 
{
    auto p = std::malloc(sz);
    BasicTest::Instance.Memory.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const char (&file)[N], const int& line)
{
    auto p = std::malloc(sz);
    BasicTest::Instance.Memory.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new (std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new(sz, tag);
    BasicTest::Instance.Memory.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new[](sz, tag);
    BasicTest::Instance.Memory.Register(p, sz, file, line);
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
    BasicTest::Instance.Memory.Unregister(p);
    std::free(p);
}

void operator delete[](void* p) noexcept
{
    BasicTest::Instance.Memory.Unregister(p);
    std::free(p);
}

void operator delete ( void* p, const std::nothrow_t& tag )
{
    BasicTest::Instance.Memory.Unregister(p);
    std::free(p);
}

void operator delete[]( void* p, const std::nothrow_t& tag )
{
    BasicTest::Instance.Memory.Unregister(p);
    std::free(p);
}

#define new(...) new(__VA_ARGS__, __FILE__, __LINE__)

#endif //!USING_BASIC_TEST_MEMORY

#ifndef Info
#define Info(__INFO_MESSAGE__, ...)\
    BasicTest::Info(__INFO_MESSAGE__,##__VA_ARGS__)
#endif //!Info

#ifndef Assert
#define Assert(__ERROR_MESSAGE__, __TEST_BOOL__, ...)\
    BasicTest::Assert(__TEST_BOOL__,##__VA_ARGS__,\
        __ERROR_MESSAGE__, __FILE__, __LINE__)
#endif //!Assert

#ifndef TestStatus
#define TestStatus BasicTest::Instance.Status.Get()
#endif //!ResultStatus

#ifndef RegisterTest
#define RegisterTest(Name, Test, ...) basic::test::Register<BasicTest> \
    Name(Test,##__VA_ARGS__, __FILE__, __LINE__)
#endif //!RegisterTest

#ifndef TestRun
#define TestRun() BasicTest::Run()
#endif //!TestRun

#ifndef BasicTestConstruct
#define BasicTestConstruct BasicTest& __test_instance = BasicTest::Instance
#endif //!BasicTestConstruct

#endif //!BASIC_TEST_H_

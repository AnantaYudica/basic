#ifndef BASIC_TEST_H_
#define BASIC_TEST_H_

#include "test/Status.h"
#include "test/Output.h"
#include "test/Memory.h"

#include <cstdio>
#include <cstdlib>
#include <utility>


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
    static Test<Ts, To, Tmem> ms_instance;
public:
    StatusType m_status;
    OutputType m_output;
    MemoryType m_mem;
private:
    Test();
public:
    static Test<Ts, To, Tmem>& GetInstance();
    static const int& GetStatus();
    template<typename... Targs>
    static void Info(const char* info_msg_cstr, Targs&&... args);
    static bool Assert(bool test, const char* error_msg_cstr, 
        const char* file, const int& line);
};

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem> Test<Ts, To, Tmem>::ms_instance;

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>::Test() :
    m_status(),
#ifdef BASIC_TEST_OUTPUT_FILENAME_EMPTY
    m_output(m_status)
#else //!BASIC_TEST_OUTPUT_FILENAME_EMPTY
    m_output(m_status, BASIC_TEST_OUTPUT_FILENAME)
#endif
#ifdef USING_BASIC_TEST_MEMORY
    ,m_mem(m_output)
#endif //USING_BASIC_TEST_MEMORY
{}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
Test<Ts, To, Tmem>& Test<Ts, To, Tmem>::GetInstance()
{
    return ms_instance;
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
const int& Test<Ts, To, Tmem>::GetStatus()
{
    return GetInstance().m_status.Get();
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
template<typename... Targs>
void Test<Ts, To, Tmem>::Info(const char* info_msg_cstr,
    Targs&&... args)
{
    GetInstance().m_output.Info(info_msg_cstr, std::forward(args)...);
}

template<typename Ts, template<typename> class To,
    template<typename> class Tmem>
bool Test<Ts, To, Tmem>::Assert(bool test, const char* error_msg_cstr,
    const char* file, const int& line)
{
    if (!test)
    {
        GetInstance().m_output.Error("Error : %s file %s line %i\n", 
            error_msg_cstr, file, line);
    }
    return test;
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
    BasicTest::GetInstance().m_mem.Register(p, sz);
    return p;
}

void* operator new[]( std::size_t sz)
{
    auto p = std::malloc(sz);
    BasicTest::GetInstance().m_mem.Register(p, sz);
    return p;
}

template<std::size_t N>
void* operator new(std::size_t sz, const char (&file)[N], const int& line) 
{
    auto p = std::malloc(sz);
    BasicTest::GetInstance().m_mem.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const char (&file)[N], const int& line)
{
    auto p = std::malloc(sz);
    BasicTest::GetInstance().m_mem.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new (std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new(sz, tag);
    BasicTest::GetInstance().m_mem.Register(p, sz, file, line);
    return p;
}

template<std::size_t N>
void* operator new[]( std::size_t sz, const std::nothrow_t& tag,
    const char (&file)[N], const int& line)
{
    auto p = ::operator new[](sz, tag);
    BasicTest::GetInstance().m_mem.Register(p, sz, file, line);
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
    BasicTest::GetInstance().m_mem.Unregister(p);
    std::free(p);
}

void operator delete[](void* p) noexcept
{
    BasicTest::GetInstance().m_mem.Unregister(p);
    std::free(p);
}

void operator delete ( void* p, const std::nothrow_t& tag )
{
    BasicTest::GetInstance().m_mem.Unregister(p);
    std::free(p);
}

void operator delete[]( void* p, const std::nothrow_t& tag )
{
    BasicTest::GetInstance().m_mem.Unregister(p);
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

#ifndef ResultStatus
#define ResultStatus BasicTest::GetInstance().m_status.Get();
#endif //!ResultStatus

#endif //!BASIC_TEST_H_

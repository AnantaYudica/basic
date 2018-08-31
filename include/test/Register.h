#ifndef BASIC_TEST_REGISTER_H_
#define BASIC_TEST_REGISTER_H_

#include <vector>

#include "Base.h"

namespace basic
{
namespace test
{

template<typename Tt>
class Register
{
private:
    Base* m_ptr;
    const char* m_file;
    const std::size_t m_line;
public:
    Register(Base* ptr, const char* file, const std::size_t& line) :
        m_ptr(ptr),
        m_file(file),
        m_line(line)
    {
        Tt::Instance.List.push_back(this);
    }
    ~Register()
    {
        delete m_ptr;
    }
public:
    bool Run();
    const char* File() const;
    const std::size_t& Line() const;
};

template<typename Tt>
bool Register<Tt>::Run()
{
    m_ptr->Test();
    return Tt::Instance.Status.Get() == EXIT_SUCCESS;
}

template<typename Tt>
const char* Register<Tt>::File() const
{
    return m_file;
}

template<typename Tt>
const std::size_t& Register<Tt>::Line() const
{
    return m_line;
}

} //!test

} //!basic

#endif //!BASIC_TEST_REGISTER_H_
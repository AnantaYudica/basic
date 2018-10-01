#ifndef BASIC_TEST_STATUS_H_
#define BASIC_TEST_STATUS_H_

#include <cstdlib>

namespace basic
{
namespace test
{

class Status
{
private:
    int m_status; 
public:
    Status();
public:
    const int& Get();
    void Error();
};

Status::Status() :
    m_status(EXIT_SUCCESS)
{}

const int& Status::Get()
{
    return m_status;
}

void Status::Error()
{
    m_status |= EXIT_FAILURE;
}

} //!test

} //!basic

#endif //!BASIC_TEST_STATUS_H_

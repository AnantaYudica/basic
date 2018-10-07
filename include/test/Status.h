#ifndef BASIC_TEST_STATUS_H_
#define BASIC_TEST_STATUS_H_

#include <cstdlib>
#include <utility>

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
    Status(const Status& cpy) = delete;
    Status(Status&& mov);
public:
    Status& operator=(const Status& cpy) = delete;
    Status& operator=(Status&& mov) = delete;
public:
    const int& Get();
    void Error();
};

Status::Status() :
    m_status(EXIT_SUCCESS)
{}

Status::Status(Status&& mov) :
    m_status(mov.m_status)
{
    mov.m_status = EXIT_SUCCESS;
}

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

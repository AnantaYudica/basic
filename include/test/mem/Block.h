#ifndef BASIC_TEST_MEM_BLOCK_H_
#define BASIC_TEST_MEM_BLOCK_H_

#ifdef USING_BASIC_TEST_MEMORY

#include <cstdlib>

namespace basic
{
namespace test
{
namespace mem
{

class Block
{
    void * m_pointer;
    std::size_t m_size;
    char * m_file;
    int m_line;
public:
    Block() :
        m_pointer(nullptr),
        m_size(0),
        m_file(nullptr),
        m_line(-1)
    {}
    Block(void * p, std::size_t s) :
        m_pointer(p),
        m_size(s),
        m_file(nullptr),
        m_line(-1)
    {

    }
    template<std::size_t N>
    Block(void * p, std::size_t s, const char (&f)[N], const int& l) :
        m_pointer(p),
        m_size(s),
        m_file((char*)std::malloc((N + 1) * sizeof(char))),
        m_line(l)
    {
        for (std::size_t i = 0; i < N; ++i)
            m_file[i] = f[i];
        m_file[N] = 0;
    }
    ~Block()
    {
        if (m_file != nullptr)
            std::free(m_file);
    }
    Block& operator=(const Block& cpy) = delete;
    Block& operator=(Block&& mov)
    {
        if (this != &mov)
        {
            if (this->m_file != nullptr)
                free(m_file);
            m_pointer = mov.m_pointer;
            mov.m_pointer = nullptr;
            m_size = mov.m_size;
            mov.m_size = 0;
            m_file = mov.m_file,
            mov.m_file = nullptr;
            m_line = mov.m_line;
            mov.m_line = -1;
        }
        return *this;
    }
    void* Pointer() const
    {
        return m_pointer;
    }
    std::size_t Size() const
    {
        return m_size;
    }
    char* File() const
    {
        return m_file;
    }
    int Line() const
    {
        return m_line;
    }
};

} //!mem

} //!test

} //!basic

#endif //!USING_BASIC_TEST_MEMORY

#endif //!BASIC_TEST_MEM_BLOCK_H_

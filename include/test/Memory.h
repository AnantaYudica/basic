#ifndef BASIC_TEST_MEMORY_H_
#define BASIC_TEST_MEMORY_H_

#ifdef USING_BASIC_TEST_MEMORY

#ifndef BASIC_TEST_MEMORY_INIT_BLOCK_SIZE
#define BASIC_TEST_MEMORY_INIT_BLOCK_SIZE 10
#endif //!BASIC_TEST_MEMORY_INIT_BLOCK_SIZE

#ifndef BASIC_TEST_MEMORY_MULTIPLY_BLOCK_SIZE
#define BASIC_TEST_MEMORY_MULTIPLY_BLOCK_SIZE 10
#endif //!BASIC_TEST_MEMORY_MULTIPLY_BLOCK_SIZE

#include "Output.h"
#include "mem/Block.h"

namespace basic
{
namespace test
{

template<typename Tout = Output<>>
class Memory final
{
private:
    mem::Block* m_blocks;
    std::size_t m_blocksLength;
    std::size_t m_blocksSize;
    Tout& m_output;
public:
    Memory(Tout& output);
public:
    ~Memory();
private:
    void ReallocationBlock();
    void AppendBlock(mem::Block& b);
public:
    void Register(void* p, const std::size_t s);
    template<std::size_t N>
    void Register(void* p, const std::size_t s,
        const char (&f)[N], const int& l);
    void Unregister(void * p);
    bool HasRegister(void * p);
};

template<typename Tout>
Memory<Tout>::Memory(Tout& output) :
    m_blocks(nullptr),
    m_blocksLength(BASIC_TEST_MEMORY_INIT_BLOCK_SIZE),
    m_blocksSize(0),
    m_output(output)
{
    m_blocks = (mem::Block*)std::malloc(m_blocksLength * 
        sizeof(mem::Block));
    assert(m_blocks != NULL);
    m_output.Debug("Memory Register begin with size %d\n", 
        m_blocksLength * sizeof(mem::Block));
}

template<typename Tout>
Memory<Tout>::~Memory()
{
    if (m_blocksSize != 0)
    {
        m_output.Debug("block size : %zu", m_blocksSize);
        for (std::size_t i = 0; i < m_blocksSize; ++i)
        {
            m_output.Error("pointer {addr : %p, size : %zu byte} "
                "has not deallocation\n", (m_blocks + i)->Pointer(), 
                (m_blocks + i)->Size());
            if ((m_blocks + i)->File() != nullptr)
            {
                m_output.Error(" in file %s, line %zu\n", 
                    (m_blocks + i)->File(), (m_blocks + i)->Line());
            }
        }
    }
    if (m_blocks != nullptr)
    {
        std::free(m_blocks);
        m_output.Debug("Memory Register end\n");
    }
}

template<typename Tout>
void Memory<Tout>::ReallocationBlock()
{
    if (m_blocksSize == m_blocksLength)
    {
        m_blocksLength *= BASIC_TEST_MEMORY_MULTIPLY_BLOCK_SIZE;
        m_blocks = (mem::Block*)std::realloc(m_blocks,
            m_blocksLength * sizeof(mem::Block));
        assert(m_blocks != NULL);
        
        m_output.Debug("Memory Register realloc with length %zu " 
            "and size %zu bytes\n", m_blocksLength, 
            m_blocksLength * sizeof(mem::Block));
    }
}

template<typename Tout>
void Memory<Tout>::AppendBlock(mem::Block& b)
{
    if (!HasRegister(b.Pointer()))
    {
        m_output.Debug("allocation memory : {pointer : %p, size : %zu}\n",
                b.Pointer(), b.Size());
        *(m_blocks + m_blocksSize) = std::move(b);
        ++m_blocksSize; 
    }
    else
    {
        m_output.Error("Memory Register duplicate");
    }
}

template<typename Tout>
void Memory<Tout>::Register(void* p, const std::size_t s)
{
    assert(p != NULL);
    assert(m_blocks != NULL);
    ReallocationBlock();
    mem::Block b(p, s);
    AppendBlock(b);
}

template<typename Tout>
template<std::size_t N>
void Memory<Tout>::Register(void* p, const std::size_t s,
    const char (&f)[N], const int& l)
{
    assert(p != NULL);
    assert(m_blocks != NULL);
    ReallocationBlock();
    mem::Block b(p, s, f, l);
    AppendBlock(b);
}

template<typename Tout>
void Memory<Tout>::Unregister(void * p)
{
    bool found = false;
    std::size_t iReplace = 0;
    for (std::size_t i = 0; i < m_blocksSize; ++i)
    {
        if (!found)
        {
            found = (p == (m_blocks + i)->Pointer());
            iReplace = i;
            if (found)
            {
                m_output.Debug("deallocation memory :"" {pointer : %p, "
                    "size : %zu}\n", (m_blocks + i)->Pointer(),
                    (m_blocks + i)->Size());
            }
        }
        else
        {
            *(m_blocks + iReplace++) =
                std::move(*(m_blocks + i));
        }
    }
    if (found) --m_blocksSize;
}

template<typename Tout>
bool Memory<Tout>::HasRegister(void * p)
{
    if (m_blocksSize == 0) return false;
    for (std::size_t i = 0; i < m_blocksSize; ++i)
    {
        if (p == (m_blocks + i)->Pointer())
            return true;
    }
    return false;
}

} //!test

} //!basic

#endif //!USING_BASIC_TEST_MEMORY

#endif //!BASIC_TEST_MEMORY_H_

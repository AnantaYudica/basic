#ifndef BASIC_TEST_VAL_SEQUENCE_H_
#define BASIC_TEST_VAL_SEQUENCE_H_

#include "../type/val/seq/Make.h"
#include "../type/val/seq/formula/Arithmetic.h"

#include <utility>

namespace basic
{
namespace test
{
namespace val
{

template<typename T, std::size_t S>
class Sequence
{
private:
    typedef typename test::type::val::seq::Make<std::size_t, 0, S,
        test::type::val::seq::formula::Arithmetic<std::size_t, 
            int, 1>>::Type IndexesSequenceType;
public:
    typedef T Type;
    typedef Type& AtType;
    typedef const Type& ConstAtType;
public:
    static constexpr std::size_t Size = S;
private:
    T m_values[S];
public:
    Sequence();
    template<typename... TVals>
    Sequence(const TVals&... vals);
    Sequence(const Sequence<T, S>& cpy);
    Sequence(Sequence<T, S>&& mov);
public:
    Sequence<T, S>& operator=(const Sequence<T, S>& cpy);
    Sequence<T, S>& operator=(Sequence<T, S>&& mov);
private:
    Sequence<T, S>& Assign(const Sequence<T, S>& cpy, 
        test::type::val::Sequence<std::size_t>);
    template<std::size_t Index, std::size_t... Indexes>
    Sequence<T, S>& Assign(const Sequence<T, S>& cpy, 
        test::type::val::Sequence<std::size_t, Index, Indexes...>);
    Sequence<T, S>& Assign(Sequence<T, S>&& mov, 
        test::type::val::Sequence<std::size_t>);
    template<std::size_t Index, std::size_t... Indexes>
    Sequence<T, S>& Assign(Sequence<T, S>&& mov, 
        test::type::val::Sequence<std::size_t, Index, Indexes...>);
public:
    template<std::size_t I>
    AtType At();
    template<std::size_t I>
    ConstAtType At() const;
};

template<typename T>
class Sequence<T, 0>
{
public:
    typedef T Type;
public:
    static constexpr std::size_t Size = 0;
public:
    Sequence();
    Sequence(const Sequence<T, 0>& cpy);
    Sequence(Sequence<T, 0>&& mov);
public:
    Sequence<T, 0>& operator=(const Sequence<T, 0>& cpy);
    Sequence<T, 0>& operator=(Sequence<T, 0>&& mov);
};

template<typename T, std::size_t S>
Sequence<T, S>::Sequence()
{}

template<typename T, std::size_t S>
template<typename... TVals>
Sequence<T, S>::Sequence(const TVals&... vals) :
    m_values{vals...}
{}

template<typename T, std::size_t S>
Sequence<T, S>::Sequence(const Sequence<T, S>& cpy)
{
    Assign(cpy, IndexesSequenceType());
}

template<typename T, std::size_t S>
Sequence<T, S>::Sequence(Sequence<T, S>&& mov)
{
    Assign(std::move(mov), IndexesSequenceType());
}

template<typename T, std::size_t S>
Sequence<T, S>& Sequence<T, S>::operator=(const Sequence<T, S>& cpy)
{
    return Assign(cpy, IndexesSequenceType());
}

template<typename T, std::size_t S>
Sequence<T, S>& Sequence<T, S>::operator=(Sequence<T, S>&& mov)
{
    return Assign(std::move(mov), IndexesSequenceType());
}

template<typename T, std::size_t S>
Sequence<T, S>& Sequence<T, S>::Assign(const Sequence<T, S>& cpy, 
    test::type::val::Sequence<std::size_t>)
{
    return *this;
}

template<typename T, std::size_t S>
template<std::size_t Index, std::size_t... Indexes>
Sequence<T, S>& Sequence<T, S>::Assign(const Sequence<T, S>& cpy, 
    test::type::val::Sequence<std::size_t, Index, Indexes...>)
{
    m_values[Index] = cpy.At<Index>();
    return Assign(cpy, test::type::val::Sequence<std::size_t, Indexes...>());
}

template<typename T, std::size_t S>
Sequence<T, S>& Sequence<T, S>::Assign(Sequence<T, S>&& mov, 
    test::type::val::Sequence<std::size_t>)
{
    return *this;
}

template<typename T, std::size_t S>
template<std::size_t Index, std::size_t... Indexes>
Sequence<T, S>& Sequence<T, S>::Assign(Sequence<T, S>&& mov, 
    test::type::val::Sequence<std::size_t, Index, Indexes...>)
{
    m_values[Index] = std::move(mov.At<Index>());
    return Assign(std::move(mov), 
        test::type::val::Sequence<std::size_t, Indexes...>());
}

template<typename T, std::size_t S>
template<std::size_t I>
typename Sequence<T, S>::AtType Sequence<T, S>::At()
{
    return m_values[I];
}

template<typename T, std::size_t S>
template<std::size_t I>
typename Sequence<T, S>::ConstAtType Sequence<T, S>::At() const
{
    return m_values[I];
}

template<typename T>
Sequence<T, 0>::Sequence()
{}

template<typename T>
Sequence<T, 0>::Sequence(const Sequence<T, 0>& cpy)
{}

template<typename T>
Sequence<T, 0>::Sequence(Sequence<T, 0>&& mov)
{}

template<typename T>
Sequence<T, 0>& Sequence<T, 0>::operator=(const Sequence<T, 0>& cpy)
{}

template<typename T>
Sequence<T, 0>& Sequence<T, 0>::operator=(Sequence<T, 0>&& mov)
{}

} //!val

} //!test

}//!basic

#endif //!BASIC_TEST_VAL_SEQUENCE_H_

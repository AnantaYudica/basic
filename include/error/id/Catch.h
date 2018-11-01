#ifndef BASIC_ERROR_IDENTIFICATION_CATCH_H_
#define BASIC_ERROR_IDENTIFICATION_CATCH_H_

#include "../Identification.h"
#include "Default.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

class Catch : public Identification
{
public:
    constexpr Catch();
    constexpr Catch(const Identification& id);
public:
    Catch(const Catch& cpy);
    Catch(Catch&& mov);
public:
    ~Catch();
public:
    Catch& operator=(const Catch&) = delete;
    Catch& operator=(Catch&&) = delete;
};

constexpr Catch::Catch() :
    Identification(Default())
{}

constexpr Catch::Catch(const Identification& id) :
    Identification(id.Flag.Default, id.Flag.Standard, 1, id.Error)
{}

Catch::Catch(const Catch& cpy) :
    Identification(cpy)
{}

Catch::Catch(Catch&& mov) :
    Identification(std::move(mov))
{}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_IDENTIFICATION_CATCH_H_

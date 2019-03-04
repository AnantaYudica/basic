#ifndef BASIC_ERROR_SYSTEM_TMPL_IMP_EXIT_H_
#define BASIC_ERROR_SYSTEM_TMPL_IMP_EXIT_H_

#include "../../../intf/Exit.h"
#include "../categ/Base.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace imp
{

template<typename TCategoryTrait, bool HasCleanup = 
    std::is_base_of<error::intf::Exit, TCategoryTrait>::value>
class Exit : 
    virtual public tmpl::categ::Base<TCategoryTrait>,
    public error::intf::Exit
{
protected:
    Exit() noexcept;
public:
    Exit(const Exit<TCategoryTrait, HasCleanup> & cpy) noexcept = delete;
    Exit(Exit<TCategoryTrait, HasCleanup> && mov) noexcept;
public:
    ~Exit() noexcept = default;
public:
    Exit<TCategoryTrait, HasCleanup> & 
    operator=(const Exit<TCategoryTrait, HasCleanup> & cpy) = delete;
    Exit<TCategoryTrait, HasCleanup> & 
    operator=(Exit<TCategoryTrait, HasCleanup> && mov) = delete;
private:
    void Cleanup(int sig) noexcept;
};

template<typename TCategoryTrait, bool HasCleanup>
Exit<TCategoryTrait, HasCleanup>::Exit() noexcept :
    tmpl::categ::Base<TCategoryTrait>(),
    error::intf::Exit()
{}

template<typename TCategoryTrait, bool HasCleanup>
Exit<TCategoryTrait, HasCleanup>::
    Exit(Exit<TCategoryTrait, HasCleanup> && mov) noexcept :
        tmpl::categ::Base<TCategoryTrait>(std::move(mov)),
        error::intf::Exit(std::move(mov))
{}

template<typename TCategoryTrait, bool HasCleanup>
void Exit<TCategoryTrait, HasCleanup>::Cleanup(int sig) noexcept
{}

} //!imp

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_IMP_EXIT_H_

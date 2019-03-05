#ifndef BASIC_ERROR_SYS_TMPL_CATEG_IMP_EXIT_HASCLEANUP_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_IMP_EXIT_HASCLEANUP_H_

#include "../Exit.h"
#include "../../../../intf/Exit.h"
#include "../../categ/Base.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace sys
{
namespace tmpl
{
namespace imp
{

template<typename TCategoryTrait>
class Exit<TCategoryTrait, true> : 
    virtual public tmpl::categ::Base<TCategoryTrait>,
    public error::intf::Exit
{
protected:
    Exit() noexcept;
public:
    Exit(const Exit<TCategoryTrait, true> & cpy) noexcept = delete;
    Exit(Exit<TCategoryTrait, true> && mov) noexcept;
public:
    ~Exit() noexcept = default;
public:
    Exit<TCategoryTrait, true> & 
    operator=(const Exit<TCategoryTrait, true> & cpy) = delete;
    Exit<TCategoryTrait, true> & 
    operator=(Exit<TCategoryTrait, true> && mov) = delete;
private:
    void Cleanup(int sig) noexcept;
};

template<typename TCategoryTrait>
Exit<TCategoryTrait, true>::Exit() noexcept :
    tmpl::categ::Base<TCategoryTrait>(),
    error::intf::Exit()
{}

template<typename TCategoryTrait>
Exit<TCategoryTrait, true>::Exit(Exit<TCategoryTrait, true> && mov) noexcept :
        tmpl::categ::Base<TCategoryTrait>(std::move(mov)),
        error::intf::Exit(std::move(mov))
{}

template<typename TCategoryTrait>
void Exit<TCategoryTrait, true>::Cleanup(int sig) noexcept
{
    static_cast<error::intf::Exit &>(this->GetCategoryTrait()).Cleanup(sig);
}

} //!imp

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_IMP_EXIT_HASCLEANUP_H_

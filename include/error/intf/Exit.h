#ifndef BASIC_ERROR_INTF_EXIT_H_
#define BASIC_ERROR_INTF_EXIT_H_

namespace basic
{
namespace error
{
namespace intf
{

class Exit
{
protected:
    Exit() = default;
    virtual ~Exit() = default;
public:
    virtual void Cleanup(int sig) noexcept = 0;
};

} //!intf

} //!error

} //!basic

#endif //!BASIC_ERROR_INTF_EXIT_H_

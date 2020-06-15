#ifndef BASIC_ERR_INTF_EXIT_H_
#define BASIC_ERR_INTF_EXIT_H_

namespace basic
{
namespace err
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

} //!err

} //!basic

#endif //!BASIC_ERR_INTF_EXIT_H_

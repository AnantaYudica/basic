#ifndef BASIC_ERROR_ID_NUMBER_H_
#define BASIC_ERROR_ID_NUMBER_H_

#include "../Identification.h"

namespace basic
{
namespace error
{
namespace id
{

NumberType Number(const Identification& id_)
{
    return reinterpret_cast<const NumberType&>(id_);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_NUMBER_H_

#ifndef _INCLUDE_JSON_WRAPPER_EXCEPTIONS_XJSONERROR_HPP_
#define _INCLUDE_JSON_WRAPPER_EXCEPTIONS_XJSONERROR_HPP_

#include <stdexcept>

namespace Wrappers
{
    /**
     * @exception XJsonError
     * @brief This exception class is thrown on any JSON (de)serialization errors.
     */
    class XJsonError : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

}  // namespace Wrappers

#endif  // _INCLUDE_JSON_WRAPPER_EXCEPTIONS_XJSONERROR_HPP_

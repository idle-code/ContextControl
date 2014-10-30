#pragma once

#include "String.hpp"
#include <stdexcept>

namespace ContextControl {

class ContextControlException : public std::runtime_error {
public:
  ContextControlException(String message)
    : std::runtime_error(message)
  { }
};

} /* namespace ContextControl */


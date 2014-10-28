#pragma once

#include "TreeNode.hpp"

namespace ContextControl {

class Command {
public:
  static Command Parse(const TreeNode &context, String expression)
  {
    return Command();
  }
public:

  bool IsSimple(void) const
  {

  }

  String ToString(void) const
  {

  }

};

} /* namespace ContextControl */


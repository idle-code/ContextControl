#pragma once

#include "TreeValue.hpp"

#include <cstdlib>

namespace ContextControl {

class TreeNode {
public:
  TreeNode(TreeValue::TypeKind node_type = TreeValue::TypeKind::Void)
    : _Value(node_type)
  { }

  std::size_t Size(void) { return 0; }
  TreeValue::TypeKind Type(void) { return _Value.Type(); }

  template<typename TargetType>
  TargetType ValueAs(void)
  {
    return TargetType();
  }

private:
  TreeValue _Value;
};

} /* ContextControl namespace */


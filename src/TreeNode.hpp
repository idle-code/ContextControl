#pragma once

#include "TreeValue.hpp"

#include <cstdlib>

typedef std::string String;

namespace ContextControl {

class TreeNode {
public:
  TreeNode(NodeKind node_type = NodeKind::Void)
    : _Value(node_type)
  { }

  std::size_t Size(void) { return 0; }
  NodeKind Type(void) { return _Value.Type(); }

  template<typename TargetType>
  TargetType ValueAs(void)
  {
    return _Value.ValueAs<TargetType>();
  }

  template<typename SourceType>
  void SetValueTo(SourceType value)
  {
    _Value.SetValueTo(value);
  }

  void Create(String new_sub_name, NodeKind new_sub_type)
  {

  }

  bool Exists(String sub_name)
  {
    return false;
  }

private:
  TreeValue _Value;
};

} /* ContextControl namespace */


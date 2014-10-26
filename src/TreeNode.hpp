#pragma once

#include "TreeValue.hpp"

#include <cstdlib>
#include <list>

typedef std::string String;

namespace ContextControl {

class TreeNode {
public:
  class ExistsException : std::logic_error {
  public:
    ExistsException(String node_name)
      : std::logic_error("Node named '" + node_name + "' exists") { }
  };

  class DoesntExistsException : std::logic_error {
  public:
    DoesntExistsException(String node_name)
      : std::logic_error("Node named '" + node_name + "' doesn't exists") { }
  };

  typedef std::list<String> NameList;
public:
  TreeNode(NodeKind node_type = NodeKind::Void)
    : _Value(node_type)
  { }

  std::size_t Size(void) { return 0; }
  NodeKind Type(void) { return _Value.Type(); }

  template<typename TargetType>
  TargetType GetValueAs(void)
  {
    return _Value.GetValueAs<TargetType>();
  }

  template<typename SourceType>
  void SetValueTo(SourceType value)
  {
    _Value.SetValueTo(value);
  }

  void Create(String new_sub_name, NodeKind new_sub_type = NodeKind::Void)
  {

  }

  void Delete(String sub_name)
  {

  }

  bool Exists(String sub_name)
  {
    return false;
  }

  NameList List(void)
  {
    return NameList();
  }

private:
  TreeValue _Value;
};

} /* ContextControl namespace */


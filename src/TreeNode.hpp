#pragma once

#include "TreeValue.hpp"

#include <cstdlib>
#include <list>
#include <utility>
#include <memory>

namespace ContextControl {

class TreeNode {
public:
  class ExistsException : std::logic_error {
  public:
    ExistsException(String node_name)
      : std::logic_error{"Node named '" + node_name + "' exists"} { }
  };

  class DoesntExistsException : std::logic_error {
  public:
    DoesntExistsException(String node_name)
      : std::logic_error{"Node named '" + node_name + "' doesn't exists"} { }
  };

  typedef std::list<String> NameList;
public:
  TreeNode(NodeKind node_type = NodeKind::Void)
    : _Value{node_type}
  { }

  std::size_t Size(void)
  {
    return _Subnodes.size();
  }

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

  void Create(const String new_sub_name, NodeKind new_sub_type = NodeKind::Void)
  {
    if (Exists(new_sub_name))
      throw ExistsException{new_sub_name};

    _Subnodes.push_back(std::make_pair(
          new_sub_name,
          std::unique_ptr<TreeNode>(new TreeNode{new_sub_type})
          ));
  }

  void Delete(const String sub_name)
  {
    if (!Exists(sub_name))
      throw DoesntExistsException{sub_name};

    _Subnodes.remove_if([&sub_name] (SubnodeMapPair &key_value) { return sub_name == key_value.first; });
  }

  bool Exists(const String sub_name)
  {
    for(SubnodeMapPair &key_value : _Subnodes) {
      if (sub_name == std::get<0>(key_value))
        return true;
    }
    return false;
  }

  NameList List(void)
  {
    NameList names;
    for(auto &key_value : _Subnodes) {
      names.push_back(std::get<0>(key_value));
    }
    return names;
  }

private:
  TreeValue _Value;
  typedef std::pair<String, std::unique_ptr<TreeNode>> SubnodeMapPair;
  typedef std::list<SubnodeMapPair> SubnodeMap;
  SubnodeMap _Subnodes;
};

} /* ContextControl namespace */


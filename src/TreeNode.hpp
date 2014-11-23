#pragma once

#include "TreeValue.hpp"
#include "ContextControlException.hpp"

#include <cstdlib>
#include <deque>
#include <utility>
#include <memory>

namespace ContextControl {

class TreeNode {
public:
  class ExistsException : public ContextControlException {
  public:
    ExistsException(String node_name)
      : ContextControlException{"Node named '" + node_name + "' exists"} { }
  };

  class DoesntExistsException : public ContextControlException {
  public:
    DoesntExistsException(String node_name)
      : ContextControlException{"Node named '" + node_name + "' doesn't exists"} { }
  };

  class InvalidPathException : public ContextControlException { //CHECK: rename to InvalidNodeNameException?
  public:
    InvalidPathException(String path)
      : ContextControlException{"Invalid path: '" + path + "'"} { }
  };

  typedef std::list<String> NameList;
  typedef std::shared_ptr<TreeNode> Pointer;
  static const Char PathDelimiter = '.';

  friend bool operator==(const TreeNode &left, const TreeNode &right);
  friend bool operator!=(const TreeNode &left, const TreeNode &right);

public:
  TreeNode(NodeKind node_type = NodeKind::Void)
    : _Value{node_type}
  { }

  std::size_t Size(void) const
  {
    return _Subnodes.size();
  }

  NodeKind Type(void) const { return _Value.Type(); }

  template<typename TargetType>
  TargetType GetValueAs(void) const
  {
    return _Value.GetValueAs<TargetType>();
  }

  template<typename SourceType>
  void SetValueTo(SourceType value)
  {
    _Value.SetValueTo(value);
  }

  void Create(const String new_sub_name)
  {
    Create(NodeKind::Void, new_sub_name);
  }

  void Create(NodeKind new_sub_type)
  {
    Create(new_sub_type, "");
  }

  void Create(NodeKind new_sub_type, const String new_sub_name)
  {
    if (new_sub_name.length() > 0 && Exists(new_sub_name))
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

    //_Subnodes.remove_if([&sub_name](SubnodeMapPair &key_value) { return sub_name == key_value.first; });
    _Subnodes.erase(
      std::remove_if(
          _Subnodes.begin(),
          _Subnodes.end(),
          [&sub_name](SubnodeMapPair &key_value) {
            return sub_name == key_value.first;
          }),
      _Subnodes.end()
      );
  }

  void Clear(void)
  {
    for(const String &subnode_name : List()) {
      Delete(subnode_name);
    }
  }

  bool Exists(const String sub_name) const
  {
    for(const SubnodeMapPair &key_value : _Subnodes) {
      if (sub_name == std::get<0>(key_value))
        return true;
    }
    return false;
  }

  NameList List(void) const
  {
    NameList names;
    for(auto &key_value : _Subnodes) {
      names.push_back(std::get<0>(key_value));
    }
    return names;
  }

  TreeNode& GetNode(const String path)
  {
    std::list<String> path_components = Split(path, PathDelimiter);
    return GetNode(path_components);
  }

  const TreeNode& GetNode(const String path) const
  {
    return const_cast<TreeNode*>(this)->GetNode(path);
  }

  TreeNode& operator[](const String path)
  {
    return GetNode(path);
  }

  const TreeNode& operator[](const String path) const
  {
    return const_cast<TreeNode*>(this)->GetNode(path);
  }

  friend bool operator==(const TreeNode &left, const TreeNode &right);
  friend bool operator!=(const TreeNode &left, const TreeNode &right);

private:
  TreeNode& GetNode(std::list<String> &path_components) const
  {
    if (path_components.empty())
      throw InvalidPathException{""};

    const String name = Trim(path_components.front());
    path_components.pop_front();

    if (name.empty())
      throw InvalidPathException{name};

    if (name[0] == '$') {
      long node_index = std::stol(name.substr(1));

      if (node_index < 0)
        throw InvalidPathException{name};
      else if (node_index >= _Subnodes.size())
        throw DoesntExistsException{name};
      else
        return *std::get<1>(_Subnodes[node_index]);
    }
    else {
      for(const SubnodeMapPair &key_value : _Subnodes) {
        if (name == std::get<0>(key_value)) {
          if (path_components.empty())
            return *std::get<1>(key_value);
          else
            return std::get<1>(key_value)->GetNode(path_components);
        }
      }
    }

    throw DoesntExistsException{name};
  }

private:
  TreeValue _Value;
  typedef std::pair<String, std::unique_ptr<TreeNode>> SubnodeMapPair;
  typedef std::deque<SubnodeMapPair> SubnodeMap;
  SubnodeMap _Subnodes;

};

//inline bool
//operator==(const TreeNode &left, const TreeNode &right)
//{
//  if (left._Value != right._Value)
//    return false;
//
//  TreeNode::SubnodeMap::const_iterator left_iterator = left._Subnodes.begin();
//  TreeNode::SubnodeMap::const_iterator right_iterator = right._Subnodes.begin();
//
//  //TODO: Implement tests for this operator first (2014.10.31)
//
//  return false;
//}

} /* ContextControl namespace */


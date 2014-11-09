#pragma once

#include "TreeNode.hpp"
#include "ContextControlException.hpp"
#include <memory>

namespace ContextControl {

class NodeListException : public ContextControlException {
public:
  NodeListException(String message)
    : ContextControlException{message}
  { }
};

class NodeList {
private:
  typedef std::list<TreeNode::Pointer> ListContainerType;
public:
  typedef ListContainerType::iterator iterator;
  typedef ListContainerType::const_iterator const_iterator;
public:
  size_t Size(void) const
  {
    return _ListContainer.size();
  }

  iterator begin(void)
  {
    return _ListContainer.begin();
  }

  const_iterator begin(void) const
  {
    return _ListContainer.begin();
  }

  iterator end(void)
  {
    return _ListContainer.end();
  }
  
  const_iterator end(void) const
  {
    return _ListContainer.end();
  }

  void Add(TreeNode::Pointer node_to_add)
  {
    if (node_to_add == nullptr)
      throw NodeListException{"Cannot add null TreeNode to NodeList"};
    _ListContainer.push_back(node_to_add);
  }

private:
  ListContainerType _ListContainer;
};

} /* namespace ContextControl */


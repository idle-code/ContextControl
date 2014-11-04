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
public:
  size_t Size(void) const
  {
    return _ListContainer.size();
  }

  iterator begin(void)
  {
    return _ListContainer.begin();
  }

  iterator end(void)
  {
    return _ListContainer.end();
  }

  void Add(TreeNode::Pointer node_to_add)
  {
    _ListContainer.push_back(node_to_add);
  }

private:
  ListContainerType _ListContainer;
};

} /* namespace ContextControl */


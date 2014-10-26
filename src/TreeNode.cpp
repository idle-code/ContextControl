#include "TreeNode.hpp"

namespace ContextControl {

bool
operator==(const TreeNode &left, const TreeNode &right)
{
  if (left.Type() != right.Type())
    return false;

  if (left._Value != right._Value)
    return false;

  if (left.Size() != right.Size())
    return false;

  TreeNode::SubnodeMap::const_iterator li = left._Subnodes.begin();
  TreeNode::SubnodeMap::const_iterator li_end = left._Subnodes.end();
  TreeNode::SubnodeMap::const_iterator ri = right._Subnodes.begin();
  TreeNode::SubnodeMap::const_iterator ri_end = right._Subnodes.end();
  while (li != li_end && ri != ri_end) {
    if (*li != *ri)
      return false;
  }

  if (li != li_end)
    return false;
  if (ri != ri_end)
    return false;

  return true;
}

bool
operator!=(const TreeNode &left, const TreeNode &right)
{
  return !(left == right);
}


} /* ContextControl namespace */


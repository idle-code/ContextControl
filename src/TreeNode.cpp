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
  const TreeNode::SubnodeMap::const_iterator li_end = left._Subnodes.end();
  TreeNode::SubnodeMap::const_iterator ri = right._Subnodes.begin();
  const TreeNode::SubnodeMap::const_iterator ri_end = right._Subnodes.end();
  while (li != li_end && ri != ri_end) {
    if (li->first != ri->first) // there is difference in naming
      return false;
    if (*li->second != *ri->second) // there is difference in sub itself
      return false;

    ++li; ++ri;
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


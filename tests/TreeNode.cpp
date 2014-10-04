#include "TreeNode.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeNodeTest, EmptyTreeNode)
{
  cc::TreeNode tree_node;

  ASSERT_EQ(0, tree_node.size());
}



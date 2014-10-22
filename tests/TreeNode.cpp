#include "TreeNode.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeNodeTest, VoidNode)
{
  cc::TreeNode tree_node;

  ASSERT_EQ(cc::NodeKind::Void, tree_node.Type());
  ASSERT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultIntegerNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Integer};

  ASSERT_EQ(cc::NodeKind::Integer, tree_node.Type());
  ASSERT_EQ(0, tree_node.ValueAs<int>());
  ASSERT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, IntegerNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Integer};

  tree_node.SetValueTo(1337);
  //tree_node = 1337;

  ASSERT_EQ(cc::NodeKind::Integer, tree_node.Type());
  ASSERT_EQ(1337, tree_node.ValueAs<int>());
  ASSERT_EQ(0, tree_node.Size());
}

//TODO: uncomment when TreeValue will be functional (2014.10.06)
//TEST(TreeNodeTest, InitializedIntegerNode)
//{
//  cc::TreeNode tree_node{cc::TreeNode::IntegerType, 123};
//
//  ASSERT_EQ(cc::TreeNode::IntegerType, tree_node.Type());
//  ASSERT_EQ(123, tree_node.ValueAs<int>());
//  ASSERT_EQ(0, tree_node.Size());
//}


#include "TreeNode.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeNodeTest, EmptyNode)
{
  cc::TreeNode tree_node;

  //ASSERT_EQ(cc::TreeValue::VoidType, tree_node.Type());
  //ASSERT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, IntegerNode)
{
  //cc::TreeNode tree_node{cc::TreeValue::IntegerType};

  //ASSERT_EQ(cc::TreeValue::IntegerType, tree_node.Type());
  //ASSERT_EQ(0, tree_node.ValueAs<int>());
  //ASSERT_EQ(0, tree_node.Size());
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


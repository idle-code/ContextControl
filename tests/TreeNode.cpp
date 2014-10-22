#include "TreeNode.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeNodeTest, VoidNode)
{
  cc::TreeNode tree_node;

  ASSERT_EQ(cc::NodeKind::Void, tree_node.Type());

  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultIntegerNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Integer};

  ASSERT_EQ(cc::NodeKind::Integer, tree_node.Type());

  EXPECT_EQ(0, tree_node.ValueAs<int>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, IntegerNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Integer};

  tree_node.SetValueTo(1337);
  //tree_node = 1337;

  ASSERT_EQ(cc::NodeKind::Integer, tree_node.Type());

  EXPECT_EQ(1337, tree_node.ValueAs<int>());
  EXPECT_EQ(std::string("1337"), tree_node.ValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, FractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  tree_node.SetValueTo(3.1415);

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(3.1415, tree_node.ValueAs<double>());
  EXPECT_EQ(0, tree_node.Size());
}


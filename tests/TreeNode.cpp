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

TEST(TreeNodeTest, DefaultFractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(0.0, tree_node.ValueAs<double>());
  EXPECT_EQ("0", tree_node.ValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, FractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  tree_node.SetValueTo(3.1415);

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(3.1415, tree_node.ValueAs<double>());
  EXPECT_EQ("3.1415", tree_node.ValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultStringNode)
{
  cc::TreeNode tree_node{cc::NodeKind::String};

  ASSERT_EQ(cc::NodeKind::String, tree_node.Type());

  EXPECT_EQ("", tree_node.ValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, StringNode)
{
  cc::TreeNode tree_node{cc::NodeKind::String};

  tree_node.SetValueTo("TEST");

  ASSERT_EQ(cc::NodeKind::String, tree_node.Type());

  EXPECT_EQ("TEST", tree_node.ValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeNodeTest, NodeCreate)
{
  cc::TreeNode root_node;

  root_node.Create("child", cc::NodeKind::Integer);

  EXPECT_EQ(1, root_node.Size());
  EXPECT_TRUE(root_node.Exists("child"));
}


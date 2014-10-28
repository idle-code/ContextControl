#include "TreeNode.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeNodeTest, VoidNode)
{
  cc::TreeNode tree_node;

  ASSERT_EQ(cc::NodeKind::Void, tree_node.Type());

  ASSERT_THROW(tree_node.GetValueAs<int>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(tree_node.SetValueTo(true), cc::TreeValue::InvalidCastException);
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultIntegerNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Integer};

  ASSERT_EQ(cc::NodeKind::Integer, tree_node.Type());

  EXPECT_EQ(0, tree_node.GetValueAs<int>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, IntegerNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Integer};

  tree_node.SetValueTo(1337);
  //tree_node = 1337;

  ASSERT_EQ(cc::NodeKind::Integer, tree_node.Type());

  EXPECT_EQ(1337, tree_node.GetValueAs<int>());
  EXPECT_EQ(std::string("1337"), tree_node.GetValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultFractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(0.0, tree_node.GetValueAs<double>());
  EXPECT_EQ("0", tree_node.GetValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, FractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  tree_node.SetValueTo(3.1415);

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(3.1415, tree_node.GetValueAs<double>());
  EXPECT_EQ("3.1415", tree_node.GetValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultStringNode)
{
  cc::TreeNode tree_node{cc::NodeKind::String};

  ASSERT_EQ(cc::NodeKind::String, tree_node.Type());

  EXPECT_EQ("", tree_node.GetValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, StringNode)
{
  cc::TreeNode tree_node{cc::NodeKind::String};

  tree_node.SetValueTo("TEST");

  ASSERT_EQ(cc::NodeKind::String, tree_node.Type());

  EXPECT_EQ("TEST", tree_node.GetValueAs<std::string>());
  EXPECT_EQ(0, tree_node.Size());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeNodeTest, NodeCreate)
{
  cc::TreeNode root_node;

  root_node.Create("child", cc::NodeKind::Integer);

  EXPECT_EQ(1, root_node.Size());
  EXPECT_TRUE(root_node.Exists("child"));

  root_node.Create("nephew");

  EXPECT_EQ(2, root_node.Size());
  EXPECT_TRUE(root_node.Exists("nephew"));
}

TEST(TreeNodeTest, NodeCreateAlreadyExisting)
{
  cc::TreeNode root_node;

  root_node.Create("child", cc::NodeKind::Integer);

  EXPECT_EQ(1, root_node.Size());
  ASSERT_TRUE(root_node.Exists("child"));

  ASSERT_THROW(root_node.Create("child"), cc::TreeNode::ExistsException);
}

TEST(TreeNodeTest, NodeDelete)
{
  cc::TreeNode root_node;

  root_node.Create("child", cc::NodeKind::Integer);

  EXPECT_EQ(1, root_node.Size());
  ASSERT_TRUE(root_node.Exists("child"));

  root_node.Delete("child");

  EXPECT_EQ(0, root_node.Size());
  ASSERT_FALSE(root_node.Exists("child"));
}

TEST(TreeNodeTest, NodeDeleteNonexistent)
{
  cc::TreeNode root_node;

  EXPECT_EQ(0, root_node.Size());
  ASSERT_FALSE(root_node.Exists("child"));
  ASSERT_THROW(root_node.Delete("child"), cc::TreeNode::DoesntExistsException);
}

TEST(TreeNodeTest, NodeList)
{
  cc::TreeNode root_node;

  root_node.Create("B", cc::NodeKind::Integer);
  root_node.Create("A", cc::NodeKind::String);
  root_node.Create("C");

  EXPECT_EQ(3, root_node.Size());
  EXPECT_TRUE(root_node.Exists("A"));
  EXPECT_TRUE(root_node.Exists("B"));
  EXPECT_TRUE(root_node.Exists("C"));

  cc::TreeNode::NameList name_list = root_node.List();

  EXPECT_EQ(3, name_list.size());
  cc::String expected_names[] = {
    cc::String("B"),
    cc::String("A"),
    cc::String("C"),
  };
  int expected_names_iterator = 0;
  for(cc::String name : name_list) {
    EXPECT_EQ(name, expected_names[expected_names_iterator]);
    ++expected_names_iterator;
  }
}

TEST(TreeNodeTest, ClearAllNodes)
{
  cc::TreeNode root_node;

  root_node.Create("B", cc::NodeKind::Integer);
  root_node.Create("A", cc::NodeKind::String);
  root_node.Create("C");

  EXPECT_EQ(3, root_node.Size());

  root_node.Clear();

  ASSERT_EQ(0, root_node.Size());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeNodeTest, SubnodeSimpleAccess)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);
  cc::TreeNode& level1_node = root_node.GetNode("level1");

  EXPECT_EQ(cc::NodeKind::Integer, level1_node.Type());
  level1_node.Create("level2", cc::NodeKind::String);

  cc::TreeNode& level2_node = level1_node.GetNode("level2");
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());
}

TEST(TreeNodeTest, NonexistentSimpleAccess)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);
  ASSERT_THROW(root_node.GetNode("level2"), cc::TreeNode::DoesntExistsException);
}

TEST(TreeNodeTest, PathAccess)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);
  root_node.GetNode("level1").Create("level2", cc::NodeKind::String);

  cc::TreeNode& level2_node = root_node.GetNode("level1.level2");
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());
}

TEST(TreeNodeTest, OperatorPathAccess)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);
  root_node.GetNode("level1").Create("level2", cc::NodeKind::String);

  cc::TreeNode& level2_node = root_node["level1.level2"];
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());
}

TEST(TreeNodeTest, PathWithWhitespaces)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);
  root_node.GetNode("level1").Create("level2", cc::NodeKind::String);

  cc::TreeNode& level2_node = root_node.GetNode("level1.level2");
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());

  cc::TreeNode& level2_node_a = root_node.GetNode("level1 . level2");
  EXPECT_TRUE(level2_node_a == level2_node);

  cc::TreeNode& level2_node_b = root_node.GetNode(" level1.level2  ");
  EXPECT_TRUE(level2_node_b == level2_node);

  ASSERT_THROW(root_node.GetNode("level 1.level 2"), cc::TreeNode::DoesntExistsException);
}

TEST(TreeNodeTest, InvalidPath)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);
  root_node.GetNode("level1").Create("level2", cc::NodeKind::String);

  ASSERT_THROW(root_node.GetNode("level1..level2"), cc::TreeNode::InvalidPathException);
}

TEST(TreeNodeTest, NonexistentSubnodePathAccess)
{
  cc::TreeNode root_node;

  root_node.Create("level1", cc::NodeKind::Integer);

  ASSERT_THROW(root_node.GetNode("level1.level2"), cc::TreeNode::DoesntExistsException);
}


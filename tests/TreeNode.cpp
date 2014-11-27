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
  EXPECT_EQ(cc::String("1337"), tree_node.GetValueAs<cc::String>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultFractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(0.0, tree_node.GetValueAs<double>());
  EXPECT_EQ("0", tree_node.GetValueAs<cc::String>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, FractionalNode)
{
  cc::TreeNode tree_node{cc::NodeKind::Fractional};

  tree_node.SetValueTo(3.1415);

  ASSERT_EQ(cc::NodeKind::Fractional, tree_node.Type());

  EXPECT_DOUBLE_EQ(3.1415, tree_node.GetValueAs<double>());
  EXPECT_EQ("3.1415", tree_node.GetValueAs<cc::String>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, DefaultStringNode)
{
  cc::TreeNode tree_node{cc::NodeKind::String};

  ASSERT_EQ(cc::NodeKind::String, tree_node.Type());

  EXPECT_EQ("", tree_node.GetValueAs<cc::String>());
  EXPECT_EQ(0, tree_node.Size());
}

TEST(TreeNodeTest, StringNode)
{
  cc::TreeNode tree_node{cc::NodeKind::String};

  tree_node.SetValueTo("TEST");

  ASSERT_EQ(cc::NodeKind::String, tree_node.Type());

  EXPECT_EQ("TEST", tree_node.GetValueAs<cc::String>());
  EXPECT_EQ(0, tree_node.Size());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeNodeTest, NodeCreate)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "child");

  EXPECT_EQ(1, root_node.Size());
  EXPECT_TRUE(root_node.Exists("child"));

  root_node.Create("nephew");

  EXPECT_EQ(2, root_node.Size());
  EXPECT_TRUE(root_node.Exists("nephew"));
}

TEST(TreeNodeTest, NodeCreateAlreadyExisting)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "child");

  EXPECT_EQ(1, root_node.Size());
  ASSERT_TRUE(root_node.Exists("child"));

  ASSERT_THROW(root_node.Create("child"), cc::TreeNode::ExistsException);
}

TEST(TreeNodeTest, NodeDelete)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "child");

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

  root_node.Create(cc::NodeKind::Integer, "B");
  root_node.Create(cc::NodeKind::String, "A");
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

  root_node.Create(cc::NodeKind::Integer, "B");
  root_node.Create(cc::NodeKind::String, "A");
  root_node.Create("C");

  EXPECT_EQ(3, root_node.Size());

  root_node.Clear();

  ASSERT_EQ(0, root_node.Size());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeNodeTest, SubnodeSimpleAccess)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "level1");
  cc::TreeNode& level1_node = root_node.GetNode("level1");

  EXPECT_EQ(cc::NodeKind::Integer, level1_node.Type());
  level1_node.Create(cc::NodeKind::String, "level2");

  cc::TreeNode& level2_node = level1_node.GetNode("level2");
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());
}

TEST(TreeNodeTest, NonexistentSimpleAccess)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "level1");
  ASSERT_THROW(root_node.GetNode("level2"), cc::TreeNode::DoesntExistsException);
}

TEST(TreeNodeTest, PathAccess)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "level1");
  root_node.GetNode("level1").Create(cc::NodeKind::String, "level2");

  cc::TreeNode& level2_node = root_node.GetNode("level1.level2");
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());
}

TEST(TreeNodeTest, OperatorPathAccess)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "level1");
  root_node.GetNode("level1").Create(cc::NodeKind::String, "level2");

  cc::TreeNode& level2_node = root_node["level1.level2"];
  EXPECT_EQ(cc::NodeKind::String, level2_node.Type());
}

TEST(TreeNodeTest, PathWithWhitespaces)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "level1");
  root_node.GetNode("level1").Create(cc::NodeKind::String, "level2");

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

  root_node.Create(cc::NodeKind::Integer, "level1");
  root_node.GetNode("level1").Create(cc::NodeKind::String, "level2");

  ASSERT_THROW(root_node.GetNode("level1..level2"), cc::TreeNode::InvalidPathException);
}

TEST(TreeNodeTest, NonexistentSubnodePathAccess)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "level1");

  ASSERT_THROW(root_node.GetNode("level1.level2"), cc::TreeNode::DoesntExistsException);
}

TEST(TreeNodeTest, SequentialPathAccess)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer, "foo");
  root_node["foo"].SetValueTo(111);
  root_node.Create(cc::NodeKind::Integer, "bar");
  root_node["bar"].SetValueTo(222);
  root_node.Create(cc::NodeKind::Integer, "spam");
  root_node["spam"].SetValueTo(333);

  ASSERT_EQ(3, root_node.Size());

  EXPECT_EQ(111, root_node.GetNode("$0").GetValueAs<int>());
  EXPECT_EQ(222, root_node.GetNode("$1").GetValueAs<int>());
  EXPECT_EQ(333, root_node.GetNode("$2").GetValueAs<int>());

  ASSERT_THROW(root_node.GetNode("$5"), cc::TreeNode::DoesntExistsException);
}

TEST(TreeNodeTest, CreateAnonymousNode)
{
  cc::TreeNode root_node;

  root_node.Create(cc::NodeKind::Integer);
  root_node["$0"].SetValueTo(1234);
  root_node.Create(cc::NodeKind::Integer);
  root_node["$1"].SetValueTo(5678);

  ASSERT_EQ(2, root_node.Size());
  ASSERT_EQ(1234, root_node["$0"].GetValueAs<int>());
  ASSERT_EQ(5678, root_node["$1"].GetValueAs<int>());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeNodeTest, SelfComparison)
{
  cc::TreeNode node{cc::NodeKind::Integer};

  ASSERT_EQ(node, node);
}

TEST(TreeNodeTest, DifferentTypeComparison)
{
  cc::TreeNode int_node{cc::NodeKind::Integer};
  cc::TreeNode string_node{cc::NodeKind::String};

  ASSERT_NE(int_node, string_node);
}

TEST(TreeNodeTest, DifferentValueComparison)
{
  cc::TreeNode int1_node{cc::NodeKind::Integer};
  int1_node.SetValueTo(123);

  cc::TreeNode int2_node{cc::NodeKind::Integer};
  int2_node.SetValueTo(321);

  ASSERT_NE(int1_node, int2_node);
}

TEST(TreeNodeTest, SameValueComparison)
{
  cc::TreeNode int1_node{cc::NodeKind::Integer};
  int1_node.SetValueTo(123);

  cc::TreeNode int2_node{cc::NodeKind::Integer};
  int2_node.SetValueTo(123);

  ASSERT_EQ(int1_node, int2_node);
}

TEST(TreeNodeTest, SubnodesComparison)
{
  cc::TreeNode a_node;
  a_node.Create(cc::NodeKind::Fractional, "sub");

  cc::TreeNode b_node;
  b_node.Create(cc::NodeKind::Fractional, "sub");

  ASSERT_EQ(a_node, b_node);
}

TEST(TreeNodeTest, DifferentSubnodeCountComparison)
{
  cc::TreeNode a_node;
  a_node.Create(cc::NodeKind::Fractional, "sub");
  a_node.Create(cc::NodeKind::Integer, "sub2");

  cc::TreeNode b_node;
  b_node.Create(cc::NodeKind::Fractional, "sub");

  ASSERT_NE(a_node, b_node);
}

TEST(TreeNodeTest, DifferentSubValueComparison)
{
  cc::TreeNode a_node;
  a_node.Create(cc::NodeKind::Fractional, "sub");
  a_node["sub"].SetValueTo(3.1415);

  cc::TreeNode b_node;
  b_node.Create(cc::NodeKind::Fractional, "sub");
  b_node["sub"].SetValueTo(2.7182);

  ASSERT_NE(a_node, b_node);
}

TEST(TreeNodeTest, DifferentSecondSubValueComparison)
{
  cc::TreeNode a_node;
  a_node.Create(cc::NodeKind::Integer, "foo");
  a_node.Create(cc::NodeKind::Integer, "bar");
  a_node["foo"].SetValueTo(3);
  a_node["bar"].SetValueTo(4);

  cc::TreeNode b_node;
  b_node.Create(cc::NodeKind::Integer, "foo");
  b_node.Create(cc::NodeKind::Integer, "bar");
  b_node["foo"].SetValueTo(3);
  b_node["bar"].SetValueTo(5);

  ASSERT_NE(a_node, b_node);
}

TEST(TreeNodeTest, SubOrderComparison)
{
  cc::TreeNode a_node;
  a_node.Create(cc::NodeKind::Integer, "foo");
  a_node.Create(cc::NodeKind::Integer, "bar");

  cc::TreeNode b_node;
  b_node.Create(cc::NodeKind::Integer, "foo");
  b_node.Create(cc::NodeKind::Integer, "bar");

  ASSERT_EQ(a_node, b_node);
}

TEST(TreeNodeTest, DifferentSubOrderComparison)
{
  cc::TreeNode a_node;
  a_node.Create(cc::NodeKind::Integer, "foo");
  a_node.Create(cc::NodeKind::Integer, "bar");

  cc::TreeNode b_node;
  b_node.Create(cc::NodeKind::Integer, "bar");
  b_node.Create(cc::NodeKind::Integer, "foo");

  ASSERT_NE(a_node, b_node);
}


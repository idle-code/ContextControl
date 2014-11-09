#include "NodeList.hpp"

#include "gtest/gtest.h"

using namespace ContextControl;

TEST(NodeListTest, EmptyList)
{
  NodeList empty_list;

  NodeList::iterator li = empty_list.begin();
  const NodeList::iterator le = empty_list.end();

  EXPECT_EQ(0, empty_list.Size());
  EXPECT_EQ(le, li);
}

//TEST(NodeListTest, EmptyListElementRequest)
//{
//  NodeList empty_list;
//
//  NodeList::iterator li = empty_list.begin();
//  const NodeList::iterator le = empty_list.end();
//
//  EXPECT_EQ(le, li);
//  ASSERT_THROW(*li, NodeListException);
//}

TEST(NodeListTest, AddElement)
{
  NodeList list;

  TreeNode::Pointer node = std::make_shared<TreeNode>(NodeKind::Integer);
  node->SetValueTo(455);

  list.Add(node);

  EXPECT_EQ(1, list.Size());

  NodeList::iterator li = list.begin();
  const NodeList::iterator le = list.end();

  EXPECT_NE(le, li);
  EXPECT_EQ(455, (*li)->GetValueAs<int>());
  ++li;
  EXPECT_EQ(le, li);
}

TEST(NodeListTest, AddNullElement)
{
  NodeList list;

  ASSERT_THROW(list.Add(nullptr), NodeListException);
}

TEST(NodeListTest, Iterators)
{
  NodeList list;

  TreeNode::Pointer node = TreeNode::Create(NodeKind::Integer);
  node->SetValueTo(1);
  list.Add(node);

  node = TreeNode::Create(NodeKind::Integer);
  node->SetValueTo(2);
  list.Add(node);

  node = TreeNode::Create(NodeKind::Fractional);
  node->SetValueTo(3.14);
  list.Add(node);

  EXPECT_EQ(3, list.Size());

  NodeList::iterator i = list.begin();
  const NodeList::iterator end = list.end();

  EXPECT_NE(end, i);
  EXPECT_EQ(1, (*i)->GetValueAs<int>());
  ++i;
  EXPECT_NE(end, i);
  EXPECT_EQ(2, (*i)->GetValueAs<int>());
  ++i;
  EXPECT_NE(end, i);
  EXPECT_DOUBLE_EQ(3.14, (*i)->GetValueAs<double>());

  double sum = 0.0;
  for (TreeNode::Pointer n : list) {
    sum += n->GetValueAs<double>();
  }
  EXPECT_DOUBLE_EQ(6.14, sum);
}

TEST(NodeListTest, ConstIterators)
{
  NodeList list;

  TreeNode::Pointer node = TreeNode::Create(NodeKind::Integer);
  node->SetValueTo(1);
  list.Add(node);

  node = TreeNode::Create(NodeKind::Integer);
  node->SetValueTo(2);
  list.Add(node);

  node = TreeNode::Create(NodeKind::Fractional);
  node->SetValueTo(3.14);
  list.Add(node);

  EXPECT_EQ(3, list.Size());

  const NodeList &const_list = list;

  NodeList::const_iterator i = const_list.begin();
  const NodeList::const_iterator end = const_list.end();

  EXPECT_NE(end, i);
  EXPECT_EQ(1, (*i)->GetValueAs<int>());
  ++i;
  EXPECT_NE(end, i);
  EXPECT_EQ(2, (*i)->GetValueAs<int>());
  ++i;
  EXPECT_NE(end, i);
  EXPECT_DOUBLE_EQ(3.14, (*i)->GetValueAs<double>());

  double sum = 0.0;
  for (TreeNode::Pointer n : list) {
    sum += n->GetValueAs<double>();
  }
  EXPECT_DOUBLE_EQ(6.14, sum);
}


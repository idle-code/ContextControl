#include "Expression.hpp"

#include "gtest/gtest.h"

using namespace ContextControl;

class ExpressionTest : public ::testing::Test {
protected:
  TreeNode root_node;

  virtual void SetUp(void)
  {
    ASSERT_EQ(0, root_node.Size());

    root_node.Create(NodeKind::Integer, "int_node");
    root_node["int_node"].SetValueTo(3);
    root_node.Create(NodeKind::String, "string_node");
    root_node["string_node"].SetValueTo("Test");
    root_node.Create("branch");
    root_node["branch"].Create(NodeKind::Integer, "seven");
    root_node["branch.seven"].SetValueTo(7);
    root_node["branch"].Create(NodeKind::Boolean, "true");
    root_node["branch.true"].SetValueTo(true);

    ASSERT_EQ(3, root_node.Size());
  }

  virtual void TearDown(void)
  {
    root_node.Clear();
  }
};

/** ----------------------------------------------------------------------- **/

TEST_F(ExpressionTest, ExpressionContext)
{
  String commant_text = "int_node: get"; // "int_node" alone should also parse
  Expression parsed_expression = Expression::Parse(root_node, commant_text);

  TreeNode &context = parsed_expression.Context();
  EXPECT_EQ(root_node["int_node"], context);
}

TEST_F(ExpressionTest, ExpressionCommand)
{
  String commant_text = "int_node: get"; // "int_node" alone should also parse
  Expression parsed_expression = Expression::Parse(root_node, commant_text);

  TreeNode &command = parsed_expression.Command();
  EXPECT_EQ(NodeKind::String, command.Type());
  EXPECT_EQ("get", command.GetValueAs<String>());
}

TEST_F(ExpressionTest, EvaluateScalar)
{
  String commant_text = "int_node: get"; // "int_node" alone should also parse
  Expression parsed_expression = Expression::Parse(root_node, commant_text);

  TreeNode result = parsed_expression.Evaluate();
  EXPECT_EQ(NodeKind::Integer, result.Type());
  EXPECT_EQ(3, result.GetValueAs<int>());
}

/*
 * .: {int_node: get} -> 3
 * .int_node: {get} -> 3
 * .: {int_node} -> 3
 * {int_node get} -> error: No "int_node" command in context .
 * .network.eth0.ip get
 * .network.eth0.ip: get
 * {.: list}: sort.descending.by.name | ${{size} - 1}
 * {int_node: get} + 2 -> 5
 * {int_node} + 2 -> 5
 * int_node + 2 -> 5
 */


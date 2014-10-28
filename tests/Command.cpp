#include "Command.hpp"

#include "gtest/gtest.h"

using namespace ContextControl;

class CommandTest : public ::testing::Test {
protected:
  TreeNode root_node;

  virtual void SetUp(void)
  {
    ASSERT_EQ(0, root_node.Size());

    root_node.Create("int_node", NodeKind::Integer);
    root_node.Create("string_node", NodeKind::String);
    root_node.Create("branch");
    root_node["branch"].Create("seven", NodeKind::Integer);
    root_node["branch.seven"].SetValueTo(7);
    root_node["branch"].Create("true", NodeKind::Boolean);
    root_node["branch.true"].SetValueTo(true);

    ASSERT_EQ(3, root_node.Size());
  }

  virtual void TearDown(void)
  {
    root_node.Clear();
  }
};

/** ----------------------------------------------------------------------- **/

TEST_F(CommandTest, NormalExpression)
{
  String commant_text = "int_node: get";
  Command parsed_command = Command::Parse(root_node, commant_text);

  //TODO: implement (2014.10.28)
  //EXPECT_EQ("int_node", parsed_command.Context().
}


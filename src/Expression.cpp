#include "Expression.hpp"

namespace ContextControl {

TreeNode& Expression::CreateCommand = [](void) -> TreeNode& {
  static TreeNode command{NodeKind::String};
  command.SetValueTo("create");
  return command;
}();

TreeNode& Expression::GetCommand = [](void) -> TreeNode& {
  static TreeNode command{NodeKind::String};
  command.SetValueTo("get");
  return command;
}();

TreeNode& Expression::SetCommand = [](void) -> TreeNode& {
  static TreeNode command{NodeKind::String};
  command.SetValueTo("set");
  return command;
}();

TreeNode& Expression::ListCommand = [](void) -> TreeNode& {
  static TreeNode command{NodeKind::String};
  command.SetValueTo("list");
  return command;
}();

TreeNode& Expression::DeleteCommand = [](void) -> TreeNode& {
  static TreeNode command{NodeKind::String};
  command.SetValueTo("delete");
  return command;
}();

} /* namespace ContextControl */


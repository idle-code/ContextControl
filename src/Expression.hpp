#pragma once

#include "TreeNode.hpp"
#include "ContextControlException.hpp"

namespace ContextControl {

class ExpressionException : public ContextControlException {
public:
  ExpressionException(String message)
    : ContextControlException{message}
  { }
};

class Expression {
public:
  static Expression Parse(const TreeNode &context, const String expression_text)
  {
    Expression expression;

    return expression;
  }

public:
  virtual ~Expression(void) { }

  TreeNode& Context(void)
  {
    return GetCommand;
  }

  TreeNode& Command(void)
  {
    return GetCommand;
  }

  //virtual TreeNode Evaluate(void);

protected:
  Expression(void)
  { }

  static TreeNode& CreateCommand;
  static TreeNode& GetCommand;
  static TreeNode& SetCommand;
  static TreeNode& ListCommand;
  static TreeNode& DeleteCommand;

private:

};

} /* namespace ContextControl */


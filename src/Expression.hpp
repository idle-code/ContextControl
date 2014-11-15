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
  static Expression Parse(TreeNode &context, const String expression_text)
  {
    Expression expression;

    std::list<String> expression_parts = Split(expression_text, ':');
    //if (expression_parts.size() > 2)
    //  throw ExpressionException{"Too many expression components delimited by colon :"};
    expression._ContextNode = &context.GetNode(expression_parts.front());
    expression._CommandNode = &GetCommand;

    return expression;
  }

public:
  virtual ~Expression(void) { }

  TreeNode& Context(void)
  {
    return *_ContextNode;
  }

  TreeNode& Command(void)
  {
    return *_CommandNode;
  }

  TreeNode Evaluate(void)
  {
    return TreeNode{};
  }

protected:
  Expression(void)
    : _ContextNode{nullptr},
      _CommandNode{nullptr}
  { }

  //CHECK: make following references const? (2014.11.08)
  static TreeNode& CreateCommand;
  static TreeNode& GetCommand;
  static TreeNode& SetCommand;
  static TreeNode& ListCommand;
  static TreeNode& DeleteCommand;

private:
  TreeNode *_ContextNode;
  TreeNode *_CommandNode;
};

} /* namespace ContextControl */


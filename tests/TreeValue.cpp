#include "TreeValue.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeValue, VoidTest)
{
  cc::TreeValue value_variant(cc::TreeValue::TypeKind::Void);

  ASSERT_EQ(cc::TreeValue::TypeKind::Void, value_variant.Type());
}

TEST(TreeValue, IntegerTypeTest)
{
  cc::TreeValue value_variant(cc::TreeValue::TypeKind::Integer);

  ASSERT_EQ(cc::TreeValue::TypeKind::Integer, value_variant.Type());
  //cc::TreeValue::IntegerValueType integer_variable = value_variant.ValueAs<cc::TreeValue::IntegerValueType>();
  ASSERT_EQ(0, value_variant.ValueAs<cc::TreeValue::IntegerValueType>());
}


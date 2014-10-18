#include "TreeValue.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeValueTest, VoidTypeTest)
{
  cc::TreeValue value_variant(cc::TreeValue::VoidType);

  ASSERT_EQ(cc::TreeValue::VoidType, value_variant.Type);
}

TEST(TreeValueTest, IntegerTypeTest)
{
  cc::TreeValue value_variant(cc::TreeValue::IntegerType);

  ASSERT_EQ(cc::TreeValue::IntegerType, value_variant.Type);
  cc::TreeValue::IntegerValueType integer_variable = value_variant.ValueAs<cc::TreeValue::IntegerValueType>();
  //ASSERT_EQ(0, value_variant.ValueAs<cc::TreeValue::IntegerType>());
}


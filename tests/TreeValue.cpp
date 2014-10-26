#include "TreeValue.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeValue, VoidTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Void);

  ASSERT_EQ(cc::NodeKind::Void, value_variant.Type());

  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::IntegerValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::BooleanValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::FractionalValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::StringValueType>(), cc::TreeValue::InvalidCastException);
}

TEST(TreeValue, IntegerTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Integer);

  ASSERT_EQ(cc::NodeKind::Integer, value_variant.Type());

  EXPECT_EQ(0, value_variant.GetValueAs<cc::TreeValue::IntegerValueType>());
  EXPECT_EQ(false, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  EXPECT_DOUBLE_EQ(0.0, value_variant.GetValueAs<cc::TreeValue::FractionalValueType>());
  EXPECT_EQ("0", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

TEST(TreeValue, BooleanTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Boolean);

  ASSERT_EQ(cc::NodeKind::Boolean, value_variant.Type());

  EXPECT_EQ(0, value_variant.GetValueAs<cc::TreeValue::IntegerValueType>());
  EXPECT_EQ(false, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  EXPECT_DOUBLE_EQ(0.0, value_variant.GetValueAs<cc::TreeValue::FractionalValueType>());
  EXPECT_EQ("false", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

TEST(TreeValue, FractionalTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Fractional);

  ASSERT_EQ(cc::NodeKind::Fractional, value_variant.Type());

  EXPECT_EQ(0, value_variant.GetValueAs<cc::TreeValue::IntegerValueType>());
  EXPECT_EQ(false, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  EXPECT_EQ(0.0f, value_variant.GetValueAs<cc::TreeValue::FractionalValueType>());
  EXPECT_EQ("0", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

TEST(TreeValue, StringTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::String);

  ASSERT_EQ(cc::NodeKind::String, value_variant.Type());

  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::IntegerValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::BooleanValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::FractionalValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_EQ("", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

/** ----------------------------------------------------------------------- **/

TEST(TreeValue, IntegerTypeValueTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Integer);
  value_variant.SetValueTo(1234);

  EXPECT_EQ(1234, value_variant.GetValueAs<cc::TreeValue::IntegerValueType>());
  EXPECT_EQ(true, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  EXPECT_DOUBLE_EQ(1234.0, value_variant.GetValueAs<cc::TreeValue::FractionalValueType>());
  EXPECT_EQ("1234", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

TEST(TreeValue, BooleanTypeValueTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Boolean);
  value_variant.SetValueTo(true);

  EXPECT_EQ(1, value_variant.GetValueAs<cc::TreeValue::IntegerValueType>());
  EXPECT_EQ(true, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  EXPECT_DOUBLE_EQ(1.0, value_variant.GetValueAs<cc::TreeValue::FractionalValueType>());
  EXPECT_EQ("true", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

TEST(TreeValue, FractionalTypeValueTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Fractional);
  value_variant.SetValueTo(3.1415);

  EXPECT_EQ(3, value_variant.GetValueAs<cc::TreeValue::IntegerValueType>());
  EXPECT_EQ(true, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  EXPECT_DOUBLE_EQ(3.1415, value_variant.GetValueAs<cc::TreeValue::FractionalValueType>());
  EXPECT_EQ("3.1415", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}

TEST(TreeValue, StringTypeValueTest)
{
  cc::TreeValue value_variant(cc::NodeKind::String);
  value_variant.SetValueTo("Test");

  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::IntegerValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::BooleanValueType>(), cc::TreeValue::InvalidCastException);
  //EXPECT_EQ(true, value_variant.GetValueAs<cc::TreeValue::BooleanValueType>());
  ASSERT_THROW(value_variant.GetValueAs<cc::TreeValue::FractionalValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_EQ("Test", value_variant.GetValueAs<cc::TreeValue::StringValueType>());
}


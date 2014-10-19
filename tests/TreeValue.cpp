#include "TreeValue.hpp"

#include "gtest/gtest.h"

namespace cc = ContextControl;

TEST(TreeValue, VoidTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Void);

  ASSERT_EQ(cc::NodeKind::Void, value_variant.Type());

  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::IntegerValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::FractionalValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::StringValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::LinkValueType>(), cc::TreeValue::InvalidCastException);
}

TEST(TreeValue, IntegerTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Integer);

  ASSERT_EQ(cc::NodeKind::Integer, value_variant.Type());
  ASSERT_EQ(0, value_variant.ValueAs<cc::TreeValue::IntegerValueType>());
  ASSERT_EQ(0.0f, value_variant.ValueAs<cc::TreeValue::FractionalValueType>());
  ASSERT_EQ("0", value_variant.ValueAs<cc::TreeValue::StringValueType>());
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::LinkValueType>(), cc::TreeValue::InvalidCastException);
}

TEST(TreeValue, FractionalTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::Fractional);

  ASSERT_EQ(cc::NodeKind::Fractional, value_variant.Type());

  ASSERT_EQ(0, value_variant.ValueAs<cc::TreeValue::IntegerValueType>());
  ASSERT_EQ(0.0f, value_variant.ValueAs<cc::TreeValue::FractionalValueType>());
  ASSERT_EQ("0", value_variant.ValueAs<cc::TreeValue::StringValueType>());
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::LinkValueType>(), cc::TreeValue::InvalidCastException);
}

TEST(TreeValue, StringTypeDefaultConstructorTest)
{
  cc::TreeValue value_variant(cc::NodeKind::String);

  ASSERT_EQ(cc::NodeKind::String, value_variant.Type());

  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::IntegerValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::FractionalValueType>(), cc::TreeValue::InvalidCastException);
  ASSERT_EQ("", value_variant.ValueAs<cc::TreeValue::StringValueType>());
  ASSERT_THROW(value_variant.ValueAs<cc::TreeValue::LinkValueType>(), cc::TreeValue::InvalidCastException);
}

TEST(TreeValue, LinkTypeDefaultConstructorTest)
{
  ASSERT_THROW(cc::TreeValue value_variant(cc::NodeKind::Link), cc::TreeValue::InvalidTypeException);
}


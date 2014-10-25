#pragma once

#include "String.hpp"
#include <stdexcept>
#include <sstream>

namespace ContextControl {

enum struct NodeKind {
  Void,
  Integer,
  Boolean,
  String,
  Fractional,
};

class TreeValue {
public:
  class UnknownCastException : std::logic_error {
  public:
    UnknownCastException(void) : std::logic_error("Unknown cast") { }
  };

  class InvalidCastException : std::logic_error {
  public:
    InvalidCastException(void) : std::logic_error("Cast to unsupported type") { }
  };

  class InvalidTypeException : std::logic_error {
  public:
    InvalidTypeException(void) : std::logic_error("Invalid type") { }
  };

public:
  typedef int IntegerValueType;
  typedef bool BooleanValueType;
  typedef String StringValueType;
  typedef double FractionalValueType;

public:
  TreeValue(NodeKind value_type)
    : _Type(value_type)
  {
    switch (value_type) {
      case NodeKind::Void:
        break;
      case NodeKind::Integer:
        _Data.IntegerValue = 0;
        break;
      case NodeKind::Boolean:
        _Data.BooleanValue = false;
        break;
      case NodeKind::String:
        _Data.StringValue = "";
        break;
      case NodeKind::Fractional:
        _Data.FractionalValue = 0.0f;
        break;

      default:
        throw InvalidTypeException();
    }
  }

  ~TreeValue(void)
  {
    //if (_Type == NodeKind::String)
    //  _Data.~StringValue();
  }

  template<typename ValueType>
  ValueType ValueAs(void)
  {
    throw UnknownCastException();
  }

  void SetValueTo(IntegerValueType value)
  {
    switch (_Type) {
      case NodeKind::Integer:
        _Data.IntegerValue = value;
        break;

      default:
        throw InvalidCastException();
    }
  }

  void SetValueTo(BooleanValueType value)
  {
    switch (_Type) {
      case NodeKind::Boolean:
        _Data.BooleanValue = value;
        break;

      default:
        throw InvalidCastException();
    }
  }

  void SetValueTo(FractionalValueType value)
  {
    switch (_Type) {
      case NodeKind::Fractional:
        _Data.FractionalValue = value;
        break;

      default:
        throw InvalidCastException();
    }
  }

  void SetValueTo(const char *value)
  {
    SetValueTo(StringValueType(value));
  }

  void SetValueTo(StringValueType value)
  {
    switch (_Type) {
      case NodeKind::String:
        _Data.StringValue = value;
        break;

      default:
        throw InvalidCastException();
    }
  }

  NodeKind Type(void) const
  {
    return _Type;
  }

private:
  struct Data { //TODO: change this struct to union
    IntegerValueType IntegerValue;
    BooleanValueType BooleanValue;
    FractionalValueType FractionalValue;
    StringValueType StringValue;
  } _Data;

  NodeKind _Type;
};

/** ----------------------------------------------------------------------- **/

template<> inline
TreeValue::IntegerValueType
TreeValue::ValueAs<TreeValue::IntegerValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer:
      return _Data.IntegerValue;

    case NodeKind::Boolean:
      return _Data.BooleanValue ? 1 : 0;

    case NodeKind::Fractional:
      return static_cast<IntegerValueType>(_Data.FractionalValue);

    case NodeKind::String: {
      std::stringstream ss(_Data.StringValue);
      IntegerValueType val;
      ss >> val;
      if (ss.fail())
        throw InvalidCastException();
      return val;
    }

    default:
      throw InvalidCastException();
  }
}

template<> inline
TreeValue::BooleanValueType
TreeValue::ValueAs<TreeValue::BooleanValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer:
      return _Data.IntegerValue != 0;

    case NodeKind::Boolean:
      return _Data.BooleanValue;

    case NodeKind::Fractional:
      return _Data.FractionalValue != 0.0;

    case NodeKind::String:
      if (_Data.StringValue == "true")
        return true;
      else if (_Data.StringValue == "false")
        return false;
      else
        throw InvalidCastException();

    default:
      throw InvalidCastException();
  }
}

template<> inline
TreeValue::FractionalValueType
TreeValue::ValueAs<TreeValue::FractionalValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer:
      return static_cast<FractionalValueType>(_Data.IntegerValue);

    case NodeKind::Boolean:
      return _Data.BooleanValue ? 1.0 : 0.0;

    case NodeKind::Fractional:
      return _Data.FractionalValue;

    case NodeKind::String: {
      std::stringstream ss(_Data.StringValue);
      FractionalValueType val;
      ss >> val;
      if (ss.fail())
        throw InvalidCastException();
      return val;
    }

    default:
      throw InvalidCastException();
  }
}

template<> inline
TreeValue::StringValueType
TreeValue::ValueAs<TreeValue::StringValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer: {
      std::stringstream ss;
      ss << _Data.IntegerValue;
      return ss.str();
    }

    case NodeKind::Boolean:
      return _Data.BooleanValue ? "true" : "false";

    case NodeKind::Fractional: {
      std::stringstream ss;
      ss << _Data.FractionalValue;
      return ss.str();
    }

    case NodeKind::String:
      return _Data.StringValue;

    default:
      throw InvalidCastException();
  }
}

} /* namespace ContextControl */


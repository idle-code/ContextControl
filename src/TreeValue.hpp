#pragma once

#include <string>
#include <stdexcept>
#include <sstream>

namespace ContextControl {

enum struct NodeKind {
  Void,
  String,
  Integer,
  Fractional,
  Link,
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
  typedef void* VoidValueType;
  typedef std::string StringValueType;
  typedef int IntegerValueType;
  typedef float FractionalValueType;
  typedef TreeValue* LinkValueType;

public:
  TreeValue(NodeKind value_type)
    : _Type(value_type)
  {
    switch (value_type) {
      case NodeKind::Void:
        break;
      case NodeKind::String:
        _Data.StringValue = "";
        break;
      case NodeKind::Integer:
        _Data.IntegerValue = 0;
        break;
      case NodeKind::Fractional:
        _Data.FractionalValue = 0.0f;
        break;
      case NodeKind::Link:
        throw InvalidTypeException();
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

  NodeKind Type(void) const
  {
    return _Type;
  }

private:
  struct Data { //TODO: change this struct to union
    VoidValueType VoidValue;
    StringValueType StringValue;
    IntegerValueType IntegerValue;
    FractionalValueType FractionalValue;
    LinkValueType LinkValue;
  } _Data;

  NodeKind _Type;
};

template<>
inline
TreeValue::IntegerValueType
TreeValue::ValueAs<TreeValue::IntegerValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer:
      return _Data.IntegerValue;

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

template<>
inline
TreeValue::FractionalValueType
TreeValue::ValueAs<TreeValue::FractionalValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer:
      return static_cast<FractionalValueType>(_Data.IntegerValue);
      break;

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

template<>
inline
TreeValue::StringValueType
TreeValue::ValueAs<TreeValue::StringValueType>(void)
{
  switch (_Type) {
    case NodeKind::Integer: {
      std::stringstream ss;
      ss << _Data.IntegerValue;
      return ss.str();
    }

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

template<>
inline
TreeValue::LinkValueType
TreeValue::ValueAs<TreeValue::LinkValueType>(void)
{
  switch (_Type) {
    case NodeKind::Link:
      return _Data.LinkValue;

    default:
      throw InvalidCastException();
  }
}

} /* namespace ContextControl */


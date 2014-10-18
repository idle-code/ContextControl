#pragma once

#include <string>
#include <stdexcept>

namespace ContextControl {

class TreeValue {
public:
  class UnknownCastException : std::exception {
  public: const char* what(void) const throw() override { return "Unknown exception"; }
  };

  class InvalidCastException : std::exception {
  };

public:
  enum struct TypeKind {
    Void,
    String,
    Integer,
    Fractional,
    Link,
  };

  typedef void* VoidValueType;
  typedef std::string StringValueType;
  typedef int IntegerValueType;
  typedef float FractionalValueType;
  typedef TreeValue* LinkValueType;

public:
  TreeValue(TypeKind value_type)
    : _Type(value_type)
  { }

  ~TreeValue(void)
  {
    //if (_Type == TypeKind::String)
    //  _Data.~StringValue();
  }

  template<typename ValueType>
  ValueType ValueAs(void)
  {
    throw UnknownCastException();
  }

  TypeKind Type(void) const
  {
    return _Type;
  }

private:
  union Data {
    VoidValueType VoidValue;
    StringValueType StringValue;
    IntegerValueType IntegerValue;
    FractionalValueType FractionalValue;
    LinkValueType LinkValue;

    Data(void) : VoidValue(nullptr) { }
    Data(StringValueType value) : StringValue(value) { }
    Data(IntegerValueType value) : IntegerValue(value) { }
    Data(FractionalValueType value) : FractionalValue(value) { }
    Data(LinkValueType value) : LinkValue(value) { }
    ~Data(void) { }
  } _Data;

  TypeKind _Type;

};

//namespace detail {
//template<>
//ValueVariant::IntegerValueType ValueVariant::ValueAs(void)
//{
//  if (Type != ValueVariant::IntegerType)
//    throw ValueVariantInvalidCastException();
//}
//
//} /* namespace detail */

} /* namespace ContextControl */


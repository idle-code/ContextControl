#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/compare.hpp>

namespace ContextControl {

//typedef std::string String; //IMPROVE: implement/import proper, UTF String class
//typedef String::value_type Char;

//inline std::list<String>
//Split(const String &text, Char delimiter)
//{
//  std::list<String> components;
//  boost::split(components, text, [delimiter](Char c) { return c == delimiter; });
//  return components;
//}
//
//inline String
//Trim(const String &text)
//{
//  String trimmed{text};
//  boost::algorithm::trim(trimmed);
//  return trimmed;
//}

/** ----------------------------------------------------------------------- **/

typedef std::string::value_type Char;

class String {
public:
  //typedef std::string::value_type Char;
public:
  String(void)
    : _value() { }

  String(const char *text)
    : _value(text) { }

  String(const String &other)
    : _value(other._value) { }

  String(const std::string &std_string)
    : _value(std_string) { }
  
  String(const std::string::iterator start, const std::string::iterator end)
    : _value(start, end) { }

  operator std::string(void) const
  {
    return _value;
  }

  String Trim(void) const
  {
    std::string trimmed{_value};
    boost::algorithm::trim(trimmed);
    return trimmed;
  }

  std::list<String> Split(Char delimiter) const
  {
    std::list<std::string> components;
    boost::split(components, _value, [delimiter](Char c) { return c == delimiter; });

    // change list's inner type std::string -> String
    std::list<String> string_components;
    for (const std::string &s : components)
      string_components.push_back(s);
    return string_components;
  }

  int Length(void) const
  {
    return _value.length();
  }

  bool IsEmpty(void) const
  {
    return Length() == 0;
  }

  String Substring(int start) const
  {
    return _value.substr(start);
  }

  Char operator[](int index) const
  {
    return _value[index];
  }

  friend String operator+(const String &left, const String &right);
  friend bool operator==(const String &left, const String &right);
  friend bool operator!=(const String &left, const String &right);

private:
  std::string _value;
};

inline String
operator+(const String &left, const String &right)
{
  return left._value + right._value;
}

inline bool
operator==(const String &left, const String &right)
{
  return left._value == right._value;
}

inline bool
operator!=(const String &left, const String &right)
{
  return left._value != right._value;
}

} /* namespace ContextControl */


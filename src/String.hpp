#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/compare.hpp>

namespace ContextControl {

typedef std::string String; //IMPROVE: implement/import proper, UTF String class
typedef String::value_type Char;

inline std::list<String>
Split(const String &text, Char delimiter)
{
  std::list<String> components;
  boost::split(components, text, [delimiter](Char c) { return c == delimiter; });
  return components;
}

inline String
Trim(const String &text)
{
  String trimmed{text};
  boost::algorithm::trim(trimmed);
  return trimmed;
}

} /* namespace ContextControl */


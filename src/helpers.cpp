/**
 * \file helpers.cpp
 * \brief rohdeschwarz helper function implementations
 */


#include "rohdeschwarz/helpers.hpp"


// std lib
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <sstream>


// constants
const char SINGLE_QUOTE = '\'';
const char DOUBLE_QUOTE = '\"';


// lambdas

auto not_a_space = [](unsigned char ch)
{
  return !std::isspace(ch);
};


auto is_quote_char = [](char character)
{
  return character == SINGLE_QUOTE || character == DOUBLE_QUOTE;
};


// helpers


std::string rohdeschwarz::leftTrim(std::string text)
{
  const auto end = std::find_if(text.begin(), text.end(), not_a_space);
  text.erase(text.begin(), end);
  return text;
}


std::string rohdeschwarz::rightTrim(std::string text)
{
  const auto rbegin = std::find_if(text.rbegin(), text.rend(), not_a_space);
  const auto begin  = rbegin.base();
  text.erase(begin, text.end());
  return text;
}


std::string rohdeschwarz::trim(const std::string& text)
{
  return leftTrim(rightTrim(text));
}


bool rohdeschwarz::isLeftQuote(const char* text)
{
  const std::string text_str(text);
  return isLeftQuote(text_str);
}


bool rohdeschwarz::isLeftQuote(const std::string& text)
{
  if (text.empty())
  {
    return false;
  }

  return !text.empty() && is_quote_char(text.front());
}


bool rohdeschwarz::isRightQuote(const char* text)
{
  const std::string text_str(text);
  return isRightQuote(text_str);
}


bool rohdeschwarz::isRightQuote(const std::string& text)
{
  return !text.empty() && is_quote_char(text.back());
}


bool rohdeschwarz::isQuoted(const char* text)
{
  const std::string text_str(text);
  return isQuoted(text_str);
}


bool rohdeschwarz::isQuoted(const std::string& text)
{
  return isLeftQuote(text) && isRightQuote(text);
}


std::string rohdeschwarz::quote(const char* text, char quote_character)
{
  const std::string text_str(text);
  return quote(text_str, quote_character);
}


std::string rohdeschwarz::quote(const std::string& text, char quote_character)
{
  std::stringstream quoted_text;
  quoted_text << quote_character << text << quote_character;
  return quoted_text.str();
}


std::string rohdeschwarz::unquote(const char* text)
{
  const std::string text_str(text);
  return unquote(text_str);
}


std::string rohdeschwarz::unquote(const std::string& text)
{
  return isQuoted(text)?
    text.substr(1, text.size() - 2)
    : text;
}


std::vector<std::string> rohdeschwarz::split(const char* csvList, const char separator)
{
  const std::string csv_list_str(csvList);
  return split(csv_list_str, separator);
}


std::vector<std::string> rohdeschwarz::split(const std::string& csvList, const char separator)
{
  std::vector<std::string> parts;
  if (csvList.empty())
  {
    // no parts
    return parts;
  }

  // find initial values
  std::size_t start = 0;
  std::size_t end   = csvList.find(separator);
  while (end != std::string::npos)
  {
    // append part
    const std::size_t length = end - start;
    const std::string part = csvList.substr(start, length);
    parts.emplace_back(part);

    // find next part
    // starting at next character
    start = end + 1;
    end   = csvList.find(separator, start);
  }

  // find last value
  const std::string part = csvList.substr(start);
  parts.emplace_back(part);
  return parts;
}

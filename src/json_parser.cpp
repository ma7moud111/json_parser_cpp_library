#include "../include/json_parser.hpp"
#include <stdexcept>

CJsonParser::CJsonParser(const std::string &input) { m_text = input; }


CJsonValue CJsonParser::parse() {
  skip_whitespace();
  return parse_value();
}


void CJsonParser::skip_whitespace() {
  while (m_pos < m_text.size() && std::isspace(m_text[m_pos]))
    m_pos++;
}


char CJsonParser::peek() const {
  if (m_pos >= m_text.size())
    return '\0';
  return m_text[m_pos];
}


char CJsonParser::consume() { return m_text[m_pos++]; }


CJsonValue CJsonParser::parse_value() {
  skip_whitespace();

  char c = peek();

  if (c == '{')
    return parse_object();

  if (c == '[')
    return parse_array();

  if (c == '"')
    return parse_string();

  if (std::isdigit(c) || c == '-')
    return parse_number();

  if (m_text.substr(m_pos, 4) == "true" || m_text.substr(m_pos, 5) == "false")
    return parse_bool();

  if (m_text.substr(m_pos, 4) == "null")
    return parse_null();

  throw std::runtime_error("Invalid JSON value");
}



CJsonValue CJsonParser::parse_object() {

  CJsonValue obj;

  consume(); 

  skip_whitespace();

  if (peek() == '}') {
    consume();
    return obj;
  }

  while (true) {

    skip_whitespace(); 

    std::string key = parse_string();

    skip_whitespace();

    consume(); 
    skip_whitespace();

    CJsonValue value = parse_value();

    obj[key] = value;

    skip_whitespace();

    if (peek() == '}') {
      consume();
      break;
    }

    consume(); 
  }

  return obj;
}



CJsonValue CJsonParser::parse_array() {
  CJsonValue arr;

  consume(); 

  skip_whitespace();

  size_t index = 0;

  if (peek() == ']') {
    consume();
    return arr;
  }

  while (true) {
    arr[index++] = parse_value();

    skip_whitespace();

    if (peek() == ']') {
      consume();
      break;
    }

    consume(); 
  }

  return arr;
}

std::string CJsonParser::parse_string() {

  if (consume() != '"')
    throw std::runtime_error("Expected string");

  std::string result;

  while (peek() != '"') {
    result += consume();
  }

  consume(); 

  return result;
}

CJsonValue CJsonParser::parse_number() {
  std::string number;

  while (m_pos < m_text.size() &&
         (std::isdigit(m_text[m_pos]) || m_text[m_pos] == '.' || m_text[m_pos] == '-')) {
    number += consume();
  }

  if (number.find('.') != std::string::npos)
    return CJsonValue(std::stod(number));

  return CJsonValue(std::stoi(number));
}


CJsonValue CJsonParser::parse_bool() {
  if (m_text.substr(m_pos, 4) == "true") {
    m_pos += 4;
    return CJsonValue(true);
  }

  m_pos += 5;
  return CJsonValue(false);
}


CJsonValue CJsonParser::parse_null() {
  m_pos += 4;
  return CJsonValue();
}
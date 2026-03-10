#pragma once

#include "json_value.hpp"
#include <string>

class CJsonParser {
private:
  std::string text;
  size_t pos = 0;

public:
  CJsonParser(const std::string &input);

  CJsonValue parse();

private:
  CJsonValue parse_value();
  CJsonValue parse_object();
  CJsonValue parse_array();
  CJsonValue parse_string();
  CJsonValue parse_number();
  CJsonValue parse_bool();
  CJsonValue parse_null();

  void skip_whitespace();
  char peek() const;
  char consume();
};
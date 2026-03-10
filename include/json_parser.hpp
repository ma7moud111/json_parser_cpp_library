#pragma once

#include "json_value.hpp"
#include <cstddef>
#include <string>

class CJsonParser {

private:
  std::string m_text;
  size_t m_pos;

public:
  CJsonValue parse();

private:
  CJsonValue parse_value();
  CJsonValue parse_object();
  CJsonValue parse_array();
  CJsonValue parse_string();
  CJsonValue parse_number();

  void skip_whitespaces();  

};
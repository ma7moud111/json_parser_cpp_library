#pragma once

#include "json_value.hpp"

class CJsonSerializer {
public:
  static std::string serialize(const CJsonValue &value, int indent = 0);
  
  private:
  static std::string indent_str(int indent);
  static std::string serialize_object(const CJsonValue& value, int indent);
  static std::string serialize_array(const CJsonValue& value, int indent);
  static std::string serialize_string(const CJsonValue &value);
};
#pragma once

#include "json_value.hpp"

class CJsonSerializer {
public:
  static std::string serialize(const CJsonValue &value);
  
private:
  static std::string serialize_object(const CJsonValue &value);
  static std::string serialize_array(const CJsonValue &value);
  static std::string serialize_string(const CJsonValue &value);
};
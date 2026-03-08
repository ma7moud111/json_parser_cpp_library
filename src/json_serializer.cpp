#include "../include/json_serializer.hpp"
#include "../include/json_value.hpp"
#include <string>

std::string CJsonSerializer::serialize(const CJsonValue& value) {

  const auto &v = value.get_value();

  switch (v.index()) {
  case 0:
    return "null";

  case 1:
    return std::to_string(std::get<int>(v));

  case 2:
    return std::to_string(std::get<double>(v));

  case 3:
    return std::get<bool>(v) ? "true" : "false";

  case 4:
    return "\"" + std::get<std::string>(v) + "\"";

  case 5:
    return serialize_object(value);

  case 6:
    return serialize_array(value);
  }

  return "";   
}
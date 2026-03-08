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


std::string CJsonSerializer::serialize_object(const CJsonValue &value) {

  const auto &obj = std::get<CJsonValue::JsonObject>(value.get_value());

  std::string result = "{";
  bool first = true;

  for (const auto &[key, val] : obj) {
    if (!first) {
      result += ",";
    }

    result += "\"" + key + "\"";
    result += serialize(val);

    first = false;
  }
  result += "}";

  return result;
}

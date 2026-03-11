#include "../include/json_serializer.hpp"
#include "../include/json_value.hpp"
#include <string>

std::string CJsonSerializer::serialize(const CJsonValue &value, int indent) {
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
    return CJsonSerializer::serialize_object(value, indent);

  case 6:
    return CJsonSerializer::serialize_array(value, indent);
  }

  return "";
}

std::string CJsonSerializer::indent_str(int indent) { return std::string(indent * 2, ' '); }


std::string CJsonSerializer::serialize_object(const CJsonValue &value,
                                              int indent) {
  const auto &obj = std::get<CJsonValue::JsonObject>(value.get_value());

  std::string result = "{";

  if (!obj.empty())
    result += "\n";

  bool first = true;

  for (const auto &[key, val] : obj) {
    if (!first)
      result += "," + std::string("\n");

    result += indent_str(indent + 1);
    result += "\"" + key + "\": ";
    result += serialize(val, indent + 1);

    first = false;
  }

  if (!obj.empty()) {
    result += "\n";
    result += indent_str(indent);
  }

  result += "}";

  return result;
}

std::string CJsonSerializer::serialize_array(const CJsonValue &value,
                                             int indent) {
  const auto &arr = std::get<CJsonValue::JsonArray>(value.get_value());

  std::string result = "[";

  if (!arr.empty())
    result += "\n";

  for (size_t i = 0; i < arr.size(); i++) {
    result += indent_str(indent + 1);
    result += serialize(arr[i], indent + 1);

    if (i != arr.size() - 1)
      result += ",";

    result += "\n";
  }

  if (!arr.empty())
    result += indent_str(indent);

  result += "]";

  return result;
}
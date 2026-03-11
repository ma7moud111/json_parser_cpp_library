#include <fstream>
#include <sstream>
#include "../include/simple_json.hpp"
#include "../include/json_parser.hpp"
#include "../include/json_serializer.hpp"

std::optional<CJsonValue> CSimpleJson::read_str(const std::string &text) {
  try {
    CJsonParser parser(text);
    return parser.parse();
  } catch (...) {
    return std::nullopt;
  }
}

std::string CSimpleJson::write_str(const CJsonValue &value) {
  return CJsonSerializer::serialize(value);
}

std::optional<CJsonValue> CSimpleJson::read_file(const std::string &path) {
  std::ifstream file(path);

  if (!file)
    return std::nullopt;

  std::stringstream buffer;
  buffer << file.rdbuf();

  return read_str(buffer.str());
}

bool CSimpleJson::write_file(const CJsonValue &value, const std::string &path) {
  std::ofstream file(path);

  if (!file)
    return false;

  file << CJsonSerializer::serialize(value);

  return true;
}

bool CSimpleJson::is_valid(const std::string &text) {
  try {
    CJsonParser parser(text);
    parser.parse();
    return true;
  } catch (...) {
    return false;
  }
}
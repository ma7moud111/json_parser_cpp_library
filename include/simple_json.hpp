#pragma once

#include "json_value.hpp"
#include <optional>
#include <string>

class CSimpleJson {
public:
  static std::optional<CJsonValue> read_str(const std::string &text);
  
  static std::string write_str(const CJsonValue &value);

  static std::optional<CJsonValue> read_file(const std::string &path);

  static bool write_file(const CJsonValue &value, const std::string &path);

  static bool is_valid(const std::string &text);
};
#pragma once

#include <string>
#include <map>
#include <variant>
#include <vector>


class CJsonValue {

private:
  std::variant<std::nullptr_t, int, double, bool, std::string,
               std::map<std::string, CJsonValue>, std::vector<CJsonValue>>
      m_values;


public:
  CJsonValue() = default;
  CJsonValue(int v);
  CJsonValue(double v);
  CJsonValue(bool v);
  CJsonValue(const std::string &v);
  
  bool is_object() const;
  bool is_array() const;
  bool is_string() const;
  bool is_number() const;
  bool is_bool() const;

  CJsonValue &operator[](std::string key);
  CJsonValue &operator[](int index);
  
};
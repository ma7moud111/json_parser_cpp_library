#pragma once

#include <string>
#include <map>
#include <variant>
#include <vector>
class CJsonValue {

private:
  using JsonObject = std::map<std::string, CJsonValue>;
  using JsonArray = std::vector<CJsonValue>;

  std::variant<std::nullptr_t, int, double, bool, std::string, JsonObject,
               JsonArray>
      m_value;

public:
  CJsonValue() = default;
  CJsonValue(int v) : m_value(v) {}
  CJsonValue(double v) : m_value(v){}
  CJsonValue(bool v) : m_value(v){}
  CJsonValue(const std::string &v) : m_value(v){}
  CJsonValue(const char *v) : m_value(std::string(v)){}

  bool is_object() const { return m_value.index() == 5; }

  bool is_null() const { return m_value.index() == 0; }

  bool is_array() const { return m_value.index() == 6; }

  bool is_string() const { return m_value.index() == 4; }
  
  bool is_number() const {
    return m_value.index() == 1 || m_value.index() == 2;
  }

  bool is_bool() const { return m_value.index() == 3; }

  CJsonValue &operator[](std::string key) {
    if (!is_object()) {
      m_value = JsonObject{};
    }

    auto &obj = std::get<JsonObject>(m_value);
    return obj[key];
  }

  CJsonValue &operator[](int index) {
    if (!is_array()) {
      m_value = JsonArray{};
    }

    auto &arr = std::get<JsonArray>(m_value);
    return arr[index];
  }
  
};
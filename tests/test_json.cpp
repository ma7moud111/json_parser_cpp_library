#include "../include/simple_json.hpp"
#include <iostream>

void test_parse_json() {
  std::cout << "========== Test JSON Parse ==========" << std::endl;

  std::string text = R"({
        "name": "Mahmoud",
        "age": 24,
        "skills": ["C++", "Linux"],
        "active": true
    })";

  auto json = CSimpleJson::read_str(text);

  if (!json) {
    std::cout << "Failed to parse JSON" << std::endl;
    return;
  }

  std::cout << "Parsed JSON successfully" << std::endl;

  std::cout << "Serialized JSON:" << std::endl;
  std::cout << CSimpleJson::write_str(*json) << std::endl;

  std::cout << std::endl;
}

void test_build_json() {
  std::cout << "========== Test Build JSON ==========" << std::endl;

  CJsonValue json;

  json["name"] = "Mahmoud";
  json["age"] = 24;

  json["skills"][0] = "C++";
  json["skills"][1] = "Linux";

  json["active"] = true;

  std::cout << "Generated JSON:" << std::endl;
  std::cout << CSimpleJson::write_str(json) << std::endl;

  std::cout << std::endl;
}

void test_json_file() {
  std::cout << "========== Test File IO ==========" << std::endl;

  CJsonValue json;

  json["name"] = "Mahmoud";
  json["age"] = 24;
  json["skills"][0] = "C++";
  json["skills"][1] = "Linux";
  json["skills"][2] = "Qt6";
  json["company"] = "Coretech Innovation";

  if (CSimpleJson::write_file(json, "test.json"))
    std::cout << "File written successfully" << std::endl;
  else
    std::cout << "Failed to write file" << std::endl;

  auto parsed = CSimpleJson::read_file("test.json");

  if (parsed)
    std::cout << "File read successfully:" << std::endl
              << CSimpleJson::write_str(*parsed) << std::endl;
  else
    std::cout << "Failed to read file" << std::endl;

  std::cout << std::endl;
}

void test_validation() {
  std::cout << "========== Test JSON Validation ==========" << std::endl;

  std::string valid = R"({"name":"Mahmoud","age":24})";
  std::string invalid = R"({"name":"Mahmoud",})";

  std::cout << "Valid JSON test: "
            << (CSimpleJson::is_valid(valid) ? "true" : "false") << std::endl;

  std::cout << "Invalid JSON test: "
            << (CSimpleJson::is_valid(invalid) ? "true" : "false") << std::endl;

  std::cout << std::endl;
}

int main() {
  std::cout << "=========================================" << std::endl;
  std::cout << "        Simple JSON Library Tests" << std::endl;
  std::cout << "=========================================" << std::endl;

  std::cout << std::endl;

  test_parse_json();
  test_build_json();
  test_json_file();
  test_validation();

  std::cout << "All tests finished." << std::endl;

  return 0;
}
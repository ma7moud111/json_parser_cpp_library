#include "../include/simple_json.hpp"
#include <iostream>

void parse_example()
{
    std::cout << "---- Parsing JSON from string ----\n";

    std::string text = R"({
        "name": "Mahmoud",
        "age": 24,
        "skills": ["C++", "Linux"],
        "active": true
    })";

    auto result = CSimpleJson::read_str(text);

    if (!result)
    {
        std::cout << "Parsing failed\n\n";
        return;
    }

    std::cout << "JSON parsed successfully\n";
    std::cout << CSimpleJson::write_str(*result) << "\n\n";
}

void build_example()
{
    std::cout << "---- Building JSON programmatically ----\n";

    CJsonValue root;

    root["name"] = "Mahmoud";
    root["age"] = 24;
    root["skills"][0] = "C++";
    root["skills"][1] = "Linux";
    root["active"] = true;

    std::cout << CSimpleJson::write_str(root) << "\n\n";
}

void file_io_example()
{
    std::cout << "---- File read/write test ----\n";

    CJsonValue data;

    data["name"] = "Mahmoud";
    data["age"] = 24;
    data["skills"][0] = "C++";
    data["skills"][1] = "Linux";
    data["skills"][2] = "Qt6";
    data["company"] = "Coretech Innovation";

    if (CSimpleJson::write_file(data, "test.json"))
        std::cout << "JSON written to file\n";
    else
        std::cout << "Failed to write file\n";

    auto loaded = CSimpleJson::read_file("test.json");

    if (loaded)
    {
        std::cout << "File loaded successfully\n";
        std::cout << CSimpleJson::write_str(*loaded) << "\n";
    }
    else
    {
        std::cout << "Could not read file\n";
    }

    std::cout << "\n";
}

void validation_example()
{
    std::cout << "---- JSON validation ----\n";

    std::string valid_json = R"({"name":"Mahmoud","age":24})";
    std::string invalid_json = R"({"name":"Mahmoud",})";

    std::cout << "Valid JSON: "
              << (CSimpleJson::is_valid(valid_json) ? "true" : "false")
              << "\n";

    std::cout << "Invalid JSON: "
              << (CSimpleJson::is_valid(invalid_json) ? "true" : "false")
              << "\n\n";
}

int main()
{
    std::cout << "Simple JSON Library Demo\n";
    std::cout << "========================\n\n";

    parse_example();
    build_example();
    file_io_example();
    validation_example();

    std::cout << "Done.\n";

    return 0;
}
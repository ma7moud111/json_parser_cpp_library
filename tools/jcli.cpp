#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include "../include/simple_json.hpp"

std::vector<std::string> split(const std::string& path)
{
    std::vector<std::string> tokens;
    std::stringstream ss(path);
    std::string token;

    while (std::getline(ss, token, '.'))
        tokens.push_back(token);

    return tokens;
}

bool is_number(const std::string& s)
{
    for (char c : s)
    {
        if (!std::isdigit(c))
            return false;
    }
    return !s.empty();
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: jcli <file> [query]" << std::endl;
        return 1;
    }

    std::string file = argv[1];

    CSimpleJson json;

    auto result = json.read_file(file);

    if (!result)
    {
        std::cout << "Invalid JSON file" << std::endl;
        return 1;
    }

    CJsonValue value = *result;

    if (argc == 2)
    {
        std::cout << json.write_str(value) << std::endl;
        return 0;
    }

    std::string query = argv[2];
    auto keys = split(query);

    CJsonValue* current = &value;

    for (const auto& key : keys)
    {
        if (current->is_object())
        {
            current = &((*current)[key]);
        }
        else if (current->is_array() && is_number(key))
        {
            int index = std::stoi(key);
            current = &((*current)[index]);
        }
        else
        {
            std::cout << "Invalid query path" << std::endl;
            return 1;
        }
    }

    std::cout << json.write_str(*current) << std::endl;

    return 0;
}
#include <nlohmann/json.hpp>
#include "weather.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

std::string weather::run_py_command(std::string city_name)
{
    std::string command = "python3 fetchdata.py " + city_name;
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    return result;
}

std::map<std::string, std::string> weather::parse_python_data(const std::string city_name)
{
    std::string result = run_py_command(city_name);
    json j = json::parse(result);
    auto w = j["weather"];

    std::map<std::string, std::string> weather = {
        {"IsDay", std::to_string(w["is_day"].get<int>())},
        {"temperature", std::to_string(w["temperature"].get<double>())},
        {"windspeed", std::to_string(w["windspeed"].get<double>())},
        {"winddirection", std::to_string(w["winddirection"].get<int>())}
    };

    return weather;
}



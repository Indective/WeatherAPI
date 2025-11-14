#pragma once

#include <iostream>
#include <string>
#include <map>

namespace weather
{
    std::string run_py_command(std::string city_name);
    std::map<std::string, std::string> parse_python_data(const std::string city_name);
    void display_weather_info(std::string text, bool &searched, std::map<std::string,std::string> &weather);
    std::string user_text(std::string text);
}
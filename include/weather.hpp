#include <iostream>
#include <string>
#include <map>

namespace weather
{
    std::string run_py_command(std::string city_name);
    std::map<std::string, std::string> parse_python_data(const std::string city_name);
}
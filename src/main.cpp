#include "weather.hpp"
#include <iostream>
#include "string"
#include <map>
#include <filesystem>

namespace fs =  std::filesystem;

int main()
{
    fs::current_path(fs::current_path().parent_path().string());
    fs::current_path(fs::current_path().string() + "/src");

    std::string city_name;
    std::map<std::string,std::string> weather;

    while(true)
    {
        std::cout << "Enter city name : " << std::endl;
        std::getline(std::cin, city_name);

        weather = weather::parse_python_data(city_name);
        for(const auto& howismyweather : weather)
        {
            std::cout << howismyweather.first << " : " << howismyweather.second << std::endl;
        }
    }
    
    return 0;
}
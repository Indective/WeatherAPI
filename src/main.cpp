#include "weather.hpp"
#include "raylib.h"
#include <iostream>
#include <string>
#include <map>
#include <filesystem>

namespace fs =  std::filesystem;

int main()
{
    const int screen_width = 900;
    const int screen_height = 1500;

    fs::current_path(fs::current_path().parent_path().string());
    fs::current_path(fs::current_path().string() + "/src");
    std::map<std::string,std::string> weather;

    std::string city_name;
    
    while(true)
    {
        std::cout << "\nEnter City Name : ";
        std::getline(std::cin, city_name);
        weather = weather::parse_python_data(city_name);

        for(auto& howismyweather : weather)
        {
            std::cout << howismyweather.first << " " << howismyweather.second << std::endl;
        }
    }

    
    
    return 0;
}

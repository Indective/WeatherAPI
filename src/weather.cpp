#include <nlohmann/json.hpp>
#include "weather.hpp"
#include "raylib.h"
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
        {"Fetching for city : ", city_name},
        {"temperature (°C) : ", std::to_string(w["temperature_2m"].get<int>())},
        {"windspeed (km/h) : ", std::to_string(w["wind_speed_10m"].get<int>())},
        {"winddirection (°) : ", std::to_string(w["wind_direction_10m"].get<int>())},
        {"rain (mm) : ", std::to_string(w["rain"].get<int>())},
        {"relative humidity (%) : ", std::to_string(w["relative_humidity_2m"].get<int>())},
        {"visibility (m) : ", std::to_string(w["visibility"].get<int>())},
        {"interval (seconds) : ", std::to_string(w["interval"].get<int>())}
    };

    return weather;
}

void weather::display_weather_info(std::string text, bool &searched, std::map<std::string,std::string> &weather, const int screen_width, const int screen_height)
{
    const int posx = screen_width/2-  200; // X position for items to be displayed 
    const int posy = screen_height/2 * 0.30;
    if(IsKeyPressed(KEY_ENTER)) // start searching if the user pressed ENTER
    {
        if(!(text == ""))
        {
            weather = weather::parse_python_data(text);
            searched = true;
        }
    } 

    if(searched)
    {   
        int line_counter = 0; // count lines when displaying results
        for(auto& howismyweather : weather)
        {
            DrawText(howismyweather.first.c_str(),posx,posy + line_counter,20,BLACK);
            DrawText(howismyweather.second.c_str(),posx + 300,posy + line_counter,20,BLACK);\

            line_counter += 50; // advance 50 pixels now for better visualization

        }
    }
}

std::string weather::user_text(std::string text)
{
    int key = GetCharPressed(); // get key pressed in char (unicode)
    while(key > 0)
    {
        if(key >= 32 && key <= 125) // check if unicode value is within range of valid chars
        {
            text.push_back((char)key); // convert uncicode value to char and it to text string
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty())  // remove last character when pressing backspace
    {
        text.pop_back();
    }

    return text;
}

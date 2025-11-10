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

    Rectangle text_box = {50, 50, 250, 40};

    bool focused = false;
    bool searched = false;
    int line_counter = 0; // count lines when displaying results
    char* result = "no city searched yet"; // last result fetched (city name)
    std::string text = ""; // text string to be displayed on screen based on what the user types
    
    while(true)
    {
        searched = false;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse_position = GetMousePosition();
            focused = CheckCollisionPointRec(mouse_position,text_box);
        }
        if(focused)
        {
            int key = GetCharPressed(); // get key pressed in char (unicode)
            while(key > 0)
            {
                if(key >= 32 && key <= 125) // check if unicode value is within range of valid chars
                {
                    text.push_back((char)key); // convert uncicode value to char and it to text string
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !text.empty())  // remove last character when pressing backspace
            {
                text.pop_back();
            }

            if(IsKeyPressed(KEY_ENTER)) // start searching if the user pressed ENTER
            {
                result = "Fetching for city : ", text.c_str();
                weather = weather::parse_python_data(text);
                
                focused = false;
                searched = true;
            }

        }


        // Begin drawing
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Weather ass API",10,10,40,BLACK);

        DrawRectangleRec(text_box, RAYWHITE); // draw text box
        DrawRectangleLinesEx(text_box, 2, focused ? BLUE : DARKGRAY);

        DrawText(text.c_str(), text_box.x + 8, text_box.y + 10, 20, BLACK);

        // Cursor
        if (focused && (GetTime() * 2 - (int)(GetTime() * 2) < 0.5)) 
        {
            int tw = MeasureText(text.c_str(), 20);
            DrawLine(text_box.x + 8 + tw + 2, text_box.y + 8, text_box.x + 8 + tw + 2, text_box.y + 32, BLACK);
        }

        if(searched)
        {
            DrawText(result,75,75,10,BLACK);
            for(auto& howismyweather : weather)
            {
                DrawText(howismyweather.first.c_str(),75,80 + line_counter,5,BLACK);
                DrawText(howismyweather.second.c_str(),80,80 + line_counter,5,BLACK);
                line_counter ++;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

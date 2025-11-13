#include "weather.hpp"
#include "raylib.h"
#include <iostream>
#include <string>
#include <map>
#include <filesystem>

namespace fs =  std::filesystem;

int main()
{
    const int screen_width = 1500;
    const int screen_height = 900;

    fs::current_path(fs::current_path().parent_path().string());
    fs::current_path(fs::current_path().string() + "/src");
    std::map<std::string,std::string> weather;

    Rectangle text_box = {60, 60, 250, 40};

    bool focused = false;
    bool searched = false;
    const char* result = "no city searched yet"; // last result fetched 
    std::string text = ""; // text string to be displayed on screen based on what the user types
    
    SetTargetFPS(60);
    InitWindow(screen_width,screen_height,"Weather API");

    while(true)
    {
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

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !text.empty())  // remove last character when pressing backspace
            {
                text.pop_back();
            }

            if(IsKeyPressed(KEY_ENTER)) // start searching if the user pressed ENTER
            {
                if(!(text == ""))
                {
                    const char* temp = text.c_str();
                    result = "Fetching for city : ", temp;
                    weather = weather::parse_python_data(text);
                    
                    focused = false;
                    searched = true;
                }
            }
        }


        // Begin drawing
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Weather API",10,10,40,BLACK);

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
            int line_counter = 0; // count lines when displaying results
            DrawText(result,60,130,20,BLACK);
            for(auto& howismyweather : weather)
            {
                std::cout << howismyweather.first << " " << howismyweather.second << std::endl;
                DrawText(howismyweather.first.c_str(),60,150 + line_counter,20,BLACK);
                DrawText(howismyweather.second.c_str(),60 + 200,150 + line_counter,20,BLACK);
                line_counter += 50;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

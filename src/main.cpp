#include "weather.hpp"
#include "raylib.h"
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <vector>

namespace fs =  std::filesystem;

int main()
{
    const int screen_width = 1500;
    const int screen_height = 900;

    fs::current_path(fs::current_path().parent_path().string());
    fs::current_path(fs::current_path().string() + "/src");

    std::string text;
    Rectangle text_box = {screen_width/2 - 150, 80, 250, 40};

    bool searched = false;
    SetTargetFPS(60);
    InitWindow(screen_width,screen_height,"Weather API");
    std::map<std::string,std::string> weather;

    while(!WindowShouldClose())
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse_position = GetMousePosition();
        }

        text = weather::user_text(text);

        // Begin drawing
        BeginDrawing();
        ClearBackground((Color){220, 230, 255, 255});

        DrawText("Weather API",screen_width/2 - 150,10,40,BLACK);

        DrawRectangleRec(text_box, RAYWHITE); // draw text box
        DrawRectangleLinesEx(text_box, 2, BLUE);

        DrawText(text.c_str(), text_box.x + 8, text_box.y + 10, 20, BLACK);

        // Cursor
        if ((GetTime() * 2 - (int)(GetTime() * 2) < 0.5)) 
        {
            int tw = MeasureText(text.c_str(), 20);
            DrawLine(text_box.x + 8 + tw + 2, text_box.y + 8, text_box.x + 8 + tw + 2, text_box.y + 32, BLACK);
        }

        weather::display_weather_info(text, searched, weather, screen_width, screen_height);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

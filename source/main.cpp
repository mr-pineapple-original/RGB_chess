#pragma once
// Normal Libraries
#include <iostream>
#include <vector>
#include <math.h>
// Raylib Libraries
#include <raylib.h>
// My libraries
#include "mainmenu.hpp"
#include "player.hpp"
#include "sprite.hpp"

// Using namespace
using namespace std;
bool game_state = false;
int main()
{
    // Setting the window
    int monitor = GetCurrentMonitor();
    const int screen_width = GetMonitorWidth(monitor);
    const int screen_height = GetMonitorHeight(monitor);
    const float grid_width = screen_width * 0.5;
    const float grid_height = screen_height;
    const float grid_offset = screen_width * 0.25;
    // Rectangle grid;
    // grid.x = grid_offset;    // 25% from left
    // grid.y = 0;              // top of screen
    // grid.width = grid_width; // 50% width
    // grid.height = grid_height; // full height
    // DrawRectangleRec(grid,GREEN);
    // DrawRectangleLinesEx(grid,2,WHITE);
    InitWindow(screen_width, screen_height, "RGB Chess");
    SetTargetFPS(60);
    InitAudioDevice();
    while (!WindowShouldClose()) // When game is opened
    {
        BeginDrawing();
        /* code */
        DrawText("Congrats! You created your first window!", 0 , 0, 20, GREEN);
        if(game_state == false)
        {
            main_menu_display();
            Player player;
            player.handle_user_input();
        }
        else
        {
            Sprite2D sprite = get_sprite(Type::Knight);
            DrawTextureRec(
                sprite.texture,
                sprite.src,
                Vector2{100, 100},
                WHITE
            );
        }
        EndDrawing();
    }
    

    CloseWindow();
    CloseAudioDevice();

    return 0;
}

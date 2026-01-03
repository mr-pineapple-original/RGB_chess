#pragma once
#include<raylib.h>
#include "main.cpp"
extern bool game_state;
bool text_button_clicked(const char* text, int x_position, int y_position, int font_size) // To see if the user has clicked the text
{
    int width = MeasureText(text , font_size);
    int height = y_position + font_size;
    Rectangle boundaries = {(float)x_position, (float)y_position , (float)width , (float)height};
    Vector2 mouse_position = GetMousePosition();
    if(CheckCollisionPointRec(mouse_position, boundaries) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // If the mouyse is pressed
        return true;                                                                                 // within the boundaries of
                                                                                                     // the button then return true
    else 
    return false;
}
void main_menu_display()
{
    const int START_GAME_TEXT_X = GetScreenWidth()/2 - 120;
    const int START_GAME_TEXT_Y = GetScreenHeight()/2 - 60;
    const int EXIT_GAME_TEXT_X = GetScreenWidth()/2 - 120;
    const int EXIT_GAME_TEXT_Y = GetScreenHeight()/2 - 20;
    
    DrawText("Start Game", GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 60, 40, LIGHTGRAY);
    DrawText("Exit Game", GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 20, 40, LIGHTGRAY);
    if(text_button_clicked("Start Game", START_GAME_TEXT_X, START_GAME_TEXT_Y, 40))
    {
        game_state = true;
    }
    if(text_button_clicked("Exit Game", EXIT_GAME_TEXT_X, EXIT_GAME_TEXT_Y, 40))
    exit(0);
}
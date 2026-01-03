
#include <raylib.h>

#include "mainmenu.hpp"
#include "sprite.hpp"
#include "game_state.hpp"

int main()
{
    InitWindow(1280, 720, "RGB Chess");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (game_state == GameState::MainMenu)
        {
            main_menu_display();
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
    return 0;
}


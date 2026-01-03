#pragma once
#include "player.hpp"
void Player::handle_user_input()
{
    if (IsKeyPressed(KEY_F11)) 
    {
        ToggleFullscreen();
    }
}

#include "player.hpp"

void Player::handle_user_input()
{
    if (IsKeyPressed(KEY_F11)) // Toggling full screen etc
    {
    ToggleFullscreen();
    }
}
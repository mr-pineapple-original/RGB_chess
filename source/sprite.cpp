#include "sprite.hpp"

Sprite2D get_sprite(Type type)
{
    static Texture2D chessTexture = LoadTexture("sprites/chess.png");

    constexpr int SPRITE_SIZE = 16;
    int index = static_cast<int>(type);

    Rectangle src {
        static_cast<float>(index * SPRITE_SIZE),
        0.0f,
        static_cast<float>(SPRITE_SIZE),
        static_cast<float>(SPRITE_SIZE)
    };

    return Sprite2D {
        chessTexture,
        src
    };
}





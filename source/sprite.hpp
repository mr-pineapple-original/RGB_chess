#pragma once
#include <raylib.h>

enum class Type {
    Pawn   = 1,
    Rook   = 2,
    Knight = 3,
    Bishop = 4,
    Queen  = 5,
    King   = 6
};

struct Sprite2D {
    Texture2D texture;
    Rectangle src;
};

Sprite2D get_sprite(Type type);


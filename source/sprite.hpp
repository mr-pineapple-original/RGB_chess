#pragma once
#include <raylib.h>

enum class Type {
    Pawn   = 0,
    Rook   = 1,
    Knight = 2,
    Bishop = 3,
    Queen  = 4,
    King   = 5
};

struct Sprite2D {
    Texture2D texture;
    Rectangle src;
};

Sprite2D get_sprite(Type type);


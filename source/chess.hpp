#pragma once
#include<iostream>
#include<raylib.h>

// Creating chess board using modular programming and mixing it with
// OOP for excelllent results XD
void create_chess_board()
{
    for(int rows = 0; rows < 8; rows++)
    {
        for(int cols = 0; cols < 8; cols++)
        {
            bool is_light_square = (rows+cols) % 2 != 0;
            std::string square_color = (is_light_square) ? "light_col" : "dark_col";
        }
    }
}

// class chess_pieces
// {   
//     public:
//         static const int none = 0;
//         static const int king = 1;
//         static const int pawn = 2;
//         static const int knight = 3;
//         static const int bishop = 4;
//         static const int 
// };
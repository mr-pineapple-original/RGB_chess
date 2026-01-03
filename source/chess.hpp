#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<raylib.h>

// Creating chess board using modular programming and mixing it with
// OOP for excelllent results XD

extern int squares[64];
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

class chess_pieces
{   
    public:
        static const int none = 0;
        static const int king = 1;
        static const int pawn = 2;
        static const int knight = 3;
        static const int bishop = 4;
        static const int rook = 5;
        static const int queen = 6;

        static const int white = 8;
        static const int black = 16;
};  

class chess_fen_encryption
{
    public:
    const std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; 
};

static constexpr int direction_offsets[8] = {8,-8,-1,1,7,-7,9,-9}; 
static std::vector<std::vector<int>> num_squares_to_edge(64, std::vector<int>(8,0));

void static precomputed_move_data()
{
    for(int rows = 0; rows < 8; rows++)
    {
        for(int cols = 0; cols < 8; cols++)
        {
            int num_north = 7 - cols;
            int num_south = cols;
            int num_west = rows;
            int num_east = 7 - rows;

                int square_index = cols * 8 + rows;
                num_squares_to_edge[square_index] = {
                    num_north,
                    num_south,
                    num_west,
                    num_east,
                    std::min(num_north, num_west),
                    std::min(num_south, num_east),
                    std::min(num_north, num_east),
                    std::min(num_south,num_west),
                };
        }
    }
}
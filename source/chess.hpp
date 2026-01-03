#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include <unordered_map>

#include "sprite.hpp"
// ====== Board ======
extern int squares[64];

void create_chess_board();
void precomputed_move_data();
void draw_pieces();
void update_board_metrics();
Type piece_to_sprite(int piece);
std::unordered_map<char, int> load_position_fen(const std::string& fen);

// ====== Pieces ======
class ChessPiece
{
public:
    static const int none   = 0;
    static const int king   = 1;
    static const int pawn   = 2;
    static const int knight = 3;
    static const int bishop = 4;
    static const int rook   = 5;
    static const int queen  = 6;

    static const int white  = 8;
    static const int black  = 16;
};

// ====== FEN ======
extern const std::string start_fen;

// ====== Move data ======
extern const int direction_offsets[8];
extern std::vector<std::vector<int>> num_squares_to_edge;

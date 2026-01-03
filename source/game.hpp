#pragma once
#include "player.hpp"
#include "game_state.hpp"
#include "chess.hpp"

void game_draw()
{
    if(game_state==GameState::Started)
    {
    create_chess_board();
    load_position_fen(start_fen);
    draw_pieces();
    }
}
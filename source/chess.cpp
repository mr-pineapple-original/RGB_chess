#pragma once
#include<iostream>
#include<cctype>
#include<unordered_map> // Of course we need to use data structures to make this program
#include "chess.hpp"        
const std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
std::string fen;
// static void load_position_fen(string fen)
// {
//      var piece_type_from_symbol = new Dictionary<char,int>()
//      {
//         ['k'] = chess_pieces.king, ['p'] = chess_pieces.pawn, ['n'] = chess_pieces.knight,
//         ['b'] = chess_pieces.bishop, ['r'] = chess_pieces.rook, ['q'] = chess_pieces.queen
//      };
// };
std::unordered_map<char,int> load_position_fen(std::string fen)
{
    std::unordered_map<char,int> piece_type_from_symbol = {
    {'k', chess_pieces::king},
    {'p', chess_pieces::pawn},
    {'n', chess_pieces::knight},
    {'b', chess_pieces::bishop},
    {'r', chess_pieces::rook},
    {'q', chess_pieces::queen}
};
    std::string fen_board = fen.substr(0, fen.find(' '));
    int rows = 0, cols = 7;
    for (char symbol : fen_board)
    {
        if(symbol=='/')
        {
            rows = 0;
            cols--;
        }
        else
        {
            if(std::isdigit(symbol))
            {
                rows = rows +  symbol - '0';
            }
            else
            {
                int piece_colour = (std::isupper(symbol)) ? chess_pieces::white : chess_pieces::black;
                int piece_type = piece_type_from_symbol[std::tolower(symbol)];
                squares[cols * 8 + rows] = piece_type | piece_colour;
                rows++;
            }
        }
    }
    return piece_type_from_symbol;
}

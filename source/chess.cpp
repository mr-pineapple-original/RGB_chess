#include "chess.hpp"
#include "sprite.hpp"

#include <iostream>
#include <cctype>
#include <unordered_map>
#include <algorithm>

// ====== Globals ======
int squares[64] = {0};
int selected_piece = ChessPiece::none;
float board_x = 0.0f;
float board_y = 0.0f;
float square_size = 0.0f;






const std::string start_fen =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const int direction_offsets[8] = { 8, -8, -1, 1, 7, -7, 9, -9 };

std::vector<std::vector<int>> num_squares_to_edge(64, std::vector<int>(8, 0));

struct Move_piece {
    int start_square;
    int target_square;
};
// Vector to store moves globally (or pass by reference)
std::vector<Move_piece> moves;

void update_board_metrics()
{
    square_size = GetScreenHeight() / 8.0f;
    board_x = (GetScreenWidth()  - square_size * 8) / 2.0f;
    board_y = (GetScreenHeight() - square_size * 8) / 2.0f;
}

// ====== Board drawing ======
void create_chess_board()
{
    float square_size = GetScreenHeight() / 8.0f;

    float board_width  = square_size * 8;
    float board_height = square_size * 8;

    float offset_x = (GetScreenWidth()  - board_width)  / 2.0f;
    float offset_y = (GetScreenHeight() - board_height) / 2.0f;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            bool is_light = (row + col) % 2 == 0;
            Color color = is_light ? RAYWHITE : DARKGRAY;

            float x = offset_x + col * square_size;
            float y = offset_y + row * square_size;

            DrawRectangle(
                (int)x,
                (int)y,
                (int)square_size,
                (int)square_size,
                color
            );
        }
    }
}

// ====== Precompute move data ======
void precomputed_move_data()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int north = 7 - row;
            int south = row;
            int west  = col;
            int east  = 7 - col;

            int index = row * 8 + col;

            num_squares_to_edge[index] = {
                north,
                south,
                west,
                east,
                std::min(north, west),
                std::min(south, east),
                std::min(north, east),
                std::min(south, west)
            };
        }
    }
}


// Helper functions
bool is_type(int piece, int type) {
    return (piece & 7) == type; // mask color bits
}

bool is_colour(int piece, int colour) {
    return (piece & (ChessPiece::white | ChessPiece::black)) == colour;
}

bool is_sliding_piece(int piece) {
    int t = piece & 7;
    return t == ChessPiece::rook || t == ChessPiece::bishop || t == ChessPiece::queen;
}


void generate_sliding_moves(int start_square, int piece, int friendly_color, int opponent_color)
{
    int start_index = is_type(piece, ChessPiece::bishop) ? 4 : 0;
    int end_index   = is_type(piece, ChessPiece::rook)   ? 4 : 8;

    for (int direction_index = start_index; direction_index < end_index; direction_index++)
    {
        for (int n = 0; n < num_squares_to_edge[start_square][direction_index]; n++)
        {
            int target_square = start_square + direction_offsets[direction_index] * (n + 1);
            int piece_on_target_square = squares[target_square];

            // Blocked by friendly piece
            if (is_colour(piece_on_target_square, friendly_color)) break;

            // Add move
            moves.push_back({start_square, target_square});

            // Can't go further if we capture opponent
            if (is_colour(piece_on_target_square, opponent_color)) break;
        }
    }
}

// Generate all moves
std::vector<Move_piece> generate_moves(int colour_to_move)
{
    moves.clear(); // start fresh

    int friendly_color = colour_to_move;
    int opponent_color = (colour_to_move == ChessPiece::white) ? ChessPiece::black : ChessPiece::white;

    for (int start_square = 0; start_square < 64; start_square++)
    {
        int piece = squares[start_square];
        if (piece == ChessPiece::none) continue;

        if (is_colour(piece, friendly_color))
        {
            if (is_sliding_piece(piece))
            {
                generate_sliding_moves(start_square, piece, friendly_color, opponent_color);
            }
            // TODO: handle non-sliding pieces (pawn, knight, king)
        }
    }
}

// ====== FEN loader ======
std::unordered_map<char, int> load_position_fen(const std::string& fen)
{
    std::unordered_map<char, int> piece_map = {
        {'k', ChessPiece::king},
        {'p', ChessPiece::pawn},
        {'n', ChessPiece::knight},
        {'b', ChessPiece::bishop},
        {'r', ChessPiece::rook},
        {'q', ChessPiece::queen}
    };

    std::string board = fen.substr(0, fen.find(' '));

    int row = 7, col = 0;

    for (char c : board)
    {
        if (c == '/')
        {
            row--;
            col = 0;
        }
        else if (std::isdigit(c))
        {
            col += c - '0';
        }
        else
        {
            int color = std::isupper(c)
                        ? ChessPiece::white
                        : ChessPiece::black;

            int piece = piece_map[std::tolower(c)];
            squares[row * 8 + col] = piece | color;
            col++;
        }
    }

    return piece_map;
}



void draw_pieces()
{
    float square_size = GetScreenHeight() / 8.0f;
    float offset_x = (GetScreenWidth() - square_size * 8) / 2.0f;
    float offset_y = (GetScreenHeight() - square_size * 8) / 2.0f;

    for (int index = 0; index < 64; index++)
    {
        int piece = squares[index];
        if (piece == ChessPiece::none) continue;

        int row = index / 8;
        int col = index % 8;

        Sprite2D sprite = get_sprite(piece_to_sprite(piece));

        Rectangle dst = {
            offset_x + col * square_size,
            offset_y + row * square_size,
            square_size,
            square_size
        };
        Color color = WHITE;
        if (piece & ChessPiece::white) {
            color = WHITE;
        }
        else if (piece & ChessPiece::black) {
            color = GRAY;
        }
        DrawTexturePro(
            sprite.texture,
            sprite.src,
            dst,
            {0, 0},
            0.0f,
            color
        );

        bool hovered = CheckCollisionPointRec(GetMousePosition(), dst);
        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            
            selected_piece = piece;
            moves.clear();
            generate_sliding_moves(index, piece, ChessPiece::white, ChessPiece::black);

            for (const Move_piece& m : moves) {
                int file = m.target_square % 8;
                int rank = m.target_square / 8;

                float cx = board_x + file * square_size + square_size * 0.5f;
                float cy = board_y + rank * square_size + square_size * 0.5f;

                DrawCircle(cx, cy, square_size * 0.15f, Fade(BLACK, 0.5f));
            }
            std::cout << "[Piece Clicked]: " << piece << "[Moves]: " << moves[0] << std::endl;
        }

        

    }
}

Type piece_to_sprite(int piece)
{
    switch (piece & 7) // mask color bits
    {
        case ChessPiece::pawn:   return Type::Pawn;
        case ChessPiece::rook:   return Type::Rook;
        case ChessPiece::knight: return Type::Knight;
        case ChessPiece::bishop: return Type::Bishop;
        case ChessPiece::queen:  return Type::Queen;
        case ChessPiece::king:   return Type::King;
        default:                   return Type::Pawn; // safe fallback
    }
}


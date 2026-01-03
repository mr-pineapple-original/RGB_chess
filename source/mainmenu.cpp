#include "mainmenu.hpp"
#include "game_state.hpp"
#include <cstdlib>

static bool is_text_button_clicked(const char *text, int x_position,
                                   int y_position, int font_size) {
  int width = MeasureText(text, font_size);
  Rectangle bounds{(float)x_position, (float)y_position, (float)width,
                   (float)font_size};

  Vector2 mouse = GetMousePosition();
  return CheckCollisionPointRec(mouse, bounds) &&
         IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void main_menu_display() {
  const int start_x = GetScreenWidth() / 2 - 120;
  const int start_y = GetScreenHeight() / 2 - 60;
  const int exit_x = GetScreenWidth() / 2 - 120;
  const int exit_y = GetScreenHeight() / 2 - 20;

  DrawText("Start Game", start_x, start_y, 40, LIGHTGRAY);
  DrawText("Exit Game", exit_x, exit_y, 40, LIGHTGRAY);

  if (is_text_button_clicked("Start Game", start_x, start_y, 40))
    game_state = GameState::Started;

  if (is_text_button_clicked("Exit Game", exit_x, exit_y, 40))
    std::exit(0);
}

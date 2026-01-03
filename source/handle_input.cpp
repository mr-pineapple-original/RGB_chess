#include "handle_input.hpp"

void handle_input() {
  if (IsKeyPressed(KEY_F11)) {
    ToggleFullscreen();
  } else if (IsKeyPressed(KEY_Q)) {
    CloseWindow();
  }
}

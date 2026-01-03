#include "mainmenu.hpp"
#include "game_state.hpp"
#include <cstdlib>

static Texture2D startButtonTex = {};
static Texture2D exitButtonTex = {};
static bool buttons_loaded = false;

static void load_buttons() {
  if (buttons_loaded)
    return;

  startButtonTex = LoadTexture("sprites/start-button.png");
  exitButtonTex = LoadTexture("sprites/exit-button.png");

  buttons_loaded = true;
}

static bool animated_sprite_button(Texture2D texture, int x, int y, float scale,
                                   float frame_time) {
  static float timer = 0.0f;
  static int frame = 0;

  constexpr int FRAME_W = 32;
  constexpr int FRAME_H = 16;

  int frame_count = texture.width / FRAME_W;

  timer += GetFrameTime();
  if (timer >= frame_time) {
    timer = 0.0f;
    frame = (frame + 1) % frame_count;
  }

  Rectangle src{(float)(frame * FRAME_W), 0.0f, (float)FRAME_W, (float)FRAME_H};

  Rectangle dst{(float)x, (float)y, FRAME_W * scale, FRAME_H * scale};

  DrawTexturePro(texture, src, dst, Vector2{0, 0}, 0.0f, WHITE);

  Vector2 mouse = GetMousePosition();
  bool hovered = CheckCollisionPointRec(mouse, dst);

  return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
void main_menu_display() {
  load_buttons();

  const int scale = 4;
  const int btn_w = 32 * scale;
  const int btn_h = 16 * scale;
  const int gap = 20;

  const int start_x = GetScreenWidth() / 2 - btn_w / 2;
  const int exit_x = start_x;

  const int start_y = GetScreenHeight() / 2 - btn_h - gap / 2;
  const int exit_y = GetScreenHeight() / 2 + gap / 2;

  if (animated_sprite_button(startButtonTex, start_x, start_y, scale, 0.25f))
    game_state = GameState::Started;

  if (animated_sprite_button(exitButtonTex, exit_x, exit_y, scale, 0.25f))
    std::exit(0);
}

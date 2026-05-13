#include "game.h"
#include <raylib.h>

int tick = 0;

int main() {

  Color darkBlue = {44, 44, 127, 255};

  InitWindow(300, 600, "raylib Tetris");
  SetTargetFPS(60);

  Game game = Game();

  while (WindowShouldClose() == false) {

    game.ProcessInput();

    if (tick <= 10) {
      tick++;
    } else {
      game.Process();
      tick = 0;
    }

    BeginDrawing();
    ClearBackground(darkBlue);

    game.Draw();

    EndDrawing();
  }

  CloseWindow();
}

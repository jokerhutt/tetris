#include "block.h"
#include "blocks.cpp"
#include "grid.h"
#include <raylib.h>

int main() {

  Color darkBlue = {44, 44, 127, 255};

  InitWindow(300, 600, "raylib Tetris");
  SetTargetFPS(60);

  Grid grid = Grid();
  grid.Print();

  LBlock lBlock = LBlock();

  while (WindowShouldClose() == false) {

    BeginDrawing();
    ClearBackground(darkBlue);
    grid.Draw();
    lBlock.Draw(1, 1);

    EndDrawing();
  }

  CloseWindow();
}

#pragma once
#include "block.h"
#include "imgui.h"
#include "rlImGui.h"
#include <raylib.h>

class UI {

public:
  UI(int height, int width);
  int width;
  int height;
  void Draw(Block nextBlock, bool gameOver);
};

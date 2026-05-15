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
  enum class Action { None, PlayAgain, Exit };
  Action Draw(Block nextBlock, bool gameOver, int score);
};

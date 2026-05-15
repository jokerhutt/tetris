#pragma once
#include "block.h"
#include "blocks.cpp"
#include "grid.h"
#include "position.h"
#include "ui.h"
#include <iostream>
#include <vector>

class Game {

public:
  Game();
  Grid grid;
  bool gameOver;
  Block currentBlock;
  Block nextBlock;
  std::vector<Block> blocks;
  int uiOffsetY;
  void ProcessInput();
  void Draw();
  void Process();

private:
  Block GenerateRandomBlock();
  UI ui;
  int placementTimer;
  int clearAnimationTimer;
  void ProcessBlock();
  void MoveBlockLeft();
  void MoveBlockRight();
  bool IsBlockOutside();
  bool BlockFits();
  void RotateBlock();
  std::vector<Block> GetAllBlocks();
};

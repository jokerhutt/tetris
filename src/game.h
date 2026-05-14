#pragma once
#include "block.h"
#include "blocks.cpp"
#include "grid.h"
#include "position.h"
#include <iostream>
#include <vector>

class Game {

public:
  Game();
  Grid grid;
  Block currentBlock;
  std::vector<Block> blocks;
  void ProcessInput();
  void Draw();
  void Process();

private:
  Block GenerateRandomBlock();
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

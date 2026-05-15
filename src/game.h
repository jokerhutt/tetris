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
  int linesCleared;
  Block currentBlock;
  Block nextBlock;
  std::vector<Block> blocks;
  int uiOffsetY;
  void ProcessInput();
  void ProcessMusic();
  int GetTickRate();
  void Draw();
  int score;
  void PlayAgain();
  bool ShouldExit() const;
  void Process();

private:
  Music music;
  Block GenerateRandomBlock();
  void Reset();
  bool playMusic;
  void ToggleMusic();
  void AddPoints();
  UI ui;
  bool exitRequested;
  int placementTimer;
  int clearAnimationTimer;
  void ProcessBlock();
  void MoveBlockLeft();
  void MoveBlockRight();
  void MoveBlockDown();
  bool IsBlockOutside();
  bool BlockFits();
  void RotateBlock();
  std::vector<Block> GetAllBlocks();
};

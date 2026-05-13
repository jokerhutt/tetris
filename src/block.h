#pragma once
#include "colors.h"
#include "position.h"
#include <map>

class Block {

public:
  Block();
  int id;
  std::map<int, std::vector<Position>> cells;
  void Move(int rows, int cols);

private:
  int cellSize;
  int rotationState;
  std::vector<Color> colors;
};

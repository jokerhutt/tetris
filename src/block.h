#pragma once
#include "colors.h"
#include "position.h"
#include <iostream>
#include <map>

class Block {

public:
  Block();
  int id;
  void Draw(int offsetX, int offsetY);
  std::map<int, std::vector<Position>> cells;
  void MoveDown(int rows, int cols);
  void PrintPosition();
  void Rotate();
  void UndoRotation();
  std::vector<Position> GetCellPositions();

private:
  int cellSize;
  int rotationState;
  int rowOffset;
  int columnOffset;
  std::vector<Color> colors;
};

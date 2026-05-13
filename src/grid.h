#pragma once
#include "position.h"
#include <raylib.h>
#include <vector>

class Grid {
public:
  Grid();
  void Initialize();
  void Print();
  void Draw();
  void PlaceBlock(std::vector<Position> positions, int colorId);
  bool IsCellOutside(int row, int col);
  bool IsCellEmpty(int row, int col);
  bool IsAtBottom(int row, int col);
  int grid[20][10];

private:
  std::vector<Color> GetCellColors();
  int numCols;
  int numRows;
  int cellSize;
  std::vector<Color> colors;
};

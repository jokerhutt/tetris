#pragma once
#include <raylib.h>
#include <vector>

class Grid {
public:
  Grid();
  void Initialize();
  void Print();
  void Draw();
  int grid[20][10];

private:
  std::vector<Color> GetCellColors();
  int numCols;
  int numRows;
  int cellSize;
  std::vector<Color> colors;
};

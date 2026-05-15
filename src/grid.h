#pragma once
#include "position.h"
#include <raylib.h>
#include <vector>

class Grid {
public:
  Grid();
  void Initialize();
  void Print();
  void Draw(int offsetY, bool isClearing);
  int clearAnimationTick;
  std::vector<int> rowsToClear;
  void PlaceBlock(std::vector<Position> positions, int colorId);
  void ProcessRows();
  bool IsCellOutside(int row, int col);
  bool IsCellEmpty(int row, int col);
  bool IsBelowCollideable(int row, int col);
  void ClearRows();
  int grid[20][10];

private:
  std::vector<Color> GetCellColors();
  void ClearRow(int rowToClear);
  bool IsRowFull(int row);
  int numCols;
  int numRows;
  int cellSize;
  std::vector<Color> colors;
};

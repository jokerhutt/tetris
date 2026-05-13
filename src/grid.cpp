#include "grid.h"
#include "colors.h"
#include <iostream>
#include <vector>

Grid::Grid() {

  numRows = 20;
  numCols = 10;
  cellSize = 30;
  Initialize();
  colors = GetCellColors();
}

void Grid::Initialize() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      grid[row][col] = 0;
    }
  }
}

void Grid::PlaceBlock(std::vector<Position> positions, int colorId) {

  for (Position pos : positions) {
    grid[pos.row][pos.column] = colorId;
  }
}

bool Grid::IsCellOutside(int row, int col) {
  if (row <= 0 || row >= numRows || col <= 0 || col >= numCols) {
    return true;
  }
  return false;
}

bool Grid::IsCellEmpty(int row, int col) { return grid[row][col] == 0; }

bool Grid::IsAtBottom(int row, int col) {
  int nextRow = row + 1;
  if (nextRow == numRows) {
    return true;
  }

  if (grid[nextRow][col] != 0) {
    return true;
  }

  return false;
}

std::vector<Color> Grid::GetCellColors() {
  return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
};

void Grid::Draw() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      int cellValue = grid[row][col];
      DrawRectangle(col * cellSize + 1, row * cellSize + 1, cellSize - 1,
                    cellSize - 1, colors[cellValue]);
    }
  }
};

void Grid::Print() {
  for (int row = 0; row < numRows; row++) {
    for (int column = 0; column < numCols; column++) {
      std::cout << grid[row][column];
    }
  }
}

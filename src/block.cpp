#include "block.h"

Block::Block() {
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  rowOffset = 0;
  columnOffset = 0;
};

void Block::MoveDown(int rows, int cols) {
  rowOffset += rows;
  columnOffset += cols;
}

void Block::Draw(int offsetX, int offsetY) {
  std::vector<Position> tiles = GetCellPositions();
  for (Position item : tiles) {
    DrawRectangle(item.column * cellSize + offsetX,
                  item.row * cellSize + offsetY, cellSize - 1, cellSize - 1,
                  colors[id]);
  }
}

void Block::Rotate() {

  if (rotationState == 3) {
    rotationState = 0;
  } else {
    rotationState++;
  }
}

void Block::UndoRotation() {
  if (rotationState == 0) {
    rotationState = 3;
  } else {
    rotationState--;
  }
}

void Block::PrintPosition() {

  std::vector<Position> tiles = GetCellPositions();

  std::cout << "POSITION: " << std::endl;
  for (Position pos : tiles) {
    std::cout << "| X: " << pos.row << " Y: " << pos.column << " | \n";
  }
  std::cout << "================" << std::endl;
}

std::vector<Position> Block::GetCellPositions() {

  std::vector<Position> tiles = cells[rotationState];
  std::vector<Position> movedTiles;

  for (Position item : tiles) {
    Position newPos =
        Position(item.row + rowOffset, item.column + columnOffset);
    movedTiles.push_back(newPos);
  }

  return movedTiles;
}

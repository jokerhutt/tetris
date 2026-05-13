#include "game.h"

Game::Game() {

  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GenerateRandomBlock();
}

void Game::Draw() {

  grid.Draw();
  currentBlock.Draw(1, 1);
}

void Game::Process() { ProcessBlock(); }

bool Game::IsBlockOutside() {
  std::vector<Position> positions = currentBlock.GetCellPositions();

  for (Position pos : positions) {
    if (grid.IsCellOutside(pos.row, pos.column)) {
      return true;
    }
  }
  return false;
}

void Game::ProcessInput() {
  int keyPressed = GetKeyPressed();
  if (keyPressed != 0) {

    switch (keyPressed) {
    case KEY_LEFT:

      break;

    case KEY_RIGHT:

      break;

    case KEY_UP:
      RotateBlock();
      break;

    case KEY_DOWN:
      // Move down faster?
      break;
    }
  }
}

void Game::RotateBlock() {

  currentBlock.Rotate();

  if (IsBlockOutside() || !BlockFits()) {
    currentBlock.UndoRotation();
  }
}

void Game::ProcessBlock() {
  currentBlock.MoveDown(1, 0);
  if (IsBlockOutside()) {
    std::cout << "Block outside";
    currentBlock.MoveDown(-1, 0);
  }

  std::vector<Position> positions = currentBlock.GetCellPositions();

  bool isAtBottom = false;

  for (Position pos : positions) {
    if (grid.IsAtBottom(pos.row, pos.column)) {
      isAtBottom = true;
      std::cout << "Is at bottom";
      break;
    }
  }

  std::cout << "Is at bottom " << isAtBottom << std::endl;

  if (isAtBottom) {
    grid.PlaceBlock(positions, currentBlock.id);
    currentBlock = GenerateRandomBlock();
    return;
  }
}

bool Game::BlockFits() {

  std::vector<Position> positions = currentBlock.GetCellPositions();
  for (Position pos : positions) {
    if (grid.IsCellEmpty(pos.row, pos.column) == false) {
      return false;
    }
  }
  return true;
}

std::vector<Block> Game::GetAllBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

Block Game::GenerateRandomBlock() {
  int randomIndex = GetRandomValue(0, blocks.size() - 1);
  return blocks[randomIndex];
}

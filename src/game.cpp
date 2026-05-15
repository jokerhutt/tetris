#include "game.h"

Game::Game() : ui(120, 300) {

  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GenerateRandomBlock();
  nextBlock = GenerateRandomBlock();
  uiOffsetY = 120;
  placementTimer = 0;
  clearAnimationTimer = 0;
  gameOver = false;
}

void Game::Draw() {
  if (clearAnimationTimer > 0) {
    grid.Draw(uiOffsetY, true);
  } else {
    grid.Draw(uiOffsetY, false);
  }
  currentBlock.Draw(1, 1 + uiOffsetY);

  ui.Draw(nextBlock);
}

void Game::Process() {
  if (!gameOver) {
    if (grid.rowsToClear.size() > 0) {
      grid.clearAnimationTick++;
      if (clearAnimationTimer >= 4) {
        grid.ClearRows();
        clearAnimationTimer = 0;
      } else {
        clearAnimationTimer++;
      }
    } else {
      ProcessBlock();
      grid.ProcessRows();
    }
  }
}

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
      MoveBlockLeft();
      break;

    case KEY_RIGHT:
      MoveBlockRight();
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

void Game::MoveBlockRight() {
  currentBlock.Move(0, 1);
  if (IsBlockOutside() || !BlockFits()) {
    currentBlock.Move(0, -1);
    return;
  }
}

void Game::MoveBlockLeft() {
  currentBlock.Move(0, -1);
  if (IsBlockOutside() || !BlockFits()) {
    currentBlock.Move(0, 1);
    return;
  }
}

void Game::RotateBlock() {

  currentBlock.Rotate();

  if (IsBlockOutside() || !BlockFits()) {
    currentBlock.UndoRotation();
  }
}

void Game::ProcessBlock() {
  if (placementTimer == 0) {
    currentBlock.Move(1, 0);
    if (IsBlockOutside()) {
      std::cout << "Block outside";
      currentBlock.Move(-1, 0);
    }
  }

  std::vector<Position> positions = currentBlock.GetCellPositions();

  bool isAtBottom = false;

  for (Position pos : positions) {
    if (grid.IsBelowCollideable(pos.row, pos.column)) {
      isAtBottom = true;
      std::cout << "Is at bottom";
      break;
    }
  }

  std::cout << "Is at bottom " << isAtBottom << std::endl;

  if (isAtBottom) {
    if (placementTimer >= 3) {
      grid.PlaceBlock(positions, currentBlock.id);
      currentBlock = nextBlock;
      if (!BlockFits() || IsBlockOutside()) {
        gameOver = true;
        return;
      }
      nextBlock = GenerateRandomBlock();
    } else {
      placementTimer++;
    }
  } else {
    placementTimer = 0;
  }
  return;
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

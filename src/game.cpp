#include "game.h"

Game::Game() : ui(120, 300) {

  music = LoadMusicStream("assets/audio/korobeiniki.mp3");
  PlayMusicStream(music);

  score = 0;
  linesCleared = 0;
  grid = Grid();
  playMusic = true;
  blocks = GetAllBlocks();
  currentBlock = GenerateRandomBlock();
  nextBlock = GenerateRandomBlock();
  uiOffsetY = 120;
  placementTimer = 0;
  clearAnimationTimer = 0;
  gameOver = false;
  exitRequested = false;
}

void Game::Reset() {
  grid.Initialize();
  currentBlock = GenerateRandomBlock();
  score = 0;
  linesCleared = 0;
  nextBlock = GenerateRandomBlock();
  placementTimer = 0;
  clearAnimationTimer = 0;
  gameOver = false;
}

int Game::GetTickRate() {

  if (linesCleared <= 10) {
    return 10;
  } else if (linesCleared <= 20) {
    return 9;
  } else if (linesCleared <= 30) {
    return 8;
  } else if (linesCleared <= 40) {
    return 7;
  } else if (linesCleared <= 50) {
    return 6;
  } else if (linesCleared <= 60) {
    return 5;
  } else {
    return 4;
  }
}

void Game::PlayAgain() { Reset(); }

bool Game::ShouldExit() const { return exitRequested; }

void Game::Draw() {
  if (clearAnimationTimer > 0) {
    grid.Draw(uiOffsetY, true);
  } else {
    grid.Draw(uiOffsetY, false);
  }
  currentBlock.Draw(1, 1 + uiOffsetY);

  UI::Action action = ui.Draw(nextBlock, gameOver, score);
  if (action == UI::Action::PlayAgain) {
    PlayAgain();
  } else if (action == UI::Action::Exit) {
    exitRequested = true;
  }
}

void Game::AddPoints() {
  switch (grid.rowsToClear.size()) {

  case 1:
    score += 100;
    break;

  case 2:
    score += 300;
    break;

  case 3:
    score += 500;
    break;

  case 4:
    score += 800;
    break;
  }
}

void Game::ProcessMusic() { UpdateMusicStream(music); }

void Game::Process() {
  if (!gameOver) {
    if (grid.rowsToClear.size() > 0) {
      grid.clearAnimationTick++;
      if (clearAnimationTimer >= 4) {
        AddPoints();
        linesCleared += grid.rowsToClear.size();
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

void Game::ToggleMusic() {
  if (!playMusic) {
    ResumeMusicStream(music);
  } else {
    PauseMusicStream(music);
  }

  playMusic = !playMusic;
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

    case KEY_M:
      ToggleMusic();
      break;

    case KEY_UP:
      RotateBlock();
      break;

    case KEY_DOWN:
      break;
    }
  }
  if (IsKeyDown(KEY_DOWN)) {
    MoveBlockDown();
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

void Game::MoveBlockDown() {
  currentBlock.Move(1, 0);
  if (IsBlockOutside() || !BlockFits()) {
    currentBlock.Move(-1, 0);
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
    if (IsBlockOutside() || !BlockFits()) {
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

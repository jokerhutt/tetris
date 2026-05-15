#include "ui.h"

#include <algorithm>
#include <cfloat>
#include <string>

// The UI is all vibe coded sorry

namespace {
ImU32 ToImColor(Color color) {
  return IM_COL32(color.r, color.g, color.b, color.a);
}

void DrawNextBlockPreview(ImDrawList *drawList, Block block, ImVec2 origin,
                          ImVec2 size) {
  std::vector<Position> cells = block.GetCellPositions();

  int minRow = cells[0].row;
  int maxRow = cells[0].row;
  int minColumn = cells[0].column;
  int maxColumn = cells[0].column;

  for (const Position &cell : cells) {
    minRow = std::min(minRow, cell.row);
    maxRow = std::max(maxRow, cell.row);
    minColumn = std::min(minColumn, cell.column);
    maxColumn = std::max(maxColumn, cell.column);
  }

  const float cellSize = 20.0f;
  const float gap = 2.0f;
  const float blockWidth = (maxColumn - minColumn + 1) * cellSize;
  const float blockHeight = (maxRow - minRow + 1) * cellSize;
  const float startX = origin.x + (size.x - blockWidth) * 0.5f;
  const float startY = origin.y + (size.y - blockHeight) * 0.5f;
  std::vector<Color> colors = GetCellColors();
  ImU32 cellColor = ToImColor(colors[block.id]);

  for (const Position &cell : cells) {
    float x = startX + (cell.column - minColumn) * cellSize;
    float y = startY + (cell.row - minRow) * cellSize;
    drawList->AddRectFilled(ImVec2(x, y),
                            ImVec2(x + cellSize - gap, y + cellSize - gap),
                            cellColor, 4.0f);
  }
}

void DrawCenteredText(ImDrawList *drawList, ImFont *font, const char *text,
                      float fontSize, float centerX, float y, ImU32 color) {
  ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text);
  drawList->AddText(font, fontSize, ImVec2(centerX - textSize.x * 0.5f, y),
                    color, text);
}

UI::Action DrawGameOverOverlay(int score) {
  const float screenWidth = static_cast<float>(GetScreenWidth());
  const float screenHeight = static_cast<float>(GetScreenHeight());

  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSize(ImVec2(screenWidth, screenHeight));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));

  ImGui::Begin("Game Over Overlay", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoScrollbar |
                   ImGuiWindowFlags_NoScrollWithMouse);

  ImDrawList *drawList = ImGui::GetWindowDrawList();
  ImFont *font = ImGui::GetFont();
  const float cardWidth = 242.0f;
  const float cardHeight = 194.0f;
  const float cardX = (screenWidth - cardWidth) * 0.5f;
  const float cardY = (screenHeight - cardHeight) * 0.5f;
  const float centerX = screenWidth * 0.5f;
  const std::string scoreText = "YOUR SCORE: " + std::to_string(score);
  UI::Action action = UI::Action::None;

  drawList->AddRectFilled(ImVec2(0.0f, 0.0f), ImVec2(screenWidth, screenHeight),
                          IM_COL32(5, 8, 20, 180));
  drawList->AddRectFilled(ImVec2(cardX, cardY),
                          ImVec2(cardX + cardWidth, cardY + cardHeight),
                          IM_COL32(24, 28, 45, 245), 8.0f);
  drawList->AddRect(ImVec2(cardX, cardY),
                    ImVec2(cardX + cardWidth, cardY + cardHeight),
                    IM_COL32(255, 88, 88, 255), 8.0f, 0, 2.0f);
  DrawCenteredText(drawList, font, "GAME OVER", 38.0f, centerX, cardY + 22.0f,
                   IM_COL32(255, 244, 244, 255));
  DrawCenteredText(drawList, font, scoreText.c_str(), 18.0f, centerX,
                   cardY + 80.0f, IM_COL32(184, 196, 230, 255));

  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f, 9.0f));
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 88, 88, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 112, 112, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(212, 64, 64, 255));
  ImGui::SetCursorScreenPos(ImVec2(cardX + 28.0f, cardY + 120.0f));
  if (ImGui::Button("PLAY AGAIN", ImVec2(cardWidth - 56.0f, 34.0f))) {
    action = UI::Action::PlayAgain;
  }
  ImGui::PopStyleColor(3);

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(55, 64, 94, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(68, 79, 114, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(40, 48, 72, 255));
  ImGui::SetCursorScreenPos(ImVec2(cardX + 28.0f, cardY + 158.0f));
  if (ImGui::Button("EXIT", ImVec2(cardWidth - 56.0f, 30.0f))) {
    action = UI::Action::Exit;
  }
  ImGui::PopStyleColor(3);
  ImGui::PopStyleVar(2);

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);

  return action;
}
} // namespace

UI::UI(int height, int width) {
  this->height = height;
  this->width = width;
};

UI::Action UI::Draw(Block nextBlock, bool gameOver, int score) {
  rlImGuiBegin();
  Action action = Action::None;

  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(width, height));

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(18, 22, 38, 255));

  ImGui::Begin(

      "UI",

      nullptr,

      ImGuiWindowFlags_NoTitleBar |

          ImGuiWindowFlags_NoResize |

          ImGuiWindowFlags_NoMove |

          ImGuiWindowFlags_NoCollapse |

          ImGuiWindowFlags_NoScrollbar |

          ImGuiWindowFlags_NoScrollWithMouse

  );

  ImDrawList *drawList = ImGui::GetWindowDrawList();
  ImVec2 windowPos = ImGui::GetWindowPos();
  ImVec2 panelMin(windowPos.x + 12.0f, windowPos.y + 12.0f);
  ImVec2 panelMax(windowPos.x + width - 12.0f, windowPos.y + height - 12.0f);
  ImVec2 previewMin(panelMax.x - 128.0f, panelMin.y + 40.0f);
  ImVec2 previewSize(104.0f, 52.0f);
  ImFont *font = ImGui::GetFont();

  drawList->AddRectFilled(panelMin, panelMax, IM_COL32(30, 36, 58, 255), 8.0f);
  drawList->AddRect(panelMin, panelMax, IM_COL32(82, 98, 145, 180), 8.0f, 0,
                    1.0f);
  drawList->AddText(font, 28.0f, ImVec2(panelMin.x + 16.0f, panelMin.y + 18.0f),
                    IM_COL32(245, 247, 255, 255), "TETRIS");
  drawList->AddRectFilled(ImVec2(panelMin.x + 18.0f, panelMin.y + 58.0f),
                          ImVec2(panelMin.x + 82.0f, panelMin.y + 62.0f),
                          IM_COL32(255, 88, 88, 255), 2.0f);
  drawList->AddText(ImVec2(panelMin.x + 18.0f, panelMin.y + 70.0f),
                    IM_COL32(184, 196, 230, 255), "SCORE");
  drawList->AddText(font, 22.0f, ImVec2(panelMin.x + 78.0f, panelMin.y + 66.0f),
                    IM_COL32(245, 247, 255, 255),
                    std::to_string(score).c_str());
  drawList->AddText(ImVec2(previewMin.x, panelMin.y + 16.0f),
                    IM_COL32(184, 196, 230, 255), "NEXT");

  drawList->AddRectFilled(
      previewMin,
      ImVec2(previewMin.x + previewSize.x, previewMin.y + previewSize.y),
      IM_COL32(14, 18, 31, 255), 6.0f);
  drawList->AddRect(
      previewMin,
      ImVec2(previewMin.x + previewSize.x, previewMin.y + previewSize.y),
      IM_COL32(95, 113, 166, 150), 6.0f, 0, 1.0f);
  DrawNextBlockPreview(drawList, nextBlock, previewMin, previewSize);

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);

  if (gameOver) {
    action = DrawGameOverOverlay(score);
  }

  rlImGuiEnd();

  return action;
}

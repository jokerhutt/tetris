#include "ui.h"

UI::UI(int height, int width) {
  this->height = height;
  this->width = width;
};

void UI::Draw(Block nextBlock) {
  rlImGuiBegin();

  ImGui::SetNextWindowPos(ImVec2(0, 0));

  ImGui::SetNextWindowSize(ImVec2(300, 50));

  ImGui::Begin(

      "UI",

      nullptr,

      ImGuiWindowFlags_NoTitleBar |

          ImGuiWindowFlags_NoResize |

          ImGuiWindowFlags_NoMove |

          ImGuiWindowFlags_NoCollapse

  );

  ImVec2 pos = ImGui::GetCursorScreenPos();

  float windowWidth = 300;

  float windowHeight = 120;

  nextBlock.Draw(

      pos.x + (windowWidth / 80),

      pos.y + (windowHeight / 2) - 15

  );

  ImGui::End();

  rlImGuiEnd();
}

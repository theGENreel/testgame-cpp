#include "overlays/InventoryOverlay.h"
#include <curses.h>
#include <string>

InventoryOverlay::InventoryOverlay(PlayerEntity* player) {
  this->player = player;
}

void InventoryOverlay::Draw() {
  box(this->GetWindow(), '|', '-');
  for (int i = 0; i < this->player->GetInventory()->GetSlots().size(); i++) {
    Slot* slot = this->player->GetInventory()->GetSlots()[i];
    std::string it = slot->GetName() + std::string(this->GetWindowWidth() - slot->GetName().length() - std::to_string(slot->GetCount()).length() - 4, ' ') + std::to_string(slot->GetCount()); 
    wmove(this->GetWindow(), i + 1, 2);
    if (i == this->selection)
      wattron(this->GetWindow(), A_REVERSE);
    waddstr(this->GetWindow(), it.c_str());
    if (i == this->selection)
      wattroff(this->GetWindow(), A_REVERSE);
  }
  wrefresh(this->GetWindow());
}

void InventoryOverlay::Input(int key) {
  if ((key == int('w') || key == KEY_UP) && this->selection > 0)
    this->selection -= 1;
  else if ((key == int('s') || key == KEY_DOWN) && this->selection < this->player->GetInventory()->GetSlots().size() - 1)
    this->selection += 1;
  else if (key == 27)
    this->exiting = true;
}

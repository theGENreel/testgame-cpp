#include "overlays/CraftingOverlay.h"
#include "Crafts.h"
#include <curses.h>
#include <string>

CraftingOverlay::CraftingOverlay(PlayerEntity* player) {
  this->player = player;
}

void CraftingOverlay::Draw() {
  wclear(this->GetWindow());
  box(this->GetWindow(), '|', '-');
  wmove(this->GetWindow(), 1, 1);
  waddstr(this->GetWindow(), "General");
  wmove(this->GetWindow(), 2, 1);
  waddstr(this->GetWindow(), std::string(this->GetWindowWidth() - 2, '-').c_str());
  int main_end = this->GetWindowWidth() * this->main_width;
  for(int i = 0; i < Crafts::GetCrafts().size(); i++) {
    wmove(this->GetWindow(), 3 + i, 1);
    std::string out_name = Crafts::GetCrafts()[i].out.GetName();
    std::string text = out_name + std::string(main_end - out_name.length(), ' ');
    if (i == this->craft_selection)
      wattron(this->GetWindow(), A_REVERSE);
    else if (this->player->GetInventory()->HasItem(*Crafts::GetCrafts()[i].in[0].GetItem(), Crafts::GetCrafts()[i].in[0].GetCount()))
      wattron(this->GetWindow(), A_NORMAL);
    else
      wattron(this->GetWindow(), A_DIM);
    waddstr(this->GetWindow(), text.c_str());
    if (i == this->craft_selection)
      wattroff(this->GetWindow(), A_REVERSE);
    else if (this->player->GetInventory()->HasItem(*Crafts::GetCrafts()[i].in[0].GetItem(), Crafts::GetCrafts()[i].in[0].GetCount()))
      wattroff(this->GetWindow(), A_NORMAL);
    else
      wattroff(this->GetWindow(), A_DIM);
  }
  wmove(this->GetWindow(), 2, main_end);
  waddwstr(this->GetWindow(), std::wstring(L"┬").c_str());
  for (int i = 3; i < this->GetWindowHeight() - 1; i++) {
    wmove(this->GetWindow(), i, main_end);
    waddch(this->GetWindow(), '|');
  }
  wmove(this->GetWindow(), this->GetWindowHeight() - 1, main_end);
  waddwstr(this->GetWindow(), std::wstring(L"┴").c_str());
  wmove(this->GetWindow(), 3, main_end + 1);
  waddstr(this->GetWindow(), "Needed:");
  int i;
  std::string count;
  for (i = 0; i < Crafts::GetCrafts()[this->craft_selection].in.size(); i++) {
    Slot in_slot = Crafts::GetCrafts()[this->craft_selection].in[i];
    wmove(this->GetWindow(), 4 + i, main_end + 1);
    count = std::string(this->GetWindowWidth() - main_end - in_slot.GetName().length() - 1 - std::to_string(in_slot.GetCount()).length() - 1, ' ') + std::to_string(in_slot.GetCount());
    waddstr(this->GetWindow(), (in_slot.GetName() + count).c_str());
  }
  wmove(this->GetWindow(), 4 + i + 2, main_end + 1);
  waddstr(this->GetWindow(), "Output:");
  wmove(this->GetWindow(), 4 + i + 3, main_end + 1);
  Slot out_slot = Crafts::GetCrafts()[this->craft_selection].out;
  count = std::string(this->GetWindowWidth() - main_end - out_slot.GetName().length() - 1 - std::to_string(out_slot.GetCount()).length() - 1, ' ') + std::to_string(out_slot.GetCount());
  waddstr(this->GetWindow(), (out_slot.GetName() + count).c_str());
  wrefresh(this->GetWindow());
}

void CraftingOverlay::Input(int key) {
  switch (key) {
    case int('a'): case KEY_LEFT:
      if (this->category_selection > 0)
        this->category_selection -= 1;
      break;
    case int('d'): case KEY_RIGHT:
      if (this->category_selection < 0) //TODO
        this->category_selection += 1;
      break;
    case int('w'): case KEY_UP:
      if (this->craft_selection > 0)
        this->craft_selection -= 1;
      break;
    case int('s'): case KEY_DOWN:
      if (this->craft_selection < Crafts::GetCrafts().size() - 1)
        this->craft_selection += 1;
      break;
    case 10: case KEY_ENTER: {
      for (Slot slot : Crafts::GetCrafts()[this->craft_selection].in)
        if (!this->player->GetInventory()->HasItem(*slot.GetItem(), slot.GetCount()))
          return;
      Slot out_slot = Crafts::GetCrafts()[this->craft_selection].out;
      for (Slot slot : Crafts::GetCrafts()[this->craft_selection].in)
        this->player->GetInventory()->RemoveItem(*slot.GetItem(), slot.GetCount());
      this->player->GetInventory()->AddItem(*out_slot.GetItem(), out_slot.GetCount());
      break;
    }
    case 27:
      this->exiting = true;
  }
}

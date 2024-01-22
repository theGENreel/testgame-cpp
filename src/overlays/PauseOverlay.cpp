#include "overlays/PauseOverlay.h"
#include <cstring>
#include <curses.h>
#include <string>

PauseOverlay::PauseOverlay(): BaseOverlay(0.3) {
}

bool PauseOverlay::IsGameShuttingDown() {
  return this->shutdown_game;
}

void PauseOverlay::Draw() {
  box(this->GetWindow(), '|', '-');

  wmove(this->GetWindow(), 1, 1);
  waddstr(this->GetWindow(), this->StringInMid("Pause").c_str());
  wmove(this->GetWindow(), 2, 1);
  for(int i=0; i<this->GetWindowWidth()-2; i++) {
    wprintw(this->GetWindow(), "-");
  }
  for (int i = 0; i < sizeof(this->buttons) / sizeof(std::string); i++) {
    wmove(this->GetWindow(), i+3, 1);
    if (i == this->selection)
      wattron(this->GetWindow(), A_REVERSE);
    waddstr(this->GetWindow(), this->StringInMid(this->buttons[i]).c_str());
    if (i == this->selection)
      wattroff(this->GetWindow(), A_REVERSE);
  }
  wrefresh(this->GetWindow());
}

void PauseOverlay::Input(int key) {
  switch (key) {
    case int('w'): case KEY_UP:
      if (this->selection > 0)
        this->selection -= 1;
      break;
    case int('s'): case KEY_DOWN:
      if (this->selection < (sizeof(this->buttons) / sizeof(std::string)) - 1)
        this->selection += 1;
      break;
    case 10: case KEY_ENTER:
      switch (this->selection) {
        case 0:
          this->exiting = true;
          break;
        case 1:
          this->shutdown_game = true;
          break;
      }
    case 27:
      this->exiting = true;
      break;
  }
}

#include "Camera.h"
#include "curses.h"
#include "GameMap.h"
#include "entities/PlayerEntity.h"
#include <chrono>
#include <clocale>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

void game(Camera* camera) {
  while (!camera->IsExiting()) {
    //auto timer = chrono::steady_clock::now() + chrono::milliseconds(50);
    camera->Tick();
    //this_thread::sleep_until(timer);
  }
}

void new_game() {
  int screen_w, screen_h;
  getmaxyx(stdscr, screen_h, screen_w);
  int window_separator = screen_w * 0.85;
  GameMap *game_map = new GameMap();
  WINDOW *game_window = newwin(screen_h, window_separator, 0, 0);
  WINDOW *info_window = newwin(screen_h, screen_w-window_separator, 0, window_separator+1);
  Camera *camera = new Camera(stdscr, game_map, screen_w - (screen_w - window_separator) - 1, screen_h - 1, game_window, info_window);
  PlayerEntity *player = new PlayerEntity(camera, 1, 1);
  game_map->body_layer[1][1] = player;
  camera->SetFollowing(player);
  game(camera);
}

void main_menu(WINDOW *window) {
  new_game();
  string buttons[2] = {"New Game", "Exit"};
  short int selection = 0;
  while (true) {
    for (short int idx=0; idx<sizeof(buttons)/sizeof(string); idx++) {
      if (idx == selection)
        attron(A_REVERSE);
      mvaddstr(1 + idx, 1, buttons[idx].c_str());
      if (idx == selection)
        attroff(A_REVERSE);
    }
    int key = getch();
    switch (key) {
      case int('w'): case KEY_UP:
        if (selection > 0)
          selection -= 1;
        break;
      case int('s'): case KEY_DOWN:
        if (selection < sizeof(buttons)/sizeof(string))
          selection += 1;
        break;
      case 10:
        switch (selection) {
          case 0:
            new_game();
            break;
          case 1:
            endwin();
            return;
            break;
        }
    }
    refresh();
  }
}

int main() {
  setlocale(LC_ALL, "en_US.UTF-8");
  set_escdelay(0);
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  main_menu(stdscr);
  return 0;
}

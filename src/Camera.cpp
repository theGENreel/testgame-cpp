#include "Camera.h"
#include "GameMap.h"
#include "entities/BaseEntity.h"
#include "entities/PlayerEntity.h"
#include <curses.h>
#include <string>
#include <thread>

Camera::Camera(WINDOW *window, GameMap *game_map, int width, int height, WINDOW *game_window, WINDOW *info_window) {
  this->window = window;
  this->game_map = game_map;
  this->width = width;
  this->height = height;
  this->game_window = game_window;
  this->info_window = info_window;
}

GameMap* Camera::GetMap() {
  return this->game_map;
}

bool Camera::IsExiting() {
  return this->exiting;
}

void Camera::SetExiting(bool exiting) {
  this->exiting = exiting;
}

BaseEntity* Camera::GetFollowing() {
  return this->following;
}

void Camera::SetFollowing(BaseEntity* following) {
  this->following = following;
}

BaseOverlay* Camera::GetOverlay() {
  return this->overlay;
}

void Camera::SetOverlay(BaseOverlay* overlay) {
  this->overlay = overlay;
}

void Camera::Tick() {
  int key = getch();
  wclear(this->game_window);
  wclear(this->info_window);
  if (this->overlay == nullptr) {
    this->Draw(this->game_window);
    this->DrawInfo(this->info_window);
    switch (key) {
      case int('w'): case int('s'): case int('a'): case int('d'): case int('1'): case int('2'): case int('3'): case int('4'): case int('5'): case int('6'): case int('7'): case int('8'): case int('9'): case int('0'): case int('i'): case int('c'):
        {
          PlayerEntity* player = dynamic_cast<PlayerEntity*>(this->following);
          if (player)
            player->Control(key);
          break;
        }
      case 27:
        this->SetOverlay(new PauseOverlay());
        break;
    }
  } else {
    if (this->overlay->IsExiting())
      this->overlay = nullptr;
    else {
      this->overlay->Draw();
      //this->DrawInfo(this->info_window);
      this->overlay->Input(key);
    }
  }
}

void Camera::Draw(WINDOW *window) {
  this->Update();
  for (int line = this->y; line < this->height+this->y; line++) {
    for (int cell = this->x; cell < this->width + this->x; cell++) {
      if (dynamic_cast<AirBlock*>(this->game_map->body_layer[line][cell]))
        waddch(window, this->game_map->floor_layer[line][cell]->GetSymbol());
      else
        waddch(window, this->game_map->body_layer[line][cell]->GetSymbol());
    } 
    waddstr(window, "\n");
  }
  wrefresh(window);
}

void Camera::DrawInfo(WINDOW *window) {
  wmove(window, 0, 0);
  waddstr(window, (std::to_string(this->following->GetY()) + ':' + std::to_string(this->following->GetX()) + '\n').c_str());
  PlayerEntity* player = dynamic_cast<PlayerEntity*>(this->following);
  if (player){
    waddstr(window, "Inventory:\n");
    for (int i = 0; i < player->GetInventory()->GetSlots().size(); i++) {
      Slot* slot = player->GetInventory()->GetSlots()[i];
      if (i == player->GetSelectedItemIndex())
        waddch(window, '*');
      waddstr(window, (slot->GetItem()->unique_name + ": " + std::to_string(slot->GetCount()) + '\n').c_str());
    }
  }
  wrefresh(window);
}

void Camera::Update() {
  if (this->following->GetX() - this->x < this->width * 0.2 && this->x > 0)
    this->x -= 1;
  if (this->following->GetX() - this->x > this->width * 0.8 && this->x + this->width < this->game_map->SIZE)
    this->x += 1;
  if (this->following->GetY() - this->y < this->height * 0.2 && this->y > 0)
    this->y -= 1;
  if (this->following->GetY() - this->y > this->height * 0.8 && this->y + this->height < this->game_map->SIZE)
    this->y += 1;
}

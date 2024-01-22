#include "entities/BaseEntity.h"
#include "GameMap.h"
#include "entities/PlayerEntity.h"
#include <iostream>

BaseEntity::BaseEntity(GameMap* game_map, char32_t symbol, int x, int y) {
  this->game_map = game_map;
  this->symbol = symbol;
  this->x = x;
  this->y = y;
}

char32_t BaseEntity::GetSymbol() {
  return this->symbol;
}

void BaseEntity::SetSymbol(char32_t symbol) {
  this->symbol = symbol;
}

int BaseEntity::GetX() {
  return this->x;
}

int BaseEntity::GetY() {
  return this->y;
}

void BaseEntity::MoveUp() {
  this->side = 'u';
  if (this->y > 0) {
    if (!this->game_map->body_layer[this->y - 1][this->x]->IsOpaque()) {
      this->game_map->body_layer[this->y][this->x] = this->inside_block;
      this->inside_block = dynamic_cast<BaseBlock*>(this->game_map->body_layer[this->y - 1][this->x]);
      this->game_map->body_layer[this->y - 1][this->x] = this;
      this->y -= 1;
    }
  }
}

void BaseEntity::MoveDown() {
  this->side = 'd';
  if (this->y < this->game_map->SIZE - 1) {
    if (!this->game_map->body_layer[this->y + 1][this->x]->IsOpaque()) {
      this->game_map->body_layer[this->y][this->x] = this->inside_block;
      this->inside_block = dynamic_cast<BaseBlock*>(this->game_map->body_layer[this->y + 1][this->x]);
      this->game_map->body_layer[this->y + 1][this->x] = this;
      this->y += 1;
    }
  }
}

void BaseEntity::MoveLeft() {
  this->side = 'l';
  if (this->x > 0) {
    if (!this->game_map->body_layer[this->y][this->x - 1]->IsOpaque()) {
      this->game_map->body_layer[this->y][this->x] = this->inside_block;
      this->inside_block = dynamic_cast<BaseBlock*>(this->game_map->body_layer[this->y][this->x - 1]);
      this->game_map->body_layer[this->y][this->x - 1] = this;
      this->x -= 1;
    }
  }
}

void BaseEntity::MoveRight() {
  this->side = 'r';
  if (this->x < this->game_map->SIZE - 1) {
    if (!this->game_map->body_layer[this->y][this->x + 1]->IsOpaque()) {
      this->game_map->body_layer[this->y][this->x] = this->inside_block;
      this->inside_block = dynamic_cast<BaseBlock*>(this->game_map->body_layer[this->y][this->x + 1]);
      this->game_map->body_layer[this->y][this->x + 1] = this;
      this->x += 1;
    }
  }
}

void BaseEntity::Tick() {

}

bool BaseEntity::IsOpaque() {
  return false;
}

void BaseEntity::Control(int key) {

}

#include "GameMap.h"

GameMap::GameMap() {
  for(int i=0; i<this->SIZE; i++) {
    std::fill_n(this->body_layer[i], this->SIZE, new AirBlock());
    std::fill_n(this->floor_layer[i], this->SIZE, new StoneFBlock());
  }
  this->body_layer[3][3] = new StoneBlock();
}

#ifndef _GAMEMAP_H_
#define _GAMEMAP_H_

#include "IPlaceable.h"
#include "algorithm"
#include "blocks/AirBlock.h"
#include "fblocks/BaseFBlock.h"
#include "fblocks/StoneFBlock.h"
#include "blocks/StoneBlock.h"

class GameMap {
public:
  GameMap();
  static const int SIZE = 250;
  IPlaceable *body_layer[SIZE][SIZE];
  BaseFBlock* floor_layer[SIZE][SIZE];

private:
};

#endif

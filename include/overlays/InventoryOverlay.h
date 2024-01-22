#pragma once
#include "BaseOverlay.h"
#include "entities/PlayerEntity.h"

class InventoryOverlay: public BaseOverlay {
  public:
    InventoryOverlay(PlayerEntity* player);
    void Draw();
    void Input(int key);

  private:
    PlayerEntity* player;
    unsigned short int selection = 0;
};

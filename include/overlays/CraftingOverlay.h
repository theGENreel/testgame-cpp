#pragma once
#include "BaseOverlay.h"
#include "entities/PlayerEntity.h"
#include "Crafts.h"

class CraftingOverlay: public BaseOverlay {
  public:
    CraftingOverlay(PlayerEntity* player);
    void Draw();
    void Input(int key);

  private:
    PlayerEntity* player;
    unsigned short int craft_selection = 0;
    unsigned short int category_selection = 0;
    constexpr static const float main_width = 0.7;
};

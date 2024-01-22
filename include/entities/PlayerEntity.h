#pragma once
#include "entities/BaseEntity.h"
#include "Camera.h"
#include "inventory/container.h"

class PlayerEntity: public BaseEntity {
  public:
    PlayerEntity(Camera* camera, int x, int y);
    void Control(int key);
    Container* GetInventory();
    unsigned short int GetSelectedItemIndex();

  private:
    Camera* camera;
    Container* inventory = new Container(10);
    unsigned short int selected_item = 0;
};

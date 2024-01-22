#include "entities/PlayerEntity.h"
#include "entities/BaseEntity.h"
#include "overlays/CraftingOverlay.h"
#include "overlays/InventoryOverlay.h"
#include "items/CopperOreItem.h"
#include "items/CoalItem.h"
#include <iostream>

PlayerEntity::PlayerEntity(Camera* camera, int x, int y) : BaseEntity(camera->GetMap(), '@', x, y) {
  this->camera = camera;
  //this->GetInventory()->GetSlots()[1]->AddItem(new CoalItem(), 5);
  this->GetInventory()->AddItem(CopperOreItem(), 64);
}

Container* PlayerEntity::GetInventory() {
  return this->inventory;
}

unsigned short int PlayerEntity::GetSelectedItemIndex() {
  return this->selected_item;
}

void PlayerEntity::Control(int key) {
  switch (key) {
    case int('w'):
      this->MoveUp();
      break;
    case int('s'):
      this->MoveDown();
      break;
    case int('a'):
      this->MoveLeft();
      break;
    case int('d'):
      this->MoveRight();
      break;
    case int('1'): case int('2'): case int('3'): case int('4'): case int('5'): case int('6'): case int('7'): case int('8'): case int('9'): case int('0'): {
      unsigned short int num = int(key - '0');
      this->selected_item = num != 0 ? num - 1 : 9;
      break;
    }
    case int('i'):
      this->camera->SetOverlay(new InventoryOverlay(this));
      break;
    case int('c'):
      this->camera->SetOverlay(new CraftingOverlay(this));
      break;
  }
}

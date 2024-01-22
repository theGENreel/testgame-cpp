#pragma once

#include "items/BaseItem.h"
#include <string>

class Slot {
  public:
    Slot(int max_size, BaseItem* item = nullptr, int count = 0);
    BaseItem* GetItem();
    void AddItem(BaseItem* item, int count);
    std::string GetName();
    int RemainCount();
    int GetCount();
    void SetCount(int count);
    int GetMaxSize();
    bool IsFilled();
    void MergeSlot(Slot* slot, int count = 0);

  private:
    BaseItem *item = nullptr;
    int max_size = 64;
    int count = 0;
};

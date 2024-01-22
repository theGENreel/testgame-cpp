#include <vector>
#include "inventory/slot.h"

class Container {
  public:
    Container(int slots_count, int slot_size = 64);
    std::vector<Slot*> GetSlots();
    std::vector<BaseItem> GetItems();
    Slot* GetEmptySlot();
    std::vector<Slot*> GetOccupiedSlots();
    Slot* GetSlotForItem(BaseItem item);
    void MergeSlot(Slot* slot, int count = 0);
    bool HasItem(BaseItem item, int count = 1);
    void RemoveItem(BaseItem item, int count = 1);
    void AddItem(BaseItem item, int count = 1);

  protected:
    std::vector<Slot*> slots;
  private:
};

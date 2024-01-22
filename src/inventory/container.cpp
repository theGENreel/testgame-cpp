#include "inventory/container.h"
#include <algorithm>

Container::Container(int slots_count, int slot_size) {
  for (int i = 0; i < slots_count; i++)
    this->slots.push_back(new Slot(slot_size)); 
}

std::vector<BaseItem> Container::GetItems() {
  std::vector<BaseItem> new_vector;
  for (Slot* slot : this->slots) {
    if (slot->GetItem() != nullptr && std::find(new_vector.begin(), new_vector.end(), *slot->GetItem()) == new_vector.end()) {
      new_vector.push_back(*slot->GetItem());
    }
  }
  return new_vector;
}

std::vector<Slot*> Container::GetSlots() {
  return this->slots;
}

Slot* Container::GetEmptySlot() {
  for (Slot* slot : this->slots)
    if (slot->GetItem() == nullptr)
      return slot;
  return nullptr;
}

std::vector<Slot*> Container::GetOccupiedSlots() {
  std::vector<Slot*> new_vector;
  for (Slot* slot : this->slots)
    if (slot->GetItem() != nullptr)
      new_vector.push_back(slot);
  return new_vector;
} 

Slot* Container::GetSlotForItem(BaseItem item) {
  for (Slot* slot : this->slots)
    if (slot->GetItem() != nullptr)
      if (*slot->GetItem() == item)
        if (slot->GetCount() < slot->GetMaxSize())
          return slot;
  return this->GetEmptySlot();
}

void Container::MergeSlot(Slot* ext_slot, int count) {
  if (count != 0 && ext_slot->GetCount() < count)
    count = ext_slot->GetCount();
  if (ext_slot->GetCount() > 0) {
    if (count == 0) {
      while (ext_slot->GetCount() > 0) {
        Slot* slot = this->GetSlotForItem(*ext_slot->GetItem());
        if (slot == nullptr)
          break;
        slot->MergeSlot(ext_slot, count);
      }
    } else {
      while (ext_slot->GetCount() > ext_slot->GetCount() - count) {
        Slot* slot = this->GetSlotForItem(*ext_slot->GetItem());
        if (slot == nullptr)
          break;
        slot->MergeSlot(ext_slot, count);
      }
    }
  }
}

bool Container::HasItem(BaseItem item, int count) {
  int found_count = 0;
  for (Slot* slot : this->slots)
    if (*slot->GetItem() == item)
      found_count += slot->GetCount();
  return found_count >= count ? true : false;
}

void Container::RemoveItem(BaseItem item, int count) {
  while (count > 0) {
    if (!this->HasItem(item, count))
      break;
    std::vector<BaseItem> items = this->GetItems();
    for (int i = 0; i<items.size(); i++) {
      if (items[i] == item) { 
        if (count >= this->slots[i]->GetCount()) {
          count -= this->slots[i]->GetCount();
          this->slots[i]->SetCount(0);
        } else {
          this->slots[i]->SetCount(this->slots[i]->GetCount() - count);
        }
      }
    }
  }
}

void Container::AddItem(BaseItem item, int count) {
  Slot* slot = new Slot(count, &item, count);
  this->MergeSlot(slot);
}

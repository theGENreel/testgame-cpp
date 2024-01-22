#include "inventory/slot.h"
#include <algorithm>

Slot::Slot(int max_size, BaseItem* item, int count) {
  this->max_size = max_size;
    if (item != nullptr && count > 0) {
      this->item = item;
      this->count = count;
    }
}

BaseItem* Slot::GetItem() {
  return this->item;
}

std::string Slot::GetName() {
  return this->item == nullptr ? "Empty" : this->item->GetName();
}

bool Slot::IsFilled() {
  return this->count < this->max_size ? false : true; 
}

int Slot::RemainCount() {
  return this->max_size - this->count;
}

int Slot::GetCount() {
  return this->count;
}

void Slot::SetCount(int count) {
  this->count = count;
  if (count == 0)
    this->item = nullptr;
}

int Slot::GetMaxSize() {
  return this->max_size;
}

void Slot::AddItem(BaseItem* item, int count) {
  if (this->item == nullptr)
    this->item = item;

  if (this->item->GetName() == item->GetName())
    if (this->count + count <= this->max_size)
      this->count += count;
}

/*void Slot::MergeSlot(Slot* slot, int count) {
  if (count == 0 && slot->GetCount() > 0) {
    if (this->item == nullptr)
      this->item = slot->item;
    if (this->item == slot->item) {
      if (this->count + slot->count <= this->max_size) {
        this->count += slot->count;
        slot->count -= count;
        if (slot->count == 0)
          slot->item = nullptr;
      } else {
        slot->count -= this->max_size - this->count;
        this->count = this->max_size;
      }
    } 
  }
}*/

void Slot::MergeSlot(Slot* ext_slot, int count) {
  if (count == 0 && ext_slot->count > 0) {
    if (this->item == nullptr)
      this->item = ext_slot->item;
    if (this->item == ext_slot->item) {
      if (this->count + ext_slot->count <= this->max_size) {
        this->count += ext_slot->count;
        ext_slot->count = 0;
        ext_slot->item = nullptr;
      } else {
        ext_slot->count -= this->max_size - this->count;
        this->count = this->max_size;
      }
    }
  } else if (count != 0 && ext_slot->count > 0) {
    if (this->item == nullptr)
      this->item = ext_slot->item;
    if (this->item == ext_slot->item) {
      if (this->count + count <= this->max_size) {
        this->count += count;
        ext_slot->count -= count;
        if (ext_slot->count == 0)
          ext_slot->item = nullptr;
      } else {
        ext_slot->count -= this->max_size - this->count;
        this->count = this->max_size;
      }
    }
  }
}

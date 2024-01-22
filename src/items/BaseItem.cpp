#include "items/BaseItem.h"

BaseItem::BaseItem(std::string unique_name) {
  this->unique_name = unique_name;
}

std::string BaseItem::GetName() {
  return this->name;
}

void BaseItem::SetName(std::string name) {
  this->name = name;
}

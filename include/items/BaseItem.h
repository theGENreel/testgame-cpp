#pragma once

#include <string>
class BaseItem {
  public:
    BaseItem(std::string unique_name);
    std::string GetName();
    std::string unique_name = "base_item";
    void SetName(std::string name);
    bool operator==(const BaseItem& item) const {
      return this->unique_name == item.unique_name;
    }

  private:
    bool interactable = false;
    std::string name = "Item";
    //std::string unique_name = "base_item";
};

#pragma once

#include <vector>
#include "inventory/slot.h"
class Crafts {
  public:
    struct Craft {
      std::vector<Slot> in;
      Slot out;
    };
    static std::vector<Craft> GetCrafts();

  private:
    static const std::vector<Craft> crafts;
};

#include "Crafts.h"
#include "items/CopperOreItem.h"
#include "items/CoalItem.h"
#include <vector>

const std::vector<Crafts::Craft> Crafts::crafts = {
  {{Slot(2, new CopperOreItem(), 2)}, Slot(1, new CoalItem(), 1)}
};

std::vector<Crafts::Craft> Crafts::GetCrafts() {
  return Crafts::crafts;
}

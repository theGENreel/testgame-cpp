#include "fblocks/BaseFBlock.h"

BaseFBlock::BaseFBlock() {

}

char32_t BaseFBlock::GetSymbol() {
  return this->symbol;
}

void BaseFBlock::SetSymbol(char32_t symbol) {
  this->symbol = symbol;
}

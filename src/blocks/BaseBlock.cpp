#include "blocks/BaseBlock.h"

BaseBlock::BaseBlock() {

}

char32_t BaseBlock::GetSymbol() {
  return this->symbol;
}

void BaseBlock::SetSymbol(char32_t symbol) {
  this->symbol = symbol;
}

bool BaseBlock::IsOpaque() {
  return this->opaque;
}

void BaseBlock::SetOpaque(bool opaque) {
  this->opaque = opaque;
}

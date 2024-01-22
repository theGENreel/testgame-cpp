#ifndef _BASEBLOCK_H_
#define _BASEBLOCK_H_

#include "IPlaceable.h"
class BaseBlock: public IPlaceable {
  public:
    BaseBlock();
    virtual ~BaseBlock() = default;
    char32_t GetSymbol();
    void SetSymbol(char32_t symbol);
    bool IsOpaque();
    void SetOpaque(bool opaque);

  private:
    char32_t symbol = ' ';
    bool opaque = false;
};
#endif

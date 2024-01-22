#pragma once

class IPlaceable {
  public:
    virtual char32_t GetSymbol() = 0; 
    virtual bool IsOpaque() = 0;
};

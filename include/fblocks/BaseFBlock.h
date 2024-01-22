#ifndef _BASEFBLOCK_H_
#define _BASEFBLOCK_H_

class BaseFBlock {
  public:
    BaseFBlock();
    char32_t GetSymbol();
    void SetSymbol(char32_t symbol);

  private:
    char32_t symbol = U'.';
};
#endif // !_BASEFBLOCK_H_

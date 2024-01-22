#pragma once
#include "IPlaceable.h"
#include "blocks/AirBlock.h"
#include "GameMap.h"

class BaseEntity: public IPlaceable {
  public:
    BaseEntity(GameMap* game_map, char32_t symbol , int x, int y);
    char32_t GetSymbol();
    void SetSymbol(char32_t symbol);
    int GetX();
    int GetY();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Tick();
    bool IsOpaque();
    void Control(int key);

  private:
    GameMap* game_map;
    char32_t symbol;
    int x = 0;
    int y = 0;
    char side = 'r';
    BaseBlock* inside_block = new AirBlock();
};

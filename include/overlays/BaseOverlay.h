#pragma once

#include <curses.h>
#include <string>
class BaseOverlay {
  public:
    BaseOverlay(float size_multiplier = 0.8);
    virtual ~BaseOverlay() = default;
    bool IsPausing();
    void SetPausing(bool pausing);
    float GetSizeMutliplier();
    void SetSizeMultiplier(float multiplier);
    virtual void Input(int key);
    virtual void Draw();
    WINDOW* GetWindow();
    int GetScreenWidth();
    int GetScreenHeight();
    int GetWindowWidth();
    int GetWindowHeight();
    bool IsExiting();

  private:
    WINDOW *window;
    bool pausing = false;
    int screen_width;
    int screen_height;
  float size_multiplier = 0.8;
  protected:
    std::string StringInMid(std::string); 
    bool exiting = false;
};

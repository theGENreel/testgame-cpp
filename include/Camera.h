#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <curses.h>
#include "GameMap.h"
#include "entities/BaseEntity.h"
#include "overlays/PauseOverlay.h"

class Camera {
  public:
    Camera(WINDOW *window, GameMap *game_map, int width, int height, WINDOW *game_window, WINDOW *info_window);
    void Tick();
    GameMap* GetMap();
    BaseEntity* GetFollowing();
    void SetFollowing(BaseEntity* following);
    bool IsExiting();
    void SetExiting(bool exiting);
    BaseOverlay* GetOverlay();
    void SetOverlay(BaseOverlay* overlay);

  private:
    void Draw(WINDOW *window);
    void DrawInfo(WINDOW *window);
    void Update();
    WINDOW *window;
    int width;
    int height;
    GameMap *game_map;
    WINDOW *game_window;
    WINDOW *info_window;
    int x = 0;
    int y = 0;
    bool exiting = false;
    BaseEntity* following = nullptr;
    BaseOverlay* overlay = nullptr;
};
#endif

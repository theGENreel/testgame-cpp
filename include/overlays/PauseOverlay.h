#include "BaseOverlay.h"

class PauseOverlay: public BaseOverlay {
  public:
    PauseOverlay();
    void Draw();
    void Input(int key);
    bool IsGameShuttingDown();

  private:
    unsigned short int selection = 0;
    bool shutdown_game = false;
    std::string buttons[2] = {"Continue", "Exit"};
};

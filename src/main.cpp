
#include <iostream>
#include "Game.h"
int main() {
  Game* game = new Game{};

  eng::Engine& engine = eng::Engine::getInstance();
  engine.SetApplication(game);
  if (!engine.Init(1200, 700)) {
    std::cout << "3. Engine Failed" << std::endl;
    return -1;
  }
  std::cout << "4.Engine running" << std::endl;
  engine.Run();
  engine.Destroy();

  return 0;
}

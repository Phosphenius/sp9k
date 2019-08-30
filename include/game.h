#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <SFML/Graphics.hpp>

namespace sp9k {
class Game {
  sf::RenderWindow window;
  sf::Clock clock;
  Player player;
  void update();
  void draw();

public:
  Game(std::string title);
  void run();
};
} // namespace sp9k
#endif

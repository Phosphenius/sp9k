#ifndef GAME_H
#define GAME_H

#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "renderer.h"

namespace sp9k {
class Game {
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;

public:
  Player player;

  Game();
  void update(float dt);
  void render(Renderer &renderer);
  void createBullets(sf::Vector2f position);
  void createEnemy(sf::Vector2f position, sf::Vector2f velocity);
};
} // namespace sp9k
#endif

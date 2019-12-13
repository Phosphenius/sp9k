#ifndef GAME_H
#define GAME_H

#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include <random>

namespace sp9k {
class Game {
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;
  float elapsed_t = .0f;
  float spawn_t = .0f;
  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist_x{40, 920};

  float spawnFreqFunc(float elapsed_t);

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

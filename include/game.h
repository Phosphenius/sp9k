#ifndef GAME_H
#define GAME_H

#include "bullet.h"
#include "enemy.h"
#include "animation.h"
#include "player.h"
#include "renderer.h"
#include "stats.h"
#include <random>

namespace sp9k {
class Game {
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;
  std::vector<Animation> explosions;
  float elapsed_t = .0f;
  float spawn_t = .0f;
  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist_x{40, 920};
  std::uniform_int_distribution<int> dist_velo{50, 63};
  GameStats stats;

  float spawnFreqFunc(float elapsed_t);

public:
  Player player;

  Game();
  GameStats getStats();
  void update(float dt);
  void render(Renderer &renderer);
  void createBullets(sf::Vector2f position);
  void createEnemy(sf::Vector2f position, sf::Vector2f velocity);
  void createExplosion(sf::Vector2f position);
};
} // namespace sp9k
#endif

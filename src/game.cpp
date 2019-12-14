#include "game.h"

namespace sp9k {
Game::Game() : player(sf::Vector2f(480, 360)) {}

float Game::spawnFreqFunc(float elapsed_t) {
  return 1 / (0.008 * elapsed_t + 0.3f);
}

void Game::update(float dt) {
  elapsed_t += dt;
  spawn_t += dt;

  if (spawn_t >= spawnFreqFunc(elapsed_t)) {
    spawn_t = .0f;

    sf::Vector2f pos(dist_x(generator), -20);
    createEnemy(pos, sf::Vector2f(0, 50));
  }

  // FIXME: Find better y value after which bullets should be removed
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](Bullet const &bullet) {
                                 return bullet.position.y <= -200 ||
                                        !bullet.getIsAlive();
                               }),
                bullets.end());

  enemies.erase(
      std::remove_if(enemies.begin(), enemies.end(),
                     [](Enemy const &enemy) { return !enemy.getIsAlive(); }),
      enemies.end());

  for (auto &bullet : bullets) {
    bullet.update(dt);
  }

  for (auto &enemy : enemies) {
    enemy.update(dt);

    if (enemy.position.y >= 750) {
        player.takeDamage(30);
        enemy.takeDamage(9999);
    }
  }

  player.update(dt);

  for (size_t i = 0; i < enemies.size(); ++i) {

    auto &enemy = enemies[i];

    for (size_t j = 0; j < bullets.size(); ++j) {
      auto &bullet = bullets[j];

      if (!enemy.collidesWith(bullet) || !enemy.getIsAlive() ||
          !bullet.getIsAlive()) {
        continue;
      }

      enemy.takeDamage(4);
      bullet.takeDamage(1);
    }

    if (!player.collidesWith(enemy)) {
      continue;
    }

    player.takeDamage(50);
    enemy.takeDamage(50);
  }
}

void Game::render(Renderer &renderer) {
  renderer.render(player);
  renderer.render(bullets);
  renderer.render(enemies);
}

void Game::createBullets(sf::Vector2f position) {
  sf::Vector2f offset1(-12, -50);
  sf::Vector2f offset2(12, -50);

  bullets.emplace_back(position + offset1, sf::Vector2f(0, -600));
  bullets.emplace_back(position + offset2, sf::Vector2f(0, -600));
}

void Game::createEnemy(sf::Vector2f position, sf::Vector2f velocity) {
  enemies.emplace_back(position, velocity);
}

} // namespace sp9k

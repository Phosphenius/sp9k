#include "game.h"

namespace sp9k {
Game::Game() : player(sf::Vector2f(480, 360)) {}

float Game::spawnFreqFunc(float elapsed_t) {
  return 1 / (0.008 * elapsed_t + 0.3f);
}

GameStats Game::getStats() {
    return stats;
}

void Game::update(float dt) {
  stats.time += dt;
  elapsed_t += dt;
  spawn_t += dt;

  if (spawn_t >= spawnFreqFunc(elapsed_t)) {
    spawn_t = .0f;

    sf::Vector2f pos(dist_x(generator), -20);
    sf::Vector2f velo(0, dist_velo(generator));
    createEnemy(pos, velo);
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
        stats.enemiesEscaped++;
    }
  }

  player.update(dt);

  for (auto &explosion: explosions) {
    explosion.update(dt);
  }

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
      stats.bulletsHit++;

      if (!enemy.getIsAlive()) {
        stats.enemiesKilled++;
        createExplosion(enemy.position);
      }
    }

    if (!player.collidesWith(enemy)) {
      continue;
    }

    player.takeDamage(50);
    enemy.takeDamage(50);

    if (!enemy.getIsAlive()) {
      createExplosion(enemy.position);
      stats.enemiesKilled++;
    }
  }
}

void Game::render(Renderer &renderer) {
  renderer.renderTexture(
      sf::Vector2f(820, 700), "health_bar",
      sf::IntRect(0, 0, player.getHealthPercentage() * 256, 16));
  renderer.render(player);
  renderer.render(bullets);
  renderer.render(enemies);
  renderer.render(explosions);
}

void Game::createBullets(sf::Vector2f position) {
  int numAddEmitterPairs = 0; // number of additional bullets fired
  int drift = 100;            // horizontal speed of additional bullets

  sf::Vector2f offset1(-12, -50);
  sf::Vector2f offset2(12, -50);

  for (int i = 0; i < numAddEmitterPairs + 1; ++i) {
    bullets.emplace_back(position + offset1, sf::Vector2f(i * drift, -600));
    bullets.emplace_back(position + offset2, sf::Vector2f(i * -drift, -600));
    stats.bulletsFired += 2;
  }
}

void Game::createEnemy(sf::Vector2f position, sf::Vector2f velocity) {
  enemies.emplace_back(position, velocity);
}

void Game::createExplosion(sf::Vector2f position) {
  explosions.emplace_back(position, 15);
}

} // namespace sp9k

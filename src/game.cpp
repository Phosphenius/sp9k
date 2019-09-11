#include "game.h"

namespace sp9k {
Game::Game() : player(sf::Vector2f(480, 360)) {}

void Game::update(float dt) {

  for (size_t i = 0; i < bullets.size(); ++i) {
    if (bullets[i].position.y <= -200) {
      bullets.erase(bullets.begin() + i);
    }
  }

  for (auto &bullet : bullets) {
    bullet.update(dt);
  }

  for (auto &enemy : enemies) {
    enemy.update(dt);
  }
  player.update(dt);

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

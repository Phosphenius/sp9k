#include "renderer.h"

namespace sp9k {
void Renderer::renderSprite(sf::Vector2f pos, std::string texName) {
  sf::Sprite sprite;

  auto &tex = textureCache.getTexture(texName);
  sprite.setTexture(tex);
  sprite.setPosition(pos);
  sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);

  window.draw(sprite);
}

void Renderer::renderCircle(sf::Vector2f pos, float radius) {
  sf::CircleShape circle(radius);
  circle.setPosition(pos);
  circle.setOrigin(sf::Vector2f(radius, radius));
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineThickness(1);

  window.draw(circle);
}

void Renderer::render(Player &player) {
  renderSprite(player.position, "ship1");
  if (renderBounds) {
    renderCircle(player.position, player.radius);
  }
}

void Renderer::render(std::vector<Bullet> &bullets) {
  for (auto &bullet : bullets) {
    renderSprite(bullet.position, "shot1");

    if (!renderBounds) {
      continue;
    }

    renderCircle(bullet.position, bullet.radius);
  }
}

void Renderer::render(std::vector<Enemy> &enemies) {
  for (auto &enemy : enemies) {

    sf::Sprite sprite;

    auto &tex = textureCache.getTexture("ship2");
    sprite.setTexture(tex);
    sprite.setPosition(enemy.position);
    sprite.setRotation(180);
    sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);

    window.draw(sprite);
    if (!renderBounds) {
      continue;
    }

    renderCircle(enemy.position, enemy.radius);
  }
}

} // namespace sp9k

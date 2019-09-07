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
  renderSprite(player.pos, "ship1");
  if (renderBounds) {
    renderCircle(player.pos, player.radius);
  }
}

void Renderer::render(std::vector<std::unique_ptr<Bullet>> &bullets) {
  for (auto &bullet : bullets) {
    renderSprite(bullet->pos, "shot1");

    if (!renderBounds) {
      continue;
    }

    renderCircle(bullet->pos, bullet->radius);
  }
}

} // namespace sp9k

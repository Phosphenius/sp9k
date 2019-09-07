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

void Renderer::render(Player &player) {
    renderSprite(player.pos, "ship1");
}

void Renderer::render(std::vector<std::unique_ptr<Bullet>> &bullets) {
  for (auto &bullet : bullets) {
    renderSprite(bullet->pos, "shot1");
  }
}

} // namespace sp9k

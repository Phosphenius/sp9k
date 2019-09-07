#ifndef RENDERER_H
#define RENDERER_H

#include "texture_cache.h"
#include "bullet.h"
#include "player.h"

namespace sp9k {
class Renderer {
  sf::RenderWindow &window;
  TextureCache &textureCache;
  void renderSprite(sf::Vector2f pos, std::string texName);
  void renderCircle(sf::Vector2f pos, float radius);

public:
  bool renderBounds;
  Renderer(sf::RenderWindow &window, TextureCache &textureCache)
      : window(window), textureCache(textureCache), renderBounds(false) {};
  void render(Player &player);
  void render(std::vector<std::unique_ptr<Bullet>> &bullets);
};

} // namespace sp9k
#endif

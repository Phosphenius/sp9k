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

public:
  Renderer(sf::RenderWindow &window, TextureCache &textureCache)
      : window(window), textureCache(textureCache){};
  void render(Player &player);
  void render(std::vector<std::unique_ptr<Bullet>> &bullets);
};

} // namespace sp9k
#endif

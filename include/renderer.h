#ifndef RENDERER_H
#define RENDERER_H

#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "texture_cache.h"

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
  void render(std::vector<Bullet> &bullets);
  void render(std::vector<Enemy> &enemies);
};

} // namespace sp9k
#endif

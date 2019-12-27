#ifndef RENDERER_H
#define RENDERER_H

#include "asset_cache.h"
#include "bullet.h"
#include "enemy.h"
#include "nc_texture.h"
#include "player.h"

namespace sp9k {
class Renderer {
  sf::RenderWindow &window;
  AssetCache<NCTexture> &textureCache;
  void renderSprite(sf::Vector2f pos, std::string texName);
  void renderCircle(sf::Vector2f pos, float radius);

public:
  bool renderBounds;
  Renderer(sf::RenderWindow &window, AssetCache<NCTexture> &textureCache)
      : window(window), textureCache(textureCache), renderBounds(false){};
  void render(Player &player);
  void render(std::vector<Bullet> &bullets);
  void render(std::vector<Enemy> &enemies);
};

} // namespace sp9k
#endif

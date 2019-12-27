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
  AssetCache<sf::Font> &fontCache;
  void renderSprite(sf::Vector2f pos, std::string texName);
  void renderCircle(sf::Vector2f pos, float radius);

public:
  bool renderBounds;
  Renderer(sf::RenderWindow &window, AssetCache<NCTexture> &textureCache,
           AssetCache<sf::Font> &fontCache)
      : window(window), textureCache(textureCache), fontCache(fontCache),
        renderBounds(false){};
  void render(Player &player);
  void render(std::vector<Bullet> &bullets);
  void render(std::vector<Enemy> &enemies);
  void renderText(std::string textStr, sf::Vector2f position, size_t size = 12) const;
  // TODO: Add renderTextColored()
};

} // namespace sp9k
#endif

#pragma once

#include "animation.h"
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
  void renderCircle(sf::Vector2f pos, float radius);

public:
  bool renderBounds;
  Renderer(sf::RenderWindow &window, AssetCache<NCTexture> &textureCache,
           AssetCache<sf::Font> &fontCache);
  void render(Player &player);
  void render(std::vector<Bullet> &bullets);
  void render(std::vector<Enemy> &enemies);
  void render(std::vector<Animation> &animations);
  void renderText(std::string textStr, sf::Vector2f position,
                  size_t size = 12) const;
  void renderTexture(sf::Vector2f pos, std::string texName);
  void renderTexture(sf::Vector2f pos, std::string texName, sf::IntRect rect);
  // TODO: Add renderTextColored()
};

} // namespace sp9k

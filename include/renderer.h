#ifndef RENDERER_H
#define RENDERER_H

#include "texture_cache.h"

namespace sp9k {
class Renderer {
  sf::RenderWindow &window;
  TextureCache &textureCache;

public:
  Renderer(sf::RenderWindow &window, TextureCache &textureCache)
      : window(window), textureCache(textureCache){};
  void renderTexture(std::string texName, sf::Vector2f pos);
  void renderTextureCentered(std::string texName, sf::Vector2f pos);
};

} // namespace sp9k
#endif

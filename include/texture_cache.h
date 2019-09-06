#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "nc_texture.h"

namespace sp9k {
class TextureCache {
  std::unordered_map<std::string, std::unique_ptr<NCTexture>> textures;

public:
  TextureCache();
  const NCTexture &getTexture(std::string name);
};
} // namespace sp9k
#endif

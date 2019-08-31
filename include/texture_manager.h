#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

namespace sp9k {
class TextureManager {
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;

public:
  TextureManager();
  const sf::Texture &getTexture(std::string name);
};
} // namespace sp9k
#endif

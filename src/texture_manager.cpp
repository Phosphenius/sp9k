#include "texture_manager.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace fs = std::filesystem;

namespace sp9k {
TextureManager::TextureManager() {
  for (auto &entry : fs::directory_iterator("gfx")) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    texture->loadFromFile(entry.path());

    std::string filename = entry.path().filename();
    filename = filename.substr(0, filename.find("."));
    textures.insert({filename, std::move(texture)});
  }
}

const sf::Texture &TextureManager::getTexture(std::string name) {
  return *textures.at(name);
}
} // namespace sp9k

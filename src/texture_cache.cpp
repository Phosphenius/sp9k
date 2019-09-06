// Loads textures from disk and holds them in memory

#include "texture_cache.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace fs = std::filesystem;

namespace sp9k {
TextureCache::TextureCache() {
  for (auto &entry : fs::directory_iterator("gfx")) {
    std::unique_ptr<NCTexture> texture = std::make_unique<NCTexture>();
    texture->loadFromFile(entry.path());

    std::string filename = entry.path().filename();
    filename = filename.substr(0, filename.find("."));
    textures.insert({filename, std::move(texture)});
  }
}

const NCTexture &TextureCache::getTexture(std::string name) {
  return *textures.at(name);
}
} // namespace sp9k

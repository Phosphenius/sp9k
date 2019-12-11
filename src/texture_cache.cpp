// Loads textures from disk and holds them in memory

#include "config.h"
#include "texture_cache.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace fs = std::filesystem;

namespace sp9k {
TextureCache::TextureCache() {
  fs::path asset_root_path(SP9k_ASSET_ROOT_PATH);
  fs::path gfx_path("gfx");
  for (auto &entry : fs::directory_iterator(asset_root_path / gfx_path)) {
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

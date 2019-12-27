// Loads assets from disk and holds them in memory

#include "asset_cache.h"
#include "config.h"
#include "nc_texture.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace sp9k {
template <typename T> AssetCache<T>::AssetCache(std::string path) {
  // FIXME: Class should not depend on a constant stored in "config.h"
  fs::path asset_root_path(SP9k_ASSET_ROOT_PATH);
  fs::path gfx_path(path);
  for (auto &entry : fs::directory_iterator(asset_root_path / gfx_path)) {
    std::unique_ptr<T> asset = std::make_unique<T>();
    asset->loadFromFile(entry.path());

    std::string filename = entry.path().filename();
    filename = filename.substr(0, filename.find("."));
    assets.insert({filename, std::move(asset)});
  }
}

template <typename T> const T &AssetCache<T>::getAsset(std::string name) const {
  return *assets.at(name);
}

// We only need those types
template class AssetCache<NCTexture>;
template class AssetCache<sf::Font>;
} // namespace sp9k

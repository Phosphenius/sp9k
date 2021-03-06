// Loads assets from disk and holds them in memory

#include "asset_cache.h"
#include "nc_texture.h"
#include <filesystem>

#ifndef ASSETDIR
#define ASSETDIR "./"
#endif

namespace fs = std::filesystem;

namespace sp9k {
template <typename T>
AssetCache<T>::AssetCache(std::string path,
                          std::vector<std::string> exludeFiles) {
  fs::path asset_root_path(ASSETDIR);
  fs::path gfx_path(path);

  for (auto &entry : fs::directory_iterator(asset_root_path / gfx_path)) {
    std::string filename = entry.path().filename();

    if (std::find(exludeFiles.begin(), exludeFiles.end(), filename) !=
        exludeFiles.end()) {
      continue;
    }

    std::unique_ptr<T> asset = std::make_unique<T>();
    asset->loadFromFile(entry.path());

    filename = filename.substr(0, filename.find("."));

    assets.insert({filename, std::move(asset)});
  }
}

template <typename T>
const T &AssetCache<T>::getAsset(const std::string &name) const {
  return *assets.at(name);
}

// We only need those types
template class AssetCache<NCTexture>;
template class AssetCache<sf::Font>;
} // namespace sp9k

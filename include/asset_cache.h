#pragma once

#include <algorithm>
#include <memory>
#include <unordered_map>

namespace sp9k {
template <typename T> class AssetCache {
  std::unordered_map<std::string, std::unique_ptr<T>> assets;

public:
  AssetCache(std::string path, std::vector<std::string> exludeFiles = {});
  const T &getAsset(const std::string &name) const;
};
} // namespace sp9k

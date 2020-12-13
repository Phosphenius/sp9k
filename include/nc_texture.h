#pragma once

// Non-copyable texture to make sure we really don't copy any textures by
// accident

#include <SFML/Graphics.hpp>

namespace sp9k {
class NCTexture : public sf::Texture, private sf::NonCopyable {};
} // namespace sp9k

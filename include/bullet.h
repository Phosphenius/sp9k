#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>

namespace sp9k {
class Bullet : public Entity {

public:
  Bullet(sf::Vector2f position, sf::Vector2f velocity);
  void update(float dt);
};
} // namespace sp9k

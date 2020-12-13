#pragma once

#include "entity.h"

namespace sp9k {
class Enemy : public Entity {
public:
  Enemy(sf::Vector2f position, sf::Vector2f velocity);
  void update(float dt);
};
} // namespace sp9k

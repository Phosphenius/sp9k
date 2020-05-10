#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <SFML/Graphics.hpp>

namespace sp9k {
class Player : public Entity{
  static constexpr float maxVelocity = 450.0f;

public:
  sf::Vector2f accel{0, 0};

  Player(sf::Vector2f position);
  void update(float dt);
  float getHealthPercentage();
};
} // namespace sp9k
#endif

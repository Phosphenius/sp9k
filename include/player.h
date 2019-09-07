#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

namespace sp9k {
class Player {
  const float maxVelocity = 450.0f;

public:
  sf::Vector2f accel;
  sf::Vector2f pos;
  sf::Vector2f velocity;
  float radius;

  Player(sf::Vector2f pos);
  void update(float dt);
};
} // namespace sp9k
#endif

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

namespace sp9k {
class Player {
  sf::Vector2f pos;
  sf::Vector2f accel;
  sf::Vector2f velocity;
  const float maxVelocity = 500.0f;
  const float maxAccel = 40.0f;

public:
  Player(sf::Vector2f pos);
  sf::Vector2f getPos();
  void update(float dt);
  void setAccel(sf::Vector2f accel);
};
} // namespace sp9k
#endif

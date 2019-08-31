#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

namespace sp9k {
class Player {
  sf::Sprite sprite;
  sf::Vector2f accel;
  sf::Vector2f velocity;
  float maxVelocity = 500.0f;
  float maxAccel = 40.0f;
  float accelGain = 550.0f;

public:
  Player(const sf::Texture &texture);
  void update(float dt);
  void draw(sf::RenderWindow &window);
};
} // namespace sp9k
#endif

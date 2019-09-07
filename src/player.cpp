#include "player.h"

namespace sp9k {

Player::Player(sf::Vector2f pos)
    : accel(sf::Vector2f(0, 0)), pos(pos), velocity(sf::Vector2f(0, 0)) {}

void Player::update(float dt) {
  velocity += accel * dt;
  velocity *= 0.965f; // "friction"

  velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
  velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);

  pos += velocity * dt;

  if (pos.x <= 0) {
    pos.x = 0;
    velocity.x = 0;
  } else if (pos.x >= 960) {
    pos.x = 960;
    velocity.x = 0;
  }

  if (pos.y <= 0) {
    pos.y = 0;
    velocity.y = 0;
  } else if (pos.y >= 720) {
    pos.y = 720;
    velocity.y = 0;
  }
}

} // namespace sp9k

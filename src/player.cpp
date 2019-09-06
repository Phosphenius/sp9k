#include "player.h"

namespace sp9k {

Player::Player(sf::Vector2f pos)
    : pos(pos), accel(sf::Vector2f(0, 0)), velocity(sf::Vector2f(0, 0)) {}

sf::Vector2f Player::getPos() {
    return pos;
}

void Player::update(float dt) {
  velocity += accel;
  velocity *= 0.965f; // "friction"

  velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
  velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);

  pos += velocity * dt;

  if (pos.x <= 0) {
    pos.x = 0;
  } else if (pos.x >= 960) {
    pos.x = 960;
  }

  if (pos.y <= 0) {
    pos.y = 0;
  } else if (pos.y >= 720) {
    pos.y = 720;
  }
}

void Player::setAccel(sf::Vector2f accel) {
  this->accel.x = std::clamp(accel.x, -maxAccel, maxAccel);
  this->accel.y = std::clamp(accel.y, -maxAccel, maxAccel);
}

} // namespace sp9k

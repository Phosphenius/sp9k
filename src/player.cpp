#include "player.h"
#include <cmath>

namespace sp9k {

Player::Player(sf::Vector2f position)
    : Entity(250, 40, position, sf::Vector2f(0, 0)) {}

const float Player::maxVelocity;

void Player::update(float dt) {
  velocity += accel * dt;

  sf::Vector2f friction = -velocity;

  if (std::fpclassify(friction.x) != FP_ZERO ||
      std::fpclassify(friction.y) != FP_ZERO) {
    auto frictionLen = std::hypot(friction.x, friction.y);
    friction = sf::Vector2f(friction.x / frictionLen, friction.y / frictionLen);

    velocity += friction * 300.0f * dt;
  }

  velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
  velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);

  position += velocity * dt;

  if (position.x <= 0) {
    position.x = 0;
    velocity.x = 0;
  } else if (position.x >= 960) {
    position.x = 960;
    velocity.x = 0;
  }

  if (position.y <= 0) {
    position.y = 0;
    velocity.y = 0;
  } else if (position.y >= 720) {
    position.y = 720;
    velocity.y = 0;
  }
}

float Player::getHealthPercentage() {
  float percent_health = getHitPoints() / 250.f;

  if (percent_health < 0) {
    percent_health = 0;
  }

  return percent_health;
}

} // namespace sp9k

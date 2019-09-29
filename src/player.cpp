#include "player.h"

namespace sp9k {

Player::Player(sf::Vector2f position) : Entity(250, 40, position, sf::Vector2f(0, 0)) {}

void Player::update(float dt) {
  velocity += accel * dt;
  // FIXME probably not frame rate independent
  velocity *= (0.965f + dt); // "friction"

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

} // namespace sp9k

#include "player.h"

namespace sp9k {

Player::Player() {
  texture.loadFromFile("gfx/ship1.png");
  sprite.setTexture(texture);
  sprite.setOrigin(
      sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
  sprite.setPosition(480, 360);
}
void Player::update(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && accel.x > -maxAccel) {
    accel.x -= accelGain * dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
             accel.x < maxAccel) {
    accel.x += accelGain * dt;
  } else {
    accel.x = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && accel.y > -maxAccel) {
    accel.y -= accelGain * dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
             accel.y < maxAccel) {
    accel.y += accelGain * dt;
  } else {
    accel.y = 0;
  }

  velocity += accel;
  velocity *= 0.965f;

  velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
  velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);

  sprite.move(velocity * dt);

  sf::Vector2f sprite_pos = sprite.getPosition();

  if (sprite_pos.x <= 0) {
    sprite_pos.x = 0;
  } else if (sprite_pos.x >= 960) {
    sprite_pos.x = 960;
  }

  if (sprite_pos.y <= 0) {
    sprite_pos.y = 0;
  } else if (sprite_pos.y >= 720) {
    sprite_pos.y = 720;
  }

  sprite.setPosition(sprite_pos);
}

void Player::draw(sf::RenderWindow &window) { window.draw(sprite); }
} // namespace sp9k

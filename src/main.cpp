#include "config.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::stringstream title;
  title << "SFML | SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH << std::endl;
  std::cout << title.str() << std::endl;

  sf::RenderWindow window(sf::VideoMode(960, 720), title.str());
  window.setFramerateLimit(60);

  sf::Clock clock;

  sf::Texture tex;

  if (!tex.loadFromFile("gfx/ship1.png")) {
    std::cerr << "Cannot load texture" << std::endl;
    return 1;
  }

  sf::Vector2f accel;
  sf::Vector2f velocity;
  float maxVelocity = 500.0f;
  float maxAccel = 40.0f;
  float accelGain = 550.0f;

  sf::Sprite sprite;
  sprite.setTexture(tex);
  sprite.setOrigin(sf::Vector2f(tex.getSize().x / 2, tex.getSize().y / 2));
  sprite.setPosition(480, 360);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float dt = clock.restart().asSeconds();

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

    window.clear();
    window.draw(sprite);
    window.display();
  }

  return 0;
}

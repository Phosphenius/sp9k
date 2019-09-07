#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

namespace sp9k {
class Bullet {

public:
  sf::Vector2f pos;
  sf::Vector2f velocity;
  float radius;

  Bullet(sf::Vector2f pos, sf::Vector2f velocity);
};
} // namespace sp9k
#endif

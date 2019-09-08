#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

namespace sp9k {
class Entity {
public:
  sf::Vector2f position;
  sf::Vector2f velocity;
  float radius;
  Entity(sf::Vector2f position = {0, 0}, sf::Vector2f velocity = {0, 0},
         float radius = 0)
      : position(position), velocity(velocity), radius(radius){};
  void virtual update(float dt) = 0;
};
} // namespace sp9k
#endif

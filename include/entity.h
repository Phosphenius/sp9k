#pragma once

#include <SFML/Graphics.hpp>

namespace sp9k {
class Entity {

  bool isAlive = true;
  int hitPoints = 0;

public:
  sf::Vector2f position{0, 0};
  sf::Vector2f velocity{0, 0};
  float radius = .0f;

  Entity(int hitPoints, float radius);
  Entity(int hitPoints, float radius, sf::Vector2f position,
         sf::Vector2f velocity);
  virtual ~Entity() = default;
  void virtual update(float dt) = 0;
  bool getIsAlive() const;
  int getHitPoints() const;
  void takeDamage(unsigned int damage);
  bool collidesWith(const Entity &entity) const;
};
} // namespace sp9k

#include "entity.h"
#include <cassert>

namespace sp9k {

Entity::Entity(int hitPoints, float radius) {
  assert(hitPoints > 0);
  assert(radius > 0);
  this->hitPoints = hitPoints;
  this->radius = radius;
}

Entity::Entity(int hitPoints, float radius, sf::Vector2f position,
               sf::Vector2f velocity)
    : Entity::Entity(hitPoints, radius) {
  this->position = position;
  this->velocity = velocity;
}

bool Entity::getIsAlive() { return isAlive; }

int Entity::getHitPoints() { return hitPoints; }

void Entity::takeDamage(int damage) {
  assert(damage > 0);
  assert(isAlive);

  hitPoints -= damage;

  if (hitPoints <= 0) {
    isAlive = false;
  }
}

} // namespace sp9k

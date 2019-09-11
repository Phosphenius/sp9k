#include "enemy.h"

namespace sp9k {
Enemy::Enemy(sf::Vector2f position, sf::Vector2f velocity)
    : Entity(position, velocity, 50) {}

void Enemy::update(float dt) { position += velocity * dt; }
} // namespace sp9k

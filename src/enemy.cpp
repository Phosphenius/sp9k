#include "enemy.h"

namespace sp9k {
Enemy::Enemy(sf::Vector2f position, sf::Vector2f velocity)
    : Entity(15, 22.0f, position, velocity) {}

void Enemy::update(float dt) { position += velocity * dt; }
} // namespace sp9k

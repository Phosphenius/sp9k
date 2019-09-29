#include "bullet.h"

namespace sp9k {
Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
    : Entity(1, 10, position, velocity) {}
void Bullet::update(float dt) { position += velocity * dt; }
} // namespace sp9k

#include "bullet.h"

namespace sp9k {
Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
    : Entity(position, velocity, 10) {}
void Bullet::update(float dt) { position += velocity * dt; }
} // namespace sp9k

#include "bullet.h"

namespace sp9k {
Bullet::Bullet(sf::Vector2f pos, sf::Vector2f velocity)
    : pos(pos), velocity(velocity), radius(10) {}
} // namespace sp9k

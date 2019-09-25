#include "math.h"
#include <cmath>

namespace sp9k {
float vectorLength(sf::Vector2f vec) { return hypotf(vec.x, vec.y); }

float distance(sf::Vector2f vec1, sf::Vector2f vec2) {
  return vectorLength(vec2 - vec1);
}

} // namespace sp9k

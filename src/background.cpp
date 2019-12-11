#include "background.h"

namespace sp9k {

Background::Background(unsigned int count)
    : vertices(sf::Points, count), velocities(count) {
  for (size_t i = 0; i < velocities.size(); ++i) {
    vertices[i].position = sf::Vector2f(dist_x(generator), dist_y(generator));
    vertices[i].color = sf::Color::White;

    velocities[i] = dist_velo(generator);
  }
}

void Background::update(float dt) {
  for (std::size_t i = 0; i < velocities.size(); ++i) {
    if (vertices[i].position.y > 720) {
      resetStar(i);
    }

    vertices[i].position.y += velocities[i] * dt;
  }
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(vertices, states);
}

void Background::resetStar(std::size_t index) {
  vertices[index] = sf::Vector2f(dist_x(generator), -1);
  velocities[index] = dist_velo(generator);
}

} // namespace sp9k

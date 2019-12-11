#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <random>

namespace sp9k {

class Background : public sf::Drawable {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist_x{1, 960};
  std::uniform_int_distribution<int> dist_y{1, 720};
  std::uniform_int_distribution<int> dist_velo{20, 35};
  sf::VertexArray vertices;
  std::vector<int> velocities;

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void resetStar(std::size_t index);

public:
  Background(unsigned int count);
  void update(float dt);
};

} // namespace sp9k

#endif

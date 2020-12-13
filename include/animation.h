#pragma once

#include <SFML/Graphics.hpp>

namespace sp9k {
class Animation {
  float elapsed_t = 0.f;
  sf::Vector2f position;
  int currRow = 0;
  int currCol = 0;
  float frameTime;
  bool isActive;
  int numRows;
  int numCols;

public:
  Animation(sf::Vector2f position, unsigned int framesPerSec, int numRows = 4,
            int numCols = 4);
  void update(float dt);
  sf::Vector2f getPosition();
  bool getIsActive();
  int getCurrentRow();
  int getCurrentCol();
};
} // namespace sp9k

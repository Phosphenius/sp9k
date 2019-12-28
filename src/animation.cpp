#include "animation.h"

namespace sp9k {
Animation::Animation(sf::Vector2f position, unsigned int framesPerSec,
                     int numRows, int numCols)
    : position(position), isActive(true), numRows(numRows), numCols(numCols) {
  frameTime = 1.f / framesPerSec;
}

void Animation::update(float dt) {
  elapsed_t += dt;

  if (elapsed_t < frameTime) {
    return;
  }

  elapsed_t -= frameTime;

  currCol++;

  if (currCol >= numCols) {
    currCol = 0;

    currRow++;
    if (currRow >= numRows) {
      isActive = false;
    }
  }
}

sf::Vector2f Animation::getPosition() { return position; }

bool Animation::getIsActive() { return isActive; }

int Animation::getCurrentRow() { return currRow; }
// TODO: sf::IntRect getCurrentRect
int Animation::getCurrentCol() { return currCol; }

} // namespace sp9k

#include "config.h"
#include "game.h"
#include <iostream>
#include <sstream>

int main() {
  std::stringstream title;
  title << "SFML | SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH << std::endl;
  std::cout << title.str() << std::endl;

  sp9k::Game game(title.str());

  game.run();

  return EXIT_SUCCESS;
}

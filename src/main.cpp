#include "config.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::stringstream title;
  title << "SFML Starfighter v" << sfml_starfighter_VERSION_MAJOR << "."
        << sfml_starfighter_VERSION_MINOR << std::endl;
  std::cout << title.str() << std::endl;

  sf::RenderWindow window(sf::VideoMode(600, 400), title.str());
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.display();
  }

  return 0;
}

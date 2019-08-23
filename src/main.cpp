#include "config.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::stringstream title;
  title << "SFML | SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH << std::endl;
  std::cout << title.str() << std::endl;

  sf::RenderWindow window(sf::VideoMode(600, 400), title.str());
  window.setFramerateLimit(60);

  sf::Texture tex;

  if (!tex.loadFromFile("gfx/ship1.png")) {
      std::cerr << "Cannot load texture" << std::endl;
      return 1;
  }

  sf::Sprite sprite;
  sprite.setTexture(tex);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(sprite);
    window.display();
  }

  return 0;
}

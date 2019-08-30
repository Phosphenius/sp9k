#include "config.h"
#include "player.h" 
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::stringstream title;
  title << "SFML | SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH << std::endl;
  std::cout << title.str() << std::endl;

  sf::RenderWindow window(sf::VideoMode(960, 720), title.str());
  window.setFramerateLimit(60);

  sf::Clock clock;
  sp9k::Player player;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float dt = clock.restart().asSeconds();

    player.update(dt);

    window.clear();
    player.draw(window);
    window.display();
  }

  return 0;
}

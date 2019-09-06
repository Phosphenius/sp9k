#include "config.h"
#include "player.h"
#include "renderer.h"
#include "texture_cache.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main() {
  std::stringstream title;
  title << "SFML | SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH << std::endl;
  std::cout << title.str() << std::endl;

  sf::RenderWindow window(sf::VideoMode(960, 720), title.str());
  window.setFramerateLimit(60);
  sf::Clock clock;

  sf::Font font;

  font.loadFromFile("fonts/Xolonium-Regular.ttf");

  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(12);
  text.setFillColor(sf::Color::White);
  text.setPosition(5, 703);

  sp9k::TextureCache textureCache;
  sp9k::Renderer renderer(window, textureCache);
  sp9k::Player player(sf::Vector2f(480, 360));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float dt = clock.restart().asSeconds();

    sf::Vector2f accel;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      accel.x = -550;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      accel.x = 550;
    } else {
      accel.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        accel.y = -550;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        accel.y = 550;
    } else {
        accel.y = 0;
    }

    player.setAccel(accel * dt);

    std::stringstream fps;
    fps << "FPS: " << static_cast<int>(1.f / dt);
    text.setString(fps.str());

    player.update(dt);

    window.clear();
    renderer.renderTextureCentered("ship1", player.getPos());
    window.draw(text);
    window.display();
  }

  return EXIT_SUCCESS;
}

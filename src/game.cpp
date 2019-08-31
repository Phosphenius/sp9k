#include "game.h"

namespace sp9k {
Game::Game(std::string title)
    : window(sf::VideoMode(960, 720), title),
      player(textureManager.getTexture("ship1")) {
  window.setFramerateLimit(60);
}

void Game::update() {
  float dt = clock.restart().asSeconds();

  this->player.update(dt);
}

void Game::draw() { player.draw(window); }

void Game::run() {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    this->update();
    window.clear();
    this->draw();
    window.display();
  }
}
} // namespace sp9k

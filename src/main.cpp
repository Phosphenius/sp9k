#include "bullet.h"
#include "config.h"
#include "enemy.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture_cache.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "background.h"

int main() {
  std::stringstream title;
  title << "SFML | SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH;
  std::cout << title.str() << std::endl;

  sf::RenderWindow window(sf::VideoMode(960, 720), title.str());
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  sf::Clock clock;

  sf::Font font;

  font.loadFromFile(
      std::string(SP9k_ASSET_ROOT_PATH).append("/fonts/Xolonium-Regular.ttf"));

  sf::Text fpsText;
  fpsText.setFont(font);
  fpsText.setCharacterSize(12);
  fpsText.setFillColor(sf::Color::White);
  fpsText.setPosition(5, 703);

  sf::Text statsText("", font, 12);
  statsText.setFillColor(sf::Color::White);
  statsText.setPosition(5, 5);

  sf::Sprite healthbar;
  sp9k::NCTexture healthbar_tex;
  healthbar_tex.loadFromFile(
      std::string(SP9k_ASSET_ROOT_PATH).append("/gfx/health_bar.png"));
  healthbar.setTexture(healthbar_tex);
  healthbar.setPosition(sf::Vector2f(700, 700));

  sp9k::Game game;
  sp9k::Background background(420);
  sp9k::TextureCache textureCache;
  sp9k::Renderer renderer(window, textureCache);

#ifndef NDEBUG
  renderer.renderBounds = true;
#endif

  float elapsed_t = 0.f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float dt = clock.restart().asSeconds();
    elapsed_t += dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      game.player.accel.x = -1200;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      game.player.accel.x = 1200;
    } else {
      game.player.accel.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      game.player.accel.y = -1750;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      game.player.accel.y = 1000;
    } else {
      game.player.accel.y = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsed_t >= 0.2) {
      elapsed_t = 0.f;

      game.createBullets(game.player.position);
    }

    game.update(dt);
    background.update(dt);

    float percent_health = game.player.getHitPoints() / 250.f;

    if (percent_health < 0) {
      percent_health = 0;
    }

    healthbar.setTextureRect(sf::IntRect(0, 0, percent_health * 256, 16));

    std::stringstream fps;
    fps << "FPS: " << static_cast<int>(1.f / dt);
    fpsText.setString(fps.str());

#ifndef NDEBUG
    std::stringstream stats;
    stats << "Pos: " << static_cast<int>(game.player.position.x) << ", "
          << static_cast<int>(game.player.position.y) << std::endl
          << "Accel: " << game.player.accel.x << ", " << game.player.accel.y
          << std::endl
          << "Velocity: " << game.player.velocity.x << ", "
          << game.player.velocity.y << std::endl
          << "\nBullets fired: " << game.getStats().bulletsFired << '\n'
          << "Bullets hit: " << game.getStats().bulletsHit << '\n'
          << "Enemies killed: " << game.getStats().enemiesKilled << '\n'
          << "Enemies escaped: " << game.getStats().enemiesEscaped << '\n'
          << "Time: " << game.getStats().time << '\n'
          << "Accuracy: " << game.getStats().getAccuracy() << '\n';
    statsText.setString(stats.str());
#endif

    window.clear();
    window.draw(background);
    window.draw(healthbar);
    game.render(renderer);
    window.draw(fpsText);
#ifndef NDEBUG
    window.draw(statsText);
#endif
    window.display();
  }

  return EXIT_SUCCESS;
}

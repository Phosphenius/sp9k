#include "bullet.h"
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
  window.setVerticalSyncEnabled(true);
  sf::Clock clock;

  sf::Font font;

  font.loadFromFile("fonts/Xolonium-Regular.ttf");

  sf::Text fpsText;
  fpsText.setFont(font);
  fpsText.setCharacterSize(12);
  fpsText.setFillColor(sf::Color::White);
  fpsText.setPosition(5, 703);

  sf::Text statsText("", font, 12);
  statsText.setFillColor(sf::Color::White);
  statsText.setPosition(5, 5);

  sp9k::TextureCache textureCache;
  sp9k::Renderer renderer(window, textureCache);
  sp9k::Player player(sf::Vector2f(480, 360));

#ifndef NDEBUG
  renderer.renderBounds = true;
#endif

  std::vector<std::unique_ptr<sp9k::Bullet>> bullets;

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
      player.accel.x = -1200;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player.accel.x = 1200;
    } else {
      player.accel.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      player.accel.y = -1750;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      player.accel.y = 1000;
    } else {
      player.accel.y = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsed_t >= 0.2) {
      elapsed_t = 0.f;

      sf::Vector2f offset1(-12, -50);
      sf::Vector2f offset2(12, -50);

      bullets.push_back(std::make_unique<sp9k::Bullet>(player.pos + offset1,
                                                       sf::Vector2f(0, -600)));

      bullets.push_back(std::make_unique<sp9k::Bullet>(player.pos + offset2,
                                                       sf::Vector2f(0, -600)));
    }

    for (size_t i = 0; i < bullets.size(); ++i) {
      if (bullets[i]->pos.y <= -200) {
        bullets.erase(bullets.begin() + i);
      }
    }

    for (auto &bullet : bullets) {
      bullet->pos += bullet->velocity * dt;
    }

    std::stringstream fps;
    fps << "FPS: " << static_cast<int>(1.f / dt);
    fpsText.setString(fps.str());

#ifndef NDEBUG
    std::stringstream stats;
    stats << "Pos: " << static_cast<int>(player.pos.x) << ", "
          << static_cast<int>(player.pos.y) << std::endl
          << "Accel: " << player.accel.x << ", " << player.accel.y << std::endl
          << "Velocity: " << player.velocity.x << ", " << player.velocity.y
          << std::endl;
    statsText.setString(stats.str());
#endif

    player.update(dt);

    window.clear();
    renderer.render(player);
    renderer.render(bullets);
    window.draw(fpsText);
#ifndef NDEBUG
    window.draw(statsText);
#endif
    window.display();
  }

  return EXIT_SUCCESS;
}

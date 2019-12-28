#include "application.h"
#include <sstream>
#include <syslog.h>

namespace sp9k {
Application::Application(const std::string &title)
    : window(sf::VideoMode(960, 720), title,
             sf::Style::Titlebar | sf::Style::Close),
      textureCache("gfx"), fontCache("fonts", {"LICENSE.txt"}),
      renderer(window, textureCache, fontCache), background(420) {
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  std::string healthbarPath(SP9k_ASSET_ROOT_PATH);
  healthbarPath.append("/gfx/health_bar.png");

  if (!healthbar_tex.loadFromFile(healthbarPath)) {
    syslog(LOG_ERR, "Unable to load texture: %s", healthbarPath.c_str());
  }

  healthbar.setTexture(healthbar_tex);
  healthbar.setPosition(sf::Vector2f(700, 700));

#ifndef NDEBUG
  renderer.renderBounds = true;
#endif
}

void Application::update() {
  float dt = clock.restart().asSeconds();
  fps = static_cast<int>(1.f / dt);
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
}

void Application::render() {
  std::stringstream fpsStr;
  fpsStr << "FPS: " << fps;

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
#endif

  window.clear();
  window.draw(background);
  window.draw(healthbar);
  renderer.renderText(fpsStr.str(), sf::Vector2f(5, 703), 12);
  game.render(renderer);
#ifndef NDEBUG
  renderer.renderText(stats.str(), sf::Vector2f(5, 5), 12);
#endif
  window.display();
}

void Application::run() {

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    update();
    render();
  }
}
} // namespace sp9k

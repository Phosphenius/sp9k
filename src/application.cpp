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

#ifndef NDEBUG
  renderer.renderBounds = true;
#endif

  stateContext.pushState(stateContext.getMenuState());
}

void Application::update() {
  float dt = clock.restart().asSeconds();
  fps = static_cast<int>(1.f / dt);

  if (auto state = stateContext.getCurrentState()) {
    (*state)->update(dt);
  }

  background.update(dt);
}

void Application::render() {
  std::stringstream fpsStr;
  fpsStr << "FPS: " << fps;

  window.clear();

  window.draw(background);

  if (auto state = stateContext.getCurrentState()) {
    (*state)->render(renderer);
  }

  renderer.renderText(fpsStr.str(), sf::Vector2f(5, 703), 12);
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

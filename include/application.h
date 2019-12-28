#include "asset_cache.h"
#include "config.h"
#include "background.h"
#include "game.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>

#ifndef APPLICATION_H
#define APPLICATION_H

namespace sp9k {
class Application {
  sf::RenderWindow window;
  Game game;
  AssetCache<NCTexture> textureCache;
  AssetCache<sf::Font> fontCache;
  Renderer renderer;
  sf::Clock clock;
  sf::Font font;
  float elapsed_t = 0.f;
  sf::Sprite healthbar;
  Background background;
  int fps = 0.f;
  NCTexture healthbar_tex;

  void update();
  void render();

public:
  Application(const std::string &title);
  void run();
};
} // namespace sp9k

#endif

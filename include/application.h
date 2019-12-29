#include "asset_cache.h"
#include "background.h"
#include "config.h"
#include "game.h"
#include "in_game_state.h"
#include "renderer.h"
#include "state_context.h"
#include <SFML/Graphics.hpp>

#ifndef APPLICATION_H
#define APPLICATION_H

namespace sp9k {
class Application {
  sf::RenderWindow window;
  AssetCache<NCTexture> textureCache;
  AssetCache<sf::Font> fontCache;
  Renderer renderer;
  sf::Clock clock;
  sf::Font font;
  Background background;
  int fps = 0.f;
  InGameState inGameState;
  StateContext stateContext;

  void update();
  void render();

public:
  Application(const std::string &title);
  void run();
};
} // namespace sp9k

#endif

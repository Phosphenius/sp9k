#include "game_over_state.h"
#include "state_context.h"
#include <syslog.h>

namespace sp9k {

GameOverState::GameOverState(StateContext &context)
    : AbstractState::AbstractState(context) {}

void GameOverState::enter() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Entering GameOverState");
#endif
}

void GameOverState::leave() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Leaving GameOverState");
#endif
}

void GameOverState::pause() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Pausing GameOverState");
#endif
}

void GameOverState::resume() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Resuming GameOverState");
#endif
}

void GameOverState::update([[maybe_unused]] float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    context.popState(); // remove this state
    context.popState(); // remove current in game state
    context.pushState(context.getInGameState());
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    context.closeFlag = true;
  }
}

void GameOverState::render(Renderer renderer) {
  renderer.renderText("Game Over", sf::Vector2f(380, 200), 30);
  renderer.renderText("Press ENTER to play again or ESC to quit",
                      sf::Vector2f(265, 500), 20);
}

} // namespace sp9k

#include "menu_state.h"
#include "state_context.h"
#include <syslog.h>

namespace sp9k {

MenuState::MenuState(StateContext &context)
    : AbstractState::AbstractState(context) {}

void MenuState::enter() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Entering MenuState");
#endif
}

void MenuState::leave() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Leaving MenuState");
#endif
}

void MenuState::pause() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Pausing MenuState");
#endif
}

void MenuState::resume() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Resuming MenuState");
#endif
}

void MenuState::update([[maybe_unused]] float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    context.pushState(context.getInGameState());
  }
}

void MenuState::render(Renderer renderer) {
  renderer.renderTexture(sf::Vector2f(480, 200), "logo");
  renderer.renderText("Press ENTER to start", sf::Vector2f(380, 500), 20);
}
} // namespace sp9k

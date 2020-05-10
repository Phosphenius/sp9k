#include "abstract_state.h"
#include "state_context.h"
#include <syslog.h>

namespace sp9k {

StateContext::StateContext() {
  menuState = std::make_unique<MenuState>(*this);
  gameState = std::make_unique<InGameState>(*this);
  gameOverState = std::make_unique<GameOverState>(*this);
}

void StateContext::pushState(AbstractState *new_state) {
  if (!stack.empty()) {
    stack.top()->pause();
  }

  stack.push(new_state);
  stack.top()->enter();
}

void StateContext::popState() {
  if (!stack.empty()) {
    stack.top()->leave();
    stack.pop();
  } else {
    syslog(LOG_WARNING, "Attempting to pop on empty state stack");
  }

  if (!stack.empty()) {
    stack.top()->resume();
  }
}

std::optional<AbstractState *> StateContext::getCurrentState() {
  return stack.empty() ? std::nullopt
                       : std::optional<AbstractState *>{stack.top()};
}

AbstractState *StateContext::getMenuState() { return menuState.get(); }

AbstractState *StateContext::getInGameState() { return gameState.get(); }

AbstractState *StateContext::getGameOverState() { return gameOverState.get(); }

} // namespace sp9k

#include "abstract_state.h"
#include "state_context.h"

namespace sp9k {

StateContext::StateContext() {
  menuState = std::make_unique<MenuState>(*this);
  gameState = std::make_unique<InGameState>(*this);
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

} // namespace sp9k

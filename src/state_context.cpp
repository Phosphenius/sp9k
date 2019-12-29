#include "state_context.h"
#include "abstract_state.h"

namespace sp9k {

StateContext::StateContext(AbstractState *initial_state) {
  pushState(initial_state);
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

// FIXME: Do we really need this method?
void StateContext::changeState(AbstractState *new_state) {
  if (!stack.empty()) {
    stack.top()->leave();
  }

  stack.push(new_state);
  stack.top()->enter();
}

// FIXME: Make this return an optional reference to AbstractState instead of a
// pointer
std::optional<AbstractState *> StateContext::getCurrentState() {
  return stack.empty() ? std::nullopt
                       : std::optional<AbstractState *>{stack.top()};
}

} // namespace sp9k

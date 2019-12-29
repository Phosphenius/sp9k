#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <optional>
#include <stack>

namespace sp9k {

class AbstractState;

class StateContext {
  std::stack<AbstractState *> stack;

public:
  StateContext() = default;
  StateContext(const StateContext&) = delete;
  StateContext(AbstractState *initial_state);
  void pushState(AbstractState *new_state);
  void popState();
  void changeState(AbstractState *new_state);
  std::optional<AbstractState *> getCurrentState();
};
} // namespace sp9k

#endif

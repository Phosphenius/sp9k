#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <abstract_state.h>
#include <in_game_state.h>
#include <memory>
#include <menu_state.h>
#include <optional>
#include <stack>

namespace sp9k {

class StateContext {
  std::stack<AbstractState *> stack;
  std::unique_ptr<MenuState> menuState;
  std::unique_ptr<InGameState> gameState;

public:
  StateContext();
  StateContext(const StateContext &) = delete;
  void pushState(AbstractState *new_state);
  void popState();
  std::optional<AbstractState *> getCurrentState();
  AbstractState *getMenuState();
  AbstractState *getInGameState();
};
} // namespace sp9k

#endif

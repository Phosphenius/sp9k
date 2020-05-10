#ifndef STATE_CONTEXT_H
#define STATE_CONTEXT_H

#include "abstract_state.h"
#include "game_over_state.h"
#include "in_game_state.h"
#include "menu_state.h"
#include <memory>
#include <optional>
#include <stack>

namespace sp9k {

class StateContext {
  std::stack<AbstractState *> stack;
  std::unique_ptr<MenuState> menuState;
  std::unique_ptr<InGameState> gameState;
  std::unique_ptr<GameOverState> gameOverState;

public:
  bool closeFlag = false;
  StateContext();
  StateContext(const StateContext &) = delete;
  void pushState(AbstractState *new_state);
  void popState();
  std::optional<AbstractState *> getCurrentState();
  AbstractState *getMenuState();
  AbstractState *getInGameState();
  AbstractState *getGameOverState();
};
} // namespace sp9k

#endif

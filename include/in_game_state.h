#ifndef IN_GAME_STATE_H
#define IN_GAME_STATE_H

#include "abstract_state.h"
#include "game.h"

namespace sp9k {
class InGameState : public AbstractState {
  Game game;
  float elapsed_t = 0.f;

public:
  InGameState(StateContext &context);
  void enter();
  void leave();
  void pause();
  void resume();
  void update(float dt);
  void render(Renderer renderer);
};
} // namespace sp9k
#endif

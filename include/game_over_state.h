#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "abstract_state.h"

namespace sp9k {

class GameOverState : public AbstractState {

public:
  GameOverState(StateContext &context);
  void enter();
  void leave();
  void pause();
  void resume();
  void update(float dt);
  void render(Renderer renderer);
};

} // namespace sp9k
#endif

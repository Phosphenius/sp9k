#pragma once

#include "abstract_state.h"

namespace sp9k {
class MenuState : public AbstractState {

public:
  MenuState(StateContext &context);
  void enter();
  void leave();
  void pause();
  void resume();
  void update(float dt);
  void render(Renderer renderer);
};
} // namespace sp9k

#ifndef STATE_H
#define STATE_H

#include "renderer.h"
#include "state_context.h"

namespace sp9k {
class AbstractState {
protected:
  StateContext context;

public:
  // TODO: Maybe add processEvent(s) method
  virtual void enter() = 0;
  virtual void leave() = 0;
  virtual void pause() = 0;
  virtual void resume() = 0;
  virtual void update(float dt) = 0;
  virtual void render(Renderer renderer) = 0;
};
} // namespace sp9k
#endif

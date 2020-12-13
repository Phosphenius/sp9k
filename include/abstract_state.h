#pragma once

#include "renderer.h"

namespace sp9k {

class StateContext;

class AbstractState {

protected:
  StateContext &context;

public:
  // TODO: Maybe add processEvent(s) method
  AbstractState(StateContext &context) : context(context){};
  AbstractState(const AbstractState &) = delete;
  virtual ~AbstractState() = default;
  virtual void enter() = 0;
  virtual void leave() = 0;
  virtual void pause() = 0;
  virtual void resume() = 0;
  virtual void update(float dt) = 0;
  virtual void render(Renderer renderer) = 0;
};
} // namespace sp9k

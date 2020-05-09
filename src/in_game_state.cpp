#include "in_game_state.h"
#include <sstream>
#include <syslog.h>

namespace sp9k {

InGameState::InGameState(StateContext &context)
    : AbstractState::AbstractState(context) {}

void InGameState::enter() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Entering InGameState");
#endif
}

void InGameState::leave() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Leaving InGameState");
#endif
}

void InGameState::pause() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Pausing InGameState");
#endif
}

void InGameState::resume() {
#ifndef NDEBUG
  syslog(LOG_DEBUG, "Resuming InGameState");
#endif
}

void InGameState::update(float dt) {
  game.update(dt);
  elapsed_t += dt;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    game.player.accel.x = -1200;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    game.player.accel.x = 1200;
  } else {
    game.player.accel.x = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    game.player.accel.y = -1750;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    game.player.accel.y = 1000;
  } else {
    game.player.accel.y = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsed_t >= 0.2) {
    elapsed_t = 0.f;

    game.createBullets(game.player.position);
  }
}

void InGameState::render(Renderer renderer) {
  game.render(renderer);

#ifndef NDEBUG
  std::stringstream stats;
  stats << "Pos: " << static_cast<int>(game.player.position.x) << ", "
        << static_cast<int>(game.player.position.y) << std::endl
        << "Accel: " << game.player.accel.x << ", " << game.player.accel.y
        << std::endl
        << "Velocity: " << game.player.velocity.x << ", "
        << game.player.velocity.y << std::endl
        << "\nBullets fired: " << game.getStats().bulletsFired << '\n'
        << "Bullets hit: " << game.getStats().bulletsHit << '\n'
        << "Enemies killed: " << game.getStats().enemiesKilled << '\n'
        << "Enemies escaped: " << game.getStats().enemiesEscaped << '\n'
        << "Time: " << game.getStats().time << '\n'
        << "Accuracy: " << game.getStats().getAccuracy() << '\n';
  renderer.renderText(stats.str(), sf::Vector2f(5, 5), 12);
#endif
}
} // namespace sp9k

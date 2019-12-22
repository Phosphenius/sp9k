#ifndef STATS_H
#define STATS_H

namespace sp9k {
struct GameStats {
  int bulletsFired = 0;
  int bulletsHit = 0;
  int enemiesKilled = 0;
  int enemiesEscaped = 0;
  float time = 0;
  float getAccuracy();
};
} // namespace sp9k
#endif

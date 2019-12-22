#include "stats.h"

namespace sp9k {
float GameStats::getAccuracy() {
  if (bulletsFired == 0) {
    return 0;
  }

  return bulletsHit / static_cast<float>(bulletsFired);
}
} // namespace sp9k

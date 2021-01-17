#pragma once

#include "socket.h"

namespace sp9k {
class ShellClient {
  Socket sock;
  bool quit {false};

public:
  std::string prompt {">"};
  ShellClient(std::string socket_path);
  void run();
};
} // namespace sp9k
// namespace sp9k

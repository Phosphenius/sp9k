#pragma once

#include <cstdint>
#include <string>

#include "socket.h"

namespace sp9k {

struct ShellMessageHeader {
  std::uint16_t size;
  std::uint8_t type;
};

struct ShellMessage {
  std::string msg;
  int type;
};

void send_shell_ipc_msg(Socket &sock, const std::string &msg, int type);
ShellMessage recv_shell_ipc_msg(Socket &sock);

} // namespace sp9k

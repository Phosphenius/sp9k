#include <iostream>
#include <vector>

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "shell_ipc.h"
#include "shell_server.h"

namespace sp9k {
ShellServer::ShellServer(std::string socket_path) {
  unlink(socket_path.c_str());
  listen_socket = std::make_unique<Socket>(
      socket_path, SOCK_STREAM | SOCK_NONBLOCK, FD_CLOEXEC);

  listen_socket->bind_and_listen(1);
}

void ShellServer::update() {
  if (!data_socket) {
    data_socket = Socket::acceptConnection(*listen_socket);
  }

  ShellMessage sh_msg = recv_shell_ipc_msg(*data_socket);

  if (sh_msg.msg == "version") {
    send_shell_ipc_msg(*data_socket, VERSION, 0);
  } else {
    send_shell_ipc_msg(*data_socket, "Unknown command", 0);
  }
}
} // namespace sp9k

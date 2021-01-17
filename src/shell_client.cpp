#include <cstring>
#include <iostream>
#include <vector>

#include <readline/history.h>
#include <readline/readline.h>
#include <sys/socket.h>

#include "shell_client.h"
#include "shell_ipc.h"

namespace sp9k {
ShellClient::ShellClient(std::string socket_path)
    : sock(socket_path, SOCK_STREAM, 0) {

  sock.connectTo();

  std::cout << "connecting..\n";
}

void ShellClient::run() {
  char *rl_buffer;

  while (!quit) {
    rl_buffer = readline(prompt.c_str());

    if (!rl_buffer || !*rl_buffer) {
      continue;
    }

    add_history(rl_buffer);

    send_shell_ipc_msg(sock, rl_buffer, 4);
    ShellMessage res = recv_shell_ipc_msg(sock);

    std::cout << res.msg << std::endl;

    free(rl_buffer);
  }
}
} // namespace sp9k

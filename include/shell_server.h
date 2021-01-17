#pragma once

#include <readline/history.h>
#include <readline/readline.h>

#include "socket.h"

namespace sp9k {
class ShellServer {
    std::unique_ptr<Socket> listen_socket;
    std::unique_ptr<Socket> data_socket;
    public:
        void update();
        ShellServer(std::string socket_path);
};
} // namespace sp9k

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <sys/un.h>

namespace sp9k {
class Socket {
  int fd;
  struct sockaddr_un addr;
  std::string name;
  Socket(int fd);

public:
  int getFd() const;
  void connectTo();
  void bind_and_listen(int backlog);
  void sendData(const std::vector<std::byte> buffer);
  std::vector<std::byte> recvData(std::size_t len);
  Socket(std::string name, int flags, int setfd_flags);
  Socket(const Socket &) = delete;
  Socket &operator=(const Socket other) = delete;
  ~Socket();
  static std::unique_ptr<Socket> acceptConnection(const Socket &listen_socket);
};

} // namespace sp9k

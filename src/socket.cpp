#include <cerrno>
#include <cstring>
#include <stdexcept>

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "socket.h"

namespace sp9k {
Socket::Socket(std::string name, int flags, int setfd_flags) : name(name) {
  int ret = 0;
  fd = socket(AF_UNIX, flags, 0);

  if (fd == -1) {
    throw std::runtime_error(std::string("socket: ") + std::strerror(errno));
  }

  if (setfd_flags) {
    ret = fcntl(fd, F_SETFD, setfd_flags);

    if (ret == -1) {
      throw std::runtime_error(std::string("fcntl: ") + std::strerror(errno));
    }
  }
}

Socket::Socket(int fd) { this->fd = fd; }

void Socket::connectTo() {
  if (name.empty()) {
    throw std::logic_error(
        "'name' cannot be empty when connecting to a socket");
  }

  int ret = 0;

  std::memset(&addr, 0, sizeof(struct sockaddr_un));

  addr.sun_family = AF_UNIX;
  std::strncpy(addr.sun_path, name.c_str(), sizeof(addr.sun_path) - 1);

  ret = connect(fd, reinterpret_cast<const struct sockaddr *>(&addr),
                sizeof(struct sockaddr_un));

  if (ret == -1) {
    throw std::runtime_error(std::string("connect: ") + std::strerror(errno));
  }
}

void Socket::bind_and_listen(int backlog) {
  if (name.empty()) {
    throw std::logic_error("'name' cannot be empty when binding a socket");
  }
  int ret = 0;

  std::memset(&addr, 0, sizeof(struct sockaddr_un));

  addr.sun_family = AF_UNIX;
  std::strncpy(addr.sun_path, name.c_str(), sizeof(addr.sun_path) - 1);

  ret = bind(fd, reinterpret_cast<const struct sockaddr *>(&addr),
             sizeof(struct sockaddr_un));

  if (ret == -1) {
    throw std::runtime_error(std::string("bind: ") + std::strerror(errno));
  }

  ret = listen(fd, backlog);

  if (ret == -1) {
    throw std::runtime_error(std::string("listen: ") + std::strerror(errno));
  }
}

void Socket::sendData(const std::vector<std::byte> buffer) {
  int buf_size = buffer.size();
  int bytes_sent = 0;

  bytes_sent = send(fd, std::data(buffer), buf_size, 0);

  if (bytes_sent == -1) {
    throw std::runtime_error(std::string("send: ") + std::strerror(errno));
  }

  if (bytes_sent != buf_size) {
    // FIXME: Send remaining data
    throw std::runtime_error(
        "Could not send entire buffer with one 'send()' call");
  }
}

std::vector<std::byte> Socket::recvData(std::size_t len) {
  std::vector<std::byte> buffer(len);
  int bytes_recvd = 0;

  bytes_recvd = recv(fd, std::data(buffer), len, 0);

  if (bytes_recvd == -1) {
    throw std::runtime_error(std::string("recv: ") + std::strerror(errno));
  }

  if (bytes_recvd != static_cast<int>(len)) {
    // FIXME: Receive remaining data
    throw std::runtime_error(
        "Could not receive entire buffer with one 'recv()' call");
  }

  return buffer;
}

std::unique_ptr<Socket> Socket::acceptConnection(const Socket &listen_socket) {
  int new_fd = accept(listen_socket.getFd(), NULL, NULL);

  if (new_fd == -1) {
    throw std::runtime_error(std::string("accept: ") + std::strerror(errno));
  }

  // FIXME: Can this be done without 'new'?
  return std::unique_ptr<Socket>{new Socket(new_fd)};
}

Socket::~Socket() {
  if (fd) {
    close(fd);
  }
}

int Socket::getFd() const { return fd; }
} // namespace sp9k

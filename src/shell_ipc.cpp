#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>

#include "shell_ipc.h"

namespace sp9k {

void send_shell_ipc_msg(Socket &sock, const std::string &msg, int type) {
  int msg_size = msg.size();

  ShellMessageHeader header{};
  header.size = msg_size;
  header.type = type;

  std::vector<std::byte> buf = {std::byte(header.type),
                                std::byte(header.size << 8),
                                std::byte(header.size)};
  sock.sendData(buf);

  std::vector<std::byte> msg_buf;
  std::for_each(msg.begin(), msg.end(),
                [&msg_buf](const char &c) { msg_buf.push_back(std::byte(c)); });

  sock.sendData(msg_buf);
}

ShellMessage recv_shell_ipc_msg(Socket &sock) {
  std::vector<std::byte> header_buf;

  header_buf = sock.recvData(3);

  ShellMessageHeader header;
  header.type = std::to_integer<std::uint8_t>(header_buf[0]);
  header.size = std::to_integer<std::uint32_t>(header_buf[1] << 8) |
                std::to_integer<std::uint32_t>(header_buf[2]);

  std::vector<std::byte> raw_buf = sock.recvData(header.size);

  ShellMessage result;
  result.type = header.type;
  result.msg = reinterpret_cast<const char *>(std::data(raw_buf));

  return result;
}
} // namespace sp9k

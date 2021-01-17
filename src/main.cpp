#include <iostream>
#include <sstream>

#include <syslog.h>
#include <getopt.h>

#include "application.h"
#include "shell_server.h"
#include "shell_client.h"

int main(int argc, char *const argv[]) {
  std::stringstream title_ss;

  title_ss << "SP9k v" << VERSION;
  std::string title = title_ss.str();

  int opt = 0;
  char optchar = '?';
  bool shell_mode = false;

  while ((opt = getopt(argc, argv, "svh")) != -1) {
    optchar = static_cast<char>(opt);

    switch (optchar) {
    case 's': // shell mode
      shell_mode = true;
      break;

    case 'v':
      std::cout << title << '\n';
      return EXIT_SUCCESS;
      break;

    case 'h':
      std::cout << "show help\n";
      return EXIT_SUCCESS;
      break;

    default: /* '?' */
      std::cerr << "usage: " << argv[0] << " [-t] [-h]\n";
      return EXIT_FAILURE;
    }
  }

  if(shell_mode) {
      sp9k::ShellClient sh_client("/tmp/sp9k.sock");

      sh_client.run();
      return EXIT_SUCCESS;
  }

  sp9k::ShellServer sh_srv("/tmp/sp9k.sock");

  while(1) {
      sh_srv.update();
  }

  // open syslog
  openlog("sp9k", LOG_PID | LOG_CONS, LOG_USER);

  std::cout << title << '\n';

  syslog(LOG_INFO, "Launching %s", title.c_str());

  sp9k::Application app(title);
  app.run();

  syslog(LOG_INFO, "Terminating %s", title.c_str());

  closelog();
  return EXIT_SUCCESS;
}

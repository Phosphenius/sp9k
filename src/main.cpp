#include "application.h"
#include "config.h"
#include <iostream>
#include <sstream>
#include <syslog.h>

int main() {
  // open syslog
  openlog("sp9k", LOG_PID | LOG_CONS, LOG_USER);

  std::stringstream title;
  title << "SP9k v" << SP9k_VERSION_MAJOR << "." << SP9k_VERSION_MINOR
        << "." << SP9k_VERSION_PATCH;
  std::cout << title.str() << std::endl;

  syslog(LOG_INFO, "Launching %s", title.str().c_str());

  sp9k::Application app(title.str());
  app.run();

  closelog();
  return EXIT_SUCCESS;
}

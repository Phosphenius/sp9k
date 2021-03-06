#include "application.h"
#include <iostream>
#include <sstream>
#include <syslog.h>

int main() {
  // open syslog
  openlog("sp9k", LOG_PID | LOG_CONS, LOG_USER);

  std::stringstream title_ss;
  title_ss << "SP9k " << VERSION;

  std::string title = title_ss.str();

  std::cout << title << '\n';

  syslog(LOG_INFO, "Launching %s", title.c_str());

  sp9k::Application app(title);
  app.run();

  syslog(LOG_INFO, "Terminating %s", title.c_str());

  closelog();
  return EXIT_SUCCESS;
}

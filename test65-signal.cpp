#include <csignal>
#include <iostream>
#include <unistd.h>
 
//  volatile std::sig_atomic_t gSignalStatus;
  int gSignalStatus;
  static volatile bool g_quit;
 
void signal_handler(int signal)
{
  gSignalStatus = signal;
  std::cout << ">>>SignalValue: " << gSignalStatus << '\n';
  g_quit = true;
  //exit(1);
}
 
int main()
{
  // Install a signal handler
  std::signal(SIGINT, signal_handler);
 
  std::cout << "SignalValue: " << gSignalStatus << '\n';
  std::cout << "waiting signal " << SIGINT << '\n';
  //std::raise(SIGINT);
  while( !g_quit )
  {
    std::cout << "SignalValue: " << gSignalStatus << '\n';
//    sleep(1);
  }

  return 0;
}

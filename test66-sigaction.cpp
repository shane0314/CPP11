/* examples
http://lazarenko.me/signal-handler/
http://man7.org/linux/man-pages/man2/mprotect.2.html
*/
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void handler(int sig)
{
    std::cout << "Got signal. sig: " << sig << std::endl;
    exit(EXIT_FAILURE);
}

int main( int argc, char *argv[] )
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset( &sa.sa_mask );
    sa.sa_handler = &handler;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    while(true) {
        std::cout << "doing something useful" << std::endl;
        sleep(1);
    }
}

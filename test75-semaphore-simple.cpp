#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

sem_t sem;

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void
handler(int sig)
{
    write(STDOUT_FILENO, "sem_post() from handler\n", 24);
    if (sem_post(&sem) == -1) {
        write(STDERR_FILENO, "sem_post() failed\n", 18);
        _exit(EXIT_FAILURE);
    }
}

int
main(int argc, char *argv[])
{
   int s;

   if (sem_init(&sem, 0, 0) == -1)
        handle_error("sem_init");

   /* Establish SIGALRM handler; set alarm timer using argv[1] */

   /* Calculate relative interval as current time plus
       number of seconds given argv[2] */

    if (sem_post(&sem) == -1) {
        write(STDERR_FILENO, "sem_post() failed\n", 18);
        _exit(EXIT_FAILURE);
    }
    else {
        printf("sem_post() success\n");
    }

    if (sem_post(&sem) == -1) {
        write(STDERR_FILENO, "sem_post() failed 2\n", 18);
        _exit(EXIT_FAILURE);
    }
    else {
        printf("sem_post() success 2\n");
    }

   s = sem_wait(&sem);
   /* Check what happened */
   if (s == -1) {
        perror("sem_wait");
    } else
        printf("sem_wait() succeeded\n");

   s = sem_wait(&sem);
   /* Check what happened */
   if (s == -1) {
        perror("sem_wait 2");
    } else
        printf("sem_wait() succeeded 2\n");

   s = sem_wait(&sem);
   /* Check what happened */
   if (s == -1) {
        perror("sem_wait 3");
    } else
        printf("sem_wait() succeeded 3\n");

   exit((s == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
